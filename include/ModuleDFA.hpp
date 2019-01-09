# include <iostream>
# include <climits>
# include <armadillo> 
# include <typeinfo>
using namespace std;
using namespace arma; 


int main(){

    mat nsr001;
    nsr001.load("chf206.csv",raw_ascii); // wczytanie tachogramu
    mat tachogram = nsr001.rows(0,659); // pobranie pewnej ilości próbek
  

    //int m = 4; // tworzenie wektora z oknami
    mat M;
    mat F;
    
    int k = tachogram.n_rows;
    
     for(int m = 4; m<=64; m= m+2){
            //M(j) = m;
         //sprawdzenie rozmiaru tachogramu
         mat tachogram2;
         if(m<k){
        int modulo =k % m;
        
        unsigned int win = k - modulo; // wyznaczenie granicy okna
        tachogram2 = tachogram.rows(0,win-1); // wyznaczenie zakresu próbek (1:granica okna)
        k = tachogram2.n_rows;
         }else{
           unsigned int win = k; 
          tachogram2 = tachogram.rows(0,win-1);
         }
        //całkowanie
        mat x = cumsum(tachogram2,0); // skumulowana suma
      
        mat z;
       mat xos(k,1, fill::zeros);

        for(int a = 0; a < k ; a++){
           
            mat mean_tachogram = mean(tachogram2);
        
            mat pr = tachogram2.row(a);
            
            mat z = (pr-mean_tachogram);  
            xos(a,0) = z(0,0);
            
        }

        mat y = cumsum(xos,0);
        
        //dopasowanie krzywej polyfit/polyval
     int len_x = x.n_rows;
   
    int q = round(len_x/m);
   
    int a = 0;
    int b = m; 
    
    
   vec X(len_x);
    vec y2(len_x);
    vec x5(q,2);

     for (int i = 0; i<=q  ; i++){
       
      if (b==64 && i == 0 ){
           
          break; 
         }
    
     
         y2.rows(a,b) = y.rows(a,b);
         X.rows(a,b)= x.rows(a,b);
         for (int t = 0; t <=q; t++ ){
                mat a = X.row(t);
                mat  b = y2.row(t);

              mat pol = polyfit(X,y2,1);
         }
         cout <<size(y2)<<endl; 
         cout <<size(X)<<endl;

      //x5.row(i) = polyfit(X,y2,1);
       
        b++;
        a++;
         
     }
     
    
 
        //TU COŚ NIE DZIAŁA, NIE MAM JUŻ POMYSŁU CO JEST ŹLE
        //polifit
        //  vec y_p;
        //  vec x2 = vectorise(x);
        //  vec y2 = vectorise(y);
        //  vec x3 ;
        //  vec y3 ;
           

    //        for (int p = 0; p < k ; p++){
               
    //           x3 = x2.rows(p,k-1);
    //          y3 = y2.rows(p,k-1);
               
    //       //     //y_p = polyfit(x3,y3,1); // wywala sie na polyfit 
             
               
    //       }
    //     //   cout<<y_p<<endl;
    //     // //polyval
        
    //     vec y_p3;
    //     vec x4;
    //     vec y_p2;
    //       for (int jj = 0; jj< k; jj++){ 
    //             x4 = x3.rows(jj,k-1);
    //             y_p2 = y_p.rows(jj,k-1);
    //     //         y_p3= polyval(y_p2,x4); // ten sam problem co z polyfitem
    //        }

    //      mat y_p4 = vectorise(y_p3);
    //      mat roz = square(y-y_p4);
    //    // F(m) = sqrt((1/k)*sum(roz));
    //   // M(m) = m; // Zapisanie zmian długości okna
          
       
    //  }
    //   mat log_m = log10(M); // Nie wiem czy jest to właściwywy logarytm
    //   mat log_f = log10(F);

    // //vec alfa1 = polyfit(log_m(0,6),log_f(0,6)),1);
    // //vec alfa2 = polyfit(log_m.row(6),log_f.row(6)),1);
    
    // //vec line_alfa1 = polyval(alfa1, log_m(0,6));
    // //vec line_alfa2 = polyval(alfa2, log_m.row(6));
     
     }
     }