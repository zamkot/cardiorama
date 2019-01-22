#pragma once
#include <RPeaksModuleBase.hpp>
#include <EcgBaselineModuleBase.hpp>

class RPeaksModule : public RPeaksModuleBase {
public:
    RPeaksModule (EcgBaselineModuleBase& ecgBaselineModule) : ecgBaselineModule(ecgBaselineModule) {
        ecgBaselineModule.attach(this);
    }

    RPeaksData getResults() override {
        if (resultsValid()) {
            consoleLog("%sModule::getResults(): returninng cached results", moduleIdToString(id).c_str());
        }
        else {
            ecgBaselineModule.getResults();
            consoleLog("%sModule::getResults(): recalculating results", moduleIdToString(id).c_str());
            validateResults();
        }
        
        return {};
    };

    void configure(RPeaksConfig) override {
        invalidateResults();
    }; 

    void setOnStatusChangeCallback(onModuleStatusChange_t callback) {
        ModuleBase::setOnStatusChangeCallback(callback);
    };

private:
    EcgBaselineModuleBase& ecgBaselineModule;
};
