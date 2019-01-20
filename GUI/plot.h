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

Chart *setChart_ECG_Baseline();
Chart *setChart_R_peaks(std::vector<int> r_peaks);
Chart *setChart_QRS();
Chart *setChart_T_Waves_ALT();
Chart *setChart_HRV1();
Chart *setChart_HRV_2_hist();
Chart *setChart_HRV2_poincare();
Chart *setChart_HRV_DFA();


#endif // PLOT_H

