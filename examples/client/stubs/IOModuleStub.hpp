#pragma once
#include <IOModuleBase.hpp>

class IOModule : public IOModuleBase {
public:
    void setInputFileName(std::string) override {}
    std::vector<double> getRawSignal() override {}
};
