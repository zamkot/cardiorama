#include <RPeaksModule.hpp>
#include <iostream>
#include <math.h>
#include <cmath>
#define pi 3.14159265358979323846

// R peak Module
RPeaksModule::RPeaksModule(EcgBaselineModuleBase& ecgBaselineModule): ecgBaselineModule{ecgBaselineModule}
{
}

// Configuration 
void RPeaksModule::configure(RPeaksConfig rPeaksConfig)
{
    this->rPeaksConfig = rPeaksConfig;

    // Taking output results from EcgBaeline 
    auto ecgBaselineResults = ecgBaselineModule.getResults();

    // rawSignal was used when the EcgBaseline was not done 
    rawSignal = ecgBaselineResults.samples;

    // filtered signal from EcgBaseline module 
    filteredSignal = ecgBaselineResults.samples; 

    // invalid results NOTIFY from ModulBase.cpp
    invalidateResults(); 
}

void RPeaksModule::runRPeaks()
{
    // Deteriming algorithm to use 
    switch (rPeaksConfig.algorithm) {
        case RPeaksConfig::Algorithm::PAN_TOMPKINS:
            PanTompkins();
            break;
        case RPeaksConfig::Algorithm::HILBERT:
//            hilbert();
            std::cout << "Hilbert algorithm not implemented yet. Bye." << std::endl;
            exit(114);
        default:
            PanTompkins();
    }
    
    // valid results
    validateResults();  
}

// Run finding R peaks and get the result as std vector int
RPeaksData RPeaksModule::getResults() {
    if(!resultsValid()) {
        runRPeaks();
        results.rpeaks = armadilloVecToStdVec(RPeakVec);
        return results;
    }
    return results;
}


void RPeaksModule::PanTompkins()
{
    // signal from ECG_Baseline (for tests it was RAW from 100.csv and others)
    filteredSignal = rawSignal;

    // Highpass (Cutoff = 5, Moving window lenght = 24) - from literature and tests)  but it could be also 8 Hz 
    filterHighpass(5,30);

    // Lowpass  (Cutoff = 15, Moving window lenght = 24) - from literature and tests) but it could be also 20 Hz      
    filterLowpass(15,30);

    // Differentiate - favoring QRS      
    differentiate();    

    // Squaring - favoring even more QRS        
    square();

    // Integration (window length = 19) - from tests (different then matlab 13) - get just one wave                   
    integrate(19);              

    arma::vec peaks = findPeaks(filteredSignal);  //  Candidates for R Peak
    int N = int(peaks.size());  // peaks size 

    arma::vec peakValue(N); // peak value for each sample
    for (int i=0; i<N; i++)
        peakValue[i] = filteredSignal(int(peaks[i])); // peak value for each sample

    // Maxiumum value of peak
    double maxValue = double(peakValue[0]);

    // Maximum number
    int maxNumber = int(peaks[0]);

    // Number of samples 
    int samplesNumber = int(floor(0.2 * rPeaksConfig.samplingFrequency)); // 200ms (r-R(j-1))>0.2*fs

    // Rpeak vector
    arma::vec Rpeaks(N);
    int counter = 0;

    // Adaptive thersholding of finding r peaks greater then 1
    if (N > 1)
    {
        for (int i=1; i<N; i++)
        {
            // If current peak value is greater then current local maximum 
            //                            and 
            // if the distance between them is lower then 200 ms then please do:
            if((peakValue[i] > maxValue) && ((peaks[i] - maxNumber) < samplesNumber)) 
            {
                maxValue = peakValue[i]; // set the maximum  
                maxNumber = int(peaks[i]); // set the max distance 
            }
            // If the distance is greater then 200ms WE'VE GOT IT
            // lets take it as the R Peak YEAH!
            // but let's keep looking around 
            else if ((peaks[i] - maxNumber) >= samplesNumber)
            {
                Rpeaks[counter++] = maxNumber;
                maxValue = peakValue[i];
                maxNumber = int(peaks[i]);
            }
            // Ok if it's the last one (R) let's count it and do a vector 
            if ((i == (N-1)) && (Rpeaks[counter-1] != maxNumber))
            {
                Rpeaks[counter++] = maxNumber; // mmm nice vector 
            }
        }
        // Now we have to make subvetor with only the size of found R 
        RPeakVec = Rpeaks.subvec(0,counter-1);
    }
    else
    {
        RPeakVec = peaks; // If we didn't get any peak lets show it
    }
    RPeakVec -= 9; // delay caused from our filter, BAD FILTER ;/  
}


// Useful modules and functions

void RPeaksModule::filterHighpass(double fc, int M)
{
    // init
    fc = fc / rPeaksConfig.samplingFrequency / 2; // cut-off frequency
    int N = 2 * M + 1; 

    // coefficients of filter
    arma::vec h(N);
    for (int i=-M; i<0; i++)
        h[i+M] = -2*pi*fc*arma::sinc(2*pi*fc*i); // -sin(2*pi*fs*t) / pi*t for t!=0 (from left side)

    h[M] = 1-2*fc; // 1-2*fc for t=0

    for (int i=1; i<=M; i++)
        h[i+M] = -2*pi*fc*arma::sinc(2*pi*fc*i); // -sin(2*pi*fs*t) / pi*t for t!=0 (from right side)

    // Kaiser window with beta = 9
    arma::vec window(N);
    for (int i=0; i<N; i++) {
        double bb = besseli0(9);
        window[i] = besseli0(9*sqrt(4.0*i*(N-1-i))/(N-1))/bb;
    }

    // Convolution
    arma::vec hw(N);
    hw = h % window;

    // Filtered signal
    filteredSignal = arma::conv(filteredSignal, hw, "same");
}

void RPeaksModule::filterLowpass(double fc, int M)
{
    // init
    fc = fc / rPeaksConfig.samplingFrequency / 2; // cut-off frequency  
    int N = 2 * M + 1;  

    // coefficients of filter
    arma::vec h(N);
    for (int i=-M; i<0; i++)
        h[i+M] = 2*pi*fc*arma::sinc(2*pi*fc*i); // sin(2*pi*fs*t) / pi*t for t!=0 (from left side)

    h[M] = 2*fc; // 2*fc for t=0

    for (int i=1; i<=M; i++)
        h[i+M] = 2*pi*fc*arma::sinc(2*pi*fc*i); // sin(2*pi*fs*t) / pi*t for t!=0 (from right side)

    // Kaiser window with beta = 9
    arma::vec window(N);
    for (int i=0; i<N; i++) {
        double bb = besseli0(9);
        window[i] = besseli0(9 * sqrt(4.0 * i * (N - 1 - i)) / (N - 1)) / bb;
    }

    // Convolution
    arma::vec hw(N);
    hw = h % window;

    // Filtered signal
    filteredSignal = arma::conv(filteredSignal, hw, "same");
}

void RPeaksModule::differentiate()
{
    // init
    int N = int(filteredSignal.size());
    arma::vec signalDiff(N);
    signalDiff[0] = 0;
    signalDiff[1] = 0;
    signalDiff[N-2] = 0;
    signalDiff[N-1] = 0;

    // Differentiate from formula
    for (int i=2; i<N-2; i++)
        signalDiff[i] = (-filteredSignal(i-2) - 2*filteredSignal(i-1) + 2*filteredSignal(i+1) + filteredSignal(i+2)) / 8;
    filteredSignal = signalDiff;

}

void RPeaksModule::square()
{
    // I don't have to explain it or do i?
    filteredSignal = filteredSignal % filteredSignal;
}

void RPeaksModule::integrate(int W)
{
    //init
    int N = int(filteredSignal.size());
    arma::vec  signal = arma::zeros<arma::vec>(N);

    // Integration with use of moving window and according to the formula
    for (int i=W-1; i<N; i++)
    {
        for (int j=i-W+1; j<=i; j++)
        {
            signal[i] = signal[i] + filteredSignal[j];
        }
        signal[i] = signal[i] / W;
    }
    filteredSignal = signal;
}

double RPeaksModule::besseli0( double x )
{
    double y=1.0,s=1.0,x2=x*x,n=1.0;
    while (s > y*1.0e-9)
    {
        s *= x2/4.0/(n*n);
        y += s;
        n += 1;
    }
    return y;
}

// Finding R Peaks with use of threshold (simple)
arma::vec RPeaksModule::findPeaks(arma::vec signal)
{
    int N = int(signal.size()); // size of the signal 
    arma::vec peaks(N); // vector for peaks 
    double threshold = signal.max() / 10;   // when greater - misleading points of QRS in some fluctuations of ECG line
    int counter = 0;

    if (N > 1) // If there at least one sample 
    {
        for (int i=1; i<N-1; i++) // length after thresholding
        {
            // if samples from left and right are lower from the detected sample
            // and sample exceed threshold WE MIGHT HAVE A PEAK YEAH!  
            if ((signal(i) > signal(i-1)) && (signal(i) > signal(i+1)) && (signal(i) > threshold)) 
                                                                                                   
            {
                peaks[counter++] = i; // count this bastards
            }
        }
        peaks = peaks.subvec(0,counter-1); // bring them to subvector of signal 
    }
    return peaks; 
}

// Conversion from armadillo vector to standard vector
std::vector<double> RPeaksModule::armadilloVecToStdVec(const arma::vec& invec) {
    std::vector<double> stdvec;
    for(auto element: invec) {
        stdvec.push_back((double)element);
    }

    return stdvec;
}