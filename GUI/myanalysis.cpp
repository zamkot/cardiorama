#include "../include/AnalysisInterface.hpp"
#include<iostream>
#include <QDebug>
using namespace std;

void Analysis::loadFile(std::string path)
{
    qDebug()<<QString("File opened ");
    qDebug()<<QString::fromStdString(path);

}

void Analysis::sendRPeaksConfig(RPeaksConfig)
{
    qDebug()<<QString("The R-Peaks detection method was choosen");
}

Signal Analysis::runEcgBaseline()
{
    return {};
}

RPeaksData Analysis::runRPeaks()
{
    RPeaksData rpeaksdata;
   // rpeaksdata.rpeaks = vector<int>({1,2,3,4,5,8,11,2,4,6,2,1,6,7,9,0,10});
    rpeaksdata.rpeaks = vector<int>({2,5,8,12,15,18,22,25,28,32,35,38,42,45,48,52,55,58,62,65,68,72,75,78,82,85,88,92,95,98,
                                    102,105,108,112,115,118,122,125,128,132,135,138,142,145,148,152,155,158,162,165,168,172,175,178,182,185,188,192,195,198,
                                    202,205,208,212,215,218,222,225,228,232,235,238,242,245,248,252,255,258,262,265,268,272,275,278,282,285,288,292,295,298
                                    });
    return rpeaksdata;
}

WavesData Analysis::runWaves()
{
    WavesData wavesdata;
    wavesdata.qrsOnset = vector<int>({5,6,7,8,2,4,6,2,1,6,7,9,0,10,7,9,0,10});
    wavesdata.qrsEnd= vector<int>({9,10,11,12,2,4,6,2,1,6,7,9,0,10,7,9,0,10});
    wavesdata.tEnd = vector<int>({13,14,15,16,2,4,6,2,1,6,7,9,0,10,7,9,0,10});
    wavesdata.pOnset = vector<int>({17,18,19,20,2,4,6,2,1,6,7,9,0,10,7,9,0,10});
    wavesdata.pEnd = vector<int>({21,22,23,24,2,4,6,2,1,6,7,9,0,10,7,9,0,10});
    return wavesdata;
}



