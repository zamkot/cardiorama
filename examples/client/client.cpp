#include <iostream>
#include <Analysis.hpp>

std::string moduleIdToString(ModuleId id) {
    switch (id) {
        case ModuleId::IO          : return "IO";
        case ModuleId::EcgBaseline : return "EcgBaseline";
        case ModuleId::RPeaks      : return "RPeaks";
        case ModuleId::Waves       : return "Waves";
        case ModuleId::TWaves      : return "TWaves";
        case ModuleId::Hrv1        : return "Hrv1";
        case ModuleId::Hrv2        : return "Hrv2";
        case ModuleId::HrvDfa      : return "HrvDfa";
        case ModuleId::HeartClass  : return "HeartClass";
        default : return "unknown";
    }
}

class App {
    void onModuleStatusUpdate(ModuleId id, bool resultsValid) {
        std::cout 
            << name << ", " 
            << moduleIdToString(id) << ", " 
            << (resultsValid ? "valid" : "invalid") << std::endl;
    }

    std::string name;

    Analysis analysis;

public:
    App(std::string name)
    :  name{name}, 
       analysis([this] (ModuleId id, bool resultsValid) { onModuleStatusUpdate(id, resultsValid); }) 
    {}
    
    void go() {
    }
};

int main() {
    App app("Jeden");
    app.go();
}
