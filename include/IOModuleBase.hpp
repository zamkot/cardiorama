#pragma once
#include <ModuleBase.hpp>
#include <vector>

class IOModuleBase : public ModuleBase {
public:
    virtual std::vector<double> getRawSignal() = 0;
};
