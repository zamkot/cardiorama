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


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ECG ANALYSIS");
    ui->Tab->setCurrentIndex(0);
    ui->sampling_f->setRange(0,500);
    ui->sampling_f->setValue(360);
    auto result = ui->sampling_f->value();
    // AUTO configuraton
    ui->Hilbert->setChecked(true);
    RPeaksConfig::Algorithm choice1;
    choice1 = RPeaksConfig::Algorithm::HILBERT;
    RPeaksConfig rPeaksConfig{choice1,result};
    analysis.sendRPeaksConfig(rPeaksConfig);

    ui->Butterworth->setChecked(true);
    EcgBaselineConfig::Algorithm choice2;
    choice2 = EcgBaselineConfig::Algorithm::BUTTERWORTH;
    EcgBaselineConfig ecgBaselineConfig{choice2};
    analysis.sendEcgBaselineConfig(ecgBaselineConfig);

    ui->nr_of_bins->setRange(70,150);
    ui->nr_of_bins->setSingleStep(10);

    ui->sampling_f->setSingleStep(10);

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



void MainWindow::on_Butterworth_clicked()
{
    EcgBaselineConfig::Algorithm choice;
    choice = EcgBaselineConfig::Algorithm::BUTTERWORTH;
    EcgBaselineConfig ecgBaselineConfig{choice};

    if(ecgBaselineConfig.algorithm == EcgBaselineConfig::Algorithm::BUTTERWORTH)
      {qDebug()<<QString("Butter");}
     analysis.sendEcgBaselineConfig(ecgBaselineConfig);
};

void MainWindow::on_WD_clicked()
{
    EcgBaselineConfig::Algorithm choice;
    choice = EcgBaselineConfig::Algorithm::WAVELET;
    EcgBaselineConfig ecgBaselineConfig2{choice};

    if(ecgBaselineConfig2.algorithm == EcgBaselineConfig::Algorithm::WAVELET)
         {qDebug()<<QString("WD");}
    analysis.sendEcgBaselineConfig(ecgBaselineConfig2);
}


void MainWindow::on_Hilbert_clicked()
{
    auto result = ui->sampling_f->value();
    RPeaksConfig::Algorithm choice;
    choice = RPeaksConfig::Algorithm::HILBERT;
    RPeaksConfig rPeaksConfig{choice,result};


    if(rPeaksConfig.algorithm == RPeaksConfig::Algorithm::HILBERT)
      {qDebug()<<QString("Hilbert");}
     analysis.sendRPeaksConfig(rPeaksConfig);

}

void MainWindow::on_PanTompkins_clicked()
{   // here sending also sample frequency
    auto result = ui->sampling_f->value();
    RPeaksConfig::Algorithm choice;
    choice = RPeaksConfig::Algorithm::PAN_TOMPKINS;
    RPeaksConfig rPeaksConfig{choice,result};

    if(rPeaksConfig.algorithm == RPeaksConfig::Algorithm::PAN_TOMPKINS)
      {qDebug()<<QString("Tompkins");}
     analysis.sendRPeaksConfig(rPeaksConfig);
}


void MainWindow::on_nr_of_bins_valueChanged(int arg1)
{

    Hrv2Config hrv2Config{arg1};
    analysis.sendHrv2Config(hrv2Config);

}


void MainWindow::on_RunECG_BASELINE_clicked()
{
    ui->Tab->setCurrentIndex(0);

    auto result = analysis.runEcgBaseline();
    Chart *chart = setChart_ECG_Baseline(result.samples);
    QWidget *ECG_BASELINE= QApplication::activeWindow();
    QScrollArea *scrollB = ECG_BASELINE->findChild< QScrollArea*>("scrollAreaB");
    ChartView *baseline = new ChartView(chart, ECG_BASELINE);
    chart->axisX()->setRange(0,2500);
    scrollB->setWidget(baseline);
    baseline->setRenderHints(QPainter::Antialiasing);
    baseline->grabGesture(Qt::PanGesture);
    baseline->grabGesture(Qt::PinchGesture);


}

void MainWindow::on_RunR_PEAKS_clicked()
{

     ui->Tab->setCurrentIndex(1);

     auto result = analysis.runRPeaks();
     auto result2 = analysis.runEcgBaseline();
     for (size_t i =0;i<result.rpeaks.size();i++)
     {
         qDebug()<<result.rpeaks[i];

     }

     Chart *chart = setChart_R_peaks(result.rpeaks,result2.samples);
     QWidget *R_PEAKS= QApplication::activeWindow();
     QScrollArea *scrollR = R_PEAKS->findChild< QScrollArea*>("scrollAreaR");
     ChartView *plot = new ChartView(chart, R_PEAKS);
     chart->axisX()->setRange(0,2500);
     scrollR->setWidget(plot);

     plot->setRenderHints(QPainter::Antialiasing);
     plot->grabGesture(Qt::PanGesture);
     plot->grabGesture(Qt::PinchGesture);

}


void MainWindow::on_RunWAVES_clicked()
{
    ui->Tab->setCurrentIndex(2);

    auto result = analysis.runWaves();
    auto result2 = analysis.runEcgBaseline();
    auto result3 = analysis.runRPeaks();

    Chart *chart = setChart_QRS(result.Q_wektor,result.QRSonset_wektor,result.QRSend_wektor,result.P_wektor,result.Pend_wektor,
                                result.Ponset_wektor,result.T_wektor,result3.rpeaks,result2.samples);

    QWidget *WAVES= QApplication::activeWindow();
    QScrollArea *scrollW = WAVES->findChild< QScrollArea*>("scrollAreaW");
    ChartView *plot = new ChartView(chart, WAVES);
    chart->axisX()->setRange(0,2500);
    scrollW->setWidget(plot);

    plot->setRenderHints(QPainter::Antialiasing);
    plot->grabGesture(Qt::PanGesture);
    plot->grabGesture(Qt::PinchGesture);

}


void MainWindow::on_RunT_WAVES_ALT_clicked()
{

    ui->Tab->setCurrentIndex(3);
    auto result = analysis.runTWaves();
    auto result2 = analysis.runEcgBaseline();
    Chart *chart = setChart_T_Waves_ALT(result.resultTWA,result2.samples);
    QWidget *T_WAVES_ALT= QApplication::activeWindow();
    QScrollArea *scrollT = T_WAVES_ALT->findChild< QScrollArea*>("scrollAreaT");
    ChartView *plot = new ChartView(chart,T_WAVES_ALT);
    chart->axisX()->setRange(0,2500);
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

    auto result = analysis.runHrvDfa();
    Chart *chart = setChart_HRV_DFA(result.log_window_sizes,result.log_fluctuation,result.line_alfa1,result.line_alfa2);
    QWidget *HRVD= QApplication::activeWindow();
    QScrollArea *scrollHD = HRVD->findChild< QScrollArea*>("scrollAreaHD");
    ChartView *plot = new ChartView(chart,HRVD);
    //chart->axisX()->setRange(0,50);
    scrollHD->setWidget(plot);

    plot->setRenderHints(QPainter::Antialiasing);
    plot->grabGesture(Qt::PanGesture);
    plot->grabGesture(Qt::PinchGesture);

    QTableWidget *Alpha = HRVD->findChild<QTableWidget*>("Alpha");
    Alpha->clearContents();


    int convertlength = static_cast<int>(result.line_alfa1.size());
    Alpha->setRowCount(convertlength);
    double *array = result.line_alfa1.data();

    for(int j = 0; j<convertlength; j++)
    {
        QTableWidgetItem* newItem = new QTableWidgetItem();
        newItem->setText(QString::number(array[j]));
        Alpha->setItem(j,0,newItem);
    }

    int convertlength2 = static_cast<int>(result.line_alfa2.size());
    Alpha->setRowCount(convertlength2);
    double *array2 = result.line_alfa2.data();

    for(int j = 0; j<convertlength2; j++)
    {
        QTableWidgetItem* newItem2 = new QTableWidgetItem();
        newItem2->setText(QString::number(array2[j]));
        Alpha->setItem(j,1,newItem2);
    }

}

void MainWindow::on_RunHEART_CLASS_clicked()
{
    ui->Tab->setCurrentIndex(7);

    auto result = analysis.runHeartClass();
    auto result2 = analysis.runEcgBaseline();

    Chart *chart = setChart_Heart_Class(result.qrsPosition,result.heartClass,result2.samples);
    QWidget *HEART_CLASS = QApplication::activeWindow();
    QScrollArea *scrollR = HEART_CLASS->findChild< QScrollArea*>("scrollAreaHC");
    ChartView *plot = new ChartView(chart, HEART_CLASS);
    chart->axisX()->setRange(0,2500);
    scrollR->setWidget(plot);


    plot->setRenderHints(QPainter::Antialiasing);
    plot->grabGesture(Qt::PanGesture);
    plot->grabGesture(Qt::PinchGesture);
}









