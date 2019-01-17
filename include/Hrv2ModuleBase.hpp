#pragma once
#include <ModuleBase.hpp>


struct Hrv2Data {

};

struct Hrv2Config {

};

class Hrv2ModuleBase : public ModuleBase {
public:
    virtual Hrv2Data getResults() = 0;
    virtual void configure(Hrv2Config) = 0;
};
