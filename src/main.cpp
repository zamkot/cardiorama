#include <iostream>

int main() {
    std::cout << "To jest cardiorama. Jeszcze nic tu nie ma" << std::endl;
}



#include <iostream>
#include <vector>
#include <RPeaksModuleStub.hpp>
#include <HrvDfaModule.hpp>
#include <DataFrame.hpp>

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

#include <iostream>
#include <fstream>

#include <RPeaksModule.h>

void testfile(std::string filename) {// test modułu rpeaks
    EcgBaselineModule ecgBaselineModule;
    ecgBaselineModule.configure(filename);
    RPeaksModule rPeaksModuleTest(ecgBaselineModule);
    auto results = rPeaksModuleTest.getResults();

    std::ofstream outfile(std::__cxx11::string(ecgBaselineModule.getFilename()) + std::__cxx11::string("_results.csv"), std::ios_base::trunc);
    for(auto element: results.rpeaks) {
        std::cout << element << ",";
        outfile << element << ",";
    }
}

int main() {
    std::cout << "test modułu rpeaks" << std::endl;
    testfile("100.csv");
    testfile("102.csv");
    testfile("105.csv");
    testfile("106.csv");
    testfile("109.csv");
    testfile("115.csv");
    testfile("123.csv");
    testfile("220.csv");
    testfile("228.csv");
    testfile("234.csv");
}
