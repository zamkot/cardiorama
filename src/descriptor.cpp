#include <iostream>
#include <numeric>
#include <stdio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <armadillo>
#include <iterator>
#include "heartClassBase.hpp"
#include "heartClassModule.hpp"

// ------PRIVATE---------------

std::vector<double> heartClassModule::maxValue(std::vector<std::vector <double>> &signal)
{
    std::vector<double> maxes;
    maxes.resize(signal.size());

    std::transform(std::cbegin(signal), std::cend(signal), std::begin(maxes), [](const std::vector<double> &sig)
    {
        return *(std::max_element(std::cbegin(sig), std::cend(sig)));
    });
    return maxes;
}

std::vector<double> heartClassModule::minValue(std::vector<std::vector <double>> &signal)
{
    std::vector<double> mins;
    mins.resize(signal.size());
    
    std::transform(std::cbegin(signal),std::cend(signal),std::begin(mins), [](const std::vector<double> &sig)
    {
        return *(std::min_element(std::cbegin(sig), std::cend(sig)));
    });

    return mins;
}

std::vector<std::vector<double>> heartClassModule::ptsAboveTh(std::vector<std::vector<double>> &signal)
{
    std::vector<double> ths;
    ths.resize(signal.size());
    auto maxes = maxValue(signal);

    std::transform(std::cbegin(maxes), std::cend(maxes), std::begin(ths), [](const double& max){
        return 0.7*max;
    });

    std::vector<std::vector <double>> ptsAbove;
    ptsAbove.reserve(signal.size());

    std::transform(std::cbegin(signal),std::cend(signal),std::begin(ths),std::back_inserter(ptsAbove), [](const std::vector<double> &sig, const double &th)
    {
        std::vector<double> ptsA;
        std::copy_if(std::cbegin(sig),std::cend(sig),std::back_inserter(ptsA),[&](const double& value)
        {
            return value > th;
        });

        return ptsA;
    } );

    return ptsAbove;
    
}

std::vector <double> heartClassModule::qrsAuc(std::vector<std::vector<double>> &signal)
{
    std::vector<double> integrals;
    integrals.resize(signal.size());

    std::transform(std::cbegin(signal), std::cend(signal), std::begin(integrals), [](const std::vector<double> &sig)
    {
        return std::accumulate(std::cbegin(sig), std::cend(sig), 0);
    });
    return integrals;
}

std::vector <double> heartClassModule::qrsPosRatio(std::vector<std::vector<double>> &signal)
{
    std::vector<double> posRatios;
    posRatios.resize(signal.size());

    std::transform(std::cbegin(signal), std::cend(signal), std::begin(posRatios), [](const std::vector<double> &sig)
    {
        auto integral = std::accumulate(std::cbegin(sig), std::cend(sig), 0);
        auto posIntegral = std::accumulate(std::cbegin(sig), std::cend(sig), 0, [](double acc,double val)
        {
            return val>0?: acc+val : acc;
        });
        float ratio = static_cast<float>(posIntegral)/integral;

        return ratio;
    });
    return posRatios;
}

std::vector <double> heartClassModule::qrsNegRatio(std::vector<std::vector<double>> &signal)
{
    std::vector<double> negRatios;
    negRatios.resize(signal.size());

    std::transform(std::cbegin(signal), std::cend(signal), std::begin(negRatios), [](const std::vector<double> &sig)
    {
        auto integral = std::accumulate(std::cbegin(sig), std::cend(sig), 0);
        auto negIntegral = std::accumulate(std::cbegin(sig), std::cend(sig), 0, [](double acc,double val)
        {
            return val<0?: acc+val: acc;
        });
        float ratio = static_cast<float>(negIntegral)/integral;

        return ratio;
    });
    return negRatios;
}
std::vector <int> heartClassModule::aucComparsion(std::vector<std::vector<double>> &signal)
{
    auto posRatios = qrsPosRatio(signal); //vector<float>
    auto negRatios = qrsNegRatio(signal); //vector<float>
    std::vector<double> comparsion(posRatios.size());

    std::transform(std::cbegin(posRatios), std::cend(posRatios),std::cbegin(negRatios), std::begin(comparison), 
        [](const int& posRatio, const int& negRatio){
        return posRatio >= negRatio ? 1 : 0;
    });

     std::vector<int> comparsion1(comparsion.begin(), comparsion.end());

     return comparsion1;
}
std::vector<double> heartClassModule::kurtosis(std::vector<std::vector<double>> &signal)
{
    std::vector <double> kurtosisVec;
    double sum,n;
    double var, S, kurtosis,avg;
    for (int i = 0; i < signal.size(); i++)
     {

         n = signal[i].size();
         sum = accumulate(signal[i].begin(), signal[i].end(), 0);   
         avg = (double)sum/n; 
         
         for (int j = 0; j < n ; j++) 
          {
             var += (signal[i][j] - avg)*(signal[i][j] - avg);
	            
          }   
          var = (double)(var)/(n - 1);  
          S = (double)sqrt(var);
         for (int j = 0; j < n; j++)
          {
            kurtosis += (signal[i][j] - avg)*(signal[i][j] - avg)*(signal[i][j] - avg)*(signal[i][j] - avg);
          }
         kurtosis = kurtosis/(n*S*S*S*S);
         kurtosis -= 3;
    
        kurtosisVec.push_back(kurtosis);
     }
    
    return kurtosisVec;

}

std::vector<double> heartClassModule::skewness(std::vector<std::vector<double>> &signal)
{
    std::vector <double> skewnessVec;
    double sum,n;
    double var,skewness, S,avg;
    for (int i = 0; i < signal.size(); i++)
     {

         n = signal[i].size();
         sum = accumulate(signal[i].begin(), signal[i].end(), 0);   
         avg = (double)sum/n; 
         
         for (int j = 0; j < n ; j++) 
          {
             var += (signal[i][j] - avg)*(signal[i][j] - avg);
	            
          }   
          var = (double)(var)/(n - 1);  
          S = (double)sqrt(var);
         for (int j = 0; j < n; j++)
	      {
		    skewness += (signal[i][j] - avg)*(signal[i][j] - avg)*(signal[i][j] - avg);
	      }
	    skewness = skewness/(n * S * S * S);

        skewnessVec.push_back(skewness);
         
     }
    
    return skewnessVec;
}

std::vector<std::vector<double>> heartClassModule::prepareSignal(std::vector<double> &rawSignal, std::vector<int> &rPeaks, int &samplingFrequency)
{
    int frames;
    std::vector<std::vector<double>> prepared;
    frames = 0.2*samplingFrequency;

    for (int i=0; i<rPeaks.size(); i++)
        {
            std::vector <double> slice((rawSignal.data())[rPeaks[i]-frames],(rawSignal.data())[rPeaks[i]-frames]);
            prepared[i] = slice;
        }


    return prepared;
}


// ------------------------PUBLIC------------------------------------
heartClassModule::heartClassModule(std::vector<double> rawSignal,std::vector<int> rPeaks, int sF){
        this->samplingFrequency = sF;
        this->signal = prepareSignal(rawSignal, rPeaks, samplingFrequency);
        
 }

int heartClassModule::getResults(){
    return 0;
}

void heartClassModule::notify()
{
    /****/
}
void heartClassModule::invalidateResults()
{
    /****/
}
void heartClassModule::validateResults()
{
    /****/
}
void heartClassModule::attach(ModuleBase* observer)
{
    /****/
}
void heartClassModule::setFeatures(){
    this->signalFeatures.maxValue = maxValue(signal);
    this->signalFeatures.minValue = minValue(signal);
    this->signalFeatures.ptsAboveTh = ptsAboveTh(signal);
    this->signalFeatures.qrsAuc = qrsAuc(signal);
    this->signalFeatures.qrsPosRatio = qrsPosRatio(signal);
    this->signalFeatures.qrsNegRatio = qrsNegRatio(signal);
    this->signalFeatures.aucComparsion = aucComparsion(signal);
    this->signalFeatures.kurtosis = kurtosis(signal);
    this->signalFeatures.skewness = skewness(signal);
}

    

    