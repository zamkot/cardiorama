#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include "chart.h"


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
                tr("DAT files(*.dat)"));

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

    QWidget *ECG_BASELINE= QApplication::activeWindow();
    QChartView *plot = ECG_BASELINE->findChild<QChartView*>("BASELINE");
    QChart *baseline =  setChart_ECG_Baseline();
    plot->setChart(baseline);
    plot->setRenderHints(QPainter::Antialiasing);

}

void MainWindow::on_RunR_PEAKS_clicked()
{

     ui->Tab->setCurrentIndex(1);

     auto result = analysis.runRPeaks();
     for (size_t i =0;i<result.rpeaks.size();i++)
     {
         qDebug()<<result.rpeaks[i];

     }

     QWidget *R_PEAKS= QApplication::activeWindow();
     QChartView *plot = R_PEAKS->findChild<QChartView*>("RPEAKSCHART");
     QChart *chart = setChart_R_peaks();
     plot->setChart(chart);
     plot->setRenderHints(QPainter::Antialiasing);
}

void MainWindow::on_RunWAVES_clicked()
{
    ui->Tab->setCurrentIndex(2);

    auto result = analysis.runWaves();
    for (size_t i =0;i<result.qrsOnset.size();i++)
    {
        qDebug()<<result.qrsOnset[i];
    }

    for (size_t i =0;i<result.qrsEnd.size();i++)
    {
        qDebug()<<result.qrsEnd[i];
    }

    for (size_t i =0;i<result.tEnd.size();i++)
    {
       qDebug()<<result.tEnd[i];
    }

    for (size_t i =0;i<result.pOnset.size();i++)
    {
        qDebug()<<result.pOnset[i];
    }

    for (size_t i =0;i<result.pEnd.size();i++)
    {
       qDebug()<<result.pEnd[i];
    }

}


void MainWindow::on_RunT_WAVES_ALT_clicked()
{

    ui->Tab->setCurrentIndex(3);

}

void MainWindow::on_RunHRV1_clicked()
{

    ui->Tab->setCurrentIndex(4);

}

void MainWindow::on_RunHRV2_clicked()
{
    ui->Tab->setCurrentIndex(5);

    QWidget *HRV2= QApplication::activeWindow();
    QChartView *bar_chart = HRV2->findChild<QChartView*>("HRV2CHART");
    QChart *histogram = setChart_HRV_2();
    bar_chart->setChart(histogram);
    bar_chart->setRenderHints(QPainter::Antialiasing);
}

void MainWindow::on_RunHRV_DFA_clicked()
{
    ui->Tab->setCurrentIndex(6);

}

void MainWindow::on_RunHEART_CLASS_clicked()
{

    ui->Tab->setCurrentIndex(7);

}


