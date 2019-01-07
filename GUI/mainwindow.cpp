#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QMessageBox>
#include<QPixmap>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ECG ANALYSIS");
    QPixmap pix("/home/krypto/Pulpit/ecg");
       // int w = ui->label_pic->width();
       // int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(1300,150));
    QPixmap pix2("/home/krypto/Pobrane/tachf2");
    ui->label_2->setPixmap(pix2.scaled(700,100));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_OpenFile_clicked()
{   QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All files (*.*)"
                );
    //QMessageBox::information(this,tr("File Name"),filename);

    ui->textBrowser->setText(QString("File path: %1").arg(filename));

}

