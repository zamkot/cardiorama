#include <iostream>
#include <fstream>

#include <RPeaksModule.h>

void testfile(std::string filename) {// test modułu rpeaks
    EcgBaselineModule ecgBaselineModule;
    ecgBaselineModule.configure(filename);
    RPeaksModule rPeaksModuleTest(ecgBaselineModule);
    auto results = rPeaksModuleTest.getResults();

    std::ofstream outfile(std::__cxx11::string(ecgBaselineModule.getFilename()) + std::__cxx11::string("_results.csv"), std::ios_base::trunc);
    for(auto element: results.rpeaks) {
        std::cout << element << ",";
        outfile << element << ",";
    }
}

int main() {
    std::cout << "test modułu rpeaks" << std::endl;
    testfile("100.csv");
    testfile("102.csv");
    testfile("105.csv");
    testfile("106.csv");
    testfile("109.csv");
    testfile("115.csv");
    testfile("123.csv");
    testfile("220.csv");
    testfile("228.csv");
    testfile("234.csv");
}
