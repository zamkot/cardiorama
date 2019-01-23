#pragma once
#include <ModuleBase.hpp>
#include <TWavesModuleBase.hpp>

#include<EcgBaselineModuleBase.hpp>
#include<WavesModuleBase.hpp>


class TWavesModule : public TWavesModuleBase {
    
    EcgBaselineModuleBase& ecgBaselineModule; 
    WavesModuleBase& wavesModule; //* sprawdzić nazwę - w TWavesModule.cpp też

    TWavesData results; 

    void runTWaves(); 


public:

    TWavesModule(EcgBaselineModuleBase&, WavesModuleBase&);

    TWavesData getResults() override;
    
    // Opcjonalne. Możesz powrzucać do tych metod jakieś printy do debugowania.
    //void notify() override;
    //void invalidateResults() override;
};
