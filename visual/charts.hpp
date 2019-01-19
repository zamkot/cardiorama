#ifndef CHARTS_HPP
#define CHARTS_HPP

#endif // CHARTS_HPP

#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QScatterSeries>
#include <QColor>
#include <QtCharts/QAbstractBarSeries>
#include <cmath>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QValueAxis>

#define maxECG  30
#define DEFAULT_MARKER_SIZE 10

QT_CHARTS_USE_NAMESPACE

//Function declarations
QChart * setChart_R_peaks(); //podpite
QChart * setChart_HRV_1(); //In progress
QChart * setChart_HRV_2_hist(); //podpięte
QChart * setChart_HRV_2_poincare(); //podpięte
QChart * setChart_HVR_DFA(); //TODO
QChart * setChart_ECG_Baseline(); //podpięte
QChart * setChart_QRS(); //podpięte
QChart * setChart_T_Waves_ALT(); //podpięte
