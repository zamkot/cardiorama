#ifndef CHART_H
#define CHART_H

#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts>
#include <QString>
#include <cmath>
#include <algorithm>

QT_CHARTS_USE_NAMESPACE

QChart *setChart_ECG_Baseline();
QChart *setChart_R_peaks();
QChart *setChart_QRS();
QChart *setChart_T_Waves_ALT();
QChart *setChart_HRV_1();
QChart *setChart_HRV_2();
QChart *setChart_HVR_DFA();

#endif // CHART_H
