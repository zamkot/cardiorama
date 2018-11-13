#pragma once
#include <ModuleBase.hpp>
#include <Datatypes.hpp>


class EcgBaselineModuleBase : public ModuleBase {
public:
    virtual Signal getResults() = 0;
};