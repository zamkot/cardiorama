#ifndef CARDIORAMA_RPEAKSMODULE_H
#define CARDIORAMA_RPEAKSMODULE_H

#include <RPeaksModuleBase.hpp>
#include <EcgBaselineModule.hpp>
#include <Datatypes.hpp>
#include <IOModule.hpp>

#define RPeaksAlgorithm short
#define HILBERT 0
#define PAN_TOMPKINS 1

#include <cmath>
#include <complex>
#include <vector>

typedef std::vector<double>::const_iterator R_peaksIter;
typedef std::vector<R_peaksIter> R_peaksIterVector;
typedef std::complex<double> ComplexDouble;
typedef std::vector<ComplexDouble> VectorComplexDouble;
typedef std::pair<double, unsigned int> PairDoubleUnsignedInt;
typedef std::vector<PairDoubleUnsignedInt> VectorPairDoubleUnsignedInt;

class RPeaksModule : public RPeaksModuleBase {
private:
    EcgBaselineModule& ecgBaselineModule;

    RPeaksAlgorithm rpeaksAlgorithm;
    double frequency;

    RPeaksData results;

public:
    RPeaksModule(EcgBaselineModule& ecgBaselineModule);

    void configure(RPeaksAlgorithm rpeaksAlgorithm, double frequency = 360.0);
    void runRPeaks();
    RPeaksData getResults();

    static const double SAFETY_COEFFICIENT;
    static const unsigned short MAX_BPM; // Haskell and Fox: HRmax = 220 - age.
    static const double THRESHOLD_DIVISOR;
    static const unsigned int PT_LP_M;
    static const unsigned int PT_HP_M;
    static const unsigned int PT_MW_N;

    std::vector<double> filteredSignal;
    std::vector<double> ecgSignal;
    R_peaksIterVector itVect;
    std::vector<double> indexVector;

    void fft(const std::vector<double> & x, VectorComplexDouble & result);
    void ifft(const VectorComplexDouble & x, VectorComplexDouble & result);
    void fftHilbertWindowed(const std::vector<double> & x, std::vector<double> & result, double window_length, double window_overlap);
    void fftHilbert(const std::vector<double> & x, std::vector<double> & result);
    void setHilbertRPeaks(const VectorPairDoubleUnsignedInt & peaks, double dt);

    double PTLowPassFilter(double data, bool reset);
    double PTHighPassFilter(double data, bool reset);
    double PTDerivative (double data, bool reset);
    double PTSquaringFunction(double data);
    double PTMovingWindowIntegral(double data, bool reset);
    PairDoubleUnsignedInt Maximum(int begin, int end, std::vector<double> & values);
    void PanTompkinsDo(std::vector<double> & signal, VectorPairDoubleUnsignedInt & result);
    void PanTompkinsSetPeaks(VectorPairDoubleUnsignedInt & filter, VectorPairDoubleUnsignedInt & movingWindow);
    PairDoubleUnsignedInt Peak200MS(int & index, std::vector<double> & signal);
    int QRSCheck(PairDoubleUnsignedInt rpCandidate, PairDoubleUnsignedInt rpLast, double threshold, std::vector<double> & slope);
public:
    // funkcja znajdujaca piki metoda transformacji Hilberta
    void hilbert(void);
    // funkcja znajdujaca piki metoda Pan Tomkins
    void panTompkins(void);

    // funkcja znajdujaca piki metoda transformacji falkowej

    // funkcja zwracaja wektor iteratorow wskazujacych na probki z pikami R
    const R_peaksIterVector & getPeaksIter(void);

    // funckja zwracajaca wektor indeksow probek z pikami R
    const std::vector<double> & getPeaksIndex(void);

    const R_peaksIter ecgBegin(void);
};


class DiffSorter {
public:
    DiffSorter() {}
    bool operator()(const PairDoubleUnsignedInt& a, const PairDoubleUnsignedInt& b) const {
        return a.first > b.first;
    }
};

class PeaksCutSorter {
private:
    int scope;
public:
    PeaksCutSorter(int scope) {
        this->scope = scope;
    }
    bool operator()(const PairDoubleUnsignedInt& a, const PairDoubleUnsignedInt& b) {
        if(std::abs(a.second - (long)b.second) <= this->scope) return false;
        else return a.second < b.second;
    }
};

#endif //CARDIORAMA_RPEAKSMODULE_H
