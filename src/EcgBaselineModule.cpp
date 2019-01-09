#include <EcgBaselineModule.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

void EcgBaselineModule::runEcgBaseline() {}

EcgBaselineData EcgBaselineModule::getResults() {
    EcgBaselineData sig;

    std::cout << std::string(DATA_DIR) + "/10.csv" <<std::endl;
    std::ifstream infile(std::string(DATA_DIR) + "/maly.csv", std::ios::in);
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
