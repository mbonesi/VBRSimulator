#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _interval(500)
    , _dly(5)
    , _setpoint(40)
    , _step(2)
    , _variation(10)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_interval->setText(QString("%0").arg(_interval));
    ui->lineEdit_dly->setText(QString("%0").arg(_dly));
    ui->lineEdit_step->setText(QString("%0").arg(_step));
    ui->lineEdit_variation->setText(QString("%0").arg(_variation));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonSet_clicked()
{
    uint setPoint;
    bool bOk = false;
    setPoint = ui->lineEditSetPoint->text().toUInt(&bOk);
    if(bOk)
    {
        if(pVBRBoard)
            pVBRBoard->SetValue(setPoint);
    }
}

void MainWindow::on_SliderProbes_valueChanged(int value)
{
    ui->ProbesValue->setText(QString("Probes Value: %0").arg(value));
    if(pVBRBoard)
        pVBRBoard->InputsLevel = static_cast<uint>(value);
}

void MainWindow::on_pushButtonStartOps_clicked()
{
    bool bOk = false;
    if(pVBRBoard != nullptr)
        delete pVBRBoard;    

    _interval = ui->lineEdit_interval->text().toUInt(&bOk);
    _dly = ui->lineEdit_dly->text().toUInt(&bOk);
    _step = ui->lineEdit_step->text().toUInt(&bOk);
    _variation = ui->lineEdit_variation->text().toUInt(&bOk);

    pVBRBoard = new VBRStateMachine(_interval, _dly, _step, _variation);
    connect(pVBRBoard, &VBRStateMachine::drivenOutputChanged, this, &MainWindow::onDrivenOutputValueChanged);

    //collect user input
    on_pushButtonSet_clicked();
    on_SliderProbes_valueChanged(ui->SliderProbes->value());

    //start rolling
    pVBRBoard->Start();
}

void MainWindow::on_pushButtonStopOps_clicked()
{
    pVBRBoard->Stop();
    delete pVBRBoard;
    pVBRBoard = nullptr;
}

void MainWindow::onDrivenOutputValueChanged(uint uiNewVal)
{
    ui->OutputDriven->setText(QString("%0").arg(uiNewVal));
    ui->progressBar->setValue(static_cast<int>(uiNewVal));
}
