#pragma once
#include <ModuleBase.hpp>


struct TWavesData {

};

struct TWavesConfig {

};

class TWavesModuleBase : public ModuleBase {
public:
    virtual TWavesData getResults() = 0;
    virtual void configure(TWavesConfig) = 0;
};
