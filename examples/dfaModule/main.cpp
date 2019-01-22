#include <armadillo>
using namespace std;
using namespace arma;

int main()
{

    mat signal;
    signal.load("chf206.csv", raw_ascii);
    mat tachogram = signal.rows(0, 1279);

    vec window_sizes(31);
    vec fluctuation(31);
    mat y;
    mat x;

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
        // int len_x = x.n_rows;

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

    mat log_window_sizes = log(window_sizes);
    mat log_fluctuation = log(fluctuation);

    vec alfa1 = polyfit(log_window_sizes.rows(0, 6), log_fluctuation.rows(0, 6), 1);
    vec alfa2 = polyfit(log_window_sizes.rows(6, 30), log_fluctuation.rows(6, 30), 1);

    vec line_alfa1 = polyval(alfa1, log_window_sizes.rows(0, 6));
    vec line_alfa2 = polyval(alfa2, log_window_sizes.rows(6, 30));
}
