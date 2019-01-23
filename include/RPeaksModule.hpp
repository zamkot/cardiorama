#ifndef R_PEAKS_H
#define R_PEAKS_H

#include <EcgBaselineModule.hpp>
#include <RPeaksModuleBase.hpp>
#include <armadillo>

class RPeaksModule : public RPeaksModuleBase
{
public:
    explicit RPeaksModule(EcgBaselineModuleBase& ecgBaselineModule);
    void configure(RPeaksConfig) override;
    RPeaksData getResults() override;
private:
    EcgBaselineModuleBase& ecgBaselineModule;
    RPeaksConfig rPeaksConfig;
    RPeaksData results;
    arma::vec rawSignal;

    arma::vec filteredSignal;
    arma::vec RPeakVec;

    void runRPeaks();
    void PanTompkins();
    void filterLowpass(double fc, int M);
    void filterHighpass(double fc, int M);
    void square();
    void differentiate();
    void integrate(int W);
    arma::vec findPeaks(arma::vec signal);
    arma_inline double besseli0(double x);
    std::vector<double> armadilloVecToStdVec(const arma::vec& invec);
};

#endif //R_PEAKS_H