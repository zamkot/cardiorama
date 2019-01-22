#pragma once
#include <RPeaksModuleBase.hpp>
#include <EcgBaselineModuleBase.hpp>

class RPeaksModule : public RPeaksModuleBase {
public:
    RPeaksModule (EcgBaselineModuleBase& ecgBaselineModule) : ecgBaselineModule(ecgBaselineModule) {}
    RPeaksData getResults() override {};
    void configure(RPeaksConfig) override {}; 

private:
    EcgBaselineModuleBase& ecgBaselineModule;
};
