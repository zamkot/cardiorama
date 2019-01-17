#include <Hrv1Module.hpp>
#include <RPeaksModule.hpp>
#include <iosream>
#include <cmath>
#include <armadillo>

struct TimeDomainVar{
    double TP;
    double pVLF;
    double pLF;
    double pHF;
    double LHHF;
    double meanRR;
    double stdRR;
    double rmsRR;
    int sumNN50;
    double pNN50;
    double sdann;
    double sdanni;
    double sdsd;

};


Hrv1Module::Hrv1Module(RPeaksModuleBase& RPeaksModule):RPeaksModule{RpeaksModule}{

    RPeaksModule.attach(this);
}


void Hrv1Module::runHrv1(){

    using namespace std;
    using namespace arma;

    auto rPeaksOut = RPeaksModule.getResults();
    vec rPeaksIdx(rPeaksOut.rpeaks);
    
    // EDIT fs -> does the user pick frequency?    
    double fs = 320;
    vec data = createRRvector(rPeaksIdx, fs);

    vec tk = adjustRR(data);
    
    // EDIT F -> does the user pick range? for sure const 0.4  
	vec F = regspace<vec>(0.001, 0.001, 0.4);
    vec P = periodogramLombScargle(tk, data, F);
	TimeDomainVar timeDomainResults = timeDomain(F, data, tk);

    vec VLF;
	VLF << 0.003 << endr << 0.04;
	vec LF;
	LF << 0.04 << endr << 0.15;
	vec HF;
	HF << 0.15 << endr << 0.4;

    results.F = std::vector<double>(F.begin(), F.end());
    results.P = std::vector<double>(P.begin(), P.end());
    results.VLF = std::vector<double>(VLF.begin(), VLF.end());
    results.LF = std::vector<double>(LF.begin(), LF.end());
    results.HF = std::vector<double>(HF.begin(), HF.end());
    results.timeDomainResults = timeDomainResults

    //results = {F, P, VLF, LF, HF, timeDomainResults};
    validateResults();

}

Hrv1Data Hrv1Module::getResults(){
    if(!resultsValid()){
        runHrv1();
    }
    
    return results;
}

/*----------FUNCTIONS----------*/

// function from Hrv2Module
Hrv1Module::arma::vec createRRVector(arma::vec& rPeaksIndex, double samplingFrequency){
   
   using namespace arma;
   double deltaT = 1/samplingFrequency;
   vec rPeaks = rPeaksIndex*deltaT;
   vec vector1 = rpeaks.rows(1,rpeaks_index.n_elem-1);
   vec vector2 = rpeaks.rows(0,rpeaks_index.n_elem-2);
   vec rr = vector1-vector2; 
   return rr; 
}

Hrv1Module::arma::vec adjustRR(arma::vec& data){

    using namespace arma;

    double tmp = 0;
	vec tk(size(data));
	double sumRR = 0;
	int count = 0;
	
	// findings RRs longer than 7s
	for(uword i = 0; i < data.n_elem; i++)
	{
		sumRR = sumRR + data[i];
		tk(i) = data[i] + tmp;
		tmp = tk[i];
		
		if(i > 2 && i < data.n_elem){

			if (tk[i] - tk[i-1] > 7)
				count++;
		}
	}

    return tk;
}


Hrv1Module::arma::vec periodogramLombScargle(arma::vec& tk, arma::vec& data, arma::vec& F){

    using namespace arma;

	vec sum01(size(F));
	vec sum02(size(F));
	vec tau(size(F));

	for(int i = 0; i < F.n_elem ; i++)
	{	
		sum01 = sum(sin(4*datum::pi*F[i]*tk));
		sum02 = sum(cos(4*datum::pi*F[i]*tk));
		tau(i) = (1/(4*datum::pi*F[i]))*(atan(sum01/sum02)).eval()(0,0);
	}

	vec sum11(size(F));
	vec sum12(size(F));
	vec P(size(F));

	for(int i = 0; i < F.n_elem ; i++)
	{	
		sum11 = sum(data%(cos(2*datum::pi*F[i]*(tk-tau[i]))));
		sum11 = square(sum11)/(sum(square(cos(2*datum::pi*F[i]*(tk-tau[i])))));
		
		sum12 = sum(data%(sin(2*datum::pi*F[i]*(tk-tau[i]))));
		sum12 = square(sum12)/(sum(square(sin(2*datum::pi*F[i]*(tk-tau[i])))));

		P(i) = (0.5*(sum11+sum12)).eval()(0,0);
	}

    return P;
}

Hrv1Module::TimeDomainVar timeDomain(arma::vec& F, arma::vec& data, arma::vec& tk){
     
    using namespace arma;
    TimeDomainVar timeResults;

	// finding indexes corresponding to the VLF, LF and HF bands
	vec iVLF = zeros<vec>(size(F));
	iVLF.elem( find((F >= 0.003) && (F < 0.04))).ones();
	vec iLF = zeros<vec>(size(F));
	iLF.elem( find((F >= 0.04) && (F < 0.15))).ones();
	vec iHF = zeros<vec>(size(F));
	iHF.elem( find((F >= 0.15) && (F <= 0.4))).ones();
	
	// calculating areas withing the bands
	double aVLF, aLF, aHF;
	aVLF = as_scalar(trapz(F(find(iVLF)), P(find(iVLF))));
	aLF = as_scalar(trapz(F(find(iLF)), P(find(iLF))));
	aHF = as_scalar(trapz(F(find(iHF)), P(find(iHF))));

	timeResults.TP = as_scalar(aVLF + aLF + aHF);
	
	timeResults.pVLF = (aVLF/aTotal)*100;
	timeResults.pLF = (aLF/aTotal)*100;
	timeResults.pHF = (aHF/aTotal)*100;


	// calculating LF/HF ratio
	timeResults.LHHF = aLF/aHF;

	// mean of RR intervals in ms
	timeResults.meanRR  = mean(data) * 1000;
	
	// standard deviation of RR intervals
	timeResults.stdRR = stddev(data);

	// RMSSD
	double sumRms = 0;
	for (uword i = 0; i < (data.n_elem-1); i++)
		sumRms = sumRms + pow((data[i+1] - data[i]),2);

	timeResults.rmsRR = sqrt((pow((data.n_elem-1), -1))*sumRms);
	
	// number of RR intervals that differ more than 50 ms
	timeResults.sumNN50 = 0;
	int addIdx;
	for (uword i = 0; i < (data.n_elem - 1); i++)
	{
		if ((data[i+1] - data[i]) > 0.05)
			addIdx = 1;
		else
			addIdx = 0;
	    
		sumNN50 = sumNN50 + addIdx;
	}
	
	// percentage of RR intervals that differ more than 50 ms
	timeResults.pNN50 = double(sumNN50)/(double(data.n_elem-1))*100;

	// SDANN and SDANN index
	vec meanSdann(round(tk.max()/300));
	vec stdSdanni(round(tk.max()/300));
	uword it = 1, k = 0;

	vec signalSdann(size(data));

	for (uword i = 0; i < data.n_elem; i++)
	{
		signalSdann(i) = data[i];
		if (tk[i] >= 300*it){	
            meanSdann(it) = mean(signalSdann(span(k,i-1)));
			stdSdanni(it) = stddev(signalSdann(span(k,i-1)));
			it++;
			k = i;
		}	
	}
	timeResults.sdann = stddev(meanSdann);
	timeResults.sdanni = mean(stdSdanni);

	// SDSD
	vec signalSdsd(size(data));
	for ( uword i = 0; i < (data.n_elem - 1); i++)
		signalSdsd(i) = data[i+1] - data[i];

	timeResults.sdsd = stddev(signalSdsd);

    return timeResults;
}


