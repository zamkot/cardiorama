#pragma once
#include <ModuleBase.hpp>
#include <Datatypes.hpp>
#include <EcgBaselineModuleBase.hpp>

class EcgBaselineModule : public EcgBaselineModuleBase {

    EcgBaselineData results; 
    EcgBaselineConfig config; 

    void runEcgBaseline(); 

    std::vector<double> filt (const std::vector<double>& sos, EcgBaselineData signal);
    std::vector<double> filtfilt (const std::vector<double>& sos, EcgBaselineData signal);
    std::vector<double> processButter(EcgBaselineData signal);
    std::vector<double> processWavelet(EcgBaselineData signal);

public:

    EcgBaselineData getResults() override;
    void configure(EcgBaselineConfig) override; 
    
    void invalidateResults() override;

};
