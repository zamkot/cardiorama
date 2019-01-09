#ifndef CARDIORAMA_ECGBASELINEMODULE_H
#define CARDIORAMA_ECGBASELINEMODULE_H

#include <EcgBaselineModuleBase.hpp>
#include <string>

class EcgBaselineModule: public EcgBaselineModuleBase {
public:
    void runEcgBaseline();
    EcgBaselineData getResults() override;
    std::string getFilename();

    void configure(std::string filename);

private:
    std::string filename;
};

#endif //CARDIORAMA_ECGBASELINEMODULE_H
