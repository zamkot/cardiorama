#include "Datatypes.hpp"


struct RPeaksConfig {
    short algorithm; // 0 - HILBERT, 1 - PAN_TOMPKINS
};


class Analysis {
public:
    void loadFile(std::string path);

    Signal runEcgBaseline();
    RPeaksData runRPeaks();
    WavesData runWaves();

    void sendRPeaksConfig(RPeaksConfig);
};

// int main() {

//     Analysis analysis;

//     // wciskamy przycisk send rpeaksconfig
//     short wybor = 0; // 0 albo 1
//     RPeaksConfig rPeaksConfig{wybor};
//     analysis.sendRPeaksConfig(rPeaksConfig);

//     // wciskamy run rpeaks
//     RPeaksData wynikiRpeaks = analysis.runRPeaks(); 
// }
