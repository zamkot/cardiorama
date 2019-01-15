#include <iostream>
#include <armadillo>
#include <cmath>


using namespace std;
using namespace arma;

int main()
{
	// loading data
	vec data;
	//data.load("data3.csv");
	bool ok = data.load("data3.csv");
	
	if(ok == false)
		cout << "problem with loading data" << endl;
	else
		cout << "data loaded" << endl;
	
	double tmp = 0;
	vec tk(size(data));
	double sum_RR = 0;
	int count = 0;
	
	// findings RRs longer than 7s
	for(uword i = 0; i < data.n_elem; i++)
	{
		sum_RR = sum_RR + data[i];
		tk(i) = data[i] + tmp;
		tmp = tk[i];
		
		if(i > 2 && i < data.n_elem)
		{
			if (tk[i] - tk[i-1] > 7)
				count = count + 1;
		}
	}
	cout << "\nRRs longer than 7s = " << count << endl;

	vec F = regspace<vec>(0.001, 0.001, 0.4);
	
	vec sum01(size(F));
	vec sum02(size(F));
	vec tau(size(F));

	for(int i = 0; i < F.n_elem ; i++)
	{	
		sum01 = sum(sin(4*datum::pi*F[i]*tk));
		sum02 = sum(cos(4*datum::pi*F[i]*tk));
		tau(i) = (1/(4*datum::pi*F[i]))*(atan(sum01/sum02)).eval()(0,0);
		
	}
	/* ERASE L8R -- JUST CHECKING
	cout << sum1 << endl;
	cout << sum(tau) << endl; */
	
	vec sum11(size(F));
	vec sum12(size(F));
	vec sqrt11;
	vec sqrt12;
	vec P(size(F));
	for(int i = 0; i < F.n_elem ; i++)
	{	
		sum11 = sum(data%(cos(2*datum::pi*F[i]*(tk-tau[i]))));
		sqrt11 = square(sum11);
		sum11 = sqrt11/(sum(square(cos(2*datum::pi*F[i]*(tk-tau[i])))));
		
		sum12 = sum(data%(sin(2*datum::pi*F[i]*(tk-tau[i]))));
		sqrt12 = square(sum12);
		sum12 = sqrt12/(sum(square(sin(2*datum::pi*F[i]*(tk-tau[i])))));
		P(i) = (0.5*(sum11+sum12)).eval()(0,0);
		
	}
	
	/* ERASE L8R
	cout << P << endl;
	cout << sum11 << endl;
	cout << sum12 << endl; */

	vec VLF;
	VLF << 0.003 << endr << 0.04;
	vec LF;
	LF << 0.04 << endr << 0.15;
	vec HF;
	HF << 0.15 << endr << 0.4;

	// finding indexes corresponding to the VLF, LF and HF bands
	
	vec iVLF = zeros<vec>(size(F));
	iVLF.elem( find((F >= VLF[0]) && (F <= VLF[1]))).ones();
	vec iLF = zeros<vec>(size(F));
	iLF.elem( find((F >= LF[0]) && (F <= LF[1]))).ones();
	vec iHF = zeros<vec>(size(F));
	iHF.elem( find((F >= HF[0]) && (F <= HF[1]))).ones();
	
	// calculating areas withing the bands
	double aVLF, aLF, aHF;
	aVLF = as_scalar(trapz(F(find(iVLF)), P(find(iVLF))));
	aLF = as_scalar(trapz(F(find(iLF)), P(find(iLF))));
	aHF = as_scalar(trapz(F(find(iHF)), P(find(iHF))));

	double aTotal = as_scalar(aVLF + aLF + aHF);

	
	double pVLF = (aVLF/aTotal)*100;
	double pLF = (aLF/aTotal)*100;
	double pHF = (aHF/aTotal)*100;
	
	// calculating LF/HF ratio
	double LHHF = aLF/aHF;
	
	// mean of RR intervals in ms
	double mean_RR  = mean(data) * 1000;
	
	// standard deviation of RR intervals
	double std_RR = stddev(data);

	// RMSSD
	double sum_rms = 0;
	for (uword i = 0; i < (data.n_elem-1); i++)
		sum_rms = sum_rms + pow((data[i+1] - data[i]),2);

	double rms_RR = sqrt((pow((data.n_elem-1), -1))*sum_rms);
	
	
	// number of RR intervals that differ more than 50 ms
	int sum_NN50 = 0;
	int f;
	for (uword i = 0; i < (data.n_elem - 1); i++)
	{
		if ((data[i+1] - data[i]) > 0.05)
			f = 1;
		else
			f = 0;
	    
		sum_NN50 = sum_NN50 + f;
	}
	
	// percentage of RR intervals that differ more than 50 ms
	double pNN50 = double(sum_NN50)/(double(data.n_elem-1))*100;

	// SDANN and SDANN index
	vec mean_sdann(round(tk.max()/300));
	vec std_sdanni(round(tk.max()/300));
	uword it = 1, k = 0;

	vec x_sdann(size(data));

	for (uword i = 0; i < data.n_elem; i++)
	{
		x_sdann(i) = data[i];
		if (tk[i] >= 300*it)
		{	mean_sdann(it) = mean(x_sdann(span(k,i-1)));
			std_sdanni(it) = stddev(x_sdann(span(k,i-1)));
			it++;
			k = i;
		}
		
	}

	double sdann = stddev(mean_sdann);
	double sdanni = mean(std_sdanni);

	// SDSD
	vec x_sdsd(size(data));
	for ( uword i = 0; i < (data.n_elem - 1); i++)
		x_sdsd(i) = data[i+1] - data[i];

	double sdsd = stddev(x_sdsd);

	// Checking...
	cout << "mean_RR = " << mean_RR << endl << "std_RR = " << std_RR << endl;
	cout << "rms_RR = " << rms_RR << endl << "sum_NN50 = " << sum_NN50 << endl;
	cout << "pNN50 = " << pNN50 << endl << "sdann = " << sdann << endl;
	cout << "sdanni = " << sdanni << endl << "sdsd = " << sdsd << endl;

	
	return 0;
}
