#include <Analysis.hpp>

Analysis::Analysis(std::function<void(ModuleId, bool)> onModuleStatusUpdate) :
    ecgBaselineModule(ioModule),
    rPeaksModule(ecgBaselineModule),
    wavesModule(ecgBaselineModule, rPeaksModule)
{
    ioModule.setOnStatusChangeCallback(onModuleStatusUpdate);
    ecgBaselineModule.setOnStatusChangeCallback(onModuleStatusUpdate);
    rPeaksModule.setOnStatusChangeCallback(onModuleStatusUpdate);
    wavesModule.setOnStatusChangeCallback(onModuleStatusUpdate);
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