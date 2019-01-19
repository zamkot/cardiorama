#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
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


QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow window;

    window.show();
    window.setChart_T_Waves_ALT();
    window.setChart_HRV_2();
    window.setChart_ECG_Baseline();
    window.setChart_QRS();
    window.setChart_HRV_1();
    window.setChart_HVR_DFA();

    return a.exec();
}
