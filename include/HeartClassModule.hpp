#pragma once
#include <HeartClassModuleBase.hpp>
#include <EcgBaselineModuleBase.hpp>
#include <WavesModuleBase.hpp>

struct cardioFeatures{
    std::vector<double> maxValue;
    std::vector<double> minValue;
    std::vector<std::vector<double>> ptsAboveTh;
    std::vector<double> qrsAuc;
    std::vector<double> qrsPosRatio;
    std::vector<double> qrsNegRatio;
    std::vector<int> aucComparsion;
    std::vector<double> kurtosis;
    std::vector<double> skewness;
};


class HeartClassModule : public HeartClassModuleBase {

    HeartClassData results;
    void runHeartClass();

    EcgBaselineModuleBase& ecgBaselineModule; 
    WavesModuleBase& wavesModule;

    //atrbuty
    std::vector<std::vector<double>> signal;
    std::vector<int> rPeaks;
    int samplingFrequency;
    cardioFeatures signalFeatures;

    // metody deskryptora
    std::vector<double> maxValue(std::vector<std::vector<double>>&);
    std::vector<double> minValue(std::vector<std::vector<double>>&);
    std::vector<std::vector<double>> ptsAboveTh(std::vector<std::vector<double>>&);
    std::vector<double> qrsAuc(std::vector<std::vector<double>>&);
    std::vector<double> qrsPosRatio(std::vector<std::vector<double>>&);
    std::vector<double> qrsNegRatio(std::vector<std::vector<double>>&);
    std::vector<int> aucComparsion(std::vector<std::vector<double>>&);
    std::vector<double> kurtosis(std::vector<std::vector<double>>&);
    std::vector<double> skewness(std::vector<std::vector<double>>&);


    // metody inne
    std::vector<std::vector<double>> prepareSignal(std::vector<double>&, std::vector<int>&, int&);   

public:

    HeartClassModule(EcgBaselineModuleBase&, WavesModuleBase&);
    void setFeatures();
    HeartClassData getResults() override;
};
