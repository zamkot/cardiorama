#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "EcgBaselineModuleBase.hpp"

EcgBaselineModule::EcgBaselineModule(Physionet& ioModule): ioModule{ ioModule }       // konstruktor
{
}

void EcgBaselineModule::configure(const std::string& inputFileName, BaselineMethod baselineMethod)
{
    if(this->inputFileName != inputFileName) {
        this->inputFileName = inputFileName;
        ioModule.readFile(inputFileName);
        invalidateResults();
    }
    if(this->baselineMethod != baselineMethod) {
        this->baselineMethod = baselineMethod;
        invalidateResults();
    }

    isConfigured = true;
}

void EcgBaselineModule::runEcgBaseline()
{
    if(!isConfigured) {
        std::cout << " Error" << std::endl;
    }

    auto ioModuleInput = ioModule.getDataFrame().dataFrame; 
    EcgBaselineModule baseline = EcgBaseineModule(std::vector<double>(ioModuleInput.begin(), ioModuleInput.end()));

    if(BaselineMethod == butterworth) results = baseline.processButter(baseline);
    if(BaselineMethod == wavelet) results = baseline.processWavelet(baseline);

    validateResults();
}

EcgBaselineData EcgBaselineModule::getResults() {
    
    if (!resultsValid()) {
        runEcgBaseline();
    }

    return results;
}



// method for IIR Butterworth filter
std::vector<double> filt (const std::vector<double>& sos, EcgBaselineData signal)
{
    int length = signal.samples.size();
    std::vector <double> y(length, 0);

    double v1 = 0.0;
    double v2 = 0.0;

    for (int i = 0; i < length; ++i)
    {
        // y[n] =  b0*x[n] + b1*x[n-1] + b2*x[n-2] - a1*y[n-1] - a2*y[n-2]
        double v0 = signal.samples[i] - sos[4] * v1 - sos[5] * v2;
        y[i] = sos[0] * v0 + sos[1] * v1 + sos[2] * v2;
        v2 = v1;
        v1 = v0;
    }
    return y;
}

std::vector<double> filtfilt (const std::vector<double>& sos, EcgBaselineData signal)
{
    int l1 = signal.samples.size();
    std::vector<double> y = filt(sos, signal.samples);

    int l2 = y.size();
    std::vector<double> y2(l2);
    for (int i = 0; i<l2; ++i)
    {
        y2[i] = y[l2-i-1];
    }

    y2 = filt(sos, y2);
    for (int i = 0; i<l2; ++i)
    {
        y[i] = y2[l2-i-1];
    }

    return y;

}

std::vector<double> processButter(EcgBaselineData signal) {

    int filterOrder = 2; // filter order
    double overallGain = 1.0; // filter gain
    int fs = 360; // all signals from physionet have fs = 360 Hz
    double fc = 0.5; // cut off frequency
    double Wc = double((fc/fs)/2); // normalized cut off frequency

    // sos matrix from matlab prototype

    std::vector<double> sos;
    sos.push_back(1.00000);
    sos.push_back(-2.0000);
    sos.push_back(1.0000);
    sos.push_back(1.0000);
    sos.push_back(-1.9969);
    sos.push_back(0.9969);

    return filtfilt(sos, signal.samples);
}

// method for Wavelet decomposition
std::vector<double> processWavelet(EcgBaselineData signal) {
        std::cout << " walcze z biblioteka zewnetrzna!" << std::endl;
}


