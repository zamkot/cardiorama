#pragma once
#include <EcgBaselineModuleBase.hpp>
#include <IOModule.hpp>

class EcgBaselineModule : public EcgBaselineModuleBase {
public:
    EcgBaselineModule(IOModuleBase& ioModule) : ioModule(ioModule) {}
    EcgBaselineData getResults() override {};
    void configure(EcgBaselineConfig) override {}; 

private:
    IOModuleBase& ioModule;
};
