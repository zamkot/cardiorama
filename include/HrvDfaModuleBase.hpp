#pragma once
#include <ModuleBase.hpp>


struct HrvDfaData {

};

struct HrvDfaConfig {

};

class HrvDfaModuleBase : public ModuleBase {
public:
    virtual HrvDfaData getResults() = 0;
    virtual void configure(HrvDfaConfig) = 0;
};
