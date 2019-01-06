#pragma once
#include <ModuleBase.hpp>
#include <Datatypes.hpp>
#include <EcgBaselineModuleBase.hpp>

class RPeaksModuleBase : public ModuleBase {
public:
    virtual RPeaksData getResults() = 0;
};