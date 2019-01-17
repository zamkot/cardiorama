#pragma once
#include <vector>


struct Signal {
    std::vector<int> samples;
};




struct WavesData {
    std::vector<int> qrsOnset;
    std::vector<int> qrsEnd;
    std::vector<int> tEnd;
    std::vector<int> pOnset;
    std::vector<int> pEnd;
};
