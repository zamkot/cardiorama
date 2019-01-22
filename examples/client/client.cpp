#include <iostream>
#include <Analysis.hpp>

// #define consoleLog
#ifndef consoleLog
#include <Log.hpp>
#endif


class App {
    void onModuleStatusUpdate(ModuleId id, bool resultsValid) {
        std::cout 
            << name << ": " 
            << moduleIdToString(id) << " results " 
            << (resultsValid ? "valid" : "invalid") << std::endl;
    }

    std::string name;

    Analysis analysis;

public:
    App(std::string name)
    :  name{name}, 
       analysis([this] (ModuleId id, bool resultsValid) { onModuleStatusUpdate(id, resultsValid); }) 
    {
        std::cout << std::endl << name << ": constructed." << std::endl;
    }

    void go() {
        std::cout << std::endl << name << ": setting input file name." << std::endl;
        analysis.setInputFileName("some/path");
        
        std::cout << std::endl << name << ": getting rpeaks." << std::endl;
        analysis.getRPeaks();

        std::cout << std::endl << name << ": sending ecgBaselineConfig." << std::endl;
        analysis.configure(EcgBaselineConfig{});

        std::cout << std::endl << name << ": getting waves." << std::endl;
        analysis.getWaves();

    }
};

int main() {
    App app("App");
    app.go();
}
