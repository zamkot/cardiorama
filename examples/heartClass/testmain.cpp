#include <iostream>
#include <vector>
#include "heartClassModule.hpp"

#include <DataFrame.hpp>

std::vector<int> loadData(std::string path) {
    DataFrame df(path);
    std::cout << df << std::endl;
    std::vector<int> data = df.get<int>("Example Input Data", [](auto s){ return std::stoi(s); });

    return data;
}

int main() {
    std::vector<int> rPeaks = loadData("r_peaks.csv");
    std::vector<int> rawSignal = loadData("sygnal.csv");

    heartClassModule cycki(rawSignal,rPeaks,360);

    cycki.getWszystko();


}
