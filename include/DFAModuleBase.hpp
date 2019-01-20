#include "ModuleBase.hpp"
#include "Datatypes.hpp"

class DFAModuleBase : public ModuleBase {
public:
    virtual DFAData getResults() = 0; 
};
