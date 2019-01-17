#pragma once
#include <ModuleBase.hpp>


struct WavesData {

};

struct WavesConfig {

};

class WavesModuleBase : public ModuleBase {
public:
    virtual WavesData getResults() = 0;
    virtual void configure(WavesConfig) = 0;
};
