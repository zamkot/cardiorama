#include <DataFrame.hpp>


// Let's define some data structures to work with
struct TwoVectors {
    std::vector<int> samplesA;
    std::vector<int> samplesB;
};

enum class PeakType { ONE, TWO, THREE, NONE };

struct SingleMap {
    std::map<int, PeakType> peaks;
};


// Shows how to encode any set of iterable data structures into a printable and exportable dataframe
DataFrame dataFrameExample() {
    TwoVectors twoVectors{{1, 2, 3, 4}, {9, 8, 7}};

    SingleMap singleMap{{
        {1, PeakType::ONE},
        {2, PeakType::TWO},
        {3, PeakType::THREE},
        {4, PeakType::ONE},
        {5, PeakType::ONE},
    }};

    DataFrame df;

    // Containters holding numeric values can be passed just like that
    df.addColumn("Integers A", twoVectors.samplesA);

    // std::map holds elements of type std::pair. We need to specify how to convert them into strings
    df.addColumn("Map Keys", singleMap.peaks, [](auto element) {
        return std::to_string(element.first);
    });

    // std::to_string can't take PeakType as argument. 
    // We need to go a step further and translate enum values into strings.
    df.addColumn("Map Values", singleMap.peaks, [](auto element) {
        switch (element.second) {
            case PeakType::ONE   : return "ONE";   break;
            case PeakType::TWO   : return "TWO";   break;
            case PeakType::THREE : return "THREE"; break;
            default              : return "NONE";
        }
    });

    // You can use the callback to modify the values on the run if you need to.
    // I don't know why you'd want that.
    df.addColumn("Changed Vector", twoVectors.samplesB, [](int element) {
        return std::to_string(-2 * element);
    });

    return df;
}

void printDataFrame() {
    auto df = dataFrameExample();

    std::cout << df << std::endl;
}

void exportDataFrame() {
    auto df = dataFrameExample();

    df.toCsv("~/dataframe_example.csv");
}

void decodeDataFrame() {
    auto df = dataFrameExample();

    // DataFrames can be decoded in a simillar fashion to how we encoded them. 
    // DataFrame::get() takes as arguments the name of a column we want to extract
    // and a callback converting strings to the original type.
    // We need to explicitly indicate the expected datatype df.get<**here**>

    auto peakNumbers = df.get<int>("Map Keys", [](auto s){ return std::stoi(s); });
    
    auto peakLabels = df.get<PeakType>("Map Values", [](auto s) {
        if (s == "ONE"  ) return PeakType::ONE;
        if (s == "TWO"  ) return PeakType::TWO;
        if (s == "THREE") return PeakType::THREE;
        return PeakType::NONE;
    });

    // now we have a std::vector<int> peakNumbers and std::vector<PeakType> peakLabels.
    // lets put them back together into a std::map
    std::map<int, PeakType> data;
    for (int i = 0; i < peakNumbers.size(); i++)
        data[peakNumbers[i]] = peakLabels[i];


    // Let's print this out to make sure we've done things correctly
    for (auto element : data) {
        std::cout << element.first << ": ";

        switch (element.second) {
            case PeakType::ONE   : std::cout << "ONE";   break;
            case PeakType::TWO   : std::cout << "TWO";   break;
            case PeakType::THREE : std::cout << "THREE"; break;
            default              : std::cout << "NONE";
        }

        std::cout << std::endl;
    }
}

void importDataFrame() {
    DataFrame df("~/dataframe_example.csv");
    std::cout << df << std::endl;
}

int main() {
    // printDataFrame();
    // exportDataFrame();
    // decodeDataFrame();
    importDataFrame();
}
