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
    std::vector<int> tEnd;
    std::vector<int> pOnset;
    std::vector<int> pEnd;
};

struct Hrv2Data {
    std::vector<int> hist_values;
    std::vector<double> bin_centers;
    double hrv_index;
    double tinn;
    double SD1; 
    double SD2; 
    std::vector<double> poincareplot_x_axis;
    std::vector<double> poincareplot_y_axis; 
    double centroid_x;
    double centroid_y; 
}; 
