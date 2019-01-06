#ifndef CARDIORAMA_ECGBASELINEMODULE_H
#define CARDIORAMA_ECGBASELINEMODULE_H

#include <EcgBaselineModuleBase.hpp>

class EcgBaselineModule: public EcgBaselineModuleBase {
public:
    void runEcgBaseline();
    EcgBaselineData getResults();
};

#endif //CARDIORAMA_ECGBASELINEMODULE_H
