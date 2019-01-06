#pragma once
#include <ModuleBase.hpp>
#include <Datatypes.hpp>


class EcgBaselineModuleBase : public ModuleBase {
public:
    virtual Signal getResults() = 0;

    EcgBaselineData results; // Tu przechowujemy wyniki obliczeń
    EcgBaselineConfig config; // Opcjonalne.

    void runEcgBaseline(); 

    EcgBaselineData getResults() override;
    void configure(EcgBaselineConfig) override; 
    
    void invalidateResults() override;

private:
    std::vector<double> filt (const std::vector<double>& sos, const std::vector<double>& signal);
    std::vector<double> filtfilt (const std::vector<double>& sos, const std::vector<double>& signal);
    std::vector<double> processButter(const std::vector<double>& signal);
    std::vector<double> processWavelet(std::vector<double>& signal);

};
