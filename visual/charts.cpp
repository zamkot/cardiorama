#include "charts.hpp"

#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QCategoryAxis>
#include <QString>
#include <cmath>

//TODO: add a header with data types

/* Defines */
#define maxECG 30
#define DEFAULT_MARKER_SIZE 10


//Font for all chart titles
QFont ChartFont("Arial", 14, QFont::Bold);



//Function declarations
QChart * setChart_R_peaks(); //podpite
QChart * setChart_HRV_1(); //In progress
QChart * setChart_HRV_2_hist(); //podpięte
QChart * setChart_HRV_2_poincare(); //podpięte
QChart * setChart_HVR_DFA(); //TODO
QChart * setChart_ECG_Baseline(); //podpięte
QChart * setChart_QRS(); //podpięte
QChart * setChart_T_Waves_ALT(); //podpięte


/*Funtction declarations*/

/* This function is used to draw R peaks chart.
 * Parameters: ---
 * Return: QChart * chart, ready chart
 * TODO: Confront with Michał Kwiatosz
 * TODO: Transform to work with real data
 */
QChart * setChart_R_peaks()
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

    chart->setTitle("Detected R-peaks");

    QValueAxis * axis_y = new QValueAxis();
    axis_y->setRange(0,maxECG);
    axis_y->setTitleText("Voltage [mV]");


    QValueAxis * axis_x = new QValueAxis();
    axis_x->setRange(0,dane_y.size());
    axis_x->setTitleText("Samples");

    series_scatter2->setMarkerSize(DEFAULT_MARKER_SIZE);
    series_scatter2->setName("R peaks");

    series_line->setName("ECG Signal");

    //dodanie serii danych
    chart->addSeries(series_line);
    chart->addSeries(series_scatter2);

    chart->setAxisX(axis_x,series_line);
    chart->setAxisY(axis_y,series_line);

    chart->setAxisX(axis_x,series_scatter2);
    chart->setAxisY(axis_y,series_scatter2);
    chart->setAnimationOptions(QChart::AllAnimations);

    chart->setTitleFont(ChartFont);
    chart->legend()->show();
    chart->legend()->setAlignment(Qt::AlignRight);

    return chart;
}


/* This function is used to draw QRS and R peaks chart.
 * Parameters: ---
 * Return: QChart * chart, ready chart
 * TODO: Transform to work with real data
 */
QChart * setChart_QRS()
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

     series_line->setName("ECG Signal");
     series_rpeaks->setName("R peak");
     series_qrsOnset->setName("Qrs Onset");
     series_qrsend->setName("Qrs End");
     series_tEnd->setName("T-wave");
     series_pOnset->setName("P onset");
     series_pEnd->setName("P End");

     series_pEnd->setColor(Qt::yellow);


     series_rpeaks->setMarkerSize(DEFAULT_MARKER_SIZE);
     series_qrsOnset->setMarkerSize(DEFAULT_MARKER_SIZE);
     series_qrsend->setMarkerSize(DEFAULT_MARKER_SIZE);
     series_tEnd->setMarkerSize(DEFAULT_MARKER_SIZE);
     series_pOnset->setMarkerSize(DEFAULT_MARKER_SIZE);
     series_pEnd->setMarkerSize(DEFAULT_MARKER_SIZE);



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
     chart->legend()->setAlignment(Qt::AlignRight);

     chart->setTitle("Characteristic points of ECG signal");

     //QFont ChartFont("Arial", 14, QFont::Bold);


     chart->setTitleFont(ChartFont);
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


    return chart;
}


QChart * setChart_ECG_Baseline()
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


     //QFont ChartFont("Arial", 14, QFont::Bold);
     chart->setTitleFont(ChartFont);

    return chart;

}

QChart * setChart_HRV_2_hist()
{
/************************************HISTOGRAM********************************************/

    unsigned int i;

    //set dla osi X
    QBarSet *set0 = new QBarSet("Number of RR intervals");
    //seria danych dla hist., oś y
    QBarSeries *series = new QBarSeries();


    //przedziały
    std::vector<double> przedzialy(10);
    przedzialy = {1,2,3,4,5,6,7,8,9,10,12,13,14,15,16,17,18,19};

    std::vector<std::string> string_przedzialy;


    QList<QString> list_przedzialy;

    for(i = 0; i < przedzialy.size(); i++)
    {
        list_przedzialy.append(QString::number(przedzialy[i]));
    }

    //tu będą wartości dla danych przedziałów - dane y
    std::vector<int> int_vector_y(10);
    int_vector_y = {1,2,3,4,5,6,7,8,9,10,12,13,14,15,16,17,18,19,11};

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
    hist->setTitle("RR intervals histogram");
    hist->setAnimationOptions(QChart::AllAnimations);


    //QFont ChartFont("Arial", 14, QFont::Bold);

    hist->setTitleFont(ChartFont);

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(list_przedzialy);

    axis->setLabelsAngle(-90);

    axis->setTitleText("Duration");
    hist->createDefaultAxes();

    hist->setAxisX(axis);


    hist->legend()->setVisible(true);
    hist->legend()->setAlignment(Qt::AlignBottom);


    return hist;

}



QChart * setChart_HRV2_poincare()
{

/************************************POINCARE********************************************/

    double centroid_x = 0.6;
    double centroid_y = 0.6;

    double SD1 = 0.2;
    double SD2 = 0.5;

    std::vector<double> poincareplot_x_axis =  {0.10, 0.15, 0.24, 0.26, 0.837};;
    std::vector<double> poincareplot_y_axis = {0.915, 0.324, 0.426, 0.637, 0.118};

    QScatterSeries * series_poincare = new QScatterSeries();

    for(unsigned long i = 0; i < poincareplot_x_axis.size(); i++)
    {
         series_poincare->append(poincareplot_x_axis[i], poincareplot_y_axis[i]);
    }


    series_poincare->setMarkerSize(5);


    //linia dla SD1 i SD2
    QLineSeries * SD1_line = new QLineSeries();
    QLineSeries * SD2_line = new QLineSeries();

    //SD1-opadająca
    //SD2-rosnąca
    SD1_line->append(centroid_x*2,0);
    SD1_line->append(0,centroid_x*2);

    SD1_line->setOpacity(0.2);

    SD2_line->append(0,0);
    SD2_line->append(centroid_x*2,centroid_x*2);

    SD2_line->setOpacity(0.2);


    //wyznaczanie właściwych SD1 i SD2
    QLineSeries * SD1_line_final = new QLineSeries();
    QLineSeries * SD2_line_final = new QLineSeries();


    SD2_line_final->append(centroid_x-(SD2/sqrt(2)), centroid_y-(SD2/sqrt(2)));
    SD2_line_final->append(centroid_x+(SD2/sqrt(2)),centroid_y+(SD2/sqrt(2)));


    SD1_line_final->append(centroid_x-(SD1/sqrt(2)), centroid_y+(SD1/sqrt(2)));
    SD1_line_final->append(centroid_x+(SD1/sqrt(2)), centroid_y-(SD1/sqrt(2)));

    QScatterSeries * series_centroid = new QScatterSeries();
    series_centroid->append(centroid_x, centroid_y);


    //ELIPSA

    double x[180];
    double y[180];
    double x1[180];
    double y1[180];

    QScatterSeries * series_ellipse = new QScatterSeries();
    series_ellipse->setMarkerSize(4);

    for (int fi = 0; fi < 180; fi++)
    {
        x[fi] = SD2*cos(fi);
        y[fi] = SD1*sin(fi);
        x1[fi] = cos(M_PI/4)*x[fi]-sin(M_PI/4)*y[fi];
        y1[fi] = sin(M_PI/4)*x[fi]+cos(M_PI/4)*y[fi];


        series_ellipse->append(x1[fi]+centroid_x, y1[fi]+centroid_x);
    }


    //opisy do legendy
    series_poincare->setName("RR intervals");
    SD1_line_final->setName("SD1");
    SD2_line_final->setName("SD2");


    //series colors
    SD1_line->setColor(Qt::green);
    SD1_line_final->setColor(Qt::green);

    SD2_line->setColor(Qt::red);
    SD2_line_final->setColor(Qt::red);


    series_ellipse->setColor(0x10062);

    QChart * chart_poincare = new QChart();

    chart_poincare->addSeries(series_poincare);
    chart_poincare->addSeries(SD1_line);
    chart_poincare->addSeries(SD2_line);
    //chart_poincare->addSeries(series_centroid);
    chart_poincare->addSeries(SD2_line_final);
    chart_poincare->addSeries(SD1_line_final);
    chart_poincare->addSeries(series_ellipse);


    chart_poincare->legend()->markers(SD1_line)[0]->setVisible(false);
    chart_poincare->legend()->markers(SD2_line)[0]->setVisible(false);
    chart_poincare->legend()->markers(series_poincare)[0]->setVisible(false);
    chart_poincare->legend()->markers(series_ellipse)[0]->setVisible(false);
    chart_poincare->legend()->markers(SD1_line_final)[0]->setVisible(true);
    chart_poincare->legend()->markers(SD2_line_final)[0]->setVisible(true);


    chart_poincare->legend()->setAlignment(Qt::AlignRight);
    chart_poincare->setTitle("Poincare plot of RR intervals");

    //osie

    QValueAxis * axis_x = new QValueAxis();
    QValueAxis * axis_y = new QValueAxis();

    axis_x->setRange(0, centroid_x*2);
    axis_y->setRange(0, centroid_x*2);

    axis_x->setTitleText("RR[i] (s)");
    axis_y->setTitleText("RR[i+1] (s)");

    chart_poincare->setAxisX(axis_x,SD1_line);
    chart_poincare->setAxisY(axis_y,SD1_line);
    chart_poincare->setAxisX(axis_x,SD2_line);
    chart_poincare->setAxisY(axis_y,SD2_line);
    chart_poincare->setAxisX(axis_x,SD1_line_final);
    chart_poincare->setAxisY(axis_y,SD1_line_final);
    chart_poincare->setAxisX(axis_x,SD2_line_final);
    chart_poincare->setAxisY(axis_y,SD2_line_final);
    chart_poincare->setAxisX(axis_x,series_poincare);
    chart_poincare->setAxisY(axis_y,series_poincare);
    chart_poincare->setAxisX(axis_x,series_ellipse);
    chart_poincare->setAxisY(axis_y,series_ellipse);


    chart_poincare->setTitleFont(ChartFont);

    chart_poincare->setMinimumSize(400,400);


    return chart_poincare;
}


QChart * setChart_T_Waves_ALT()
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
     std::vector<int> t_waves_alt = {2,3,5};

     //seria danych bazowych - sygnał EKG
     QLineSeries *series_line = new QLineSeries();

     //seria danych - wektor r pików
     QScatterSeries *series_scatter2 = new QScatterSeries();


     for(i = 0; i < t_waves_alt.size(); i++)
     {
         series_scatter2->append(t_waves_alt[i], dane_y[t_waves_alt[i] - 1]);
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

     chart->setTitle("T wave alterans");
     //chart->createDefaultAxes();


     QValueAxis * axis_y = new QValueAxis();
     axis_y->setRange(0,maxECG);
     axis_y->setTitleText("Voltage [mV]");


     QValueAxis * axis_x = new QValueAxis();
     axis_x->setRange(0,dane_y.size());
     axis_x->setTitleText("Samples");

     series_scatter2->setMarkerSize(DEFAULT_MARKER_SIZE);
     series_scatter2->setName("detected alterans");

     series_line->setName("ECG Signal");

     //dodanie serii danych
     chart->addSeries(series_line);
     chart->addSeries(series_scatter2);

     chart->setAxisX(axis_x,series_line);
     chart->setAxisY(axis_y,series_line);

     chart->setAxisX(axis_x,series_scatter2);
     chart->setAxisY(axis_y,series_scatter2);
     chart->setAnimationOptions(QChart::AllAnimations);


     chart->setTitleFont(ChartFont);
     chart->legend()->show();
     chart->legend()->setAlignment(Qt::AlignRight);

     return chart;
}



QChart * setChart_HRV1()
{
    unsigned long i;

    //tu będzie wektor z częstotliwością
    std::vector<double> F = {0.01,0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08,0.1,0.2,0.3,0.4};
    //tu będzie wektor z wartościami
    std::vector<double> P = {1,2,100000,4,15,4,3,4,5,6,8,12};


    //tu będą od Zuzy wartości
    std::vector<double> ULF = {0,0.003};
    std::vector<double> VLF = {0.003,0.15};
    std::vector<double> LF = {0.16,0.2};
    std::vector<double> HF = {0.35, 0.4};

    //tu będzie oś od Zuzy
    QCategoryAxis  * axisX3 = new QCategoryAxis();
    axisX3->append("ULF", ULF[1]);
    axisX3->append("VLF", VLF[1]);
    axisX3->append("LF", LF[1]);
    axisX3->append("HF", HF[1]);
    axisX3->setGridLineVisible(true);
    axisX3->setGridLineColor(Qt::black);
    axisX3->setStartValue(true);
    axisX3->setLabelsPosition(QCategoryAxis::AxisLabelsPositionCenter);


    //tu oś xów
    QValueAxis * axis_x = new QValueAxis();
    axis_x->setRange(0,0.4);
    axis_x->setTitleText("Frequency [Hz]");
    axis_x->setGridLineVisible(false);


    //tu oś y ech
    QLogValueAxis * axis_y_log = new QLogValueAxis();
    axis_y_log->setBase(10);
    axis_y_log->setTitleText("Signal power");



    QLineSeries * series_power = new QLineSeries();

    for(i = 0; i < P.size(); i++)
    {
         series_power->append(F[i], P[i]);
    }

    QChart * chart_power = new QChart();

    chart_power->addSeries(series_power);
    chart_power->addAxis(axisX3, Qt::AlignTop);
    chart_power->setAxisX(axis_x, series_power);
    chart_power->setAxisY(axis_y_log, series_power);
    chart_power->setTitle("Power density of ECG signal");

    chart_power->setTitleFont(ChartFont);

    series_power->attachAxis(axisX3);
    //    series_power->attachAxis(axis_y_log);

     chart_power->legend()->hide();

     return chart_power;
}

QChart * setChart_HRV_1()
{
    unsigned long i = 0;
    unsigned long s = 3;
    // tu będzie wektor danymi x
    std::vector<double> log_m= {1,2,3,4,5,6};
    //a tu bedzie wektor z wartościami na ygrekach
    std::vector<double> logF = {2,15,1,4,22,6};
    //a tu bedzie wektor z wartościami na ygrekach
    std::vector<double> alpha1 = {2,3,1,};
    //a tu bedzie wektor z wartościami na ygrekach
    std::vector<double> alpha2 = {14,2,7};

    //seria danych bazowych - sygnał EKG
    QScatterSeries *series_scatter = new QScatterSeries();
    series_scatter->setMarkerSize(6);


    QLineSeries * series_alpha1 = new QLineSeries();
    QLineSeries * series_alpha2 = new QLineSeries();


    series_alpha1->setName("Alpha1");
    series_alpha2->setName("Alpha2");

    //przygotowanie serii dla sygnalu EKG
    for(i = 0; i < log_m.size(); i++)
    {
        series_scatter->append(log_m[i], logF[i]);
    }
    for(i = 0; i < log_m.size(); i++)
    {
        if(i < s)
        {
            series_alpha1->append(log_m[i], alpha1[i]);
        }
        else
        {
           series_alpha2->append(log_m[i], alpha2[i-s]);
        }

    }


    //Tworzenie nowego wykresu
    QChart *chart = new QChart();

    //dodanie serii danych
    chart->addSeries(series_scatter);
    chart->addSeries(series_alpha1);
    chart->addSeries(series_alpha2);
    chart->legend()->hide();
    chart->setTitle("DFA");


    QValueAxis * axis_y = new QValueAxis();
    axis_y->setTitleText("logF(Δm)");


    QValueAxis * axis_x = new QValueAxis();
    axis_x->setTitleText("log(Δm)");

    chart->setAxisX(axis_x,series_scatter);
    chart->setAxisY(axis_y,series_scatter);
    chart->setAxisX(axis_x,series_alpha1);
    chart->setAxisY(axis_y,series_alpha1);
    chart->setAxisX(axis_x,series_alpha2);
    chart->setAxisY(axis_y,series_alpha2);
    chart->setAnimationOptions(QChart::AllAnimations);

    chart->legend()->markers(series_alpha1)[0]->setVisible(true);
    chart->legend()->markers(series_alpha2)[0]->setVisible(true);
    chart->legend()->markers(series_scatter)[0]->setVisible(false);
    chart->legend()->show();
    chart->legend()->setAlignment(Qt::AlignRight);

    chart->setTitleFont(ChartFont);

    return chart;
}

