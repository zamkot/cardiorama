#pragma once
#include <vector>


class ModuleBase {
    std::vector<ModuleBase*> views;
    bool resultsValidFlag;

protected:
    virtual void notify();

public:
    ModuleBase();
    bool resultsValid();
    virtual void invalidateResults();
    virtual void validateResults();
    virtual void attach(ModuleBase* observer);
};