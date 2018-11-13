#pragma once
#include <ModuleBase.hpp>
#include <Datatypes.hpp>
#include <EcgBaselineModuleBase.hpp>
#include <RPeaksModuleBase.hpp>


class WavesModuleBase : public ModuleBase {
public:
    virtual WavesData getResults() = 0;
};