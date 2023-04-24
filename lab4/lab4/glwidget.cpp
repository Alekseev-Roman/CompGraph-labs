#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(QWidget* par):
    QOpenGLWidget{ par }
{

}

void GLWidget::initializeGL()
{

}

void GLWidget::resizeGL(int w, int h)
{
    width = w;
    height = h;

    glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPointSize(6);
    glLineWidth(3);

    for(int i = 0; i < points.size(); i++)
    {
        glColor3d(1, 0, 0);
        glBegin(GL_POINTS);
            glVertex2d(points[i].x(), points[i].y());
        glEnd();
    }

    createSpline();
}

void GLWidget::createSpline()
{
    for(int i = 0; i < points.size(); i++)
    {
        splinePoints.clear();
        for(float t = 0; t < 1.0; t += 0.01)
        {
            splinePoints.push_back(getPoint(i, t));
        }
    }

    glColor3d(0, 1, 0);
    glBegin(GL_LINE_STRIP);

    for(int i = 0; i < splinePoints.size(); i++)
    {
        glVertex2d(splinePoints[i].x(), splinePoints[i].y());
    }

    glEnd();

}

QPointF GLWidget::getPoint(int num, float t)
{
    QVector<QPointF> newPoints = points;

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

int GLWidget::getIndex(const QPointF &point) const
{
    for(int i = 0; i < points.size(); i++)
    {
        if(point.x() == points[i].x() && point.y() == points[i].y())
        {
            return i;
        }
    }

    return -1;
}

void GLWidget::clearWidget()
{
    points.clear();
    splinePoints.clear();
    selectedPoint = {-2.f, -2.f};

    update();
}

void GLWidget::mousePressEvent(QMouseEvent* event)
{
    float accuracy = 0.05;

    QPointF topLeftCorner {
        2 * event->pos().x() / width - 1 - accuracy,
        -2 * event->pos().y() / height + 1 + accuracy
    };

    QRectF container(topLeftCorner, QSizeF {2*accuracy, -2*accuracy});

    for(int i = 0; i < points.size(); i++)
    {
        if(container.contains(points[i]))
        {
            selectedPoint = points[i];

            if(event->buttons() & Qt::RightButton)
            {
                points.removeAt(i);
                selectedPoint = {-2.f, -2.f};
            }

            update();
            QWidget::mousePressEvent(event);
            return;
        }
    }

    update();
    QWidget::mousePressEvent(event);
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPointF position {
        2 * event->pos().x() / width - 1,
        -2 * event->pos().y() / height + 1
    };

    points.push_back(position);
    selectedPoint = {-2.f, -2.f};

    update();
    QWidget::mouseDoubleClickEvent(event);
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event)
{
    selectedPoint = {-2.f, -2.f};

    update();
    QWidget::mouseReleaseEvent(event);
}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
    int selectedPointInd = getIndex(selectedPoint);

    if(!(event->buttons() & Qt::LeftButton) || selectedPointInd < 0)
    {
        QWidget::mouseMoveEvent(event);
        return;
    }

    QPointF position {
        2 * event->pos().x() / width - 1,
        -2 * event->pos().y() / height + 1
    };

    points[selectedPointInd].setX(position.x());
    points[selectedPointInd].setY(position.y());
    selectedPoint = position;

    update();
    QWidget::mouseMoveEvent(event);
}
