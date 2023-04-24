#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setPrim();
    setVisible();
    setSFactor();
    setDFactor();
    setScissor();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPrim()
{
    primTypes.insert("GL_POINTS", GL_POINTS);
    primTypes.insert("GL_LINES", GL_LINES);
    primTypes.insert("GL_LINE_STRIP", GL_LINE_STRIP);
    primTypes.insert("GL_LINE_LOOP", GL_LINE_LOOP);
    primTypes.insert("GL_TRIANGLES", GL_TRIANGLES);
    primTypes.insert("GL_TRIANGLE_STRIP", GL_TRIANGLE_STRIP);
    primTypes.insert("GL_TRIANGLE_FAN", GL_TRIANGLE_FAN);
    primTypes.insert("GL_POLYGON", GL_POLYGON);

    ui->comboBox->addItems(primTypes.keys());
    ui->comboBox->setCurrentText("GL_POINTS");
}

void MainWindow::setVisible()
{
    visibleTypes.insert("GL_NEVER", GL_NEVER);
    visibleTypes.insert("GL_LESS", GL_LESS);
    visibleTypes.insert("GL_EQUAL", GL_EQUAL);
    visibleTypes.insert("GL_LEQUAL", GL_LEQUAL);
    visibleTypes.insert("GL_GREATER", GL_GREATER);
    visibleTypes.insert("GL_NOTEQUAL", GL_NOTEQUAL);
    visibleTypes.insert("GL_GEQUAL", GL_GEQUAL);
    visibleTypes.insert("GL_ALWAYS", GL_ALWAYS);

    ui->comboBoxVisible->addItems(visibleTypes.keys());
    ui->comboBoxVisible->setCurrentText("GL_ALWAYS");
}

void MainWindow::setSFactor()
{
    sfactorTypes.insert("GL_ZERO", GL_ZERO);
    sfactorTypes.insert("GL_ONE", GL_ONE);
    sfactorTypes.insert("GL_DST_COLOR", GL_DST_COLOR);
    sfactorTypes.insert("GL_ONE_MINUS_DST_COLOR", GL_ONE_MINUS_DST_COLOR);
    sfactorTypes.insert("GL_SRC_ALPHA", GL_SRC_ALPHA);
    sfactorTypes.insert("GL_ONE_MINUS_SRC_ALPHA", GL_ONE_MINUS_SRC_ALPHA);
    sfactorTypes.insert("GL_DST_ALPHA", GL_DST_ALPHA);
    sfactorTypes.insert("GL_ONE_MINUS_DST_ALPHA", GL_ONE_MINUS_DST_ALPHA);
    sfactorTypes.insert("GL_SRC_ALPHA_SATURATE", GL_SRC_ALPHA_SATURATE);

    ui->comboBoxSFactor->addItems(sfactorTypes.keys());
    ui->comboBoxSFactor->setCurrentText("GL_ONE");
}

void MainWindow::setDFactor()
{
    dfactorTypes.insert("GL_ZERO", GL_ZERO);
    dfactorTypes.insert("GL_ONE", GL_ONE);
    dfactorTypes.insert("GL_SRC_COLOR", GL_SRC_COLOR);
    dfactorTypes.insert("GL_ONE_MINUS_SRC_COLOR", GL_ONE_MINUS_SRC_COLOR);
    dfactorTypes.insert("GL_SRC_ALPHA", GL_SRC_ALPHA);
    dfactorTypes.insert("GL_ONE_MINUS_SRC_ALPHA", GL_ONE_MINUS_SRC_ALPHA);
    dfactorTypes.insert("GL_DST_ALPHA", GL_DST_ALPHA);
    dfactorTypes.insert("GL_ONE_MINUS_DST_ALPHA", GL_ONE_MINUS_DST_ALPHA);

    ui->comboBoxDFactor->addItems(dfactorTypes.keys());
    ui->comboBoxDFactor->setCurrentText("GL_ZERO");
}

void MainWindow::setScissor()
{
    ui->sliderX->setSliderPosition(0);
    ui->sliderY->setSliderPosition(0);
    ui->sliderW->setSliderPosition(100);
    ui->sliderH->setSliderPosition(100);
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->glWidget->setPrimType(primTypes.value(arg1));
}


void MainWindow::on_comboBoxVisible_currentTextChanged(const QString &arg1)
{
    ui->glWidget->setVisibleType(visibleTypes.value(arg1));
}


void MainWindow::on_comboBoxSFactor_currentTextChanged(const QString &arg1)
{
    ui->glWidget->setSFactorType(sfactorTypes.value(arg1));
}


void MainWindow::on_comboBoxDFactor_currentTextChanged(const QString &arg1)
{
    ui->glWidget->setDFactorType(dfactorTypes.value(arg1));
}


void MainWindow::on_sliderX_sliderMoved(int position)
{
    ui->glWidget->changeX(position);
}


void MainWindow::on_sliderY_sliderMoved(int position)
{
    ui->glWidget->changeY(position);
}


void MainWindow::on_sliderRef_sliderMoved(int position)
{
    ui->glWidget->changeCoeffVisible(position);
}


void MainWindow::on_sliderH_sliderMoved(int position)
{
    ui->glWidget->changeH(position);
}


void MainWindow::on_sliderW_sliderMoved(int position)
{
    ui->glWidget->changeW(position);
}

