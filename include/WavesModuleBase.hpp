#pragma once
#include <ModuleBase.hpp>


struct WavesData {
    
    std::vector<int> Q_wektor;
    std::vector<int> S_wektor;
    std::vector<int> QRSonset_wektor;
    std::vector<int> QRSend_wektor;
    std::vector<int> P_wektor;
    std::vector<int> Pend_wektor;
    std::vector<int> Ponset_wektor;
    std::vector<int> T_wektor;

};

class WavesModuleBase : public ModuleBase {
public:
    virtual WavesData getResults() = 0;
    virtual void configure(WavesConfig) = 0;
};
