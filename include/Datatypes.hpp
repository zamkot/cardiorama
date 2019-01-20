#pragma once
#include <vector>


struct Signal {
    std::vector<int> samples;
};

struct EcgBaselineData {
    std::vector<double> samples;
};

struct DFAData {
    std::vector<double> log_window_sizes;
    std::vector<double> log_fluctuation;
    std::vector<double> line_alfa1;
    std::vector<double> line_alfa2;
};

struct RPeaksData {
    std::vector<int> rpeaks;
};


struct WavesData {
    std::vector<int> qrsOnset;
    std::vector<int> qrsEnd;
    std::vector<int> tEnd;
    std::vector<int> pOnset;
    std::vector<int> pEnd;
};
