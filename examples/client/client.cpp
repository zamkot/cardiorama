#include <iostream>
#include <Analysis.hpp>

// #define consoleLog
#ifndef consoleLog
#include <Log.hpp>
#endif


class Client {
    void onModuleStatusUpdate(ModuleId id, bool resultsValid) {
        std::cout 
            << name << ": " 
            << moduleIdToString(id) << " results " 
            << (resultsValid ? "valid" : "invalid") << std::endl;
    }

    std::string name;

    Analysis analysis;

public:
    Client(std::string name)
    :  name{name}, 
       analysis([this] (ModuleId id, bool resultsValid) { onModuleStatusUpdate(id, resultsValid); }) 
    {
        std::cout << std::endl << name << ": constructed." << std::endl;
    }

    void go() {
        std::cout << std::endl << "==================================" << std::endl;
        std::cout << name << ": setting input file name." << std::endl;
        std::cout <<              "==================================" << std::endl;
        analysis.setInputFileName("some/path");
        
        std::cout << std::endl << "==================================" << std::endl;
        std::cout << name << ": getting rpeaks." << std::endl;
        std::cout <<              "==================================" << std::endl;
        analysis.getRPeaks();

        std::cout << std::endl << "==================================" << std::endl;
        std::cout << name << ": sending ecgBaselineConfig." << std::endl;
        std::cout <<              "==================================" << std::endl;
        analysis.configure(EcgBaselineConfig{});

        std::cout << std::endl << "==================================" << std::endl;
        std::cout << name << ": getting waves." << std::endl;
        std::cout <<              "==================================" << std::endl;
        analysis.getWaves();

        std::cout << std::endl << "==================================" << std::endl;
        std::cout << name << ": sending rPeaksConfig." << std::endl;
        std::cout <<              "==================================" << std::endl;
        analysis.configure(RPeaksConfig{});

        std::cout << std::endl << "==================================" << std::endl;
        std::cout << name << ": exporting results." << std::endl;
        std::cout <<              "==================================" << std::endl;
        analysis.exportResults();
    }
};

int main() {
    Client app("Client");
    app.go();
}
