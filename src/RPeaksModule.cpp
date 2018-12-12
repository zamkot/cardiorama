#include <RPeaksModule.h>
#include <RPeaksFinder.h>
#include <iostream>

RPeaksModule::RPeaksModule(Physionet& ioModule): ioModule{ ioModule }
{
}

void RPeaksModule::configure(const std::string& inputFileName, RPeaksAlgorithm rpeaksAlgorithm, double frequency)
{
    if(this->inputFileName != inputFileName) {
        this->inputFileName = inputFileName;
        ioModule.readFile(inputFileName);
        invalidateResults();
    }
    if(this->rpeaksAlgorithm != rpeaksAlgorithm) {
        this->rpeaksAlgorithm = rpeaksAlgorithm;
        invalidateResults();
    }
    if(this->frequency == frequency) {
        this->frequency = frequency;
        invalidateResults();
    }
    isConfigured = true;
}

void RPeaksModule::runRPeaks()
{
    if(!isConfigured) {
        std::cout << "BŁAD NIESKONFIGUROWANO MODUŁU" << std::endl;
    }

    // double czy int w ma być?
    auto ioModuleInput = ioModule.getRPeaks().rPeaks; // wczytanie sygnału z pliku, w celu póżniejszego znalezienia rpeaks
    R_peaksModule rpeaks = R_peaksModule(std::vector<double>(ioModuleInput.begin(), ioModuleInput.end()), this->frequency);

    if(rpeaksAlgorithm == HILBERT) rpeaks.hilbert();
    if(rpeaksAlgorithm == PAN_TOMPKINS) rpeaks.panTompkins();

    auto rpeaksModuleOutput = rpeaks.getPeaksIndex();
    results.rpeaks = std::vector<int>(rpeaksModuleOutput.begin(), rpeaksModuleOutput.end());

    validateResults();

//    ioModule.notify(); //??
}

RPeaksData& RPeaksModule::getResults()
{
    if(!resultsValid()) runRPeaks(); // moze by dać jakiś wybór?
    return results;
}