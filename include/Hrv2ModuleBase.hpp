#pragma once
#include <ModuleBase.hpp>


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

struct Hrv2Config {
    int num_of_bins;
};

class Hrv2ModuleBase : public ModuleBase {
public:
    virtual Hrv2Data getResults() = 0;
    virtual void configure(Hrv2Config) = 0;
};
