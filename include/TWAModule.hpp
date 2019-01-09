#pragma once
#include <ModuleBase.hpp>
#include <Datatypes.hpp>
#include <TWAModuleBase.hpp>


class TWAModule : public TWAModuleBase {
    
    EcgBaselineModuleBase& EcgBaselineModule; 
    WavesModuleBase& WavesModule; //* sprawdzić nazwę - w TWAModule.cpp też

    TWAData results; 

    void runTWA(); 


public:

    TWAModule(EcgEcgBaselineModuleBase&, WavesModuleBase&);

    TWAData getResults() override;
    
    // Opcjonalne. Możesz powrzucać do tych metod jakieś printy do debugowania.
    //void notify() override;
    //void invalidateResults() override;
};
