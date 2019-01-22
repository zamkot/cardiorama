#pragma once
#include <ModuleBase.hpp>


struct RPeaksData {
    std::vector<double> rpeaks;
};

struct RPeaksConfig {
    enum Algorithm { HILBERT, PAN_TOMPKINS };
    Algorithm algorithm;
    double samplingFrequency;
};

class RPeaksModuleBase : public ModuleBase {
public:
    virtual RPeaksData getResults() = 0;
    virtual void configure(RPeaksConfig) = 0;
};
