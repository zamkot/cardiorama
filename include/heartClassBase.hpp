#pragma once 
#include <ModuleBase.hpp>

struct heartClassesOutput{
    std::vector<int> qrsPosition;
    std::vector<char> heartClass;
};


class heartClassBase : public ModuleBase {
public:
    virtual int getResults() = 0;
};
