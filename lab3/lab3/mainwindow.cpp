#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setSteps();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSteps()
{
    ui->amountSteps->setValue(10);
}


void MainWindow::on_amountSteps_valueChanged(int arg1)
{
    ui->openGLWidget->setAmountSteps(arg1);
}

