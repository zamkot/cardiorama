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
    auto rPeaks = rPeaksModule.output();
    auto ecgBaseline = ecgBaselineModule.output();

    if (config.variant == WavesVariant::B) {
        waves.pEnd = rPeaks.rpeaks;
        waves.pOnset = ecgBaseline.samples;
    }
    else
    {
        waves.pEnd = rPeaks.rpeaks;
        waves.qrsOnset = ecgBaseline.samples;
    }

    validateResults();
}


WavesData WavesModule::output() {
    
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