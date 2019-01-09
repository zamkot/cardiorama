#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ExportData->hide();
    ui->ExportData_2->hide();

    setWindowTitle("ECG ANALYSIS");
    QPixmap pix("/home/krypto/Pulpit/QT/ecg");
       // int w = ui->label_pic->width();
       // int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(1300,150));

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
                "All files (*.*)"
                );
    ui->textBrowser->setText(QString("File path: %1").arg(filename));
    //QMessageBox::information(this,tr("File Name"),filename);
    loadFile(filename);

}

void MainWindow::loadFile(QString path)
{
    analysis.loadFile(path.toUtf8().constData());
}


void MainWindow::on_Hilbert_clicked()
{
    short wybor = 0;
    RPeaksConfig rPeaksConfig{wybor};
    analysis.sendRPeaksConfig(rPeaksConfig);

}


void MainWindow::on_PanTompkins_clicked()
{
    short wybor = 1;
    RPeaksConfig rPeaksConfig{wybor};
    analysis.sendRPeaksConfig(rPeaksConfig);

}


void MainWindow::on_RunECG_BASELINE_clicked()
{


}

void MainWindow::on_RunR_PEAKS_clicked()
{
     ui->ExportData->show();
     ui->Tab->setCurrentIndex(0);
     QWidget *R_PEAKS = QApplication::activeWindow();
     QTableWidget *Rtable = R_PEAKS->findChild<QTableWidget*>("R_table");
     Rtable->clearContents();

     auto wynik = analysis.runRPeaks();
     for (size_t i =0;i<wynik.rpeaks.size();i++)
     {
         qDebug()<<wynik.rpeaks[i];

     }

     int convertlength = static_cast<int>(wynik.rpeaks.size());
     Rtable->setRowCount(convertlength);

     int *array = wynik.rpeaks.data();

     for (size_t i =0;i<wynik.rpeaks.size();i++)
     {
         for(int j = 0; j<convertlength; j++)
         {
             QTableWidgetItem* newItem = new QTableWidgetItem();
             newItem->setText(QString::number(array[j]));
             Rtable->setItem(j,0,newItem);
         }
     }
}

void MainWindow::on_RunWAVES_clicked()
{
    ui->ExportData->show();
    ui->Tab->setCurrentIndex(1);
    QWidget *Waves = QApplication::activeWindow();
    QTableWidget *Wtable = Waves->findChild<QTableWidget*>("W_table");
    Wtable->clearContents();
    auto wynik = analysis.runWaves();
    for (size_t i =0;i<wynik.qrsOnset.size();i++)
    {
        qDebug()<<wynik.qrsOnset[i];
    }

    for (size_t i =0;i<wynik.qrsEnd.size();i++)
    {
        qDebug()<<wynik.qrsEnd[i];
    }

    for (size_t i =0;i<wynik.tEnd.size();i++)
    {
        qDebug()<<wynik.tEnd[i];
    }

    for (size_t i =0;i<wynik.pOnset.size();i++)
    {
        qDebug()<<wynik.pOnset[i];
    }

    for (size_t i =0;i<wynik.pEnd.size();i++)
    {
        qDebug()<<wynik.pEnd[i];
    }

    int convertlength = static_cast<int>(wynik.qrsOnset.size());
    Wtable->setRowCount(convertlength);

    int *array = wynik.qrsOnset.data();
     int *array1 = wynik.qrsEnd.data();
      int *array2 = wynik.tEnd.data();
       int *array3 = wynik.pOnset.data();
        int *array4 = wynik.pEnd.data();

    for (size_t i =0;i<wynik.qrsOnset.size();i++)
    {
        for(int j = 0; j<convertlength; j++)
        {
            QTableWidgetItem* newItem1 = new QTableWidgetItem();
            newItem1->setText(QString::number(array[j]));
            Wtable->setItem(j,0,newItem1);
            QTableWidgetItem* newItem2 = new QTableWidgetItem();
            newItem2->setText(QString::number(array1[j]));
            Wtable->setItem(j,1,newItem2);
            QTableWidgetItem* newItem3 = new QTableWidgetItem();
            newItem3->setText(QString::number(array2[j]));
            Wtable->setItem(j,2,newItem3);
            QTableWidgetItem* newItem4= new QTableWidgetItem();
            newItem4->setText(QString::number(array3[j]));
            Wtable->setItem(j,3,newItem4);
            QTableWidgetItem* newItem5 = new QTableWidgetItem();
            newItem5->setText(QString::number(array4[j]));
            Wtable->setItem(j,4,newItem5);
         }
    }
}


void MainWindow::on_RunT_WAVES_ALT_clicked()
{

    ui->Tab->setCurrentIndex(2);

}

void MainWindow::on_RunHRV1_clicked()
{

    ui->Tab->setCurrentIndex(3);

}

void MainWindow::on_RunHRV2_clicked()
{
    ui->Tab->setCurrentIndex(4);

}

void MainWindow::on_RunHRV_DFA_clicked()
{
    ui->Tab->setCurrentIndex(5);

}

void MainWindow::on_RunHEART_CLASS_clicked()
{

    ui->Tab->setCurrentIndex(6);

}


