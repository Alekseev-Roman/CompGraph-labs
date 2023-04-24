#include "glwidget.h"

GLWidget::GLWidget(QWidget* par):
    QOpenGLWidget{ par }
{

}

void GLWidget::createCircle()
{
    QColor colors = QColor("lightYellow");

    float a = 0.0f;

    for(int i = 0; i < 180; i++)
    {
        glColor3d(colors.redF(), colors.greenF(), colors.blueF());
        glVertex2d(radius * cos(a), radius * sin(a));
        a = i/180.0f * M_PI * 2.0f;
    }
}

void GLWidget::createPentagon(float coeff, bool rotate)
{
    QColor colors[2] = {QColor("darkRed"), QColor("yellow")};

    float a = rotate ? startAngle * coeffRotateAngle : startAngle;
    float angleIncrement = 2.0f * M_PI / 5;
    float edge = radius * coeff;

    for(int i = 0; i < 5; i++)
    {
        glColor3d(colors[i%2].redF(), colors[i%2].greenF(), colors[i%2].blueF());
        glVertex2d(edge*cos(a), edge*sin(a));
        a += angleIncrement;
    }
}

void GLWidget::createStepFractal(float coeff, bool rotate)
{
    QColor colors[3] = {QColor("black"), QColor("lightGreen"), QColor("darkGreen")};
    QColor colorsLine[3] = {QColor("lightYellow"), QColor("darkRed"), QColor("yellow")};

    float a = rotate ? startAngle * coeffRotateAngle : startAngle;
    float angleIncrement = 2.0f * M_PI / 5;
    float edge = radius * coeff;

    for(int i = 0; i < 5; i++)
    {

        // Painting triangles
        glBegin(GL_TRIANGLES);
            glColor3d(colors[2].redF(), colors[2].greenF(), colors[2].blueF());
            glVertex2d(edge*cos(a), edge*sin(a));
            glColor3d(colors[1].redF(), colors[1].greenF(), colors[1].blueF());
            glVertex2d(edge*cos(a) * coeffIncreaseEdge * coeffIncreaseEdge, edge*sin(a) * coeffIncreaseEdge * coeffIncreaseEdge);
            glColor3d(colors[2].redF(), colors[2].greenF(), colors[2].blueF());
            glVertex2d(-edge*cos(a + angleIncrement*2) * coeffIncreaseEdge, -edge*sin(a + angleIncrement*2) * coeffIncreaseEdge);
/*
            glColor3d(colors[0].redF(), colors[0].greenF(), colors[0].blueF());
            glVertex2d(-edge*cos(a + angleIncrement*2) * coeffIncreaseEdge, -edge*sin(a + angleIncrement*2) * coeffIncreaseEdge);
            glColor3d(colors[0].redF(), colors[0].greenF(), colors[0].blueF());
            glVertex2d(edge*cos(a - angleIncrement), edge*sin(a - angleIncrement));
            glColor3d(colors[0].redF(), colors[0].greenF(), colors[0].blueF());
            glVertex2d(edge*cos(a - angleIncrement) * coeffIncreaseEdge * coeffIncreaseEdge, edge*sin(a - angleIncrement) * coeffIncreaseEdge * coeffIncreaseEdge);*/
        glEnd();

        // Painting lines around triangles
        glBegin(GL_LINE_LOOP);
            glColor3d(colorsLine[0].redF(), colorsLine[0].greenF(), colorsLine[0].blueF());
            glVertex2d(edge*cos(a), edge*sin(a));
            glColor3d(colorsLine[0].redF(), colorsLine[0].greenF(), colorsLine[0].blueF());
            glVertex2d(edge*cos(a) * coeffIncreaseEdge * coeffIncreaseEdge, edge*sin(a) * coeffIncreaseEdge * coeffIncreaseEdge);
            glColor3d(colorsLine[0].redF(), colorsLine[0].greenF(), colorsLine[0].blueF());
            glVertex2d(-edge*cos(a + angleIncrement*2) * coeffIncreaseEdge, -edge*sin(a + angleIncrement*2) * coeffIncreaseEdge);
        glEnd();

        glBegin(GL_LINE_LOOP);
            glColor3d(colorsLine[0].redF(), colorsLine[0].greenF(), colorsLine[0].blueF());
            glVertex2d(-edge*cos(a + angleIncrement*2) * coeffIncreaseEdge, -edge*sin(a + angleIncrement*2) * coeffIncreaseEdge);
            glColor3d(colorsLine[0].redF(), colorsLine[0].greenF(), colorsLine[0].blueF());
            glVertex2d(edge*cos(a - angleIncrement), edge*sin(a - angleIncrement));
            glColor3d(colorsLine[0].redF(), colorsLine[0].greenF(), colorsLine[0].blueF());
            glVertex2d(edge*cos(a - angleIncrement) * coeffIncreaseEdge * coeffIncreaseEdge, edge*sin(a - angleIncrement) * coeffIncreaseEdge * coeffIncreaseEdge);
        glEnd();

        // Painting spirals
        float x = edge*cos(a) * coeffIncreaseEdge * coeffIncreaseEdge;
        float y = edge*sin(a) * coeffIncreaseEdge * coeffIncreaseEdge;
        float sx = -edge*cos(a + angleIncrement*2) * coeffIncreaseEdge;
        float sy = -edge*sin(a + angleIncrement*2) * coeffIncreaseEdge;
        float dx = (sx-x)/10;
        float dy = (sy-y)/10;

        float dvx = (edge*cos(a) + x)/200;
        float dvy = (edge*sin(a) + y)/200;

        glLineWidth(2);

        glBegin(GL_LINE_STRIP);

            for(int e = 0.; e < 5; e++)
            {
                glColor3d(colorsLine[2].redF(), colorsLine[2].greenF(), colorsLine[2].blueF());
                glVertex2d(x, y);
                x += dx + dvx;
                y += dy + dvy;

                dvx *= 0.8;
                dvy *= 0.8;
            }

            for(int e = 0; e < 6; e++)
            {
                glColor3d(colorsLine[2].redF(), colorsLine[2].greenF(), colorsLine[2].blueF());
                glVertex2d(x, y);
                x += dx - dvx;
                y += dy - dvy;

                dvx /= 0.8;
                dvy /= 0.8;
            }

        glEnd();

        glLineWidth(1);

        a += angleIncrement;
    }
}

void GLWidget::initializeGL()
{

}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWidget::setAmountSteps(int amount)
{
    amountSteps = amount;
    update();
}

void GLWidget::paintGL()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPointSize(2);
    glLineWidth(1);

    float coeffEdge = 1.0;

    glBegin(GL_LINE_LOOP);
        createCircle();
    glEnd();

    for(int i = 0; i < amountSteps; i++)
    {
        createStepFractal(coeffEdge, i%2);
        coeffEdge *= coeffIncreaseEdge;
    }

}
