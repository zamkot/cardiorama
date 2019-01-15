#include <iostream>
#include <vector>

#include <DataFrame.hpp>

std::vector<int> loadData(std::string path) {
    DataFrame df(path);
    std::cout << df << std::endl;
    std::vector<int> sygnal = df.get<int>("", [](auto s){ return std::stoi(s); });

    return sygnal;
}

std::vector<int> loadData(std::string path) {
    DataFrame df(path);
    std::cout << df << std::endl;
    std::vector<int> R_peaks = df.get<int>("", [](auto s){ return std::stoi(s); });

    return R_peaks;
}

void saveData(std::vector<int> data, std::string path) {
    DataFrame df;
    df.addColumn("Example Output Data", data, [](int number) {
        return std::to_string(number);
    });

    df.toCsv("output_data.csv");
}

std::vector<int> doCalculations(std::vector<int> sygnal, std::vector<int> r_peaks) {
    std::vector<int> results;
    for (auto number : data)
        

    return results;
}

int main() {
    std::vector<int> sygnal = loadData("sygnal.csv");
    std::vector<int> r_peaks = loadData("r_peaks.csv");
    std::vector<int> outputData = doCalculations(sygnal,r_peaks);
    saveData(outputData, "output_data.csv");
}