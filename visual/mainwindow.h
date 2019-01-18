#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setChart_R_peaks();
    void setChart_HRV_1();
    void setChart_HRV_2();
    void setChart_HVR_DFA();
    void setChart_ECG_Baseline();
    void setChart_QRS();
    void setChart_T_Waves_ALT();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
