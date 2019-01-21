#include <RPeaksModuleStub.hpp>
#include <iostream>

RPeaksModuleStub::RPeaksModuleStub(std::vector<int> _rPeaks) {
    rPeaks = _rPeaks;
}

RPeaksData RPeaksModuleStub::getResults() { return {rPeaks}; }