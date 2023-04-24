#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>

class GLWidget: public QOpenGLWidget
{
public:
    GLWidget(QWidget* par = nullptr);

    void setPrimType(GLenum typePrim);
    void changeX(int x);
    void changeY(int y);
    void changeW(int w);
    void changeH(int h);
    void setVisibleType(GLenum typeVisible);
    void setSFactorType(GLenum typeSFactor);
    void setDFactorType(GLenum typeDFactor);
    void changeCoeffVisible(int coeff);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    GLenum primType = GL_POINTS;
    GLenum visibleType = GL_ALWAYS;
    GLenum sfactorType = GL_ONE;
    GLenum dfactorType = GL_ZERO;
    float scissorsX = 0.0;
    float scissorsY = 0.0;
    float scissorsW = 1.0;
    float scissorsH = 1.0;
    float coeffVisible = 0.0;
    int sizeW = 0;
    int sizeH = 0;
};

#endif // GLWIDGET_H
