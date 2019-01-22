#pragma once
#include <ModuleBase.hpp>


struct RPeaksData {
    std::vector<int> rpeaks;
};

struct RPeaksConfig {
    enum Algorithm { HILBERT, PAN_TOMPKINS };
    Algorithm algorithm;
};

class RPeaksModuleBase : public ModuleBase {
public:
    RPeaksModuleBase() : ModuleBase(ModuleId::RPeaks) {}
    virtual RPeaksData getResults() = 0;
    virtual void configure(RPeaksConfig) = 0;
};
