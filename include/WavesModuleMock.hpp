#pragma once
#include <ModuleBase.hpp>
#include <WavesModuleBase.hpp>
#include <Datatypes.hpp>

#include <EcgBaselineModuleBase.hpp>
#include <RPeaksModuleBase.hpp>


enum class WavesVariant {
    A,
    B
};


struct WavesConfig {
    WavesVariant variant;
};


class WavesModule : public WavesModuleBase {
    using ModuleBase::ModuleBase;

    EcgBaselineModuleBase& ecgBaselineModule;
    RPeaksModuleBase& rPeaksModule;

    WavesData waves;
    WavesConfig config;

    void runWaves();

public:
    WavesModule(EcgBaselineModuleBase&, RPeaksModuleBase&);
    WavesData getResults() override;
    void notify() override;
    void invalidateResults() override;
    void configure(WavesConfig);
};
