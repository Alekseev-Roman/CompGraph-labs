#include "glwidget.h"

GLWidget::GLWidget(QWidget* par):
    QOpenGLWidget{ par }
{

}

void GLWidget::setPrimType(GLenum typePrim)
{
    primType = typePrim;
    update();
}

void GLWidget::changeX(int x)
{
    scissorsX = x / 100.0;
    update();
}

void GLWidget::changeY(int y)
{
    scissorsY = y / 100.0;
    update();
}

void GLWidget::changeW(int w)
{
    scissorsW = w / 100.0;
    update();
}

void GLWidget::changeH(int h)
{
    scissorsH = h / 100.0;
    update();
}

void GLWidget::setVisibleType(GLenum typeVisible)
{
    visibleType = typeVisible;
    update();
}

void GLWidget::setSFactorType(GLenum typeSFactor)
{
    sfactorType = typeSFactor;
    update();
}

void GLWidget::setDFactorType(GLenum typeDFactor)
{
    dfactorType = typeDFactor;
    update();
}

void GLWidget::changeCoeffVisible(int coeff)
{
    coeffVisible = coeff / 100.0;
    update();
}

void GLWidget::initializeGL()
{

}

void GLWidget::resizeGL(int w, int h)
{
    sizeW = w;
    sizeH = h;
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);

    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPointSize(6);
    glLineWidth(3);

    glAlphaFunc(visibleType, coeffVisible);
    glScissor(scissorsX * sizeW, scissorsY * sizeH, scissorsW * (1.0 - scissorsX) * sizeW, scissorsH * (1.0 - scissorsY) * sizeH);
    glBlendFunc(sfactorType, dfactorType);

    glBegin(primType);
        glColor4d(0.0f, 0.0f, 1.0f, 0.08);
        glVertex2d(0.0, 0.8);
        glColor4d(0.0f, 1.0f, 1.0f, 0.13);
        glVertex2d(0.4, 0.6);
        glColor4d(0.0f, 1.0f, 0.0f, 0.31);
        glVertex2d(0.8, 0.0);
        glColor4d(1.0f, 1.0f, 0.0f, 0.45);
        glVertex2d(0.3, -0.6);
        glColor4d(1.0f, 0.0f, 0.0f, 0.6);
        glVertex2d(0.0, -0.8);
        glColor4d(1.0f, 0.0f, 1.0f, 0.71);
        glVertex2d(-0.3, -0.7);
        glColor4d(0.0f, 1.0f, 0.7f, 0.87);
        glVertex2d(-0.8, 0.0);
        glColor4d(0.5f, 0.5f, 1.0f, 1.0);
        glVertex2d(-0.4, 0.6);
    glEnd();

    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
}
