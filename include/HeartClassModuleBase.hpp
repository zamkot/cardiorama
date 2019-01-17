#pragma once
#include <ModuleBase.hpp>


struct HeartClassData {

};

struct HeartClassConfig {

};

class HeartClassModuleBase : public ModuleBase {
public:
    virtual HeartClassData getResults() = 0;
    virtual void configure(HeartClassConfig) = 0;
};
