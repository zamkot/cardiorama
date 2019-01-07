#include <WavesModuleMock.hpp>

#include <iostream>
#include <typeinfo>
#define log(message) std::cout << typeid(*this).name() << ": " << message << std::endl


WavesModule::WavesModule(EcgBaselineModuleBase& ecgBaselineModule, RPeaksModuleBase& rPeaksModule) :
    ecgBaselineModule{ ecgBaselineModule }, rPeaksModule{ rPeaksModule } {
        ecgBaselineModule.attach(this);
        rPeaksModule.attach(this);

        config.variant = WavesVariant::A;
    }


void WavesModule::configure(WavesConfig config) {
    invalidateResults();
    this->config = config;
}


void WavesModule::runWaves() {
    log("Running");
    waves = {};
    auto rPeaks = rPeaksModule.getResults();
    auto ecgBaseline = ecgBaselineModule.getResults();

    for (auto rpeak : rPeaks.rpeaks) {
        waves.qrsEnd.push_back(ecgBaseline.samples[rpeak] * 2);
    }

    validateResults();
}


WavesData WavesModule::getResults() {
    
    if (!resultsValid()) {
        runWaves();
    }

    return waves;
}


void WavesModule::notify() {
    log("Notifying");
    ModuleBase::notify();
}


void WavesModule::invalidateResults() {
    log("Something changed");
    ModuleBase::invalidateResults();
}