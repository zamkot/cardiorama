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

private slots:
    void on_OpenFile_clicked();

private:
    Ui::MainWindow *ui;
    Analysis analysis;

    //private methods
    void loadFile(QString);
};

#endif // MAINWINDOW_H
