#pragma once
#include <string>
#include <functional>
#include <stubs/IOModuleStub.hpp>
#include <stubs/EcgBaselineModuleStub.hpp>
#include <stubs/RPeaksModuleStub.hpp>
#include <stubs/WavesModuleStub.hpp>


class Analysis {
public:
    Analysis(std::function<void(ModuleId, bool)> onModuleStatusUpdate);

    void setInputFileName(std::string fileName);

    void configure(EcgBaselineConfig);
    void configure(RPeaksConfig);
    // void configure(Hrv2Config);

    std::vector<double> getRawSignal();
    EcgBaselineData getEcgBaseline();
    RPeaksData getRPeaks();
    WavesData getWaves();

private:
    IOModule ioModule;
    EcgBaselineModule ecgBaselineModule;
    RPeaksModule rPeaksModule;
    WavesModule wavesModule;
};
