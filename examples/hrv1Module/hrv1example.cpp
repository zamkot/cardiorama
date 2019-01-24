#include <Hrv1Module.hpp>
#include <RPeaksModuleBase.hpp>
#include <vector>
#include <DataFrame.hpp>

//secret agent
class RPeaksModuleStub : public RPeaksModuleBase {

    RPeaksData results;
    std::vector<int> rPeaks;

public:
    RPeaksModuleStub(std::vector<int> rPeaks) : rPeaks{rPeaks} {}

    void configure(RPeaksConfig) override {}
    RPeaksData getResults() override { return {rPeaks}; }
};

int main(){

    using namespace std;
    vector<int> rpeaks = {11,368,656,940,1227,1513,1803,2038,2401,2704,2991,3278,3556,3856,4164,4462,4762,5054,5340,5630,5912,6208,6520,6821,7099,7386,7663,7951,8242,8532,8835,9139,9429,9705,9995,10280,10584,10892,11188,11479,11774,12059,12346,12643,12943,13262,13558,13840,14124,14416,14704,15005,15304,15605,15897,16181,16462,16751,17056,17351,17654,17944,18223,18507,18791,19078,19382,19687,19984,20267,20547,20831,21125,21421,21722,22023,22317,22601,22874,23157,23451,23754,24046,24338,24623,24910,25191,25483,25777,26082,26380,26668,26945,27231,27529,27830,28128,28424,28721,29010,29287,29574,29870,30179,30480,30772,31061,31341,31631,31924,32221,32524,32833,33123,33401,33685,33975,34271,34572,34863,35165,35453,35729,36009,36306,36602,36909,37208,37495,37777,38064,38349,38647,38948,39248,39541,39823,40092,40376,40675,40968,41266,41560,41848,42115,42410,42695,42995,43301,43598,43887,44168,44450,44737,45028,45321,45622,45920,46202,46478,46755,47036,47333,47628,47915,48201,48484,48760,49034,49322,49613,49918,50212,50487,50765,51050,51336,51625,51915,52210,52505,52778,53057,53335,53630,53921,54214,54502,54783,55058,55337,55620,55905,56203,56496,56779,57053,57327,57611,57898,58189,58483,58781,59074,59350,59625};
    RPeaksModuleStub rPeaksModule(rpeaks);
    Hrv1Module Hrv1Module(rPeaksModule);

    Hrv1Data results = Hrv1Module.getResults();

    cout << "y -> Power values:" << "\n";
    for(int i =0; i<results.P.size();i++){
        cout << results.P[i] << " "; 
    }

    cout << "\n"<< "x -> Frequency values:" << "\n";
    for(int i =0; i<results.F.size();i++){
        cout << results.F[i] << " "; 
    }

    cout << "\nTP: " << results.timeDomainResults.TP << "\n";
    cout << "pULF: " << results.timeDomainResults.pULF << "\n";
    cout << "pVLF: " << results.timeDomainResults.pVLF << "\n";
    cout << "pLF: " << results.timeDomainResults.pLF << "\n";
    cout << "pHF: " << results.timeDomainResults.pHF << "\n";
    cout << "LHHF: " << results.timeDomainResults.LHHF << "\n";
    cout << "mean RR: " << results.timeDomainResults.meanRR << "\n";
    cout << "SDNN: " << results.timeDomainResults.stdRR << "\n";
    cout << "RMSSD: " << results.timeDomainResults.rmsRR << "\n";
    cout << "NN50: " << results.timeDomainResults.sumNN50 << "\n";
    cout << "pNN50: " << results.timeDomainResults.pNN50 << "\n";
    cout << "SDANN: " << results.timeDomainResults.stdRR << "\n";
    cout << "SDANNidx: " << results.timeDomainResults.stdRR << "\n";
    cout << "SDSD: " << results.timeDomainResults.stdRR << "\n";

}

