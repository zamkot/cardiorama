#include <iostream>
#include <Datatypes.hpp>
#include <ModuleBase.hpp>
#include <EcgBaselineModuleBase.hpp>
#include <RPeaksModuleBase.hpp>
#include <WavesModule.hpp>
#include <armadillo>

#include <typeinfo>
#define log(message) std::cout << typeid(*this).name() << ": " << message << std::endl

class EcgBaselineModuleStub : public EcgBaselineModuleBase {
    Signal& rawData;

public:
    EcgBaselineModuleStub(Signal& rawData) : rawData{ rawData } {}

    Signal getResults() override {
        return rawData;
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
    Signal rawData;
    RPeaksData rPeaks;

    EcgBaselineModuleStub ecgBaselineModule(rawData);
    RPeaksModuleStub rPeaksModule(rPeaks);
    WavesModule wavesModule(ecgBaselineModule, rPeaksModule);

    rawData.samples = {1, 2, 3, 4};


    return 0;
}
