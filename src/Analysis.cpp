#include <Analysis.hpp>

Analysis::Analysis(std::function<void(ModuleId, bool)> onModuleStatusUpdate) :
    ecgBaselineModule(ioModule),
    rPeaksModule(ecgBaselineModule)
{}
