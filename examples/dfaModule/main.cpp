#include <iostream> 
#include <climits> 
#include <armadillo> 
#include <typeinfo>
using namespace std;
using namespace arma;

int main() {

    mat nsr001;
    nsr001.load("chf206.csv", raw_ascii); // wczytanie tachogramu
    mat tachogram = nsr001.rows(0, 659); // pobranie pewnej ilości próbek

    //int m = 4; // tworzenie wektora z oknami
    vec M(31);
    vec F(31);
    mat y_p3;
    mat y;
    mat x;

    int k = tachogram.n_rows;
    int length = tachogram.n_rows;
    for (int m = 4; m <= 64; m = m + 2) {
       
        M((m - 4) / 2) = m;
        //sprawdzenie rozmiaru tachogramu
        mat tachogram2;
        if (m < k) {
            int modulo = k % m;

            unsigned int win = k - modulo; // wyznaczenie granicy okna
            tachogram2 = tachogram.rows(0, win - 1); // wyznaczenie zakresu próbek (1:granica okna)
            k = tachogram2.n_rows;
        } else {
            unsigned int win = k;
            tachogram2 = tachogram.rows(0, win - 1);
        }
        //całkowanie
        x = cumsum(tachogram2, 0); // skumulowana suma

        mat z;
        mat xos(k, 1, fill::zeros);

        for (int a = 0; a < k; a++) {

            mat mean_tachogram = mean(tachogram2);

            mat pr = tachogram2.row(a);

            mat z = (pr - mean_tachogram);
            xos(a, 0) = z(0, 0);

        }

        y = cumsum(xos, 0);

        //dopasowanie krzywej polyfit/polyval
        int len_x = x.n_rows;

        int q = floor(len_x / (m));

        int a = 0;
        int b = m - 1;

        vec X(len_x);
        vec y2(len_x);
        mat matrix_polyfit(170, 2);
        vec y_p3(len_x);

        // for( int i =0; i<q-1; i++ ){ // nie może tak być, pętla powinna się wykonać tyle ile wynosi q
        //	cout <<"i"<<i<<" q "<<q<<" m: "<<m<<endl;
        // 
        //     y2.rows(a,b) = y.rows(a,b);

        //     X.rows(a,b)= x.rows(a,b);
        //	matrix_polyfit = polyfit(X,y2,1);
        //  y_p3= polyval(matrix_polyfit,X);
        //

        // b = b + m;
        //  a = a + m;

        // } 
        int i = 0;
        while (a < len_x) {

            y2.rows(a, b) = y.rows(a, b);

            X.rows(a, b) = x.rows(a, b);

            matrix_polyfit.row(i) = trans(polyfit(X.rows(a, b), y2.rows(a, b), 1));
            vec prob = trans(matrix_polyfit.row(i));

            y_p3 = polyval(matrix_polyfit.row(i), X);

            b = min(b + m, len_x - 1);
            a = a + m;
            i++;

        }
        
        F((m - 4) / 2) = as_scalar(sqrt(1.0 / length * sum(square(y_p3 - y))));

      

    }
 

    // polyval

    // F = sqrt((1/k)*sum(square(y_p3-y)));

    mat log_m = log(M); // Nie wiem czy jest to właściwywy logarytm
    mat log_f = log(F);

    vec alfa1 = polyfit(log_m.rows(0, 6), log_f.rows(0, 6), 1);
    vec alfa2 = polyfit(log_m.rows(6, 30), log_f.rows(6, 30), 1);

    vec line_alfa1 = polyval(alfa1, log_m.rows(0, 6));
    vec line_alfa2 = polyval(alfa2, log_m.rows(6, 30));
cout <<line_alfa2<<endl;
   

}
