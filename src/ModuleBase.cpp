#include <ModuleBase.hpp>
#ifndef consoleLog
#include <Log.hpp>
#endif


ModuleBase::ModuleBase(ModuleId id, onModuleStatusChange_t onStatusChange)
    :   resultsValidFlag{false}, 
        onStatusChange{onStatusChange},
        id{id} {}


ModuleId ModuleBase::getId() {
    return id;
}


void ModuleBase::setOnStatusChangeCallback(onModuleStatusChange_t callback) {
    onStatusChange = callback;
}


bool ModuleBase::resultsValid() {
    return resultsValidFlag;
}


void ModuleBase::notify() {
    for (auto view : views) {
        view->invalidateResults();
    }

    onStatusChange(id, resultsValidFlag);
}


void ModuleBase::invalidateResults() {
    if (resultsValidFlag == true) {
        resultsValidFlag = false;
        consoleLog("%sModule::invalidateResults(): changing state to invalid.", moduleIdToString(id).c_str());
        notify();
    }
    else {
        consoleLog("%sModule::invalidateResults(): already invalid.", moduleIdToString(id).c_str());
    }
}


void ModuleBase::validateResults() {
    if (resultsValidFlag == true) {
        consoleLog("%sModule::validateResults(): already valid.", moduleIdToString(id).c_str());
    }
    else {
        resultsValidFlag = true;
        consoleLog("%sModule::validateResults(): changing state to valid.", moduleIdToString(id).c_str());
    }
}


void ModuleBase::attach(ModuleBase* observer) {
    consoleLog("%s: attaching %s.", 
        moduleIdToString(id).c_str(), 
        moduleIdToString(observer->getId()).c_str());

    views.push_back(observer);
}