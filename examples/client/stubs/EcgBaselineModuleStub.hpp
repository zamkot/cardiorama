#pragma once
#include <EcgBaselineModuleBase.hpp>
#include <IOModule.hpp>
#include <Log.hpp>

class EcgBaselineModule : public EcgBaselineModuleBase {
public:
    EcgBaselineModule(IOModuleBase& ioModule) : ioModule(ioModule) {
        ioModule.attach(this);
    }

    EcgBaselineData getResults() override {
        if (resultsValid()) {
            consoleLog("%sModule::getResults(): returninng cached results", moduleIdToString(id).c_str());
        }
        else {
            ioModule.getRawSignal();
            consoleLog("%sModule::getResults(): recalculating results", moduleIdToString(id).c_str());
            validateResults();
        }

        return {};
    }

    void configure(EcgBaselineConfig) override {
        invalidateResults();
    }

    void setOnStatusChangeCallback(onModuleStatusChange_t callback) {
        ModuleBase::setOnStatusChangeCallback(callback);
    };

private:
    IOModuleBase& ioModule;
};
