#pragma once
#include <EcgBaselineModuleBase.hpp>

class EcgBaselineModule : public EcgBaselineModuleBase {

    EcgBaselineData results; 
    EcgBaselineConfig config; 
    bool isConfigured = false;

    void runEcgBaseline(); 

    std::vector<double> filt( std::vector<double> &sos,  std::vector<double> &signal);
    std::vector<double> filtfilt( std::vector<double> &sos,  std::vector<double> &signal);
    std::vector<double> processButter( std::vector<double> &signal);
    std::vector<double> processWavelet(std::vector<double> &signal);


public:

    EcgBaselineData getResults() override;
    void configure(EcgBaselineConfig::Algorithm) override;
    
  //  void invalidateResults() override;

};