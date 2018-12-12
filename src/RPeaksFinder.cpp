#include <RPeaksFinder.h>
#include <fftw3.h>
#include <algorithm>
#include <list>

const double R_peaksModule::SAFETY_COEFFICIENT = 0.8;
const unsigned short R_peaksModule::MAX_BPM = 220;
const double R_peaksModule::THRESHOLD_DIVISOR = 20;
const unsigned int R_peaksModule::PT_LP_M = 9;
const unsigned int R_peaksModule::PT_HP_M = 56;
const unsigned int R_peaksModule::PT_MW_N = 58;

R_peaksModule::R_peaksModule(const std::vector<double> & signal, double freq): ecgSignal(signal) {
    this->filteredSignal = signal;
    this->frequency = freq;
}

//======================= HILBERT ====================================


void R_peaksModule::fft(const std::vector<double> & x, VectorComplexDouble & result) {
    unsigned long N = x.size();
    fftw_complex * out = new fftw_complex[N];
    fftw_complex * in = new fftw_complex[N];
    fftw_plan plan_forward;

    for(int i = 0; i < N; i++)
    {
        in[i][0] = x[i];
        in[i][1] = 0.0;
    }
    plan_forward = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan_forward);
    for(int i = 0; i < N; i++) result[i] = ComplexDouble(out[i][0], out[i][1]);
    delete [] out;
    delete [] in;
    fftw_destroy_plan(plan_forward);
}

void R_peaksModule::ifft(const VectorComplexDouble & x, VectorComplexDouble & result) {
    int N = x.size();
    fftw_plan plan_backward;
    fftw_complex * in = new fftw_complex[N];
    fftw_complex * out = new fftw_complex[N];
    for(int i = 0; i < N; i++)
    {
        in[i][0] = x[i].real();
        in[i][1] = x[i].imag();
    }
    plan_backward = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(plan_backward);

    for(int i = 0; i < N; i++) result[i] = ComplexDouble(out[i][0]/double(N), out[i][1]/double(N));

    delete [] in;
    delete [] out;
    fftw_destroy_plan(plan_backward);
}

void R_peaksModule::fftHilbert(const std::vector<double> & x, std::vector<double> & result) {
    int N = x.size();
    VectorComplexDouble xdft(N);
    fft(x, xdft);
    std::vector<double> h(N);

    if(N % 2 == 0)
    {
        h[0] = 1;
        h[N/2] = 1;
        for(int i = 1; i < N/2; i++) h[i] = 2;
    }
    else
    {
        h[0] = 1;
        for(int i = 1; i < (N + 1)/2; i++) h[i] = 2;
    }
    VectorComplexDouble xdfth(N);
    for(int i = 0; i < N; i++) xdfth[i] = xdft[i] * h[i];

    VectorComplexDouble y(N);
    ifft(xdfth, y);
    for(int i = 0; i < N; i++) result[i] = y[i].imag();
}

void R_peaksModule::fftHilbertWindowed(const std::vector<double> & x, std::vector<double> & result, double window_length, double window_overlap) {
    unsigned int s_window_length = static_cast<unsigned int>(window_length * this->frequency);
    unsigned int s_window_overlap = static_cast<unsigned int>(window_overlap * this->frequency);

    if(s_window_length % 2) s_window_length--;

    unsigned int s_span = s_window_length - 2 * s_window_overlap;
    unsigned int offset = s_window_length/2;

    unsigned int N = x.size();
    unsigned int Ni;
    std::vector<double> xi;
    std::vector<double> ihbi;
    bool more = true;

    //first iteration
    if(offset + s_window_length/2 - 1 >= N) //last iteration
    {
        xi.clear();
        for(unsigned int i = offset - s_window_length/2 ; i < N ; i++) xi.push_back(x[i]);
        Ni = xi.size();

        ihbi.clear();
        ihbi.resize(Ni);
        fftHilbert(xi, ihbi);
        for(unsigned int i = 0; i < Ni; i++) result.push_back(ihbi[i]);
        more = false;
    }
    else
    {
        xi.clear();
        for(unsigned int i = offset - s_window_length/2 ; i < offset + s_window_length/2 ; i++) xi.push_back(x[i]);
        Ni = xi.size();

        ihbi.clear();
        ihbi.resize(Ni);
        fftHilbert(xi, ihbi);
        for(unsigned int i = 0; i < Ni-s_window_overlap; i++) result.push_back(ihbi[i]);
        offset += s_span;
    }
    while(more)
    {
        if(offset + s_window_length/2 - 1 >= N) //last iteration
        {
            xi.clear();
            for(unsigned int i = offset - s_window_length/2 ; i < N ; i++) xi.push_back(x[i]);
            Ni = xi.size();

            ihbi.clear();
            ihbi.resize(Ni);
            fftHilbert(xi, ihbi);
            for(unsigned int i = s_window_overlap;i < Ni; i++) result.push_back(ihbi[i]);
            more = false;
        }
        else
        {
            xi.clear();
            for(unsigned int i = offset - s_window_length/2 ; i < offset + s_window_length/2 ; i++) xi.push_back(x[i]);
            Ni = xi.size();

            ihbi.clear();
            ihbi.resize(Ni);
            fftHilbert(xi, ihbi);
            for(unsigned int i = s_window_overlap; i < Ni - s_window_overlap; i++) result.push_back(ihbi[i]);
            offset += s_span;
        }
    }
}

void R_peaksModule::setHilbertRPeaks(const VectorPairDoubleUnsignedInt & peaks, double dt) {
    double threshold = peaks[0].first;
    unsigned int cutoff = 0;
    while(cutoff < peaks.size() && peaks[cutoff].first >= threshold/(this->THRESHOLD_DIVISOR)) cutoff++;

    VectorPairDoubleUnsignedInt peaks_cut(cutoff);
    for(unsigned int i=0;i<cutoff;i++) peaks_cut[i] = peaks[i];

    double max_bps = this->MAX_BPM/60;
    double max_r_interval = 1/max_bps;
    int max_scope = (int)floor(this->SAFETY_COEFFICIENT*(max_r_interval/dt));

    stable_sort(peaks_cut.begin(), peaks_cut.end(), PeaksCutSorter(max_scope));

    //VectorUnsignedInt indexAlias;
    std::vector<double> & indexAlias = this->indexVector;
    indexAlias.clear();
    unsigned int fst = 0;
    unsigned int prevPeak;
    unsigned int possiblePeak;

    //first R peak
    if(this->filteredSignal.at(peaks_cut[fst].second) > 0) {
        indexAlias.push_back(peaks_cut[fst].second);
        R_peaksIter iter = this->ecgSignal.begin();
        for(unsigned int j = 0; j < peaks_cut[fst].second; j++) iter++;
        //QLOG_INFO() << "roznica" << iter - this->ecgSignal.begin();
        //QLOG_INFO() << "indeks" << peaks_cut[fst].second;
        this->itVect.push_back(iter);
        prevPeak = peaks_cut[fst].second;
    }
    else {
        possiblePeak = peaks_cut[fst].second;
        fst++;
        while(fst<cutoff && (int)peaks_cut[fst].second - (int)possiblePeak <= max_scope) {
            if(this->filteredSignal.at(peaks_cut[fst].second) > 0) {
                possiblePeak = peaks_cut[fst].second;
                break;
            }
            fst++;
        }
        if(fst<cutoff) fst--;

        indexAlias.push_back(possiblePeak);
        R_peaksIter iter = this->ecgSignal.begin();
        for(unsigned int j = 0; j < possiblePeak; j++) iter++;
        this->itVect.push_back(iter);
        //QLOG_INFO() << "roznica" << iter - this->ecgSignal.begin();
        //QLOG_INFO() << "indeks" << possiblePeak;
        prevPeak = possiblePeak;
    }
    //rest of R Peaks
    for(unsigned int i = fst + 1; i < cutoff; i++) {
        if((int)peaks_cut[i].second - (int)prevPeak > max_scope) {
            if(this->filteredSignal.at(peaks_cut[i].second) > 0) {
                indexAlias.push_back(peaks_cut[i].second);
                R_peaksIter iter = this->ecgSignal.begin();
                for(unsigned int j = 0; j < peaks_cut[i].second; j++) iter++;
                this->itVect.push_back(iter);
                //QLOG_INFO() << "roznica" << iter - this->ecgSignal.begin();
                //QLOG_INFO() << "indeks" << peaks_cut[i].second;
                prevPeak = peaks_cut[i].second;
            }
            else {
                possiblePeak = peaks_cut[i].second;
                i++;
                while(i < cutoff && (int)peaks_cut[i].second - (int)possiblePeak <= max_scope) {
                    if(filteredSignal.at(peaks_cut[i].second) > 0) {
                        possiblePeak = peaks_cut[i].second;
                        break;
                    }
                    i++;
                }
                if(i<cutoff) i--;

                indexAlias.push_back(possiblePeak);
                R_peaksIter iter = this->ecgSignal.begin();
                for(unsigned int j = 0; j < possiblePeak; j++) iter++;
                this->itVect.push_back(iter);
                //QLOG_INFO() << "roznica" << iter - this->ecgSignal.begin();
                //QLOG_INFO() << "indeks" << possiblePeak;
                prevPeak = possiblePeak;
            }
        }
    }
}

void R_peaksModule::hilbert(void) {
    this->indexVector.clear();
    this->itVect.clear();
    unsigned int N = this->filteredSignal.size();
    double dt = 1.0/this->frequency;

    std::vector<double> dsignal(N);
    for(unsigned int i = 1; i < N; i++) dsignal[i] = (this->filteredSignal[i] - this->filteredSignal[i-1])/dt;

    std::vector<double> hdsignal;

    fftHilbertWindowed(dsignal, hdsignal, 200.0, 30.0);

    VectorPairDoubleUnsignedInt diff(N);

    for(unsigned int i = 0; i < N; i++) {
        diff[i].first = hdsignal[i] * hdsignal[i] - dsignal[i] * dsignal[i];
        diff[i].second = i;
    }

    sort(diff.begin(), diff.end(), DiffSorter());

    setHilbertRPeaks(diff, dt);
}


//======================= PanTompkins =================================


double R_peaksModule::PTLowPassFilter(double data, bool reset = false)
{
    static double y1 = 0, y2 = 0, x[(2*PT_LP_M+1)*2]; //(2m+1)*2
    static int n = 2*PT_LP_M;
    if (reset)
    {
        y1 = 0; y2 = 0; n = 2*PT_LP_M;
        for(unsigned int i = 0; i < (2*PT_LP_M+1)*2; i++)
            x[i] = 0;
    }

    double y0;
    x[n] = x[n + 2*PT_LP_M+1] = data;
    y0 = (2*y1) - y2 + x[n] - (2*x[n + PT_LP_M]) + x[n + 2*PT_LP_M];
    y2 = y1;
    y1 = y0;
    y0 /= (PT_LP_M*PT_LP_M);
    //y0 /= 32;
    if(--n < 0)
        n = 2*PT_LP_M;
    return(y0);
}

double R_peaksModule::PTHighPassFilter(double data, bool reset = false)
{
    static double y1 = 0, x[2*(PT_HP_M+1)];
    static int n = PT_HP_M;
    if (reset)
    {
        y1 = 0; n = PT_HP_M;
        for(unsigned int i=0;i<2*(PT_HP_M+1);i++) x[i] = 0;
    }

    double y0;
    x[n] = x[n + PT_HP_M+1] = data;
    y0 = y1 + x[n] - x[n + PT_HP_M];
    y1 = y0;
    if(--n < 0)
        n = PT_HP_M;
    return(x[n + (int) ceil((double) (PT_HP_M-1)/2)] - (y0/PT_HP_M));
}

double R_peaksModule::PTDerivative (double data, bool reset = false)
{
    double y;
    static double x_derv[6];
    if (reset)
    {
        for (int i=0; i<6; i++) x_derv[i]=0;
    }

    /*y = 1/8 (2x( nT) + x( nT - T) - x( nT - 3T) - 2x( nT -4T))*/
    y = (data*2) + x_derv[3] - x_derv[1] - ( x_derv[0]*2);
    y /= 8;
    //y = (data*3) + 2*x_derv[5] + x_derv[4] - x_derv[2] - (x_derv[1]*2)-( x_derv[0]*3);

    for (int i = 0; i < 3; i++)
        x_derv[i] = x_derv[i + 1];
    x_derv[3] = data;
    return y;
}

double R_peaksModule::PTSquaringFunction(double data)
{
    return data*data;
}

double R_peaksModule::PTMovingWindowIntegral(double data, bool reset = false)
{
      static double x[PT_MW_N], sum = 0;
      static int ptr = 0;
      if (reset)
      {
          ptr = 0;
          sum = 0;
          for(unsigned int i=0; i<PT_MW_N; i++) x[i]=0;
      }

      double y;
      sum -= x[ptr];
      sum += data;
      x[ptr] = data;
      if(++ptr == PT_MW_N)
            ptr = 0;

      y = sum/PT_MW_N;
      return y;
}

PairDoubleUnsignedInt R_peaksModule::Maximum(int begin, int end, std::vector<double> & values) {
    double maximum = values[begin];
    int location = begin;

    for(int i = begin; i < end; i++) {
        if(values[i] > maximum) {
            maximum = values[i];
            location = i;
        }
    }
    return PairDoubleUnsignedInt(maximum, location);
}

PairDoubleUnsignedInt R_peaksModule::Peak200MS(int & index, std::vector<double>  & signal) {
    int t200 = 0.2 * this->frequency;
    int preBlankCnt = 0;
    int indexPeak = 0;

    double aPeak, tempPeak, newPeak;
    tempPeak = 0.0;
    while(index < signal.size()) {
        aPeak = signal[index];
        if(aPeak > 0 && !preBlankCnt) {
            tempPeak = aPeak;
            preBlankCnt = t200;
            indexPeak = index;
        }
        if(aPeak > tempPeak) {
            tempPeak = aPeak;
            preBlankCnt = t200;
            indexPeak = index;
        }
        else if(--preBlankCnt == 0) {
            newPeak = tempPeak;
            break;
        }

        index++;
    }
    if(index == signal.size()) {
        newPeak = tempPeak;
        indexPeak = signal.size()-2;
    }
    else index = indexPeak+t200;
    return PairDoubleUnsignedInt(newPeak, indexPeak);
}

int R_peaksModule::QRSCheck(PairDoubleUnsignedInt rpCandidate, PairDoubleUnsignedInt rpLast, double threshold, std::vector<double> & slope) {
    double intervalTime = (rpCandidate.second - rpLast.second)/this->frequency;
    if(intervalTime < 0.36) {
        int beginLast = rpLast.second - 0.36 * this->frequency;
        if(beginLast < 0) beginLast = 0;
        int beginCandidate = rpLast.second;//rpCandidate.second-0.36*samplingFreq;
        if (beginCandidate < 0 ) beginCandidate = 0;
        double slopeLast = Maximum(beginLast, rpLast.second, slope).first;
        double slopeCandidate = Maximum(beginCandidate, rpCandidate.second, slope).first;
        if(slopeCandidate*2 < slopeLast) return 0;
    }
    if(rpCandidate.first > threshold) return 1;
    else return 0;
}

void R_peaksModule::PanTompkinsDo(std::vector<double> & signal, VectorPairDoubleUnsignedInt & result) {
    std::list<int> rr1, rr2;
    int RRAVERAGE1, RRAVERAGE2, RRLOWLIMIT, RRHIGHLIMIT, RRMISSEDLIMIT;
    //wartość oczekiwana signal peak, ogólnie peak, wartość oczekiwana noise peak, próg większy, próg mniejszy
    double SPK, PEAK, NPK, THRESHOLD1, THRESHOLD2;
    std::vector<double> PTSignal, slopePTSignal, slopeRawSignal;

    bool mwindow = false;
    int N = this->filteredSignal.size();
    PTSignal.clear();
    slopePTSignal.clear();
    slopeRawSignal.clear();

    PTSignal.push_back(signal[0]);
    for (int i = 1; i < N; i++) {
        slopePTSignal.push_back(signal[i]-signal[i-1]);
        slopeRawSignal.push_back(this->filteredSignal[i]-this->filteredSignal[i-1]);
    }

    //INICJALIZACJA -----------------
    std::vector<PairDoubleUnsignedInt> noisePeaks;
    rr1.clear();
    rr2.clear();
    for(int i = 0; i < 8; i++) {
        rr1.push_back((int) (this->frequency)); //1000ms
        rr2.push_back((int) (this->frequency)); //1000ms
        PairDoubleUnsignedInt tPeak(0,0);
        if(!mwindow) tPeak = Maximum(i*this->frequency+1,(i+1)*this->frequency, signal);
        else tPeak = Maximum(i*this->frequency+1,(i+1)*this->frequency, slopePTSignal);
        result.push_back(tPeak);
    }
    int listMean = 0;
    for(std::list<int>::iterator it=rr1.begin() ; it != rr1.end(); it++) listMean+= (*it);

    listMean /= 8;
    RRAVERAGE1 = listMean;
    RRAVERAGE2 = RRAVERAGE1;
    RRLOWLIMIT = (int) (0.92*RRAVERAGE2);
    RRHIGHLIMIT = (int) (1.16*RRAVERAGE2);
    RRMISSEDLIMIT = (int) (1.66*RRAVERAGE2);

    PEAK = 0;
    for(int i = 0; i < 8; i++) {
        PEAK += result[i].first;
    }
    PEAK *= 0.125;
    SPK = PEAK;//maksymalna Mean(0,N,signal);
    NPK = 0;	//przykladowo
    THRESHOLD1 = NPK+0.25*(SPK-NPK);
    THRESHOLD2 = 0.5*THRESHOLD1;

    int index = 0, interval;
    double threshold = THRESHOLD1;
    bool qrs = false;
    PairDoubleUnsignedInt rpCandidate(signal[0],0), rpSearchBack (0,0), rpLast(signal[0],0);

    result.clear();
    while(index < N-1) {

        if(!mwindow) rpCandidate = Peak200MS(index, signal);
        else rpCandidate = Peak200MS(index, slopePTSignal);

        if(QRSCheck(rpCandidate, rpLast, threshold, slopePTSignal) != 0) {
            qrs = true;
            interval = (rpCandidate.second - rpLast.second)/this->frequency;
            result.push_back(rpCandidate);
            rpLast = rpCandidate;
            double qrsMean = 0.0;
            int licz = 0;
            for (unsigned int i = result.size()-1; i > 0 && i > result.size()-9  ; i--) {
                qrsMean += result[i].first;
                licz++;
            }
            if(licz > 0) SPK = qrsMean/licz;
            if(licz == 8) SPK = 0.125 * rpCandidate.first  +0.875 * SPK;
            THRESHOLD1 = NPK + 0.25 *(SPK - NPK);
            THRESHOLD2 = 0.5 * THRESHOLD1;

            //indexSearchBack = index;
            rpSearchBack = PairDoubleUnsignedInt(0, index);
        }
        else {
            noisePeaks.push_back(rpCandidate);
            rpLast = rpCandidate;
            double noiseMean = 0.0; int licz2 = 0;
            for(unsigned int i = noisePeaks.size()-1; i > 0 && i > noisePeaks.size()-9  ; i--) {
                noiseMean += noisePeaks[i].first;
                licz2++;
            }
            if(licz2 > 0) NPK = noiseMean/licz2;
            if(licz2 == 8) NPK = 0.125*rpCandidate.first+0.875*NPK;
            THRESHOLD1 = NPK+0.25*(SPK-NPK);
            THRESHOLD2 = 0.5*THRESHOLD1;

            if(rpCandidate.first > rpSearchBack.first) rpSearchBack = rpCandidate;
            if(index - rpSearchBack.second > RRMISSEDLIMIT) {
                if(rpSearchBack.first > THRESHOLD2) {
                    qrs = true;
                    interval = (rpCandidate.second-rpLast.second)/this->frequency;
                    result.push_back(rpCandidate);
                    rpLast = rpCandidate;
                    double qrsMean = 0.0; int licz = 0;
                    for(unsigned int i = result.size()-1; i > 0 && i > result.size()-9  ; i--)
                    {
                        qrsMean += result[i].first;
                        licz++;
                    }
                    if(licz > 0) SPK = qrsMean/licz;
                    if(licz == 8) SPK = 0.25*rpCandidate.first+0.75*SPK;
                    THRESHOLD1 = NPK+0.25*(SPK-NPK);
                    THRESHOLD2 = 0.5*THRESHOLD1;

                    rpSearchBack = PairDoubleUnsignedInt (0,index);
                }
            }
        }

        if(qrs) {
            qrs = false;
            //poprawienie czasow
            rr1.pop_front();
            rr1.push_back(interval);

            listMean = 0;
            for (std::list<int>::iterator it=rr1.begin() ; it != rr1.end(); it++) listMean+= (*it);
            listMean /= 8;
            RRAVERAGE1 = listMean;
            if(interval > RRLOWLIMIT && interval << RRHIGHLIMIT) { //RRAVERAGE2
                rr2.pop_front();
                rr2.push_back(interval);
                listMean = 0;
                for(std::list<int>::iterator it=rr2.begin() ; it != rr2.end(); it++) listMean+= (*it);
                listMean /= 8;
                RRAVERAGE2 = listMean;
                RRLOWLIMIT = (int) (0.92*RRAVERAGE2);
                RRHIGHLIMIT = (int) (1.16*RRAVERAGE2);
                RRMISSEDLIMIT = (int) (1.66*RRAVERAGE2);

            }
            threshold = THRESHOLD1;
            /*regularny, nieregularny rytm*/
            if(RRAVERAGE1 == RRAVERAGE2) {
                threshold = THRESHOLD1;
            }
            else {
                threshold = 0.5*THRESHOLD1;
            }

        }
    }
}

void R_peaksModule::PanTompkinsSetPeaks(VectorPairDoubleUnsignedInt & filter, VectorPairDoubleUnsignedInt & movingWindow) {

    std::vector<double> & indexAlias = this->indexVector;

    int eps = 10;
    int i1 = 0, i2 = 0;
    int s1Size, s2Size;
    VectorPairDoubleUnsignedInt signal1, signal2;
    int temp1, temp2, temp21;

    if(filter.size() < movingWindow.size()) {
        signal1 = filter;
        signal2 = movingWindow;

    }
    else {
        signal1 = movingWindow;
        signal2 = filter;

    }
    s1Size = signal1.size();
    s2Size = signal2.size();

    temp1 = signal1[i1].second;
    temp2 = signal2[i2].second;
    temp21 = signal2[i2+1].second;

    while(i1 < s1Size) {
        temp1 = signal1[i1].second;
        while((temp21 <= temp1 + eps) && (i2 < s2Size  -2)) {
            i2++;
            temp21 = signal2[i2+1].second;
        }
        temp2 = signal2[i2].second;
        if(abs(temp1 - temp2) <= eps) {
            int index = (temp1 + temp2)/2;
            indexAlias.push_back(index);
            R_peaksIter iter = this->ecgSignal.begin();
            for(unsigned int j = 0; j < index; j++) iter++;
            this->itVect.push_back(iter);
            //QLOG_INFO() << "roznica" << iter - this->ecgSignal.begin();
            //QLOG_INFO() << "indeks" << index;
        }

        i1++;
        while(i1 < s1Size-2 && signal1[i1].second < temp2) {
            i1++;
        }
    }

    temp1 = signal1[s1Size-1].second;
    temp2 = signal2[s2Size-1].second;
    if (abs(temp1 - temp2) <= eps) {
        int index = (temp1 + temp2)/2;
        indexAlias.push_back(index);
        R_peaksIter iter = this->ecgSignal.begin();
        for(unsigned int j = 0; j < index; j++) iter++;
        this->itVect.push_back(iter);
        //QLOG_INFO() << "roznica" << iter - this->ecgSignal.begin();
        //QLOG_INFO() << "indeks" << index;
    }
}

void R_peaksModule::panTompkins(void) {
    this->indexVector.clear();
    this->itVect.clear();
    int N = this->filteredSignal.size();
    double dt = 1/this->frequency;

    std::vector<double> time(N);
    for(int i=0;i<N;i++) time[i] = i*dt;

    std::vector<double> block_signal(N);
    double PtSign = 1.0;
    double absMax = 0.0;
    double indexMax;
    for(int i = 0; i < 2 * this->frequency; i++) {
        double temp = abs(this->filteredSignal[i]);
        if (temp > absMax) {
            absMax = temp;
            indexMax = i;
        }
    }
    if (this->filteredSignal[indexMax] >= 0) PtSign = 1.0;
    else PtSign = -1.0;
    //

    for(int i = 0; i < N; i++) {
        this->filteredSignal[i] = PtSign * this->filteredSignal[i];
        block_signal[i] = this->filteredSignal[i];
    }

    std::vector<double> fsignal(N);
    std::vector<double> mwisignal(N);

    for(int i = 0; i < N; i++) {
        bool reset = false;
        if(i == 0) reset = true;

        block_signal[i] = PTLowPassFilter(block_signal[i], reset);
        block_signal[i] = PTHighPassFilter(block_signal[i], reset);
        fsignal[i] = block_signal[i];
        block_signal[i] = PTDerivative(block_signal[i], reset);
        block_signal[i] = PTSquaringFunction(block_signal[i]);
        block_signal[i] = PTMovingWindowIntegral(block_signal[i], reset);
        mwisignal[i] = block_signal[i];
    }

    //algorytm Pan Tompkins - wyszukiwanie peaków

    VectorPairDoubleUnsignedInt rPeaksBPF;
    PanTompkinsDo(fsignal, rPeaksBPF);

    VectorPairDoubleUnsignedInt rPeaksMWI;
    PanTompkinsDo(mwisignal, rPeaksMWI);
    //VectorPairDoubleUnsignedInt rPeaksBandPassFilter = rPeaksMovingWindowIntegration;
    //obliczenie delay:
    int max1 = Maximum(rPeaksBPF[1].second - 50, rPeaksBPF[1].second + 50, this->filteredSignal).second; //ok
    int dtFilter = rPeaksBPF[1].second - max1;

    if (dtFilter < 30) dtFilter = 35;

    for(unsigned int i = 1; i<rPeaksBPF.size()-1; i++) {
        max1 = Maximum(rPeaksBPF[i].second - 2 * dtFilter, rPeaksBPF[i].second, this->filteredSignal).second;
        rPeaksBPF[i].second = max1;
    }

    for(unsigned int i = 1; i< rPeaksMWI.size() - 1; i++) {
        max1 = Maximum(rPeaksMWI[i].second - PT_MW_N - dtFilter, rPeaksMWI[i].second, this->filteredSignal).second;
        rPeaksMWI[i].second = max1;
    }

    //this->rPeaksSamples = PanTompkinsGetPeaks(rPeaksBPF, rPeaksMWI);
    PanTompkinsSetPeaks(rPeaksBPF, rPeaksMWI);
}

const R_peaksIterVector & R_peaksModule::getPeaksIter(void) {
    return this->itVect;
}

const std::vector<double> & R_peaksModule::getPeaksIndex(void) {
    return this->indexVector;
}

const R_peaksIter R_peaksModule::ecgBegin(void) {
    R_peaksIter ecgBeg = this->ecgSignal.begin();
    return ecgBeg;
}
