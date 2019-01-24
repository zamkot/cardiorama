#ifndef PLOT_H
#define PLOT_H

#include <QtCharts>
#include <QString>
#include <QColor>
#include <cmath>
#include <algorithm>
#include <chart.h>

#define maxECG  30
#define DEFAULT_MARKER_SIZE 10

QT_CHARTS_USE_NAMESPACE

Chart *setChart_ECG_Baseline(std::vector<double> samples);

Chart *setChart_R_peaks(std::vector<int> r_peaks,std::vector<double> samples);

Chart *setChart_QRS(std::vector<int> Q_wektor,std::vector<int> QRSonset_wektor,std::vector<int> QRSend_wektor,
                    std::vector<int> P_wektor,std::vector<int> Pend_wektor,std::vector<int> Ponset_wektor,
                    std::vector<int> T_wektor,std::vector<int> r_peaks,std::vector<double> samples);

Chart *setChart_T_Waves_ALT(std::vector<int> resultTWA,std::vector<double> samples);

Chart *setChart_HRV1(std::vector<double> F,std::vector<double> P,std::vector<double> ULF,std::vector<double> VLF,std::vector<double> LF,
                     std::vector<double> HF);

Chart *setChart_HRV_2_hist(std::vector<int> hist_values,std::vector<double> bin_centers);

Chart *setChart_HRV2_poincare(double SD1,double SD2,std::vector<double> poincareplot_x_axis,std::vector<double> poincareplot_y_axis,double centroid_x,double centroid_y);

Chart *setChart_HRV_DFA(std::vector<double> log_window_sizes,std::vector<double> log_fluctuation,std::vector<double> line_alfa1,std::vector<double> line_alfa2);

Chart *setChart_Heart_Class(std::vector<int> qrsPosition,std::vector<double> heartClass,std::vector<double> samples);


#endif // PLOT_H


