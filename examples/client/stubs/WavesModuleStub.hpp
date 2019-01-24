#pragma once
#include <WavesModuleBase.hpp>
#include <EcgBaselineModuleBase.hpp>
#include <RPeaksModuleBase.hpp>
#include <Log.hpp>

class WavesModule : public WavesModuleBase {
public:
    WavesModule (EcgBaselineModuleBase& ecgBaselineModule, RPeaksModuleBase& rPeaksModule) : 
        ecgBaselineModule(ecgBaselineModule),
        rPeaksModule(rPeaksModule) {
        ecgBaselineModule.attach(this);
        rPeaksModule.attach(this);
    }

    WavesData getResults() override {
        if (resultsValid()) {
            consoleLog("%sModule::getResults(): returninng cached results", moduleIdToString(id).c_str());
        }
        else {
            ecgBaselineModule.getResults();
            rPeaksModule.getResults();
            consoleLog("%sModule::getResults(): recalculating results", moduleIdToString(id).c_str());
            validateResults();
        }
        
        return {};
    }

    void setOnStatusChangeCallback(onModuleStatusChange_t callback) {
        ModuleBase::setOnStatusChangeCallback(callback);
    }

private:
    EcgBaselineModuleBase& ecgBaselineModule;
    RPeaksModuleBase& rPeaksModule;
};
