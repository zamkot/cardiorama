#pragma once

#include <ModuleBase.hpp>
#include <HeartClassModuleBase.hpp>

#include <EcgBaselineModuleBase.hpp>
#include <RPeaksModuleBase.hpp>

#include <dlib/svm_threaded.h>

const int N_FEATURES = 9;
const int SAMPLING_RATE = 360;
const int WINDOW_SIZE = 0.2 * SAMPLING_RATE;
const std::string MODEL_PATH = "../../model.dat";

typedef dlib::matrix<double, N_FEATURES, 1> samplesType;  
typedef dlib::one_vs_one_trainer<dlib::any_trainer<samplesType> > ovo_trainer;
typedef dlib::radial_basis_kernel<samplesType> rbf_kernel;

struct cardioFeatures{
    std::vector<double> maxValue;
    std::vector<double> minValue;
    std::vector<double> ptsAboveTh;
    std::vector<double> qrsAuc;
    std::vector<double> qrsPosRatio;
    std::vector<double> qrsNegRatio;
    std::vector<double> aucComparsion;
    std::vector<double> kurtosis;
    std::vector<double> skewness;
};


class HeartClassModule : public HeartClassModuleBase {

    EcgBaselineModuleBase& ecgBaselineModule;
    RPeaksModuleBase& rPeaksModule;

    // results
    HeartClassData results;

    // atruibutes
    int samplingRate = SAMPLING_RATE;
    int nFeatures = N_FEATURES;
    int windowSize = WINDOW_SIZE;

    std::vector<samplesType> samples;
    std::vector<double> labels;
    dlib::one_vs_one_decision_function<ovo_trainer> model;  
    bool modelFlag = false;

    // descriptor methods
    std::vector<std::vector<double>> prepareSignal(std::vector<double>&, std::vector<int>&, int&);
    std::vector<double> maxValue(std::vector<std::vector<double>>&);
    std::vector<double> minValue(std::vector<std::vector<double>>&);
    std::vector<double> ptsAboveTh(std::vector<std::vector<double>>&);
    std::vector<double> qrsAuc(std::vector<std::vector<double>>&);
    std::vector<double> qrsPosRatio(std::vector<std::vector<double>>&);
    std::vector<double> qrsNegRatio(std::vector<std::vector<double>>&);
    std::vector<double> aucComparsion(std::vector<std::vector<double>>&);
    std::vector<double> kurtosis(std::vector<std::vector<double>>&);
    std::vector<double> skewness(std::vector<std::vector<double>>&);
    cardioFeatures calculateFeatures(std::vector<std::vector<double>>& );   
    std::vector<std::vector<double>> transposeFeaturesVector(std::vector<std::vector<double>>& );
    std::vector<std::vector<double>> featuresToVector(cardioFeatures& );

    // calassfication methods 
    std::vector<samplesType> prepareFeatures(std::vector<std::vector<double>>& features);
    
    // other
    void runHeartClass();

public:

    // constructor 
    HeartClassModule(EcgBaselineModuleBase&, RPeaksModuleBase&);
    
    // classification methods
    void addSamples(std::vector<std::vector<double>>& features);
    void addLabels(std::vector<double>& labels);   
    void trainSVM(double gammaParameter);
    void saveModel(std::string path);
    void loadModel(std::string path);
    std::vector<double> classify(std::vector<std::vector<double>>& features);

    // virtual override
    HeartClassData getResults() override;
};
