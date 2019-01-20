#include <armadillo>

#include "DFAModuleBase.hpp"
#include "RPeaksModuleBase.hpp"
#include "Datatypes.hpp"

class DFAModule : public DFAModuleBase {

    RPeaksModuleBase& rPeaksModule;

    DFAData results;

    void runDFA();

    std::vector<double> arma2std(arma::vec vec);
    arma::vec rpeaks2tachogram(std::vector<int> rpeaks);
    arma::vec createRRVector(arma::vec& rpeaksindex, double sampling_frequency);
    arma::vec rrFiltering (arma::vec& rr);

public:

    DFAModule(RPeaksModuleBase&);

    DFAData getResults() override;
};