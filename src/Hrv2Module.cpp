#include <Hrv2Module.hpp>
#include <RPeaksModule.hpp>
#include <iostream>
#include <armadillo>
#include <cmath>

Hrv2Module::Hrv2Module(RPeaksModuleBase& RPeaksModule):RPeaksModule{RPeaksModule}{
	
    RPeaksModule.attach(this);
    config.num_of_bins = 70;
}

void Hrv2Module::configure(Hrv2Config config) {
    invalidateResults();
    this->config = config;
}

void Hrv2Module::runHrv2() {
    using namespace arma;
	
    auto rpeaksmodule_output = RPeaksModule.getResults();
    vec rpeaksindex(rpeaksmodule_output.rpeaks);
    
    vec rr = createRRVector(rpeaksindex, config.sampling_frequency);
    vec rr_filtered = rrFiltering(rr);
 
    // histogram values
    int num_of_bins = 70;
    double space_between_bin = (max(rr_filtered)-min(rr_filtered))/num_of_bins;
    vec bin_centers = linspace<vec>(min(rr_filtered)+space_between_bin/2,max(rr_filtered)-
                      space_between_bin/2,num_of_bins);
         
    uvec hist_values = hist(rr_filtered,bin_centers);
     
     
    // hrv index
    double hrv_index = double(rr_filtered.n_elem)/max(hist_values);
    // TINN 
    
    vec triangular = zeros<vec>(num_of_bins);
    double temp = 0;
    double error = 0;
    uword N = 0;
    uword M = 0;
    uword N_min, M_min;
     
    for(uword N = 0; N<index_max(hist_values); ++N){
        for(uword M=num_of_bins-1; M>index_max(hist_values); --M){
            triangular = createTriangularFunction(N,M,index_max(hist_values), max(hist_values),
                         bin_centers, num_of_bins);
            temp = errorCalculation(hist_values,triangular);
            if((N==0 && M==num_of_bins-1) || temp < error){
                error = temp;
                N_min = N;
                M_min = M;
            }
        }
    }
 
    double tinn = bin_centers(M_min) - bin_centers(N_min);
     
     
    //Poincare
     
    vec x_axis= rr_filtered.rows(0,rr_filtered.n_elem-2);
    vec y_axis = rr_filtered.rows(1,rr_filtered.n_elem-1);
 
    double SD1 = stddev(x_axis - y_axis)/sqrt(2);
    double SD2 = stddev(x_axis + y_axis)/sqrt(2);
     
    double centroid_x = mean(x_axis);
    double centroid_y = mean(y_axis);
 
    results.hist_values = std::vector<int>(hist_values.begin(), hist_values.end());
    results.bin_centers = std::vector<double>(bin_centers.begin(), bin_centers.end());    
    results.hrv_index = hrv_index;
    results.tinn = tinn;
    results.SD1 = SD1;
    results.SD2 = SD2;
    results.poincareplot_x_axis = std::vector<double>(x_axis.begin(), x_axis.end());
    results.poincareplot_y_axis = std::vector<double>(y_axis.begin(), y_axis.end());
    results.centroid_x = centroid_x;
    results.centroid_y = centroid_y; 
	
    validateResults();
	
}

Hrv2Data Hrv2Module::getResults() {
    
    if (!resultsValid()) {
        runHrv2();
    }

    return results;
}



/*--------------------------------------------------------------------------------------*/

Hrv2Module::arma::vec createRRVector(arma::vec& rpeaksindex, double sampling_frequency){
   
   using namespace arma;
   double deltaT = 1/sampling_frequency;
   vec rpeaks = rpeaksindex*deltaT;
   vec vector1 = rpeaks.rows(1,rpeaks_index.n_elem-1);
   vec vector2 = rpeaks.rows(0,rpeaks_index.n_elem-2);
   vec rr = vector1-vector2; 
   return rr; 
}



Hrv2Module::arma::vec rrFiltering (arma::vec& rr){
     
    using namespace arma;
  
    vec rr_ratio = zeros<vec>(rr.n_elem-1);
 
    for(uword i=1; i<rr.n_elem; ++i){
        rr_ratio(i-1) = rr(i)/rr(i-1);
    }
 
    vec rr_ratio_sorted = sort(rr_ratio);
 
    uword percentyle1 = ceil(rr_ratio_sorted.n_elem*0.01);
    uword percentyle99 = floor(rr_ratio_sorted.n_elem*0.99);
    uword percentyle25 = ceil(rr_ratio_sorted.n_elem*0.25);
     
    vec map = ones<vec>(rr.n_elem);
 
    for(uword i=1; i<rr.n_elem-2; i++){
        if((rr(i)/rr(i-1) < rr_ratio_sorted(percentyle1) && 
           rr(i+1)/rr(i) > rr_ratio_sorted(percentyle99) && 
           rr(i+1)/rr(i+2) > rr_ratio_sorted(percentyle25))||
           (rr(i)/rr(i-1)>rr_ratio_sorted(percentyle99) && 
           rr(i+1)/rr(i)<rr_ratio_sorted(percentyle1))){
            
               map(i) = 0;
         
        }      
    }
 
    vec rr_filtered = rr(find(map));
     
    return rr_filtered;
}
 

Hrv2Module::arma::vec createTriangularFunction(arma::uword N, arma::uword M, arma::uword index_of_maximum, 
                                   double maximum_value, arma::vec& bin_centers, int num_of_bins){
     
    using namespace arma;
     
    //left
    vec x = zeros<vec>(2);
    x(0) = bin_centers(N);
    x(1) = bin_centers(index_of_maximum);
    vec y = zeros<vec>(2);
    y(1) = maximum_value;
 
    vec coeff_left = polyfit(x,y,1);
    vec new_x_left = bin_centers.rows(N,index_of_maximum);
    vec y_estimated_left = polyval(coeff_left,new_x_left);
     
    //right
    x = zeros<vec>(2);
    x(0) = bin_centers(index_of_maximum);
    x(1) = bin_centers(M);
    y = zeros<vec>(2);
    y(0) = maximum_value;
 
    vec coeff_right = polyfit(x,y,1);
    vec new_x_right = bin_centers.rows(index_of_maximum,M);
    vec y_estimated_right = polyval(coeff_right,new_x_right);
     
    vec triangular_values = zeros<vec>(bin_centers.n_elem);
    triangular_values.rows(N,index_of_maximum) = y_estimated_left; 
    triangular_values.rows(index_of_maximum+1,M) = y_estimated_right.rows(1,y_estimated_right.n_elem-1);
     
    return triangular_values;  
}
 

Hrv2Module::double errorCalculation(arma::uvec& hist_values,arma::vec& triangular_values){
     
    using namespace arma;
     
    vec difference = hist_values - triangular_values;
    return sum(difference % difference);
}
