#pragma once
#include <ModuleBase.hpp>
#include <Datatypes.hpp>

class TWAModuleBase : public ModuleBase {
public:
    virtual TWAData getResults() = 0; // Oblicza i zwraca wynik.
};
