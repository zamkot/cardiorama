#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
{   QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All files (*.*)"
                );
    ui->textBrowser->setText(QString("File path: %1").arg(filename));
    //QMessageBox::information(this,tr("File Name"),filename);
    loadFile(filename);

}

void MainWindow::loadFile(QString)
{
    analysis.loadFile(path.toUtf8().constData());
}
