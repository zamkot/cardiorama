#include <iostream>
#include <EcgBaselineModule.hpp>
#include <IOModuleBase.hpp>
#include <DataFrame.hpp>


class IOModuleStub : public IOModuleBase 
{
public:
    std::vector<double> getRawSignal() override {
        DataFrame df("input_signal.csv");
        return df.get<double>("raw_signal", [](std::string s){ return std::stod(s); });
    }

    void setInputFileName(std::string) override {};
};

void saveData(EcgBaselineData data, std::string path) {
    DataFrame df;
    df.addColumn("filtered_ecg", data.samples, [](auto number) {
        return std::to_string(number);
    });

    df.toCsv("filtered_ecg.csv");
}

int main() {
    IOModuleStub ioModule;
    EcgBaselineModule ecgBaselineModule(ioModule);

    ecgBaselineModule.configure(EcgBaselineConfig{EcgBaselineConfig::Algorithm::BUTTERWORTH});
    EcgBaselineData filtered = ecgBaselineModule.getResults();
    
    saveData(filtered, "filtered_ecg.csv");
}
