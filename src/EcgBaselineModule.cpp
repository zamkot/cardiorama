#include <EcgBaselineModule.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

void EcgBaselineModule::runEcgBaseline() {}

EcgBaselineData EcgBaselineModule::getResults() {
    EcgBaselineData sig;

    std::cout << filename <<std::endl;
    std::ifstream infile(filename, std::ios::in);
    std::string line;
    std::string token;

    while(infile >> line) {
        std::stringstream ss(line);

        int iter = 0;
        while (std::getline(ss, token, ',')) {
            if(!iter || iter == 1) {
                iter++;
                continue;
            }
            std::stringstream ss2(token);
            int xd;
            ss2 >> xd;
            sig.samples.push_back(xd);
            iter++;
        }
    }

    return sig;
}

void EcgBaselineModule::configure(std::string filename) {
    this->filename = std::string(DATA_DIR) + "/" + filename;
}

std::string EcgBaselineModule::getFilename() {
    return this->filename;
}
