#include <Analysis.hpp>
#include <Log.hpp>
#include <sstream>

static std::string moduleStatesToString(std::map<ModuleId,bool> moduleStates) {
    std::stringstream ss;
    for (auto state : moduleStates) {
        ss << moduleIdToString(state.first) << ": " <<
            (state.second ? "valid" : "invalid") << std::endl;
    }
    return ss.str();
}


Analysis::Analysis(std::function<void(ModuleId, bool)> _notifyClient) :
    ecgBaselineModule(ioModule),
    rPeaksModule(ecgBaselineModule),
    wavesModule(ecgBaselineModule, rPeaksModule),
    notifyClient{_notifyClient}
{
    ioModule.setOnStatusChangeCallback([this] (ModuleId id, bool resultsValid) { onModuleStatusUpdate(id, resultsValid); });
    ecgBaselineModule.setOnStatusChangeCallback([this] (ModuleId id, bool resultsValid) { onModuleStatusUpdate(id, resultsValid); });
    rPeaksModule.setOnStatusChangeCallback([this] (ModuleId id, bool resultsValid) { onModuleStatusUpdate(id, resultsValid); });
    wavesModule.setOnStatusChangeCallback([this] (ModuleId id, bool resultsValid) { onModuleStatusUpdate(id, resultsValid); });
}

void Analysis::setInputFileName(std::string fileName) {
    ioModule.setInputFileName(fileName);
}

void Analysis::configure(EcgBaselineConfig config) {
    ecgBaselineModule.configure(config);
}

void Analysis::configure(RPeaksConfig config) {
    rPeaksModule.configure(config);
}

std::vector<double> Analysis::getRawSignal() {
    return ioModule.getRawSignal();
}

EcgBaselineData Analysis::getEcgBaseline() {
    return ecgBaselineModule.getResults();
}

RPeaksData Analysis::getRPeaks() {
    return rPeaksModule.getResults();
}

WavesData Analysis::getWaves() {
    return wavesModule.getResults();
}

void Analysis::onModuleStatusUpdate(ModuleId id, bool state) {
    moduleStates[id] = state;
    consoleLog("%s", moduleStatesToString(moduleStates).c_str());
    notifyClient(id, state);
}

void Analysis::exportResults() {
    for (auto state : moduleStates) {
        ModuleId id = state.first;
        bool resultsValid = state.second;

        if (resultsValid == true) {
            switch (id) {
                case ModuleId::EcgBaseline : ioModule.exportResults(ecgBaselineModule.getResults()); break;
                case ModuleId::RPeaks : ioModule.exportResults(rPeaksModule.getResults()); break;
                case ModuleId::Waves : ioModule.exportResults(wavesModule.getResults()); break;
            }
        }
    }
}