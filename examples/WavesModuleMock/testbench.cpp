#include <iostream>
#include <Datatypes.hpp>
#include <ModuleBase.hpp>
#include <EcgBaselineModuleBase.hpp>
#include <RPeaksModuleBase.hpp>
#include <WavesModuleMock.hpp>
#include <armadillo>

#include <typeinfo>
#define log(message) std::cout << typeid(*this).name() << ": " << message << std::endl

class EcgBaselineModuleStub : public EcgBaselineModuleBase {
    Signal& ecgBaseline;

public:
    EcgBaselineModuleStub(Signal& ecgBaseline) : ecgBaseline{ ecgBaseline } {}

    Signal getResults() override {
        return ecgBaseline;
    }
};


class RPeaksModuleStub : public RPeaksModuleBase {
    RPeaksData& rPeaks;

public:
    RPeaksModuleStub(RPeaksData& rPeaks) : rPeaks{ rPeaks } {}

    RPeaksData getResults() override {
        return rPeaks;
    }
};


int main() {
    Signal ecgBaseline;
    RPeaksData rPeaks;
    WavesData waves;

    EcgBaselineModuleStub ecgBaselineModule(ecgBaseline);
    RPeaksModuleStub rPeaksModule(rPeaks);
    WavesModule wavesModule(ecgBaselineModule, rPeaksModule);

    ecgBaseline.samples = {12, 15, 12, 12, 13, 15, 19, 20, 9, 10};
    rPeaks.rpeaks = {3, 6, 10};
    wavesModule.invalidateResults();
    waves = wavesModule.getResults();
    for (auto i : waves.qrsEnd) {
        std::cout << i << " ";
    }
    std::putchar('\n');


    ecgBaseline.samples = {12, 15, 12, 12, 13, 15, 19, 20, 9, 10};
    rPeaks.rpeaks = {0, 1, 2};
    wavesModule.invalidateResults();
    waves = wavesModule.getResults();
    for (auto i : waves.qrsEnd) {
        std::cout << i << " ";
    }
    std::putchar('\n');


    return 0;
}
