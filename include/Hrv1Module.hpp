#pragma once
#include <Hrv1ModuleBase.hpp>
#include <RPeaksModuleBase.hpp>
#include <IOModule.hpp>
#include <armadillo>

class Hrv1Module : public Hrv1ModuleBase{

    RPeaksModuleBase& RPeaksModule;
    Hrv1Data results;
	
    void runHrv1();
    arma::vec createRRVector(std::vector<double> &rPeaksOut, double samplingFrequency);
    arma::vec adjustRR(arma::vec& data);
    arma::vec periodogramLombScargle(arma::vec& tk, arma::vec& data, arma::vec& F);
    TimeDomainVar timeDomain(arma::vec& F, arma::vec& P, arma::vec& data, arma::vec& tk);
    
public:

    Hrv1Module(RPeaksModuleBase&);
    Hrv1Data getResults() override;

};

