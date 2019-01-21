#include <armadillo>
#include <HrvDfaModule.hpp>

HrvDfaModule::HrvDfaModule(RPeaksModuleBase &rPeaksModule) : rPeaksModule{rPeaksModule}
{
    rPeaksModule.attach(this);
}

HrvDfaData HrvDfaModule::getResults()
{
    if (!resultsValid())
    {
        runHrvDfa();
    }

    return results;
}

void HrvDfaModule::runHrvDfa()
{
    using namespace std;
    using namespace arma;

    vector<int> rpeaks = rPeaksModule.getResults().rpeaks;
    vec tachogram = rpeaks2tachogram(rpeaks);

    vec window_sizes(31);
    vec fluctuation(31);
    vec y;
    vec x;

    int trimmed_tachogram_length = tachogram.n_rows;
    int tachogram_length = tachogram.n_rows;

    //Checking size of tachogram
    for (int window_size = 4; window_size <= 64; window_size = window_size + 2)
    {
        
        window_sizes((window_size - 4) / 2) = window_size;
        mat trimmed_tachogram;
        if (window_size < trimmed_tachogram_length)
        {
            trimmed_tachogram_length -= trimmed_tachogram_length % window_size;
        }
        trimmed_tachogram = tachogram.rows(0, trimmed_tachogram_length - 1);
        
        //Integration
        x = cumsum(trimmed_tachogram, 0);
        mat tachogram_diff(trimmed_tachogram_length, 1, fill::zeros);

        for (int a = 0; a < trimmed_tachogram_length; a++)
        {

            mat mean_tachogram = mean(trimmed_tachogram);

            mat sample = trimmed_tachogram.row(a);

            mat tmp = (sample - mean_tachogram);
            tachogram_diff(a, 0) = tmp(0, 0);
        }

        y = cumsum(tachogram_diff, 0);

        // polyfit/polyval

        int windows_count = floor(trimmed_tachogram_length / (window_size));

        int a = 0;
        int b = window_size - 1;

        mat matrix_polyfit(windows_count, 2);
        vec y_fitted(trimmed_tachogram_length);

        int i = 0;
        int j = 0;
        while (a < trimmed_tachogram_length)
        {

            matrix_polyfit.row(i) = trans(polyfit(x.rows(a, b), y.rows(a, b), 1));

            y_fitted.rows(j, j + window_size - 1) = (polyval(matrix_polyfit.row(i), x.rows(a, b)));

            b = min(b + window_size, trimmed_tachogram_length - 1);
            a = a + window_size;

            i++;
            j = j + window_size;
        }

        fluctuation((window_size - 4) / 2) = as_scalar(sqrt(1.0 / tachogram_length * sum(square(y_fitted - y))));
    }

    // Fluctuation

    vec log_window_sizes = log(window_sizes);
    vec log_fluctuation = log(fluctuation);

    vec alfa1 = polyfit(log_window_sizes.rows(0, 6), log_fluctuation.rows(0, 6), 1);
    vec alfa2 = polyfit(log_window_sizes.rows(6, 30), log_fluctuation.rows(6, 30), 1);

    vec line_alfa1 = polyval(alfa1, log_window_sizes.rows(0, 6));
    vec line_alfa2 = polyval(alfa2, log_window_sizes.rows(6, 30));

    results = {
        arma2std(log_window_sizes),
        arma2std(log_fluctuation),
        arma2std(line_alfa1),
        arma2std(line_alfa2)};
}

std::vector<double> HrvDfaModule::arma2std(arma::vec vec1)
{
    return arma::conv_to<std::vector<double>>::from(vec1);
}

arma::vec HrvDfaModule::rpeaks2tachogram(std::vector<int> rpeaks)
{
    using namespace arma;
    std::vector<double> rpeaks_double(rpeaks.begin(), rpeaks.end());
    vec rpeaksindex(rpeaks_double);
    double sampling_frequency = 320;
    vec rr = createRRVector(rpeaksindex, sampling_frequency);
    return rr;
}

arma::vec HrvDfaModule::createRRVector(arma::vec rpeaksindex, double sampling_frequency)
{
    using namespace arma;
    double deltaT = 1 / sampling_frequency;
    vec rpeaks = rpeaksindex * deltaT;
    vec vector1 = rpeaks.rows(1, rpeaksindex.n_elem - 1);
    vec vector2 = rpeaks.rows(0, rpeaksindex.n_elem - 2);
    vec rr = vector1 - vector2;
    return rr;
}
