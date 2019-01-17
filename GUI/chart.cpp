#include <chart.h>

QT_CHARTS_USE_NAMESPACE

QChart *setChart_R_peaks()
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
    axis_y->setRange(0,30);
    axis_y->setTitleText("Voltage [mV]");


    QValueAxis * axis_x = new QValueAxis();
    axis_x->setRange(0,dane_y.size());
    axis_x->setTitleText("Samples");


    //dodanie serii danych
    chart->addSeries(series_scatter2);
    chart->addSeries(series_line);

    chart->setAxisX(axis_x,series_line);
    chart->setAxisY(axis_y,series_line);

    chart->setAxisX(axis_x,series_scatter2);
    chart->setAxisY(axis_y,series_scatter2);
    chart->setAnimationOptions(QChart::AllAnimations);

    return chart;
   // ui->chart_R->setChart(chart);
   // ui->chart_R->setRenderHints(QPainter::Antialiasing);
}


QChart *setChart_HRV_2()
{
/************************************HISTOGRAM********************************************/

    unsigned int i;

    //set dla osi X
    QBarSet *set0 = new QBarSet("Liczba załamków RR w danym czasie");
    //seria danych dla hist., oś y
    QBarSeries *series = new QBarSeries();


    //przedziały
    std::vector<double> przedzialy(10);
    przedzialy = {0,1,2,3,4,5,6,7,8,9};

    std::vector<std::string> string_przedzialy;


    QList<QString> list_przedzialy;

    for(i = 0; i < przedzialy.size(); i++)
    {
        list_przedzialy.append(QString::number(przedzialy[i]));
    }

    //tu będą wartości dla danych przedziałów - dane y
    std::vector<int> int_vector_y(10);
    int_vector_y = {1,2,3,4,5,6,7,8,9,1};

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

   return hist;


/************************************POINCARE********************************************/



//Error: requested more data

}

QChart *setChart_ECG_Baseline()
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
     chart->createDefaultAxes();
     chart->zoomOut();
     chart->setAnimationOptions(QChart::AllAnimations);


   return chart;
}

