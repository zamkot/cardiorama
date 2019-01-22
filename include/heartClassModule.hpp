#pragma once
#include <heartClassBase.hpp>


class heartClassModule : public heartClassDescriptorBase {
    

    //heartClassesOutput results; // Tu przechowujemy wyniki obliczeń
    //TwójModułConfig config; // Opcjonalne.

    // Serce modułu. Tutaj robisz swoje obliczenia.
    void runheartClassModule();
    std::vector<std::vector<int>> prepareSignal(std::vector<double>, std::vector<int>, int);
    std::vector<int> maxValue(std::vector<std::vector<int>>);
    std::vector<int> minValue(std::vector<std::vector<int>>);
    std::vector<std::vector<int>> ptsAboveTh(std::vector<std::vector<int>>);
    std::vector<int> qrsAuc(std::vector<std::vector<int>>);
    std::vector<float> qrsPosRatio(std::vector<std::vector<int>>);
    std::vector<float> qrsNegRatio(std::vector<std::vector<int>>);
    std::vector<int> aucComparsion(std::vector<std::vector<int>>);
    std::vector<float> kurtosis(std::vector<std::vector<int>>);
    std::vector<float> skewness(std::vector<std::vector<int>>);
    std::vector<std::vector<int>> signal;
    struct wszystko 
        {
            std::vector<int> maxValue;
            std::vector<int> minValue;
            std::vector<std::vector<int>> ptsAboveTh;
            std::vector<int> qrsAuc;
            std::vector<float> qrsPosRatio;
            std::vector<float> qrsNegRatio;
            std::vector<int> aucComparsion;
            std::vector<float> kurtosis;
            std::vector<float> skewness;

        };
    int samplingFrequency;


    // std::vector<int> featuresVector();
    // std::vector<int> setIds();
    // std::vector<int> savaFeatures();
    // std::vector<int> getFeaturesVector();
    

public:

    wszystko getWszystko()
    {
            wszystko wszystko1;
            wszystko1.maxValue = maxValue(signal);
            wszystko1.minValue = minValue(signal);
            wszystko1.ptsAboveTh = ptsAboveTh(signal);
            wszystko1.qrsAuc = qrsAuc(signal);
            wszystko1.qrsPosRatio = qrsPosRatio(signal);
            wszystko1.qrsNegRatio = qrsNegRatio(signal);
            wszystko1.aucComparsion = aucComparsion(signal);
            wszystko1.kurtosis = kurtosis(signal);
            wszystko1.skewness = skewness(signal);
            return wszystko1;

    }
    // Konstruktor przyjmuje referencje do modułów które dostarczają nasze dane wejściowe
    heartClassModule(std::vector<double> &rawSignal,std::vector<int> &rPeaks, int &sF)
    {
        samplingFrequency = sF;
        signal = prepareSignal(rawSignal, rPeaks, samplingFrequency);
        
    }

    // Będziemy implementować wirtualne metody zadeklarowane w klasie bazowej
   // heartClassesOutput getResults() override;
   // void configure(TwójModułConfig) override; // Mówiłem że to opcjonalne?
    
    // Opcjonalne. Możesz powrzucać do tych metod jakieś printy do debugowania.
    // void notify() override;
    // void invalidateResults() override;
};