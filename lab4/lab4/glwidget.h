#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <cmath>
#include <QPointF>
#include <QOpenGLFunctions>
#include <QMouseEvent>

class GLWidget: public QOpenGLWidget
{
public:
    GLWidget(QWidget* par = nullptr);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void createSpline();
    QPointF getPoint(int num, float t);
    int getIndex(const QPointF& point) const;

    void clearWidget();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);

private:
    float width;
    float height;

    QVector<QPointF> points;
    QVector<QPointF> splinePoints;
    QPointF selectedPoint {-2.f, -2.f};

};

#endif // GLWIDGET_H
