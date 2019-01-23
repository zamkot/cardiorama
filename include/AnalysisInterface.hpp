#include "Datatypes.hpp"
#include <string>



struct EcgBaselineConfig {
    enum Algorithm { BUTTERWORTH, WAVELET };
    Algorithm algorithm;
};

struct RPeaksConfig {
    short algorithm; // 0 - HILBERT, 1 - PAN_TOMPKINS
};

struct Hrv2Config {
    int num_of_bins;
};

class Analysis {
public:
    void loadFile(std::string path);

    EcgBaselineData runEcgBaseline();
    RPeaksData runRPeaks();
    WavesData runWaves();
    TWavesData runTWaves();
    Hrv1Data  runHrv1();
    Hrv2Data  runHrv2();
    HrvDfaData runHrvDfa();

    void sendEcgBaselineConfig(EcgBaselineConfig);
    void sendRPeaksConfig(RPeaksConfig);
    void sendHrv2Config(Hrv2Config);

};

