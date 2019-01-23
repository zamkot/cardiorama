#include <iostream>
#include <EcgBaselineModule.hpp>
#include <IOModuleBase.hpp>
#include <DataFrame.hpp>
#include <RPeaksModule.hpp>


class IOModuleStub : public IOModuleBase
{
public:
    std::vector<double> getRawSignal() override {
        DataFrame df("input_signal.csv");
        return df.get<double>("raw_signal", [](std::string s){ return std::stod(s); });
    }
};

void saveData(RPeaksData data, std::string path) {
    DataFrame df;
    df.addColumn("rpeaks", data.rpeaks, [](double number) {
        return std::to_string(number);
    });

    df.toCsv(std::move(path));
}

int main() {
    IOModuleStub ioModule;
    EcgBaselineModule ecgBaselineModule(ioModule);
    ecgBaselineModule.configure(EcgBaselineConfig{EcgBaselineConfig::Algorithm::BUTTERWORTH});

    RPeaksModule rPeaksModule(ecgBaselineModule);
    rPeaksModule.configure(RPeaksConfig{RPeaksConfig::Algorithm::PAN_TOMPKINS, 360});

    saveData(rPeaksModule.getResults(), "rpeaks.csv");
    std::cout << "RPEAKS TEST" << std::endl;
}

