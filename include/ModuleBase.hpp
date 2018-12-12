#pragma once
#include <vector>


class ModuleBase {
protected:
    std::vector<ModuleBase*> views;
    bool resultsValidFlag;
    bool isConfigured;
    virtual void notify();

public:
    ModuleBase();
    bool resultsValid();
    virtual void invalidateResults();
    virtual void validateResults();
    virtual void attach(ModuleBase* observer);
};