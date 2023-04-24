#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QPointF>
#include <QTimer>

class GLWidget: public QOpenGLWidget, public QOpenGLFunctions
{
public:
    GLWidget(QWidget* par = nullptr);
    ~GLWidget();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    bool initShaderProg();
    void generatePoints();

    void createSpline();
    void bindVert();
    QPointF getPoint(int num, float t);

    void updateTimer();

private:
    float _width;
    float _height;

    QVector<QPointF> _points;
    QVector<QPointF> _splinePoints;
    QOpenGLShaderProgram _shaderProg;
    QOpenGLVertexArrayObject _vao;
    QOpenGLBuffer _vbo;
    QOpenGLBuffer _ebo;

    QTimer* _timer;
    GLfloat _time = 0.f;
    GLfloat _step = 1.f;
};

#endif // GLWIDGET_H
