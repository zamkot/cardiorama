#include <iostream>
#include <ModuleBase.hpp>
#include <TWavesModule.hpp>


class EcgBaselineModuleStub : public EcgBaselineModuleBase {
    Signal& ecgBaseline;

public:
    EcgBaselineModuleStub(Signal& ecgBaseline) : ecgBaseline{ ecgBaseline } {}

    Signal getResults() override {
        return ecgBaseline;
    }
};


class WavesModuleStub : public WavesModuleBase {
    WavesData& waves;

public:
    WavesModuleStub(WavesData& waves) : waves{ waves } {}

    WavesData getResults() override {
        return waves;
    }
};


int main() {

    Signal ecgBaseline;
    WavesData waves;
    TWavesData results;

    EcgBaselineModuleStub ecgBaselineModule(ecgBaseline);
    WavesModuleStub WavesModule(waves);
    TWavesModule tWavesModule(ecgBaselineModule, WavesModule);

    ecgBaseline.samples = {4, 4, 64, 11};
    waves.T_wektor = {1, 3};

    tWavesModule.invalidateResults();
    results = tWavesModule.getResults();


    TWavesData results = TWavesModule.getResults();

    // tu najlepiej wypisać wyniki albo zapisać je do pliku żeby sprawdzić czy są poprawne.

    // cout res lmao
}