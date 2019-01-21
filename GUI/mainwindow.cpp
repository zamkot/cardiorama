#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include "chart.h"
#include "plot.h"
#include "chartview.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QValueAxis>

//Zmiany w chartach: alternans! nie alterans!

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ECG ANALYSIS");
    ui->Tab->setCurrentIndex(0);

    // AUTO configuraton
    ui->Hilbert->setChecked(true);
    short choice = 0;
    RPeaksConfig rPeaksConfig{choice};
    analysis.sendRPeaksConfig(rPeaksConfig);

    ui->Buttherworth->setChecked(true);
    //TODO enum + wywołanie przycisków
    //EcgBaselineConfig ecgBaselineConfig{choice};
    //analysis.sendEcgBaselineConfig(ecgBaselineConfig);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenFile_clicked()
{
    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                QDir::currentPath(),
                tr("DAT files(*.csv)"));

    ui->textBrowser->setText(QString("File path: %1").arg(filename));
    loadFile(filename);

}

void MainWindow::loadFile(QString path)
{
    analysis.loadFile(path.toUtf8().constData());
}


void MainWindow::on_Hilbert_clicked()
{
    short choice = 0;
    RPeaksConfig rPeaksConfig{choice};
    analysis.sendRPeaksConfig(rPeaksConfig);

}

void MainWindow::on_PanTompkins_clicked()
{
    short choice = 1;
    RPeaksConfig rPeaksConfig{choice};
    analysis.sendRPeaksConfig(rPeaksConfig);

}

void MainWindow::on_RunECG_BASELINE_clicked()
{
    ui->Tab->setCurrentIndex(0);

    auto result = analysis.runEcgBaseline();
    Chart *chart = setChart_ECG_Baseline(result.samples);
    QWidget *ECG_BASELINE= QApplication::activeWindow();
    QScrollArea *scrollB = ECG_BASELINE->findChild< QScrollArea*>("scrollAreaB");
    ChartView *baseline = new ChartView(chart, ECG_BASELINE);
    chart->axisX()->setRange(0,50);
    scrollB->setWidget(baseline);
    baseline->setRenderHints(QPainter::Antialiasing);
    baseline->grabGesture(Qt::PanGesture);
    baseline->grabGesture(Qt::PinchGesture);


}

void MainWindow::on_RunR_PEAKS_clicked()
{

     ui->Tab->setCurrentIndex(1);

     auto result = analysis.runRPeaks();
     for (size_t i =0;i<result.rpeaks.size();i++)
     {
         qDebug()<<result.rpeaks[i];

     }

     Chart *chart = setChart_R_peaks(result.rpeaks);
     QWidget *R_PEAKS= QApplication::activeWindow();
     QScrollArea *scrollR = R_PEAKS->findChild< QScrollArea*>("scrollAreaR");
     ChartView *plot = new ChartView(chart, R_PEAKS);
     chart->axisX()->setRange(0,50);
     scrollR->setWidget(plot);

     //ChartView *plot = R_PEAKS->findChild<ChartView*>("RPEAKSCHART");
     //plot->setChart(chart);
     //rectangular zooming sucks
     //plot->setRubberBand( QChartView::RectangleRubberBand);
     plot->setRenderHints(QPainter::Antialiasing);
     plot->grabGesture(Qt::PanGesture);
     plot->grabGesture(Qt::PinchGesture);

}


void MainWindow::on_RunWAVES_clicked()
{
    ui->Tab->setCurrentIndex(2);

    auto result = analysis.runWaves();

    Chart *chart = setChart_QRS(result.Q_wektor,result.S_wektor,result.QRSonset_wektor,result.QRSend_wektor,result.P_wektor,result.Pend_wektor,
                                result.Ponset_wektor,result.T_wektor);

    QWidget *WAVES= QApplication::activeWindow();
    QScrollArea *scrollW = WAVES->findChild< QScrollArea*>("scrollAreaW");
    ChartView *plot = new ChartView(chart, WAVES);
    chart->axisX()->setRange(0,15);
    scrollW->setWidget(plot);

    plot->setRenderHints(QPainter::Antialiasing);
    plot->grabGesture(Qt::PanGesture);
    plot->grabGesture(Qt::PinchGesture);

}


void MainWindow::on_RunT_WAVES_ALT_clicked()
{

    ui->Tab->setCurrentIndex(3);
    auto result = analysis.runTWaves();
    Chart *chart = setChart_T_Waves_ALT(result.resultTWA);
    QWidget *T_WAVES_ALT= QApplication::activeWindow();
    QScrollArea *scrollT = T_WAVES_ALT->findChild< QScrollArea*>("scrollAreaT");
    ChartView *plot = new ChartView(chart,T_WAVES_ALT);
    //chart->axisX()->setRange(0,50);
    scrollT->setWidget(plot);

    plot->setRenderHints(QPainter::Antialiasing);
    plot->grabGesture(Qt::PanGesture);
    plot->grabGesture(Qt::PinchGesture);

    QTableWidget *MAXTWA = T_WAVES_ALT->findChild<QTableWidget*>("MAXTWA");
    MAXTWA->clearContents();
    MAXTWA->setRowCount(1);

    QTableWidgetItem* newItem1 = new QTableWidgetItem();
    newItem1->setText(QString::number(result.maxTWA));
    MAXTWA->setItem(0,0,newItem1);


}

void MainWindow::on_RunHRV1_clicked()
{

    ui->Tab->setCurrentIndex(4);
    auto result = analysis.runHrv1();
    Chart *chart = setChart_HRV1(result.F,result.P,result.ULF,result.VLF,result.LF,result.HF);
    QWidget *HRV1= QApplication::activeWindow();
    QScrollArea *scrollH1 = HRV1->findChild< QScrollArea*>("scrollAreaH1");
    ChartView *plot = new ChartView(chart,HRV1);
    //chart->axisX()->setRange(0,50);
    scrollH1->setWidget(plot);

    plot->setRenderHints(QPainter::Antialiasing);
    plot->grabGesture(Qt::PanGesture);
    plot->grabGesture(Qt::PinchGesture);

}

void MainWindow::on_RunHRV2_clicked()
{
    ui->Tab->setCurrentIndex(5);

    QWidget *HRV2= QApplication::activeWindow();
    QScrollArea *scrollH2P = HRV2->findChild< QScrollArea*>("scrollAreaH2P");
    QScrollArea *scrollH2H = HRV2->findChild< QScrollArea*>("scrollAreaH2H");
    auto result = analysis.runHrv2();
    Chart *histogram = setChart_HRV_2_hist(result.hist_values,result.bin_centers);
    ChartView *plot = new ChartView(histogram,HRV2);
    scrollH2H->setWidget(plot);
    plot->setRenderHints(QPainter::Antialiasing);
    plot->grabGesture(Qt::PanGesture);
    plot->grabGesture(Qt::PinchGesture);

    Chart *poincare = setChart_HRV2_poincare(result.SD1,result.SD2,result.poincareplot_x_axis,result.poincareplot_y_axis,result.centroid_x,result.centroid_y);
    ChartView *plot2 = new ChartView(poincare,HRV2);
    scrollH2P->setWidget(plot2);
    plot2->setRenderHints(QPainter::Antialiasing);
    plot2->grabGesture(Qt::PanGesture);
    plot2->grabGesture(Qt::PinchGesture);

    QTableWidget *HRV2TAB = HRV2->findChild<QTableWidget*>("HRV2TAB");
    HRV2TAB->clearContents();
    HRV2TAB->setRowCount(1);

    QTableWidgetItem* newItem1 = new QTableWidgetItem();
    newItem1->setText(QString::number(result.tinn));
    HRV2TAB->setItem(0,0,newItem1);
    QTableWidgetItem* newItem2 = new QTableWidgetItem();
    newItem2->setText(QString::number(result.hrv_index));
    HRV2TAB->setItem(0,1,newItem2);
    QTableWidgetItem* newItem3 = new QTableWidgetItem();
    newItem3->setText(QString::number(result.SD1));
    HRV2TAB->setItem(0,2,newItem3);
    QTableWidgetItem* newItem4 = new QTableWidgetItem();
    newItem4->setText(QString::number(result.SD2));
    HRV2TAB->setItem(0,3,newItem4);

}

void MainWindow::on_RunHRV_DFA_clicked()
{
    ui->Tab->setCurrentIndex(6);

    Chart *chart = setChart_HRV_DFA();
    QWidget *HRVD= QApplication::activeWindow();
    QScrollArea *scrollHD = HRVD->findChild< QScrollArea*>("scrollAreaHD");
    ChartView *plot = new ChartView(chart,HRVD);
    //chart->axisX()->setRange(0,50);
    scrollHD->setWidget(plot);

    plot->setRenderHints(QPainter::Antialiasing);
    plot->grabGesture(Qt::PanGesture);
    plot->grabGesture(Qt::PinchGesture);
}

void MainWindow::on_RunHEART_CLASS_clicked()
{

    ui->Tab->setCurrentIndex(7);

}



