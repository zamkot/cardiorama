#include <iostream>
#include <vector>
#include <HrvDfaModule.hpp>
#include <DataFrame.hpp>

class RPeaksModuleStub : public RPeaksModuleBase {

    RPeaksData results;
    std::vector<int> rPeaks;


public:

    RPeaksModuleStub(std::vector<int> rPeaks) : rPeaks{rPeaks} {}

    RPeaksData getResults() override { return {rPeaks}; }
};


int main(int argc, char** argv) {
    using namespace std;

    if (argc != 2) {
        cout << "Invalid number of arguments" << endl;
        return 1;
    }

    string path = argv[1];
    DataFrame df_in(path);
    
    vector<int> rpeaks = df_in.get<int>("Rpeaks", [](string s){ return std::stoi(s); });
    
    RPeaksModuleStub rPeaksModule(rpeaks);
    HrvDfaModule hrvDfaModule(rPeaksModule);

    HrvDfaData hrvDfaData = hrvDfaModule.getResults();
    
    DataFrame df_out;

    df_out.addColumn("log_window_sizes", hrvDfaData.log_window_sizes);
    df_out.addColumn("log_fluctuation", hrvDfaData.log_fluctuation);
    df_out.addColumn("line_alfa1", hrvDfaData.line_alfa1);
    df_out.addColumn("line_alfa2", hrvDfaData.line_alfa2);

    df_out.toCsv("DFA_output.csv");
}