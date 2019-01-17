#include <RPeaksModuleBase.hpp>
#include <Datatypes.hpp>
#include <IOModule.hpp>
#include <armadillo>
#include <Hrv1ModuleBase.hpp>

class Hrv1Module : public Hrv1ModuleBase{

    RPeaksModuleBase& RPeaksModule;
    
    Hrv1Data results;
	
    void runHrv1();
    arma::vec createRRVector(arma::vec& rPeaksIndex, double samplingFrequency);
    arma::vec adjustRR(arma::vec& data);
    arma::vec periodogramLombScargle(arma::vec& tk, arma::vec& data, arma::vec& F);
    TimeDomainVar timeDomain(arma::vec& F, arma::vec& data, arma::vec& tk);
    
public:

    Hrv1Module(RPeaksModuleBase&);
    Hrv1Data getResults() override;  
	
};
