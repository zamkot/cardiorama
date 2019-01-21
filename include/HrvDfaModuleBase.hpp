#include "ModuleBase.hpp"
#include "Datatypes.hpp"

class HrvDfaModuleBase : public ModuleBase {
public:
    virtual HrvDfaData getResults() = 0; 
};
