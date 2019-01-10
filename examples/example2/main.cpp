#include <iostream>
#include <vector>

#include <DataFrame.hpp>

struct WavesData {
    std::vector<int> data1;
    std::vector<double> data2;
};

struct OutputData {
    std::vector<int> data1;
    std::vector<double> data2;
    std::vector<double> output;
};

WavesData loadData(std::string path) {
    DataFrame df(path);

    std::vector<int> data1 = df.get<int>("Seria 1", [](auto s){ return std::stoi(s); });
    std::vector<double> data2 = df.get<double>("Seria 2", [](auto s){ return std::stod(s); });

    return {data1, data2};
}

void saveData(OutputData data, std::string path) {
    DataFrame df;



    df.addColumn("Seria 1", data.data1, [](int number) {
        return std::to_string(number);
    });

    df.addColumn("Seria 2", data.data2, [](double number) {
        return std::to_string(number);
    });

    df.addColumn("Ouput", data.output, [](double number) {
        return std::to_string(number);
    });

    df.toCsv("output_data.csv");
}

OutputData doCalculations(WavesData data) {
    std::vector<double> output;

    auto data1 = data.data1;
    auto data2 = data.data2;

    for (int i = 0; i < data1.size(); i++) {
        output.push_back(static_cast<double>(data1[i]) + data2[i]);
    }

    OutputData od;
    od.data1 = data1;
    od.data2 = data2;
    od.output = output;

    return od;
}

int main() {
    WavesData inputData = loadData("input_data.csv");

    OutputData outputData = doCalculations(inputData);

    saveData(outputData, "output_data.csv");
}
