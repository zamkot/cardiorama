#include <iostream>
#include <Datatypes.hpp>
#include <ModuleBase.hpp>
#include <EcgBaselineModuleBase.hpp>
#include <RPeaksModuleBase.hpp>
#include <WavesModuleMock.hpp>

#include <typeinfo>
#define log(message) std::cout << typeid(*this).name() << ": " << message << std::endl

class EcgBaselineModuleStub : public EcgBaselineModuleBase {
    Signal& rawData;

public:
    EcgBaselineModuleStub(Signal& rawData) : rawData{ rawData } {}

    Signal output() override {
        log("Runnig output");
        Signal s;
        for (const auto& sample : rawData.samples) {
            s.samples.push_back(sample * 3);
        }
        return s;
    }

    void invalidateResults() override {
        log("Something changed");
        ModuleBase::invalidateResults();
    }

    void notify() override {
        log("Notifying");
        ModuleBase::notify();
    }
};


class RPeaksModuleStub : public RPeaksModuleBase {
    RPeaksData& rPeaks;

public:
    RPeaksModuleStub(RPeaksData& rPeaks) : rPeaks{ rPeaks } {}

    RPeaksData output() override {
        log("Runnig output");
        return rPeaks;
    }

    void invalidateResults() override {
        log("Something changed");
        ModuleBase::invalidateResults();
    }
};


int main() {
    Signal rawData;
    RPeaksData rPeaks;

    EcgBaselineModuleStub ecgBaselineModule(rawData);
    RPeaksModuleStub rPeaksModule(rPeaks);
    WavesModule wavesModule(ecgBaselineModule, rPeaksModule);

    ecgBaselineModule.invalidateResults();

    return 0;
}
