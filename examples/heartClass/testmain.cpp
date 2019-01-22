#include <iostream>
#include <vector>
#include "heartClassModule.hpp"

#include <DataFrame.hpp>

std::vector<int> loadData(std::string path) {
    DataFrame df(path);
    std::vector<int> data = df.get<int>("Example Input Data", [](auto s){ return std::stoi(s); });

    return data;
}
std::vector<double> loadData1(std::string path) {
    DataFrame df(path);
    std::vector<double> data = df.get<double>("Example Input Data", [](auto s){ return std::stoi(s); });

    return data;
}

int main() {
    std::vector<int> rPeaks = loadData("r_peaks.csv");
    std::vector<double> rawSignal = loadData1("sygnal.csv");

    heartClassModule classfier = heartClassModule(rawSignal, rPeaks, 360);
}
