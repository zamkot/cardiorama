#include <RPeaksModuleBase.hpp>
#include <Datatypes.hpp>
#include <IOModule.hpp>
#include<armadillo>

class Hrv2Module::public Hrv2ModuleBase{

    RPeaksModuleBase& RPeaksModule;
    
    Hrv2Data results;
    Hrv2Config config;
	
    void runHrv2();
	
    arma::vec rrFiltering(arma:vec& rr);
    arma::vec createTriangularFunction(arma::uword N, arma::uword M, arma::uword index_of_maximum, 
                                       double maximum_value, arma::vec& bin_centers, int num_of_bins);
    double errorCalculation(arma::uvec& hist_values,arma::vec& triangular_values);
    arma::vec createRRVector(arma::vec& rpeaksindex, double sample_frequency);
	
public:

    Hrv2Module(RPeaksModuleBase&);
    Hrv2Data getResults() override;  
    void configure(Hrv2Config) override;
	
}
