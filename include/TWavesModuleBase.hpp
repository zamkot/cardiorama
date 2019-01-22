#pragma once
#include <ModuleBase.hpp>


struct TWavesData {
    std::vector<int> resultTWA;
    double maxTWA;
};

class TWavesModuleBase : public ModuleBase {
public:
    virtual TWavesData getResults() = 0;
};
