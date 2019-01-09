#include <iostream>
#include <vector>

#include <DataFrame.hpp>

std::vector<int> loadData(std::string path) {
    DataFrame df(path);
    std::cout << df << std::endl;
    std::vector<int> data = df.get<int>("Example Input Data", [](auto s){ return std::stoi(s); });

    return data;
}

void saveData(std::vector<int> data, std::string path) {
    DataFrame df;
    df.addColumn("Example Output Data", data, [](int number) {
        return std::to_string(number);
    });

    df.toCsv("output_data.csv");
}

std::vector<int> doCalculations(std::vector<int> data) {
    std::vector<int> results;
    for (auto number : data)
        results.push_back(number * 2);

    return results;
}

int main() {
    std::vector<int> inputData = loadData("input_data.csv");
    std::vector<int> outputData = doCalculations(inputData);
    saveData(outputData, "output_data.csv");
}
