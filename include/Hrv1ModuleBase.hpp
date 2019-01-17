#pragma once
#include <ModuleBase.hpp>


struct Hrv1Data {

};

struct Hrv1Config {

};

class Hrv1ModuleBase : public ModuleBase {
public:
    virtual Hrv1Data getResults() = 0;
    virtual void configure(Hrv1Config) = 0;
};
