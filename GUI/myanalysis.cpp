#include "../include/AnalysisInterface.hpp"
#include<iostream>
#include <QDebug>
using namespace std;

void Analysis::loadFile(std::string path)
{
    qDebug()<<QString("Otwieram plik ");
    qDebug()<<QString::fromStdString(path);

}

void Analysis::sendRPeaksConfig(RPeaksConfig)
{
    qDebug()<<QString("Wybrano metodę detekcji R-peaksów");
}

Signal Analysis::runEcgBaseline()
{
    return {};
}

RPeaksData Analysis::runRPeaks()
{
    RPeaksData rpeaksdata;
    rpeaksdata.rpeaks = vector<int>({1,2,3,4,5,8});
    return rpeaksdata;
}

WavesData Analysis::runWaves()
{
    WavesData wavesdata;
    wavesdata.qrsOnset = vector<int>({5,6,7,8});
    wavesdata.qrsEnd= vector<int>({9,10,11,12});
    wavesdata.tEnd = vector<int>({13,14,15,16});
    wavesdata.pOnset = vector<int>({17,18,19,20});
    wavesdata.pEnd = vector<int>({21,22,23,24});
    return wavesdata;
}



