#pragma once
#include <ModuleBase.hpp>
#include <Datatypes.hpp>

struct EcgBaselineConfig {
   enum Algorithm { BUTTERWORTH, WAVELET };
   Algorithm algorithm;
};

class EcgBaselineModuleBase : public ModuleBase {
public:
    virtual EcgBaselineData getResults() = 0;
    virtual void configure(EcgBaselineConfig) = 0; 
};



