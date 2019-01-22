#pragma once
#include <vector>


enum class ModuleId {
    IO,
    EcgBaseline,
    RPeaks,
    Waves,
    TWaves,
    Hrv1,
    Hrv2,
    HrvDfa,
    HeartClass
};


class ModuleBase {
    std::vector<ModuleBase*> views;
    bool resultsValidFlag;

protected:
    ModuleId id;
    virtual void notify();

public:
    ModuleBase(ModuleId);
    bool resultsValid();
    virtual void invalidateResults();
    virtual void validateResults();
    virtual void attach(ModuleBase* observer);
};