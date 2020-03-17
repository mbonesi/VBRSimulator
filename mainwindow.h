#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vbrstatemachine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    uint _interval;
    uint _dly;
    uint _setpoint;
    uint _step;
    uint _variation;

    VBRStateMachine *pVBRBoard = nullptr;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonSet_clicked();

    void on_SliderProbes_valueChanged(int value);

    void on_pushButtonStartOps_clicked();

    void on_pushButtonStopOps_clicked();

    void onDrivenOutputValueChanged(uint uiNewVal);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
