#include <iostream>
#include <numeric>
#include <stdio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <armadillo>
#include <iterator>
#include <typeinfo>

#include <HeartClassModule.hpp>

#define log(message) std::cout << typeid(*this).name() << ": " << message << std::endl
# define PRINT(X) std::cout<<X<<std::endl;

// ----------------------------- CONSTRUCTOR --------------------------------

HeartClassModule::HeartClassModule(
    EcgBaselineModuleBase& ecgBaselineModule, 
    RPeaksModuleBase& rPeaksModule) 
    :  ecgBaselineModule{ecgBaselineModule}, 
       rPeaksModule{rPeaksModule} {

    rPeaksModule.attach(this);
    ecgBaselineModule.attach(this);

    std::cout<<"Hello, heart constructor here!"<<std::endl;
}

// -------------------------- DESCRIPTOR METHODS ----------------------------

std::vector<double> HeartClassModule::maxValue(std::vector<std::vector <double>> &signal) {

    std::vector<double> maxes;
    maxes.resize(signal.size());

    std::transform(std::cbegin(signal), std::cend(signal), std::begin(maxes), [](const std::vector<double> &sig)
    {
        return *(std::max_element(std::cbegin(sig), std::cend(sig)));
    });

    return maxes;
}

std::vector<double> HeartClassModule::minValue(std::vector<std::vector <double>> &signal) {

    std::vector<double> mins;
    mins.resize(signal.size());
    
    std::transform(std::cbegin(signal),std::cend(signal),std::begin(mins), [](const std::vector<double> &sig)
    {
        return *(std::min_element(std::cbegin(sig), std::cend(sig)));
    });

    return mins;
}

std::vector<double> HeartClassModule::ptsAboveTh(std::vector<std::vector<double>> &signal) {

    std::vector<double> ths;
    ths.resize(signal.size());
    auto maxes = maxValue(signal);

    std::transform(std::cbegin(maxes), std::cend(maxes), std::begin(ths), [](const double& max){
        return 0.7*max;
    });

    std::vector <double> ptsAbove;
    ptsAbove.reserve(signal.size());

    std::transform(std::cbegin(signal),std::cend(signal),std::begin(ths),std::back_inserter(ptsAbove), [](const std::vector<double> &sig, const double &th)
    {
        std::vector<double> ptsA;
        std::copy_if(std::cbegin(sig),std::cend(sig),std::back_inserter(ptsA),[&](const double& value)
        {
            return value > th;
        });

        return ptsA.size();
    } );
    return ptsAbove;
}

std::vector <double> HeartClassModule::qrsAuc(std::vector<std::vector<double>> &signal) {

    std::vector<double> integrals;
    integrals.resize(signal.size());

    std::transform(std::cbegin(signal), std::cend(signal), std::begin(integrals), [](const std::vector<double> &sig)
    {
        return std::accumulate(std::cbegin(sig), std::cend(sig), 0);
    });
    return integrals;
}

std::vector <double> HeartClassModule::qrsPosRatio(std::vector<std::vector<double>> &signal) {

    std::vector<double> posRatios;
    posRatios.resize(signal.size());

    std::transform(std::cbegin(signal), std::cend(signal), std::begin(posRatios), [](const std::vector<double> &sig)
    {
        auto integral = std::accumulate(std::cbegin(sig), std::cend(sig), 0);
        auto posIntegral = std::accumulate(std::cbegin(sig), std::cend(sig), 0, [](double acc,double val)
        {
            return val > 0 ? acc+val : acc;
        });
        float ratio = static_cast<float>(posIntegral)/integral;

        return ratio;
    });
    return posRatios;
}

std::vector <double> HeartClassModule::qrsNegRatio(std::vector<std::vector<double>> &signal){

    std::vector<double> negRatios;
    negRatios.resize(signal.size());

    std::transform(std::cbegin(signal), std::cend(signal), std::begin(negRatios), [](const std::vector<double> &sig)
    {
        auto integral = std::accumulate(std::cbegin(sig), std::cend(sig), 0);
        auto negIntegral = std::accumulate(std::cbegin(sig), std::cend(sig), 0, [](double acc,double val)
        {
            return val<0 ? acc+val : acc;
        });
        float ratio = static_cast<float>(negIntegral)/integral;

        return ratio;
    });
    return negRatios;
}

std::vector <double> HeartClassModule::aucComparsion(std::vector<std::vector<double>> &signal) {

    auto posRatios = qrsPosRatio(signal);
    auto negRatios = qrsNegRatio(signal);
    std::vector<double> comparsion(posRatios.size());

    std::transform(std::cbegin(posRatios), std::cend(posRatios),std::cbegin(negRatios), std::begin(comparsion), 
        [](const double& posRatio, const int& negRatio){
        return posRatio >= negRatio ? 1 : 0;
    });

     std::vector<double> comparsion1(comparsion.begin(), comparsion.end());

     return comparsion1;
}

std::vector<double> HeartClassModule::kurtosis(std::vector<std::vector<double>> &signal) {
    std::vector<double> kurtosisVec(signal.size());
 
    std::transform(std::cbegin(signal), std::cend(signal), std::begin(kurtosisVec),
    [](const std::vector<double>& sig){
        const auto N = sig.size();
        double avg = std::accumulate(std::cbegin(sig), std::cend(sig), 0.0) / N;
        double variance = std::accumulate(std::cbegin(sig), std::cend(sig), 0.0,
        [&](double acc, double val){
            return acc + (val - avg)*(val - avg);
        }) / (N - 1); // Wolfram liczy srednia z N
        double kurtosis = std::accumulate(cbegin(sig), std::cend(sig), 0.0,
        [&](double acc, double val){
            return acc + std::pow(val - avg, 4);
        });
        kurtosis = kurtosis /( N * std::pow(variance, 2)) - 3; // stdDev^4 = variance^2
        return kurtosis;
    });
 
    return kurtosisVec;
}

std::vector<double> HeartClassModule::skewness(std::vector<std::vector<double>> &signal) {
    std::vector <double> skewnessVec;
    double sum,n;
    double var,skewness, S,avg;
    for (int i = 0; i < signal.size(); i++){
        n = signal[i].size();
        sum = accumulate(signal[i].begin(), signal[i].end(), 0);   
        avg = (double)sum/n; 
         
        for (int j = 0; j < n ; j++) {
            var += (signal[i][j] - avg)*(signal[i][j] - avg);
        }
        var = (double)(var)/(n - 1);  
        S = (double)sqrt(var);
        for (int j = 0; j < n; j++){
           skewness += (signal[i][j] - avg)*(signal[i][j] - avg)*(signal[i][j] - avg);
        }
	    skewness = skewness/(n * S * S * S);
        skewnessVec.push_back(skewness);
    }
    return skewnessVec;
}

std::vector<std::vector<double>> HeartClassModule::prepareSignal(std::vector<double>& rawSignal, std::vector<int>& rPeaks, int& samplingFrequency) {

    std::vector<std::vector<double>> prepared(rPeaks.size());

    for (int i=0; i<rPeaks.size(); i++){
        auto start = std::max(0, rPeaks[i]-this->windowSize);
        auto end = std::min(static_cast<int>(rawSignal.size()), rPeaks[i] +windowSize);
        std::vector<double> slice(&rawSignal[start], &rawSignal[end]);
        prepared[i] = slice;
    }
    return prepared;
}

cardioFeatures HeartClassModule::calculateFeatures(std::vector<std::vector<double>>& signal) {
    cardioFeatures signalFeatures;
    signalFeatures.maxValue = maxValue(signal);
    signalFeatures.minValue = minValue(signal);
    signalFeatures.ptsAboveTh = ptsAboveTh(signal);
    signalFeatures.qrsAuc = qrsAuc(signal);
    signalFeatures.qrsPosRatio = qrsPosRatio(signal);
    signalFeatures.qrsNegRatio = qrsNegRatio(signal);
    signalFeatures.aucComparsion = aucComparsion(signal);
    signalFeatures.kurtosis = kurtosis(signal);
    signalFeatures.skewness = skewness(signal);

    return signalFeatures;
}

// ------------------------------- PRIVATE ----------------------------------

void HeartClassModule::runHeartClass() {

    auto rPeaks = rPeaksModule.getResults().rpeaks;
    auto ecgSignal = ecgBaselineModule.getResults().samples;
    auto sliced_vector = this->prepareSignal(ecgSignal, rPeaks, this->samplingRate);
    auto features = this->calculateFeatures(sliced_vector);
    this->features = features;
    auto featuresVector = this->featuresToVector(features);
    this->featuresVec = featuresVector;


    // results = {};

    // // na koniec to
    validateResults();
}

std::vector<std::vector<double>> HeartClassModule::transposeFeaturesVector(std::vector<std::vector<double>>& vect) {

    int m = vect.size();
    int n = vect[0].size();

    std::vector<std::vector<double>> outVec(n, std::vector<double>(m, 0));

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            outVec[j][i] = vect[i][j];
        }
    }
    return outVec;
};

std::vector<std::vector<double>> HeartClassModule::featuresToVector(cardioFeatures& featuresStruct) {

    int nRpeaks = featuresStruct.maxValue.size();

    // :( :( :( 
    std::vector<std::vector<double>> featuresVector(this->nFeatures, std::vector<double>(nRpeaks, 0));

    featuresVector[0] = featuresStruct.maxValue;
    featuresVector[1] = featuresStruct.minValue;
    featuresVector[2] = featuresStruct.ptsAboveTh;
    featuresVector[3] = featuresStruct.qrsAuc;
    featuresVector[4] = featuresStruct.qrsPosRatio;
    featuresVector[5] = featuresStruct.qrsNegRatio;
    featuresVector[6] = featuresStruct.aucComparsion;
    featuresVector[7] = featuresStruct.kurtosis;
    featuresVector[8] = featuresStruct.skewness;
    
    return transposeFeaturesVector(featuresVector);
};

// ------------------------PUBLIC------------------------------------























HeartClassData HeartClassModule::getResults() {
    HeartClassData results;
    std::vector<char> classes{'N'};
    results.heartClass = classes;
    std::vector<int> rpos{1};
    results.qrsPosition = rpos;

    return results;
};

void HeartClassModule::notify() {
    log("Notifying");
    ModuleBase::notify();
}


void HeartClassModule::invalidateResults() {
    log("Something changed");
    ModuleBase::invalidateResults();
}

cardioFeatures HeartClassModule::getFeatures() {
    runHeartClass();
    return this->features;
}