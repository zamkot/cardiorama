#include <iostream>
#include "EcgBaselineModule.hpp"

int main() {
    std::cout << "To jest cardiorama. Jeszcze nic tu nie ma" << std::endl;

    EcgBaselineModule ecgBaselineModule;
    ecgBaselineModule.configure(EcgBaselineConfig::BUTTERWORTH);
    //    ecgBaselineModule.configure(EcgBaselineConfig::WAVELET);


    auto results = ecgBaselineModule.getResults();

    for(double element: results.samples) {
        std::cout << element << ",";
    }

}