#pragma once
#include <string>
#include <functional>
#include <map>
#include <stubs/IOModuleStub.hpp>
#include <stubs/EcgBaselineModuleStub.hpp>
#include <stubs/RPeaksModuleStub.hpp>
#include <stubs/WavesModuleStub.hpp>


class Analysis {
public:
    Analysis(std::function<void(ModuleId, bool)> notifyClient);

    // signaling
    void onModuleStatusUpdate(ModuleId, bool);

    // configs
    void setInputFileName(std::string fileName);
    void configure(EcgBaselineConfig);
    void configure(RPeaksConfig);
    // void configure(Hrv2Config);

    // result getters
    std::vector<double> getRawSignal();
    EcgBaselineData getEcgBaseline();
    RPeaksData getRPeaks();
    WavesData getWaves();

    // misc
    void exportResults();

private:
    IOModule ioModule;
    EcgBaselineModule ecgBaselineModule;
    RPeaksModule rPeaksModule;
    WavesModule wavesModule;

    std::function<void(ModuleId, bool)> notifyClient;
    std::map<ModuleId, bool> moduleStates;
};
