#include <iostream>
#include <fstream>

#include <RPeaksModule.h>

int main() {
    std::cout << "test modułu rpeaks" << std::endl;

    // test modułu rpeaks
    EcgBaselineModule ecgBaselineModule;
    RPeaksModule rPeaksModule(ecgBaselineModule);
    rPeaksModule.configure(HILBERT, 7);

    // results invalid, wczytaj plik i przeprowadz oblicznenia
    auto results = rPeaksModule.getResults();

    std::ofstream outfile(std::string(DATA_DIR) + "/results_maly.csv", std::ios::trunc);
    for(int element: results.rpeaks) {
        std::cout << element << ",";
        outfile << element << ",";
    }
//
}