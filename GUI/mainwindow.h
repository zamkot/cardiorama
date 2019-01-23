#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../include/AnalysisInterface.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OpenFile_clicked();

    void on_RunR_PEAKS_clicked();

    void on_RunWAVES_clicked();

    void on_Hilbert_clicked();

    void on_PanTompkins_clicked();

    void on_RunECG_BASELINE_clicked();

    void on_RunT_WAVES_ALT_clicked();

    void on_RunHRV1_clicked();

    void on_RunHRV2_clicked();

    void on_RunHRV_DFA_clicked();

    void on_RunHEART_CLASS_clicked();

    void on_nr_of_bins_valueChanged(int arg1);

    void on_Butterworth_clicked();

    void on_WD_clicked();

private:
    Ui::MainWindow *ui;
    Analysis analysis;

    //private methods
    void loadFile(QString);

};

#endif // MAINWINDOW_H
