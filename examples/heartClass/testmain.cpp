#include <iostream>
#include <vector>
#include <algorithm>
#include <HeartClassModule.hpp>
#include <DataFrame.hpp>

#define PRINT(X) std::cout<<X<<std::endl

class EcgBaselineStub : public EcgBaselineModuleBase {
    EcgBaselineData results;
    std::vector<double> ecgBaseline;
    
public:
    
    EcgBaselineStub(std::vector<double> ecgBaseline) : ecgBaseline{ecgBaseline} {} 

    void configure(EcgBaselineConfig) override {} 
    EcgBaselineData getResults() override {return {ecgBaseline}; }
};

class RPeaksModuleStub : public RPeaksModuleBase {

    RPeaksData results;
    std::vector<int> rPeaks;


public:

    RPeaksModuleStub(std::vector<int> rPeaks) : rPeaks{rPeaks} {}

    void configure(RPeaksConfig) override {}
    RPeaksData getResults() override { return {rPeaks}; }
};

int main() {

    // DataFrame ecg("sygnal.csv");
    DataFrame df_rpeaks("/home/xavier/Desktop/repos/cardiorama/examples/heartClass/r_peaks.csv");
    DataFrame df_ecg("/home/xavier/Desktop/repos/cardiorama/examples/heartClass/sygnal.csv");

    std::vector<int> rpeaks = df_rpeaks.get<int>("Rpeaks", [](std::string s){ return std::stoi(s); });
    std::vector<double> ecg = df_ecg.get<double>("signal", [](std::string s){ return std::stod(s); });

    RPeaksModuleStub R(rpeaks);
    EcgBaselineStub B(ecg);

    HeartClassModule heart(B, R);

    return 0;
}