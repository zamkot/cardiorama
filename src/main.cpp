#include <iostream>
#include <fstream>

#include <RPeaksModule.h>

int main() {
    std::cout << "test modułu rpeaks" << std::endl;

    // test modułu rpeaks
    EcgBaselineModule ecgBaselineModule;
    ecgBaselineModule.configure("100.csv");
    RPeaksModule rPeaksModuleTest(ecgBaselineModule);
//    rPeaksModuleTest.configureTest();
    auto results = rPeaksModuleTest.getResults();

    std::ofstream outfile(std::string(ecgBaselineModule.getFilename()) + std::string("_nolowpass_prog7_results.csv"), std::ios::trunc);
    for(auto element: results.rpeaks) {
        std::cout << element << ",";
        outfile << element << ",";
    }
}