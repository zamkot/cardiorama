#pragma once
#include <ModuleBase.hpp>
#include <Datatypes.hpp>


class Hrv1ModuleBase : public ModuleBase{
public:
    virtual Hrv1Data getResults() = 0;

};
