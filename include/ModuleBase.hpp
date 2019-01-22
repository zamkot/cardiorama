#pragma once
#include <vector>
#include <string>


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


static std::string moduleIdToString(ModuleId id) {
    switch (id) {
        case ModuleId::IO          : return "IO";
        case ModuleId::EcgBaseline : return "EcgBaseline";
        case ModuleId::RPeaks      : return "RPeaks";
        case ModuleId::Waves       : return "Waves";
        case ModuleId::TWaves      : return "TWaves";
        case ModuleId::Hrv1        : return "Hrv1";
        case ModuleId::Hrv2        : return "Hrv2";
        case ModuleId::HrvDfa      : return "HrvDfa";
        case ModuleId::HeartClass  : return "HeartClass";
        default : return "unknown";
    }
}


class ModuleBase {
    std::vector<ModuleBase*> views;
    bool resultsValidFlag;

protected:
    ModuleId id;
    virtual void notify();

public:
    ModuleBase(ModuleId);
    ModuleId getId();
    bool resultsValid();
    virtual void invalidateResults();
    virtual void validateResults();
    virtual void attach(ModuleBase* observer);
};