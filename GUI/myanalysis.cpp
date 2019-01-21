#include "../include/AnalysisInterface.hpp"
#include<iostream>
#include <QDebug>
using namespace std;

void Analysis::loadFile(std::string path)
{
    qDebug()<<QString("File opened ");
    qDebug()<<QString::fromStdString(path);

}

void Analysis::sendEcgBaselineConfig(EcgBaselineConfig)
{
    qDebug()<<QString("The ECG detection method was choosen");
}

void Analysis::sendRPeaksConfig(RPeaksConfig)
{
    qDebug()<<QString("The R-Peaks detection method was choosen");
}

void Analysis::sendHrv2Config(Hrv2Config)
{
    qDebug()<<QString("The HRV2 num_of_bins was choosen");
}


EcgBaselineData Analysis::runEcgBaseline()
{
    EcgBaselineData ecgdata;
    ecgdata.samples = vector<double>({2,45,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7
                              ,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7
                              ,2,45,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7,2,15,1,4,22,6,8,30,29,7});
    return ecgdata;
}

RPeaksData Analysis::runRPeaks()
{
    RPeaksData rpeaksdata;
    rpeaksdata.rpeaks = vector<int>({2,5,8,12,15,18,22,25,28,32,35,38,42,45,48,52,55,58,62,65,68,72,75,78,82,85,88,92,95,98,
                                    102,105,108,112,115,118,122,125,128,132,135,138,142,145,148,152,155,158,162,165,168,172,175,178,182,185,188,192,195,198,
                                    202,205,208,212,215,218,222,225,228,232,235,238,242,245,248,252,255,258,262,265,268,272,275,278,282,285,288,292,295,298
                                    });
    return rpeaksdata;
}

WavesData Analysis::runWaves()
{
    WavesData wavesdata;
    wavesdata.Q_wektor = vector<int>({5,6,7,8,2,4,6,2,1,6,7,9,0,10,7,9,0,10});
    wavesdata.S_wektor= vector<int>({9,10,11,12,2,4,6,2,1,6,7,9,0,10,7,9,0,10});
    wavesdata.QRSonset_wektor = vector<int>({13,14,15,16,2,4,6,2,1,6,7,9,0,10,7,9,0,10});
    wavesdata.QRSend_wektor = vector<int>({17,18,19,20,2,4,6,2,1,6,7,9,0,10,7,9,0,10});
    wavesdata.P_wektor = vector<int>({21,22,23,24,2,4,6,2,1,6,7,9,0,10,7,9,0,10});
    wavesdata.Pend_wektor = vector<int>({21,22,23,24,2,4,6,2,1,6,7,9,0,10,7,9,0,10});
    wavesdata.Ponset_wektor = vector<int>({21,22,23,24,2,4,6,2,1,6,7,9,0,10,7,9,0,10});
    wavesdata.T_wektor = vector<int>({21,22,23,24,2,4,6,2,1,6,7,9,0,10,7,9,0,10});

    return wavesdata;
}


TWavesData Analysis::runTWaves()
{
    TWavesData twavesdata;
    twavesdata.resultTWA = vector<int>({1,2,4,5,6,7,9,10});
    twavesdata.maxTWA = double(5.4);

    return twavesdata;
}



Hrv1Data Analysis::runHrv1()
{
    Hrv1Data hrv1data;
    hrv1data.F = vector<double>({0.01,0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08,0.1,0.2,0.3,0.4});
    hrv1data.P = vector<double>({1,2,100000,4,15,4,3,4,5,6,8,12});
    hrv1data.ULF = vector<double>({0,0.003});
    hrv1data.VLF = vector<double>( {0.003,0.15});
    hrv1data.LF = vector<double>({0.16,0.2});
    hrv1data.HF= vector<double>({0.35, 0.4});

    return hrv1data;


}

Hrv2Data Analysis::runHrv2()
{
    Hrv2Data hrv2data;
    hrv2data.hist_values = vector<int>({1,2,3,4,5,6,7,8,9,10,12,13,14,15,16,17,18,19,11});
    hrv2data.bin_centers = vector<double>({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19});
    hrv2data.hrv_index = double(1.2);
    hrv2data.tinn = double(2.4);
    hrv2data.SD1 = double(0.2);
    hrv2data.SD2 = double(0.5);
    hrv2data.poincareplot_x_axis = vector<double>({0.10, 0.15, 0.24, 0.26, 0.837});
    hrv2data.poincareplot_y_axis = vector<double>({0.915, 0.324, 0.426, 0.637, 0.118});
    hrv2data.centroid_x = double(0.6);
    hrv2data.centroid_y = double(0.6);

    return hrv2data;


}



