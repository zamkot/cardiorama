#include <ModuleBase.hpp>
#ifndef consoleLog
#include <Log.hpp>
#endif


ModuleBase::ModuleBase(ModuleId id) : resultsValidFlag{false}, id{id} {}


ModuleId ModuleBase::getId() {
    return id;
}


bool ModuleBase::resultsValid() {
    return resultsValidFlag;
}


void ModuleBase::notify() {
    for (auto view : views) {
        view->invalidateResults();
    }
}


void ModuleBase::invalidateResults() {
    if (resultsValidFlag == true) {
        resultsValidFlag = false;
        consoleLog("%s: results invalid.", moduleIdToString(id).c_str());
        notify();
    }
    else {
        consoleLog("%sModule::invalidateResults(): redundant call.", moduleIdToString(id).c_str());
    }
}


void ModuleBase::validateResults() {
    resultsValidFlag = true;
    consoleLog("%s: results valid.", moduleIdToString(id).c_str());
}


void ModuleBase::attach(ModuleBase* observer) {
    consoleLog("%s: attaching %s.", 
        moduleIdToString(id).c_str(), 
        moduleIdToString(observer->getId()).c_str());

    views.push_back(observer);
}