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
    rpeaksdata.rpeaks = vector<int>({1,2,3,4,5,8,11,2,4,6,2,1,6,7,9,0,10});
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



