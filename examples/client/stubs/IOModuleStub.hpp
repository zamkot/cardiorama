#pragma once
#include <IOModuleBase.hpp>
#include <Log.hpp>

class IOModule : public IOModuleBase {
public:
    std::vector<double> getRawSignal() override {
        if (resultsValid()) {
            consoleLog("%sModule::getRawSignal(): returninng cached results", moduleIdToString(id).c_str());
        }
        else {
            consoleLog("%sModule::getRawSignal(): fetching results from file", moduleIdToString(id).c_str());
            validateResults();
        }
        
        return {};
    }

    void setInputFileName(std::string) override {
        invalidateResults();
    }; 

    void setOnStatusChangeCallback(onModuleStatusChange_t callback) {
        ModuleBase::setOnStatusChangeCallback(callback);
    };
};
