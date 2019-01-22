#pragma once
#include <ModuleBase.hpp>
#include <vector>
#include <string>

class IOModuleBase : public ModuleBase {
public:
    IOModuleBase() : ModuleBase(ModuleId::IO) {}
    virtual void setInputFileName(std::string) = 0;
    virtual std::vector<double> getRawSignal() = 0;
};
