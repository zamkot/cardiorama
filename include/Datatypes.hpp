#pragma once
#include <vector>


struct Signal {
    std::vector<int> samples;
};

struct EcgBaselineData {
    std::vector<double> samples;
};

struct RPeaksData {
    std::vector<int> rpeaks;
};


struct WavesData {
    std::vector<int> qrsOnset;
    std::vector<int> qrsEnd;
    std::vector<int> tOnset;
    std::vector<int> tEnd;
    std::vector<int> pOnset;
    std::vector<int> pEnd;
};

struct TWAData {
	double maxTWA
    std::vector<int> resultTWA;
};
