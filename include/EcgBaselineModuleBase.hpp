#pragma once
#include <ModuleBase.hpp>

struct EcgBaselineData {
    std::vector<double> samples;
};


struct EcgBaselineConfig {
   enum Algorithm { 
       BUTTERWORTH, WAVELET 
       };
   Algorithm algorithm;
};

class EcgBaselineModuleBase : public ModuleBase {
public:
    virtual EcgBaselineData getResults() = 0;
    virtual void configure(EcgBaselineConfig::Algorithm) = 0; 
}; 
