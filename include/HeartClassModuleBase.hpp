#pragma once 
#include <ModuleBase.hpp>

struct HeartClassData{
    std::vector<int> qrsPosition;
    std::vector<double> heartClass;
};


class HeartClassModuleBase : public ModuleBase {
public:
    virtual HeartClassData getResults() = 0;
};
