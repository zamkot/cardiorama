#include "RPeaksModuleBase.hpp"
#include "Datatypes.hpp"

class RPeaksModuleStub : public RPeaksModuleBase {

    RPeaksData results;
    std::vector<int> rPeaks;


public:

    RPeaksModuleStub(std::vector<int> rPeaks);

    RPeaksData getResults() override;
};