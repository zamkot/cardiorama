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

std::vector<int> heartClassModule::maxValue(std::vector<std::vector <int>> &signal)
{
    std::vector<int> maxes;
    maxes.resize(signal.size());

    std::transform(std::cbegin(signal), std::cend(signal), std::begin(maxes), [](const std::vector<int> &sig)
    {
        return *(std::max_element(std::cbegin(sig), std::cend(sig)));
    });
    return maxes;
}

std::vector<int> heartClassModule::minValue(std::vector<std::vector <int>> &signal)
{
    std::vector<int> mins;
    mins.resize(signal.size());
    
    std::transform(std::cbegin(signal),std::cend(signal),std::begin(mins), [](const std::vector<int> &sig)
    {
        return *(std::min_element(std::cbegin(sig), std::cend(sig)));
    });

    return mins;
}

std::vector<std::vector<int>> heartClassModule::ptsAboveTh(std::vector<std::vector<int>> &signal)
{
    std::vector<float> ths;
    ths.resize(signal.size());
    auto maxes = maxValue(signal);

    std::transform(std::cbegin(maxes), std::cend(maxes), std::begin(ths), [](const int& max){
        return 0.7*max;
    });

    std::vector<std::vector <int>> ptsAbove;
    ptsAbove.reserve(signal.size());

    std::transform(std::cbegin(signal),std::cend(signal),std::begin(ths),std::back_inserter(ptsAbove), [](const std::vector<int> &sig, const float &th)
    {
        std::vector<int> ptsA;
        std::copy_if(std::cbegin(sig),std::cend(sig),std::back_inserter(ptsA),[&](const int& value)
        {
            return value > th;
        });

        return ptsA;
    } );

    return ptsAbove;
    
}

std::vector <int> heartClassModule::qrsAuc(std::vector<std::vector<int>> &signal)
{
    std::vector<int> integrals;
    integrals.resize(signal.size());

    std::transform(std::cbegin(signal), std::cend(signal), std::begin(integrals), [](const std::vector<int> &sig)
    {
        return std::accumulate(std::cbegin(sig), std::cend(sig), 0);
    });
    return integrals;
}

std::vector <float> heartClassModule::qrsPosRatio(std::vector<std::vector<int>> &signal)
{
    std::vector<float> posRatios;
    posRatios.resize(signal.size());

    std::transform(std::cbegin(signal), std::cend(signal), std::begin(posRatios), [](const std::vector<int> &sig)
    {
        auto integral = std::accumulate(std::cbegin(sig), std::cend(sig), 0);
        auto posIntegral = std::accumulate(std::cbegin(sig), std::cend(sig), 0, [](int acc,int val)
        {
            return val>0?: acc+val: acc;
        });
        float ratio = static_cast<float>(posIntegral)/integral;

        return ratio;
    });
    return posRatios;
}

std::vector <float> heartClassModule::qrsNegRatio(std::vector<std::vector<int>> &signal)
{
    std::vector<float> negRatios;
    negRatios.resize(signal.size());

    std::transform(std::cbegin(signal), std::cend(signal), std::begin(negRatios), [](const std::vector<int> &sig)
    {
        auto integral = std::accumulate(std::cbegin(sig), std::cend(sig), 0);
        auto negIntegral = std::accumulate(std::cbegin(sig), std::cend(sig), 0, [](int acc,int val)
        {
            return val<0?: acc+val: acc;
        });
        float ratio = static_cast<float>(negIntegral)/integral;

        return ratio;
    });
    return negRatios;
}
std::vector <int> heartClassModule::aucComparsion(std::vector<std::vector<int>> &signal)
{
    std::vector<int> comparsion;
    auto posRatio = qrsPosRatio(signal);
    auto negRatio = qrsNegRatio(signal);
    for(int i = 0; i<posRatio.size(); ++i)
	{
		if(posRatio[i] >= negRatio[i])
		{
			comparsion.push_back(1);
		}
		else
		{
			comparsion.push_back(0);
		}
	}

    return comparsion;
}
std::vector<float> heartClassModule::kurtosis(std::vector<std::vector<int>> &signal)
{
    std::vector <float> kurtosisVec;
    int sum,n;
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

std::vector<float> heartClassModule::skewness(std::vector<std::vector<int>> &signal)
{
    std::vector <float> skewnessVec;
    int sum,n;
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
         for (int i = 0; i < n; i++)
	      {
		    skewness += (signal[i][j] - avg)*(signal[i][j] - avg)*(signal[i][j] - avg);
	      }
	    skewness = skewness/(n * S * S * S);

        skewnessVec.push_back(skewness)
         
     }
    
    return skewnessVec;
}

std::vector<std::vector<int>> heartClassModule::prepareSignal(std::vector<double> &rawSignal, std::vector<int> &rPeaks, int &samplingFrequency)
{
    int frame;
    std::vector<std::vector<double>> prepared;
    frame = 0.2*samplingFrequency;

    for (int i=0; i<rPeaks.size(); i++)
        {
            std::vector <double> slice(&rawSignal[rPeaks(i)-frames],&rawSignal[rPeaks(i)+frame]);
            prepared(i) = slice;
        }


    return prepared;
}