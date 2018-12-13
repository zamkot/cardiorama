#include <ModuleBase.hpp>


ModuleBase::ModuleBase() : resultsValidFlag{false} {}


bool ModuleBase::resultsValid() {
    return resultsValidFlag;
}


void ModuleBase::notify() {
    for (auto view : views) {
        view->invalidateResults();
    }
}


void ModuleBase::invalidateResults() {
    resultsValidFlag = false;
    notify();
}


void ModuleBase::validateResults() {
    resultsValidFlag = true;
}


void ModuleBase::attach(ModuleBase* observer) {
    views.push_back(observer);
}