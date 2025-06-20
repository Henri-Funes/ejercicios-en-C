#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

// ecuación general de la recta
void drawSegmentGeneral(int x1, int y1, int x2, int y2)
{
    int A = y2 - y1;
    int B = -(x2 - x1);
    int C = x2 * y1 - x1 * y2;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    if (dx > dy)
    {
        if (x1 > x2)
        {
            int tmp = x1;
            x1 = x2;
            x2 = tmp;
            tmp = y1;
            y1 = y2;
            y2 = tmp;
        }
        for (int x = x1; x <= x2; x++)
        {
            int y = (-A * x - C) / B;
            glVertex2i(x, y);
        }
    }
    else
    {
        if (y1 > y2)
        {
            int tmp = x1;
            x1 = x2;
            x2 = tmp;
            tmp = y1;
            y1 = y2;
            y2 = tmp;
        }
        for (int y = y1; y <= y2; y++)
        {
            int x = (-B * y - C) / A;
            glVertex2i(x, y);
        }
    }
}

void displaysombrilla(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-150.0, 0.0, 0.0);

    glPointSize(2.0);
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_POINTS);
    drawSegmentGeneral(500, 600, 200, 400);
    drawSegmentGeneral(500, 600, 800, 400);
    drawSegmentGeneral(200, 400, 400, 350);
    drawSegmentGeneral(800, 400, 600, 350);
    drawSegmentGeneral(400, 350, 600, 350);
    drawSegmentGeneral(400, 350, 500, 600);
    drawSegmentGeneral(500, 600, 600, 350);
    drawSegmentGeneral(480, 350, 480, 150);
    drawSegmentGeneral(520, 350, 520, 100);
    drawSegmentGeneral(480, 150, 520, 100);
    drawSegmentGeneral(520, 100, 600, 100);
    drawSegmentGeneral(520, 100, 560, 80);
    drawSegmentGeneral(560, 80, 600, 100);
    drawSegmentGeneral(600, 100, 600, 120);
    drawSegmentGeneral(600, 120, 580, 140);
    drawSegmentGeneral(580, 140, 580, 100);
    glEnd();

    glFlush();
}

void initSombrilla(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 700, 0, 700);
}