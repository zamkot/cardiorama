#pragma once
#include "ModuleBase.hpp"


struct HrvDfaData {
    std::vector<double> log_window_sizes;
    std::vector<double> log_fluctuation;
    std::vector<double> line_alfa1;
    std::vector<double> line_alfa2;
};


class HrvDfaModuleBase : public ModuleBase {
public:
    virtual HrvDfaData getResults() = 0; 
};
