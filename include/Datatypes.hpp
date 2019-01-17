#pragma once
#include <vector>


struct Signal {
    std::vector<int> samples;
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

struct Hrv1Data {
    
    std::vector<double> F;
    std::vector<double> P;
    std::vector<double> VLF;
    std::vector<double> LF;
    std::vector<double> HF;
    TimeDomanVar timeDomainResults;

}; 
