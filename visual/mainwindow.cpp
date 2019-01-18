#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QString>
#include <cmath>
#include <algorithm>

int maxECG = 30;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    void setChart_R_peaks();
    void setChart_HRV_1();
    void setChart_HRV_2();
    void setChart_HVR_DFA();
    void setChart_ECG_Baseline();
    void setChart_QRS();
    void setChart_T_Waves_ALT();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setChart_R_peaks()
{
   //Question: Czy os x ma być w próbkach, czy w czasie?

   //  QValueAxis *x_axis = new QValueAxis();

   //    x_axis->setTickCount(10);

    unsigned int i = 0;
    // tu będzie wektor danymi x - sygnał EKG
    std::vector<int> dane_x= {1,2,3,4,5,6};
    //a tu bedzie wektor z wartościami na ygrekach - sygnał EKG
    std::vector<int> dane_y = {2,15,1,4,22,6};

    //tu będzie wektor z r pikami
    std::vector<int> r_peaks = {2,3,5};

    //seria danych bazowych - sygnał EKG
    QLineSeries *series_line = new QLineSeries();

    //seria danych - wektor r pików
    QScatterSeries *series_scatter2 = new QScatterSeries();


    for(i = 0; i < r_peaks.size(); i++)
    {
        series_scatter2->append(r_peaks[i], dane_y[r_peaks[i] - 1]);
    }

    //przygotowanie serii dla sygnalu EKG
    for(i = 0; i < dane_x.size(); i++)
    {
        series_line->append(dane_x[i], dane_y[i]);
    }


    series_scatter2->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    //  series_scatter2->setColor(QColor::red());

    //Tworzenie nowego wykresu
    QChart *chart = new QChart();


    chart->legend()->hide();

    chart->setTitle("Umiejscowienie załamków R");
    //chart->createDefaultAxes();


    QValueAxis * axis_y = new QValueAxis();
    axis_y->setRange(0,maxECG);
    axis_y->setTitleText("Voltage [mV]");


    QValueAxis * axis_x = new QValueAxis();
    axis_x->setRange(0,dane_y.size());
    axis_x->setTitleText("Samples");


    //dodanie serii danych
    chart->addSeries(series_line);
    chart->addSeries(series_scatter2);

    chart->setAxisX(axis_x,series_line);
    chart->setAxisY(axis_y,series_line);

    chart->setAxisX(axis_x,series_scatter2);
    chart->setAxisY(axis_y,series_scatter2);
    chart->setAnimationOptions(QChart::AllAnimations);


    ui->chart_R->setChart(chart);
    ui->chart_R->setRenderHints(QPainter::Antialiasing);
}

void MainWindow::setChart_HRV_1()
{
    //TODO: wykres częstotliwości? not sure
}

void MainWindow::setChart_HRV_2()
{
/************************************HISTOGRAM********************************************/

    unsigned int i;

    //set dla osi X
    QBarSet *set0 = new QBarSet("Liczba załamków RR w danym czasie");
    //seria danych dla hist., oś y
    QBarSeries *series = new QBarSeries();


    //przedziały
    std::vector<double> przedzialy(10);
    przedzialy = {0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9};

    std::vector<std::string> string_przedzialy;


    QList<QString> list_przedzialy;

    for(i = 0; i < przedzialy.size(); i++)
    {
        list_przedzialy.append(QString::number(przedzialy[i]));
    }

    //tu będą wartości dla danych przedziałów - dane y
    std::vector<int> int_vector_y(10);
    int_vector_y = {0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,1};

    //int to double
    std::vector<qreal> nowy_wektor(int_vector_y.begin(), int_vector_y.end());

    //przeksztalcenie na QVector
    QVector<double> nowy_wektor_q = QVector<double>::fromStdVector(nowy_wektor);
    //   nowy_wektor_q.fromStdVector(nowy_wektor);

    //QVector double to list double
    QList<qreal> nowy_wektor_list = nowy_wektor_q.toList();

    //ustawienie serii danych dla y
    set0->append(nowy_wektor_list);
    series->append(set0);


    QChart *hist = new QChart();
    hist->addSeries(series);
    hist->setTitle("Histogram odcinków RR");
    hist->setAnimationOptions(QChart::AllAnimations);



    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(list_przedzialy);
    hist->createDefaultAxes();
    hist->legend()->setVisible(true);
    hist->legend()->setAlignment(Qt::AlignBottom);

    ui->HRV2_histogram->setChart(hist);


/************************************POINCARE********************************************/



//Error: requested more data

}

void MainWindow::setChart_HVR_DFA()
{

    // TODO: wykres dopasowania w zal. od ilości próbek???
}

void MainWindow::setChart_QRS()
{
    //Question: Czy os x ma być w próbkach, czy w czasie?

    //  QValueAxis *x_axis = new QValueAxis();

    //    x_axis->setTickCount(10);

     unsigned int i = 0;
     // tu będzie wektor danymi x - sygnał EKG
     std::vector<int> dane_x= {1,2,3,4,5,6,7,8,9,10};
     //a tu bedzie wektor z wartościami na ygrekach - sygnał EKG
     std::vector<int> dane_y = {2,15,1,4,22,6,7,11,23,0,8};

     //tu będzie wektor z r pikami
     std::vector<int> r_peaks = {2,3,5};

     //tu będzie wektor z qrsOnset
     std::vector<int> qrsOnset = {1,4};

     //tu będzie wektor z qrsend
     std::vector<int> qrsend = {6};

     //tu będzie wektor z tEnd
     std::vector<int> tEnd = {7};

     //tu będzie wektor z pOnset
     std::vector<int> pOnset = {8};

     //tu będzie wektor z pOnset
     std::vector<int> pEnd = {9,10};

     //seria danych bazowych - sygnał EKG
     QLineSeries *series_line = new QLineSeries();

     //seria danych - wektor r pików
     QScatterSeries *series_rpeaks = new QScatterSeries();
     QScatterSeries *series_qrsOnset = new QScatterSeries();
     QScatterSeries *series_qrsend = new QScatterSeries();
     QScatterSeries *series_tEnd = new QScatterSeries();
     QScatterSeries *series_pOnset = new QScatterSeries();
     QScatterSeries *series_pEnd = new QScatterSeries();


     for(i = 0; i < r_peaks.size(); i++)
     {
         series_rpeaks->append(r_peaks[i], dane_y[r_peaks[i] - 1]);
     }


     for(i = 0; i < qrsOnset.size(); i++)
     {
         series_qrsOnset->append(qrsOnset[i], dane_y[qrsOnset[i] - 1]);
     }

     for(i = 0; i < qrsend.size(); i++)
     {
         series_qrsend->append(qrsend[i], dane_y[qrsend[i] - 1]);
     }

     for(i = 0; i < tEnd.size(); i++)
     {
         series_tEnd->append(tEnd[i], dane_y[tEnd[i] - 1]);
     }

     for(i = 0; i < pOnset.size(); i++)
     {
         series_pOnset->append(pOnset[i], dane_y[pOnset[i] - 1]);
     }

     for(i = 0; i < pEnd.size(); i++)
     {
         series_pEnd->append(pEnd[i], dane_y[pEnd[i] - 1]);
     }


     //przygotowanie serii dla sygnalu EKG
     for(i = 0; i < dane_x.size(); i++)
     {
         series_line->append(dane_x[i], dane_y[i]);
     }




     series_rpeaks->setMarkerShape(QScatterSeries::MarkerShapeCircle);
     //  series_scatter2->setColor(QColor::red());

     //Tworzenie nowego wykresu
     QChart *chart = new QChart();


     chart->legend()->show();

     chart->setTitle("Characteristic points of ECG signal");
     //chart->createDefaultAxes();


     QValueAxis * axis_y = new QValueAxis();
     axis_y->setRange(0,maxECG);
     axis_y->setTitleText("Voltage [mV]");


     QValueAxis * axis_x = new QValueAxis();
     axis_x->setRange(0,dane_y.size());
     axis_x->setTitleText("Samples");


     //dodanie serii danych
     chart->addSeries(series_line);
     chart->addSeries(series_rpeaks);
     chart->addSeries(series_qrsOnset);
     chart->addSeries(series_qrsend);
     chart->addSeries(series_tEnd);
     chart->addSeries(series_pOnset);
     chart->addSeries(series_pEnd);


     chart->setAxisX(axis_x,series_line);
     chart->setAxisY(axis_y,series_line);

     chart->setAxisX(axis_x,series_rpeaks);
     chart->setAxisY(axis_y,series_rpeaks);

     chart->setAxisX(axis_x,series_qrsOnset);
     chart->setAxisY(axis_y,series_qrsOnset);

     chart->setAxisX(axis_x,series_qrsend);
     chart->setAxisY(axis_y,series_qrsend);

     chart->setAxisX(axis_x,series_tEnd);
     chart->setAxisY(axis_y,series_tEnd);

     chart->setAxisX(axis_x,series_pOnset);
     chart->setAxisY(axis_y,series_pOnset);

     chart->setAxisX(axis_x,series_pEnd);
     chart->setAxisY(axis_y,series_pEnd);

     chart->setAnimationOptions(QChart::AllAnimations);


     ui->QRS_chart->setChart(chart);
     ui->QRS_chart->setRenderHints(QPainter::Antialiasing);
}

void MainWindow::setChart_T_Waves_ALT()
{
    //Naniesienie 1 linii na wykres r pików
}

void MainWindow::setChart_ECG_Baseline()
{

    //  QValueAxis *x_axis = new QValueAxis();

    //    x_axis->setTickCount(10);

     unsigned int i = 0;
     // tu będzie wektor danymi x - sygnał EKG
     std::vector<int> dane_x= {1,2,3,4,5,6};
     //a tu bedzie wektor z wartościami na ygrekach - sygnał EKG
     std::vector<int> dane_y = {2,15,1,4,22,6};

     //seria danych bazowych - sygnał EKG
     QLineSeries *series_line = new QLineSeries();

     //przygotowanie serii dla sygnalu EKG
     for(i = 0; i < dane_x.size(); i++)
     {
         series_line->append(dane_x[i], dane_y[i]);
     }


     //Tworzenie nowego wykresu
     QChart *chart = new QChart();

     //dodanie serii danych
     chart->addSeries(series_line);


     chart->legend()->hide();

     chart->setTitle("ECG Baseline");


     QValueAxis * axis_y = new QValueAxis();
     axis_y->setRange(0, 30);
     axis_y->setTitleText("Voltage [mV]");


     QValueAxis * axis_x = new QValueAxis();
     axis_x->setRange(0,dane_y.size());
     axis_x->setTitleText("Samples");

     chart->setAxisX(axis_x,series_line);
     chart->setAxisY(axis_y,series_line);
     chart->zoomOut();
     chart->setAnimationOptions(QChart::AllAnimations);


     ui->baseline->setChart(chart);
     ui->baseline->setRenderHints(QPainter::Antialiasing);
}
