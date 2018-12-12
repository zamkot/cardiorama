#ifndef CARDIORAMA_RPEAKSMODULE_H
#define CARDIORAMA_RPEAKSMODULE_H

#include <ModuleBase.hpp>
#include <Datatypes.hpp>
#include <IOModule.hpp>

#define RPeaksAlgorithm short
#define HILBERT 0
#define PAN_TOMPKINS 1

class RPeaksModule : public ModuleBase {
private:
    Physionet& ioModule;

    std::string inputFileName;
    RPeaksAlgorithm rpeaksAlgorithm;
    double frequency;

    RPeaksData results;

public:
    RPeaksModule(Physionet&);

    void configure(const std::string& inputFileName, RPeaksAlgorithm rpeaksAlgorithm, double frequency = 360.0);
    void runRPeaks();
    RPeaksData& getResults();
};

#endif //CARDIORAMA_RPEAKSMODULE_H
