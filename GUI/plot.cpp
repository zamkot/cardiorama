#include <plot.h>
#include <chart.h>
#include <chartview.h>

/* Defines */

#define DEFAULT_MARKER_SIZE 10


//Font for all chart titles
QFont ChartFont("Arial", 14, QFont::Bold);


QT_CHARTS_USE_NAMESPACE

Chart *setChart_ECG_Baseline(std::vector<double>samples)
{

     unsigned int i = 0;

     std::vector<int> dane_x(samples.size());
     std::iota(dane_x.begin(), dane_x.end(), 1);

     //seria danych bazowych - sygnał EKG
     QLineSeries *series_line = new QLineSeries();

     //przygotowanie serii dla sygnalu EKG
     for(i = 0; i < dane_x.size(); i++)
     {
         series_line->append(dane_x[i], samples[i]);
     }


     //Tworzenie nowego wykresu
     Chart *chart = new Chart();

     //dodanie serii danych
     chart->addSeries(series_line);


     chart->legend()->hide();
     chart->setTitle("ECG Baseline");

     auto max = *max_element(std::begin(samples), std::end(samples));
     auto min = *min_element(std::begin(samples), std::end(samples));
     QValueAxis * axis_y = new QValueAxis();
     axis_y->setRange(min-2,max+2);
     axis_y->setTitleText("Voltage [mV]");


     QValueAxis * axis_x = new QValueAxis();
     axis_x->setRange(0,samples.size()+2);
     axis_x->setTitleText("Samples");


     chart->setAxisX(axis_x,series_line);
     chart->setAxisY(axis_y,series_line);
     chart->zoomOut();
     chart->setAnimationOptions(QChart::AllAnimations);
     //QFont ChartFont("Arial", 14, QFont::Bold);
     chart->setTitleFont(ChartFont);

   return chart;
}

Chart *setChart_R_peaks(std::vector<int> r_peaks,std::vector<double> samples)
{
    unsigned int i = 0;

    std::vector<int> dane_x(samples.size());
    std::iota(dane_x.begin(), dane_x.end(), 1);


    //seria danych bazowych - sygnał EKG
    QLineSeries *series_line = new QLineSeries();

    //seria danych - wektor r pików
    QScatterSeries *series_scatter2 = new QScatterSeries();


    for(i = 0; i < r_peaks.size(); i++)
    {
        series_scatter2->append(r_peaks[i], samples[r_peaks[i] - 1]);
    }

    //przygotowanie serii dla sygnalu EKG
    for(i = 0; i < dane_x.size(); i++)
    {
        series_line->append(dane_x[i], samples[i]);
    }


    series_scatter2->setMarkerShape(QScatterSeries::MarkerShapeCircle);

    //Tworzenie nowego wykresu
    Chart *chart = new Chart();


    chart->legend()->hide();


    chart->setTitle("Detected R-peaks");

    auto max = *max_element(std::begin(samples), std::end(samples));
    auto min = *min_element(std::begin(samples), std::end(samples));
    QValueAxis * axis_y = new QValueAxis();
    axis_y->setRange(min-2,max+2);
    axis_y->setTitleText("Voltage [mV]");


    QValueAxis * axis_x = new QValueAxis();
    axis_x->setRange(0,samples.size()+2);
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



Chart *setChart_QRS(std::vector<int> Q_wektor,std::vector<int> QRSonset_wektor,std::vector<int> QRSend_wektor,
                    std::vector<int> P_wektor,std::vector<int> Pend_wektor,std::vector<int> Ponset_wektor,
                    std::vector<int> T_wektor,std::vector<int> r_peaks,std::vector<double> samples)
{
    //Question: Czy os x ma być w próbkach, czy w czasie?

    //  QValueAxis *x_axis = new QValueAxis();

    //    x_axis->setTickCount(10);


     unsigned int i = 0;

     std::vector<int> dane_x(samples.size());
     std::iota(dane_x.begin(), dane_x.end(), 1);



     //seria danych bazowych - sygnał EKG
     QLineSeries *series_line = new QLineSeries();

     //seria danych - wektor r pików
     QScatterSeries *series_rpeaks = new QScatterSeries();
     QScatterSeries *series_qrsOnset = new QScatterSeries();
     QScatterSeries *series_q = new QScatterSeries();
     QScatterSeries *series_p = new QScatterSeries();
     QScatterSeries *series_qrsend = new QScatterSeries();
     QScatterSeries *series_t = new QScatterSeries();
     QScatterSeries *series_pOnset = new QScatterSeries();
     QScatterSeries *series_pEnd = new QScatterSeries();

     series_line->setName("ECG Signal");
     series_rpeaks->setName("R peak");
     series_qrsOnset->setName("Qrs Onset");
     series_qrsend->setName("Qrs End");
     series_q->setName("Q wave");
     series_p->setName("P wave");
     series_t->setName("T wave");
     series_pOnset->setName("P onset");
     series_pEnd->setName("P End");

     series_pEnd->setColor(Qt::yellow);


     series_rpeaks->setMarkerSize(DEFAULT_MARKER_SIZE);
     series_t->setMarkerSize(DEFAULT_MARKER_SIZE);
     series_p->setMarkerSize(DEFAULT_MARKER_SIZE);
     series_q->setMarkerSize(DEFAULT_MARKER_SIZE);

     series_qrsOnset->setMarkerSize(8);
     series_qrsend->setMarkerSize(8);
     series_pOnset->setMarkerSize(8);
     series_pEnd->setMarkerSize(8);



     for(i = 0; i < r_peaks.size(); i++)
     {
         series_rpeaks->append(r_peaks[i],samples[r_peaks[i] - 1]);
     }


     for(i = 0; i < QRSonset_wektor.size(); i++)
     {
         series_qrsOnset->append(QRSonset_wektor[i], samples[QRSonset_wektor[i] - 1]);
     }

     for(i = 0; i < QRSend_wektor.size(); i++)
     {
         series_qrsend->append(QRSend_wektor[i], samples[QRSend_wektor[i] - 1]);
     }

     for(i = 0; i < T_wektor.size(); i++)
     {
         series_t->append(T_wektor[i], samples[T_wektor[i] - 1]);
     }

     for(i = 0; i <Ponset_wektor.size(); i++)
     {
         series_pOnset->append(Ponset_wektor[i], samples[Ponset_wektor[i] - 1]);
     }

     for(i = 0; i < Pend_wektor.size(); i++)
     {
         series_pEnd->append(Pend_wektor[i],samples[Pend_wektor[i] - 1]);
     }


     for(i = 0; i < Q_wektor.size(); i++)
     {
         series_q->append(Q_wektor[i], samples[Q_wektor[i] - 1]);
     }

     for(i = 0; i < P_wektor.size(); i++)
     {
         series_p->append(P_wektor[i], samples[P_wektor[i] - 1]);
     }

     //przygotowanie serii dla sygnalu EKG
     for(i = 0; i < dane_x.size(); i++)
     {
         series_line->append(dane_x[i], samples[i]);
     }

     series_rpeaks->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
     series_p->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
     series_t->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
     series_q->setMarkerShape(QScatterSeries::MarkerShapeRectangle);

     //Tworzenie nowego wykresu
     Chart *chart = new Chart();


     chart->legend()->show();
     chart->legend()->setAlignment(Qt::AlignRight);

     chart->setTitle("Characteristic points of ECG signal");

     //QFont ChartFont("Arial", 14, QFont::Bold);


     chart->setTitleFont(ChartFont);
     //chart->createDefaultAxes();

     auto max = *max_element(std::begin(samples), std::end(samples));
     auto min = *min_element(std::begin(samples), std::end(samples));
     QValueAxis * axis_y = new QValueAxis();
     axis_y->setRange(min-2,max+2);
     axis_y->setTitleText("Voltage [mV]");


     QValueAxis * axis_x = new QValueAxis();
     axis_x->setRange(0,samples.size()+2);
     axis_x->setTitleText("Samples");


     //dodanie serii danych
     chart->addSeries(series_line);
     chart->addSeries(series_rpeaks);
     chart->addSeries(series_t);
     chart->addSeries(series_q);
     chart->addSeries(series_p);
     chart->addSeries(series_qrsOnset);
     chart->addSeries(series_qrsend);
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

     chart->setAxisX(axis_x,series_t);
     chart->setAxisY(axis_y,series_t);

     chart->setAxisX(axis_x,series_pOnset);
     chart->setAxisY(axis_y,series_pOnset);

     chart->setAxisX(axis_x,series_pEnd);
     chart->setAxisY(axis_y,series_pEnd);

     chart->setAxisX(axis_x,series_p);
     chart->setAxisY(axis_y,series_p);

     chart->setAxisX(axis_x,series_q);
     chart->setAxisY(axis_y,series_q);

     chart->setAnimationOptions(QChart::AllAnimations);


    return chart;
}

Chart *setChart_T_Waves_ALT(std::vector<int> resultTWA,std::vector<double> samples)
{

    //Question: Czy os x ma być w próbkach, czy w czasie?

    //  QValueAxis *x_axis = new QValueAxis();

    //    x_axis->setTickCount(10);

     unsigned int i = 0;

     std::vector<int> dane_x(samples.size());
     std::iota(dane_x.begin(), dane_x.end(), 1);

     //seria danych bazowych - sygnał EKG
     QLineSeries *series_line = new QLineSeries();

     //seria danych - wektor r pików
     QScatterSeries *series_scatter2 = new QScatterSeries();


     for(i = 0; i < resultTWA.size(); i++)
     {
         series_scatter2->append( resultTWA[i], samples[ resultTWA[i] - 1]);
     }

     //przygotowanie serii dla sygnalu EKG
     for(i = 0; i < dane_x.size(); i++)
     {
         series_line->append(dane_x[i], samples[i]);
     }


     series_scatter2->setMarkerShape(QScatterSeries::MarkerShapeCircle);
     //  series_scatter2->setColor(QColor::red());

     //Tworzenie nowego wykresu
     Chart *chart = new Chart();


     chart->legend()->hide();

     chart->setTitle("T wave alternans");
     //chart->createDefaultAxes();

     auto max = *max_element(std::begin(samples), std::end(samples));
     auto min = *min_element(std::begin(samples), std::end(samples));
     QValueAxis * axis_y = new QValueAxis();
     axis_y->setRange(min-2,max+2);
     axis_y->setTitleText("Voltage [mV]");


     QValueAxis * axis_x = new QValueAxis();
     axis_x->setRange(0,samples.size()+2);
     axis_x->setTitleText("Samples");


     series_scatter2->setMarkerSize(DEFAULT_MARKER_SIZE);
     series_scatter2->setName("detected alternans");

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

Chart *setChart_HRV1(std::vector<double> F,std::vector<double> P,std::vector<double> ULF,std::vector<double> VLF,std::vector<double> LF,
                     std::vector<double> HF)
{
    unsigned long i;

    //tu będzie wektor z częstotliwością
    //std::vector<double> F = {0.01,0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08,0.1,0.2,0.3,0.4};
    //tu będzie wektor z wartościami
    //std::vector<double> P = {1,2,100000,4,15,4,3,4,5,6,8,12};


    //tu będą od Zuzy wartości
    //std::vector<double> ULF = {0,0.003};
    //std::vector<double> VLF = {0.003,0.15};
    //std::vector<double> LF = {0.16,0.2};
    //std::vector<double> HF = {0.35, 0.4};

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
    QValueAxis *axis_x = new QValueAxis();
    axis_x->setRange(0,0.4);
    axis_x->setTitleText("Frequency [Hz]");
    axis_x->setGridLineVisible(false);


    //tu oś y ech
    QLogValueAxis *axis_y_log = new QLogValueAxis();
    axis_y_log->setBase(10);
    axis_y_log->setTitleText("Signal power [ms\xC2\xB2]");



    QLineSeries *series_power = new QLineSeries();

    for(i = 0; i < P.size(); i++)
    {
         series_power->append(F[i], P[i]);
    }

    Chart *chart_power = new Chart();

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


Chart *setChart_HRV_2_hist(std::vector<int> hist_values,std::vector<double> bin_centers)
{
/************************************HISTOGRAM********************************************/

    unsigned int i;

    //set dla osi X
    QBarSet *set0 = new QBarSet("Number of RR intervals");
    //seria danych dla hist., oś y
    QBarSeries *series = new QBarSeries();


    std::vector<std::string> string_bin_centers;


    QList<QString> list_bin_centers;

    for(i = 0; i < bin_centers.size(); i++)
    {
        list_bin_centers.append(QString::number(bin_centers[i]));
    }

    //int to double
    std::vector<qreal> nowy_wektor(hist_values.begin(), hist_values.end());

    //przeksztalcenie na QVector
    QVector<double> nowy_wektor_q = QVector<double>::fromStdVector(nowy_wektor);
    //   nowy_wektor_q.fromStdVector(nowy_wektor);

    //QVector double to list double
    QList<qreal> nowy_wektor_list = nowy_wektor_q.toList();

    //ustawienie serii danych dla y
    set0->append(nowy_wektor_list);
    series->append(set0);


    Chart *hist = new Chart();
    hist->addSeries(series);
    hist->setTitle("RR intervals histogram");
    hist->setAnimationOptions(QChart::AllAnimations);


    //QFont ChartFont("Arial", 14, QFont::Bold);

    hist->setTitleFont(ChartFont);

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(list_bin_centers);

    axis->setLabelsAngle(-90);

    axis->setTitleText("Duration");
    hist->createDefaultAxes();

    hist->setAxisX(axis);


    hist->legend()->setVisible(true);
    hist->legend()->setAlignment(Qt::AlignBottom);
    return hist;

}



Chart *setChart_HRV2_poincare(double SD1,double SD2,std::vector<double> poincareplot_x_axis,std::vector<double> poincareplot_y_axis,double centroid_x,double centroid_y)
{

/************************************POINCARE********************************************/



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

    Chart * chart_poincare = new Chart();

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

Chart *setChart_HRV_DFA(std::vector<double> log_window_sizes, std::vector<double> log_fluctuation, std::vector<double> line_alfa1, std::vector<double> line_alfa2)
{
    unsigned long i = 0;
    //unsigned long s = 6;
    unsigned long s = 3;

    //seria danych bazowych - sygnał EKG
    QScatterSeries *series_scatter = new QScatterSeries();
    series_scatter->setMarkerSize(6);


    QLineSeries * series_alpha1 = new QLineSeries();
    QLineSeries * series_alpha2 = new QLineSeries();


    series_alpha1->setName("Alpha1");
    series_alpha2->setName("Alpha2");

    //przygotowanie serii dla sygnalu EKG
    for(i = 0; i < log_window_sizes.size(); i++)
    {
        series_scatter->append(log_window_sizes[i],log_fluctuation[i]);
    }
    for(i = 0; i < log_window_sizes.size(); i++)
    {
        if(i < s)
        {
            series_alpha1->append(log_window_sizes[i], line_alfa1[i]);
        }
        else
        {
           series_alpha2->append(log_window_sizes[i], line_alfa2[i-s]);
        }

    }


    //Tworzenie nowego wykresu
    Chart *chart = new Chart();

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

Chart *setChart_Heart_Class(std::vector<int> qrsPosition,std::vector<double> heartClass,std::vector<double> samples)
{
    unsigned int i = 0;

    std::vector<int> dane_x(samples.size());
    std::iota(dane_x.begin(), dane_x.end(), 1);


//seria danych bazowych - sygnał EKG
QLineSeries *series_line = new QLineSeries();

//seria danych - wektor qrs
QScatterSeries *series_scatter2 = new QScatterSeries();
QScatterSeries *series_scatter3 = new QScatterSeries();
QScatterSeries *series_scatter4 = new QScatterSeries();


for(i = 0; i < qrsPosition.size(); i++)
{
    if(heartClass[i] == 0)
        series_scatter2->append(qrsPosition[i], samples[qrsPosition[i] - 1]);
     else if(heartClass[i] == 1)
        series_scatter3->append(qrsPosition[i], samples[qrsPosition[i] - 1]);
    else if(heartClass[i] == 2)
         series_scatter4->append(qrsPosition[i], samples[qrsPosition[i] - 1]);
}

//przygotowanie serii dla sygnalu EKG
for(i = 0; i < dane_x.size(); i++)
{
    series_line->append(dane_x[i], samples[i]);
}


series_scatter2->setMarkerShape(QScatterSeries::MarkerShapeCircle);
series_scatter3->setMarkerShape(QScatterSeries::MarkerShapeCircle);
series_scatter4->setMarkerShape(QScatterSeries::MarkerShapeCircle);

//Tworzenie nowego wykresu
Chart *chart = new Chart();


chart->legend()->hide();


chart->setTitle("Heart Class");

auto max = *max_element(std::begin(samples), std::end(samples));
auto min = *min_element(std::begin(samples), std::end(samples));
QValueAxis * axis_y = new QValueAxis();
axis_y->setRange(min-2,max+2);
axis_y->setTitleText("Voltage [mV]");


QValueAxis * axis_x = new QValueAxis();
axis_x->setRange(0,samples.size()+2);
axis_x->setTitleText("Samples");


series_scatter2->setMarkerSize(DEFAULT_MARKER_SIZE);
series_scatter2->setName("Normal");


series_scatter3->setMarkerSize(DEFAULT_MARKER_SIZE);
series_scatter3->setName("Supra Ventricular");


series_scatter4->setMarkerSize(DEFAULT_MARKER_SIZE);
series_scatter4->setName("Ventricular");

series_line->setName("ECG Signal");

//dodanie serii danych
chart->addSeries(series_line);
chart->addSeries(series_scatter2);
chart->addSeries(series_scatter3);
chart->addSeries(series_scatter4);

chart->setAxisX(axis_x,series_line);
chart->setAxisY(axis_y,series_line);

chart->setAxisX(axis_x,series_scatter2);
chart->setAxisY(axis_y,series_scatter2);

chart->setAxisX(axis_x,series_scatter3);
chart->setAxisY(axis_y,series_scatter3);

chart->setAxisX(axis_x,series_scatter4);
chart->setAxisY(axis_y,series_scatter4);
chart->setAnimationOptions(QChart::AllAnimations);



chart->setTitleFont(ChartFont);
chart->legend()->show();
chart->legend()->setAlignment(Qt::AlignRight);

return chart;
}
