#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "wavelet2s.h"
#include "EcgBaselineModule.hpp"

EcgBaselineModule::EcgBaselineModule(IOModuleBase& ioModule) : ioModule{ioModule}
{
    ioModule.attach(this);

    // Default config
    config.algorithm = EcgBaselineConfig::Algorithm::BUTTERWORTH;
}

void EcgBaselineModule::configure(EcgBaselineConfig newConfig) {
  
    if (config.algorithm != newConfig.algorithm) {
        config.algorithm = newConfig.algorithm;
        invalidateResults();
    }

    isConfigured = true;
}

void EcgBaselineModule::runEcgBaseline() {
    if (!isConfigured) {
        std::cout << " Error" << std::endl;
    }

//    vector prepared for test
    EcgBaselineData ecgBaselineData;
    std::vector<double> signal = ioModule.getRawSignal();

    ecgBaselineData.samples = signal;

    if (config.algorithm == EcgBaselineConfig::BUTTERWORTH) results.samples = processButter(ecgBaselineData.samples);
    if (config.algorithm == EcgBaselineConfig::WAVELET) results.samples = processWavelet(ecgBaselineData.samples);

    validateResults();

}

EcgBaselineData EcgBaselineModule::getResults() {

    if (!resultsValid()) {
        runEcgBaseline();
    }

    return results;
}


// method for IIR Butterworth filter
std::vector<double> EcgBaselineModule::filt(std::vector<double> &sos, std::vector<double> &signal) {
    int length = signal.size();
    std::vector<double> y(length, 0);

    double v1 = 0.0;
    double v2 = 0.0;

    for (int i = 0; i < length; ++i) {
        double v0 = signal[i] - sos[4] * v1 - sos[5] * v2;
        y[i] = sos[0] * v0 + sos[1] * v1 + sos[2] * v2;
        v2 = v1;
        v1 = v0;
    }
    return y;
}

std::vector<double> EcgBaselineModule::filtfilt(std::vector<double> &sos, std::vector<double> &signal) {
    int l1 = signal.size();
    std::vector<double> y = filt(sos, signal);

    int l2 = y.size();
    std::vector<double> y2(l2);
    for (int i = 0; i < l2; ++i) {
        y2[i] = y[l2 - i - 1];
    }

    y2 = filt(sos, y2);
    for (int i = 0; i < l2; ++i) {
        y[i] = y2[l2 - i - 1];
    }

    return y;

}

std::vector<double> EcgBaselineModule::processButter(std::vector<double> &signal) {
    int filterOrder = 2; // filter order
    int fs = 360; // all signals from physionet have fs = 360 Hz
    double fc = 0.5; // cut off frequency
    double Wc = double((fc / fs) / 2); // normalized cut off frequency

    // sos matrix from matlab prototype

    std::vector<double> sos;
    sos.push_back(1.00000);
    sos.push_back(-2.0000);
    sos.push_back(1.0000);
    sos.push_back(1.0000);
    sos.push_back(-1.9969);
    sos.push_back(0.9969);

    return filtfilt(sos, signal);
}

// method for Wavelet decomposition
std::vector<double> EcgBaselineModule::processWavelet(std::vector<double> &signal) {
    int l = 9; // decomposition level
    std::string nm = "db4"; // name Wavelet family
    std::vector<double> dwt_output; 
    std::vector<double> flag;
    std::vector<int> lenght1;

    dwt(signal, l, nm, dwt_output, flag, lenght1);

   int from = lenght1[0];
   int to = dwt_output.size()-lenght1[0];

    for (int i = from; i < to; i++) {
        dwt_output[i] = 0.0;
    }

    std::vector<double> idwt_output;
    idwt(dwt_output, flag, nm, idwt_output, lenght1);

    for (int i = 0; i < idwt_output.size(); i++)
    {
        signal[i] = signal[i] - idwt_output[i];
    }

    return signal;
}
