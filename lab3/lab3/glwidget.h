#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <cmath>

class GLWidget: public QOpenGLWidget
{
public:
    GLWidget(QWidget* par = nullptr);

    void createCircle();
    void createPentagon(float coeff, bool rotate);
    void createStepFractal(float coeff, bool rotate);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void setAmountSteps(int amount);

private:
    float radius = 0.8;
    float startAngle = 0.314f;
    float coeffRotateAngle = 3.0f;
    float coeffIncreaseEdge = 1.0f - 0.195f;
    int amountSteps = 10;
    float radSpiral = 1.05;
};

#endif // GLWIDGET_H
