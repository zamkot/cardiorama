#pragma once
#include <ModuleBase.hpp>

struct TimeDomainVar{

    double TP;
    double pVLF;
    double pLF;
    double pHF;
    double LHHF;
    double meanRR;
    double stdRR;
    double rmsRR;
    int sumNN50;
    double pNN50;
    double sdann;
    double sdanni;
    double sdsd;

};	


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

