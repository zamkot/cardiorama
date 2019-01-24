#pragma once
#include <ModuleBase.hpp>
#include <EcgBaselineModuleBase.hpp>
#include <RPeaksModuleBase.hpp>
#include <WavesModuleBase.hpp>
#include <vector>
#include <string>

class IOModuleBase : public ModuleBase {
public:
    IOModuleBase() : ModuleBase(ModuleId::IO) {}
    virtual void setInputFileName(std::string) = 0;
    virtual std::vector<double> getRawSignal() = 0;

    virtual void exportResults(EcgBaselineData&&) = 0;
    virtual void exportResults(RPeaksData&&) = 0;
    virtual void exportResults(WavesData&&) = 0;
};
