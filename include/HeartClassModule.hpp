#pragma once

#include <ModuleBase.hpp>
#include <HeartClassModuleBase.hpp>

#include <EcgBaselineModuleBase.hpp>
#include <RPeaksModuleBase.hpp>

const int N_FEATURES = 9;
const int SAMPLING_RATE = 360;
const int WINDOW_SIZE = 0.2 * SAMPLING_RATE;

struct cardioFeatures{
    std::vector<double> maxValue;
    std::vector<double> minValue;
    std::vector<double> ptsAboveTh;
    std::vector<double> qrsAuc;
    std::vector<double> qrsPosRatio;
    std::vector<double> qrsNegRatio;
    std::vector<double> aucComparsion;
    std::vector<double> kurtosis;
    std::vector<double> skewness;
};


class HeartClassModule : public HeartClassModuleBase {

    EcgBaselineModuleBase& ecgBaselineModule;
    RPeaksModuleBase& rPeaksModule;
    
    // atruibutes
    int samplingRate = SAMPLING_RATE;
    int nFeatures = N_FEATURES;
    int windowSize = WINDOW_SIZE;

    HeartClassData results;

    // descriptor methods
    std::vector<std::vector<double>> prepareSignal(std::vector<double>&, std::vector<int>&, int&);
    std::vector<double> maxValue(std::vector<std::vector<double>>&);
    std::vector<double> minValue(std::vector<std::vector<double>>&);
    std::vector<double> ptsAboveTh(std::vector<std::vector<double>>&);
    std::vector<double> qrsAuc(std::vector<std::vector<double>>&);
    std::vector<double> qrsPosRatio(std::vector<std::vector<double>>&);
    std::vector<double> qrsNegRatio(std::vector<std::vector<double>>&);
    std::vector<double> aucComparsion(std::vector<std::vector<double>>&);
    std::vector<double> kurtosis(std::vector<std::vector<double>>&);
    std::vector<double> skewness(std::vector<std::vector<double>>&);
    cardioFeatures calculateFeatures(std::vector<std::vector<double>>& );   
    std::vector<std::vector<double>> transposeFeaturesVector(std::vector<std::vector<double>>& );
    std::vector<std::vector<double>> featuresToVector(cardioFeatures& );
    
    // 

    // metody inne
    
    void runHeartClass();

public:

    cardioFeatures features;
    std::vector<std::vector<double>> featuresVec;
    std::vector<std::vector<double>> featuresVec1;

    // metody publiczne
    HeartClassModule(EcgBaselineModuleBase&, RPeaksModuleBase&);
    
    cardioFeatures getFeatures();

    HeartClassData getResults() override;
    void notify() override;
    void invalidateResults() override;
};
