#include <armadillo>

#include "HrvDfaModuleBase.hpp"
#include "RPeaksModuleBase.hpp"
#include "Datatypes.hpp"

class HrvDfaModule : public HrvDfaModuleBase {

    RPeaksModuleBase& rPeaksModule;

    HrvDfaData results;

    void runHrvDfa();

    std::vector<double> arma2std(arma::vec vec);
    arma::vec rpeaks2tachogram(std::vector<int> rpeaks);
    arma::vec createRRVector(arma::vec rpeaksindex, double sampling_frequency);
    

public:

    HrvDfaModule(RPeaksModuleBase&);

    HrvDfaData getResults() override;
};