#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/qopengl.h>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setPrim();
    void setVisible();
    void setSFactor();
    void setDFactor();
    void setScissor();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_comboBoxVisible_currentTextChanged(const QString &arg1);

    void on_comboBoxSFactor_currentTextChanged(const QString &arg1);

    void on_comboBoxDFactor_currentTextChanged(const QString &arg1);

    void on_sliderX_sliderMoved(int position);

    void on_sliderY_sliderMoved(int position);

    void on_sliderRef_sliderMoved(int position);

    void on_sliderH_sliderMoved(int position);

    void on_sliderW_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QMap<QString, GLenum> primTypes;
    QMap<QString, GLenum> visibleTypes;
    QMap<QString, GLenum> sfactorTypes;
    QMap<QString, GLenum> dfactorTypes;
};
#endif // MAINWINDOW_H
