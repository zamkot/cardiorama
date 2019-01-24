#pragma once
#include <vector>


//struct Signal {
//    std::vector<int> samples;
//};

struct EcgBaselineData {
    std::vector<double> samples;
};

struct RPeaksData {
    std::vector<int> rpeaks;
};


//struct WavesData {
//    std::vector<int> qrsOnset;
//    std::vector<int> qrsEnd;
//    std::vector<int> tEnd;
//    std::vector<int> pOnset;
//    std::vector<int> pEnd;
//};


struct WavesData {

    std::vector<int> Q_wektor;
    std::vector<int> QRSonset_wektor;
    std::vector<int> QRSend_wektor;
    std::vector<int> P_wektor;
    std::vector<int> Pend_wektor;
    std::vector<int> Ponset_wektor;
    std::vector<int> T_wektor;

};


struct TWavesData {
    std::vector<int> resultTWA;
    double maxTWA;
};

struct TimeDomainVar {
       double TP;
       double pULF;
       double pVLF;
       double pLF;
       double pHF;
       double LHHF;
       double meanRR;
       double stdRR;
       double rmsRR;
       int sumNN50;
       double pNN50;
       double sdann;
       double sdanni;
       double sdsd;
};

struct Hrv1Data {

    std::vector<double> F;
    std::vector<double> P;
    std::vector<double> ULF;
    std::vector<double> VLF;
    std::vector<double> LF;
    std::vector<double> HF;
    TimeDomainVar timeDomainResults;

};

struct Hrv2Data {
    std::vector<int> hist_values;
    std::vector<double> bin_centers;
    double hrv_index;
    double tinn;
    double SD1;
    double SD2;
    std::vector<double> poincareplot_x_axis;
    std::vector<double> poincareplot_y_axis;
    double centroid_x;
    double centroid_y;
};

struct HrvDfaData {
    std::vector<double> log_window_sizes;
    std::vector<double> log_fluctuation;
    std::vector<double> line_alfa1;
    std::vector<double> line_alfa2;
    std::vector<double> alfa1;
    std::vector<double> alfa2;
};

struct HeartClassData{
    std::vector<int> qrsPosition;
    std::vector<double> heartClass;
};
