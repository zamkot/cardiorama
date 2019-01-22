#include <iostream>
#include <vector>
#include <HeartClassModule.hpp>
#include <EcgBaselineModuleBase.hpp>
#include <WavesModuleBase.hpp>

#include <DataFrame.hpp>


class EcgBaselineStub : public EcgBaselineModuleBase {
    EcgBaselineData getResults() {
        // stąd zwracacie swoje podstawione dane
    }
    void configure(EcgBaselineConfig) {
        // to może być puste ale musi być bo się kompilator sra
    } 
};

class WavesStub : public WavesModuleBase {
    WavesData getResults() {
        // stąd zwracacie swoje podstawione dane
    }

    void configure(WavesConfig) {}
};

std::vector<int> loadData(std::string path) {
    DataFrame df(path);
    std::vector<int> data = df.get<int>("Example Input Data", [](auto s){ return std::stoi(s); });

    return data;
}
std::vector<double> loadData1(std::string path) {
    DataFrame df(path);
    std::vector<double> data = df.get<double>("Example Input Data", [](auto s){ return std::stoi(s); });

    return data;
}

int main() {
    std::vector<int> rPeaks = loadData("r_peaks.csv");
    std::vector<double> rawSignal = loadData1("sygnal.csv");

    EcgBaselineStub ecgBaselineStub;
    WavesStub wavesStub;

    HeartClassModule classfier = HeartClassModule(ecgBaselineStub, wavesStub);
    auto results = classfier.getResults();
    
    //costam
}
