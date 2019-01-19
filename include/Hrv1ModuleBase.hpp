#pragma once
#include <ModuleBase.hpp>
	
struct Hrv1Data {
    
    std::vector<double> F;
    std::vector<double> P;
    std::vector<double> ULF;
    std::vector<double> VLF;
    std::vector<double> LF;
    std::vector<double> HF;
    TimeDomainVar timeDomainResults;

}; 

class Hrv1ModuleBase : public ModuleBase {
public:
    virtual Hrv1Data getResults() = 0;
};

