#pragma once 
#include <ModuleBase.hpp>

struct heartClassesOutput{
    std::vector<int> qrsPosition;
    std::vector<char> heartClass;
};


class heartClassDescriptorBase : public ModuleBase {
    public:
            virtual std::vector<std::vector <float>>  getResults() = 0;
            //virtual void configure(heartClassDescriptorConfig) = 0;
};

// class hearClassClassificationBase : public ModuleBase {
//     public:
//             virtual heartClassesOutput getResults() = 0; 
// };
