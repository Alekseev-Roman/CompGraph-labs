#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(QWidget* par):
    QOpenGLWidget{ par },
    _ebo{QOpenGLBuffer::IndexBuffer},
    _timer{new QTimer}
{}

GLWidget::~GLWidget()
{
    _vao.destroy();
    _vbo.destroy();
    _ebo.destroy();
    _timer->stop();
    delete _timer;
}

void GLWidget::initializeGL()
{
    QColor bgc(255, 255, 255);
    initializeOpenGLFunctions();
    glClearColor(bgc.redF(), bgc.greenF(), bgc.blueF(), bgc.alphaF());
    // подключение шейдеров
    if(!initShaderProg())
    {
        std::cerr << _shaderProg.log().toStdString() << std::endl;
        return;
    }

    // генерация точек сплайна
    generatePoints();
    createSpline();
    bindVert();
    // выбор режима растрирования
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // подключение к таймеру
    connect(_timer, &QTimer::timeout, this, &GLWidget::updateTimer);
    _timer->start(200);
}

void GLWidget::resizeGL(int w, int h)
{
    _width = w;
    _height = h;

    glViewport(0, 0, w, h);
    // задание матрицы пребразований
    QMatrix4x4 transformMatrix;
    transformMatrix.setToIdentity();
    transformMatrix.rotate(25.f, 1.f, 0.f, 0.f);

    int matrixLocation = _shaderProg.uniformLocation("transformations");
    _shaderProg.setUniformValue(matrixLocation, transformMatrix);
}

void GLWidget::paintGL()
{
    _vao.bind();
    _vbo.bind();
    _ebo.bind();
    _shaderProg.bind();

    // установка переменных для передачи значений в шейдеры
    int vertexLocation = _shaderProg.attributeLocation("vPos");

    _shaderProg.enableAttributeArray(vertexLocation);
    _shaderProg.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(GLfloat)*6);

    int timeLocation = _shaderProg.uniformLocation("time");
    _shaderProg.setUniformValue(timeLocation, _time);

    glDrawElements(GL_TRIANGLE_STRIP, 6*(_splinePoints.size()-1), GL_UNSIGNED_SHORT, nullptr);
}

bool GLWidget::initShaderProg()
{
    _vao.create();
    _vao.bind();

    _vbo.create();
    _ebo.create();

    // подключаем вершинный шейдер
    if(!_shaderProg.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vs"))
    {
        return false;
    }
    // подключаем фрагментный шейдер
    if(!_shaderProg.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.fs"))
    {
        return false;
    }
    if(!_shaderProg.link())
    {
        return false;
    }
    if(!_shaderProg.bind())
    {
        return false;
    }

    return true;
}

void GLWidget::generatePoints()
{
    _points.push_back(QPointF{-0.8, 0.7});
    _points.push_back(QPointF{-0.5, -0.5});
    _points.push_back(QPointF{0.0, 0.0});
    _points.push_back(QPointF{0.2, -0.9});
    _points.push_back(QPointF{0.3, 0.4});
    _points.push_back(QPointF{0.6, -0.5});
    _points.push_back(QPointF{0.9, 0.1});
}

void GLWidget::createSpline()
{
    for(int i = 0; i < _points.size(); i++)
    {
        _splinePoints.clear();
        for(float t = 0; t < 1.0; t += 0.01)
        {
            _splinePoints.push_back(getPoint(i, t));
        }
    }
}

QPointF GLWidget::getPoint(int num, float t)
{
    QVector<QPointF> newPoints = _points;

    int i = num;

    while (i > 0) {
        for(int k = 0; k < i; k++)
        {
            newPoints[k] = newPoints[k] + t * (newPoints[k+1] - newPoints[k]);
        }

        i--;
    }

    return newPoints[0];
}

void GLWidget::bindVert()
{
    int vCount = 12 * _splinePoints.size();
    int iCount = 6 * (_splinePoints.size() - 1);
    GLfloat* vertices = new GLfloat[vCount];
    GLushort* indices = new GLushort[iCount];

    // копируем вершины в буфер
    for (GLushort i = 0; i < _splinePoints.size(); ++i)
    {
        // {x, y, 0, n1}
        vertices[12 * i + 0]  = _splinePoints[i].x();
        vertices[12 * i + 1]  = _splinePoints[i].y();
        vertices[12 * i + 2]  = 0.f;
        // {x, y, -1, n2}
        vertices[12 * i + 6]  = _splinePoints[i].x();
        vertices[12 * i + 7]  = _splinePoints[i].y();
        vertices[12 * i + 8]  = -1.f;
    }
    GLfloat dx1, dx2, dy1, dy2, dz1, dz2;
    // копируем индексы в буфер
    for (GLushort i = 0; i < _splinePoints.size() - 1; ++i)
    {
        // добавляем индексы в массив
        indices[6 * i + 0] = 2 * i + 0;
        indices[6 * i + 1] = 2 * i + 2;
        indices[6 * i + 2] = 2 * i + 1;
        indices[6 * i + 3] = 2 * i + 3;
        indices[6 * i + 4] = 2 * i + 0;
        indices[6 * i + 5] = 2 * i + 2;
    }

    _vbo.bind();
    _vbo.allocate(vertices, sizeof(GLfloat) * vCount);

    _ebo.bind();
    _ebo.allocate(indices, sizeof(GLushort) * iCount);

    _vbo.release();
    _ebo.release();
    delete [] vertices;
    delete [] indices;
}


void GLWidget::updateTimer()
{
    _time += _step;
    if (_time > 1000.f)
        _time = 0.f;
    update();
}
