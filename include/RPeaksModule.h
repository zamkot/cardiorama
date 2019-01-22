#ifndef R_PEAKS_H
#define R_PEAKS_H

#include <EcgBaselineModule.hpp>
#include <RPeaksModuleBase.hpp>
#include <armadillo>

#define RPeaksAlgorithm short
#define HILBERT 0
#define PAN_TOMPKINS 1

class RPeaksModule : public RPeaksModuleBase
{
public:
    explicit RPeaksModule(EcgBaselineModule& ecgBaselineModule, RPeaksAlgorithm rpeaksAlgorithm = PAN_TOMPKINS, double frequency = 360);
    void configure(RPeaksAlgorithm rpeaksAlgorithm = PAN_TOMPKINS, double frequency = 360);
    void configureTest();
    void runRPeaks();
    RPeaksData getResults() override;
private:
    EcgBaselineModule& ecgBaselineModule;
    RPeaksAlgorithm rpeaksAlgorithm;
    double frequency;
    RPeaksData results;

    arma::vec rawSignal;
    arma::vec filteredSignal;
    double samplingFrequency;
    arma::vec r_peaks_vec;

    void Pan_Tompkins();
    void filter_lowpass(double fc, int M);
    void filter_highpass(double fc, int M);
    void square();
    void differentiate();
    void integrate(int W);
    arma::vec find_peaks(arma::vec signal);
    arma_inline double besseli0(double x);
    arma::vec stdvecToArmavec(const std::vector<int>& invec);
    std::vector<int> armavecToStdvec(const arma::vec& invec);

    bool isTest;
};

#endif //R_PEAKS_H