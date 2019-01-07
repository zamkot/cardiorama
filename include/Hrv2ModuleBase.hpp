#pragma once
#include <ModuleBase.hpp>
#include <Datatypes.hpp>

struct Hrv2Config{
    int num_of_bins;
};

class Hrv2ModuleBase : public ModuleBase{
public:
    virtual Hrv2Data getResults() = 0;
    virtual void configure(Hrv2Config) = 0;
};
	
	
