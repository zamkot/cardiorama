#pragma once
#include <string>
#include <functional>
#include <stubs/IOModuleStub.hpp>
#include <stubs/EcgBaselineModuleStub.hpp>
#include <stubs/RPeaksModuleStub.hpp>


class Analysis {
public:
    Analysis(std::function<void(ModuleId, bool)>);

    void setInputFileName(std::string fileName);

    void configure(EcgBaselineConfig);
    void configure(RPeaksConfig);
    // void configure(Hrv2Config);


private:
    IOModule ioModule;
    EcgBaselineModule ecgBaselineModule;
    RPeaksModule rPeaksModule;
};
