#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static void drawLineBresenham(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        glVertex2i(x1, y1);
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void drawCirclePolar(float cx, float cy, float r)
{
    for (int i = 0; i < 360; i++)
    {
        float theta = i * (M_PI / 180.0);
        float x = cx + r * cos(theta);
        float y = cy + r * sin(theta);
        glVertex2f(x, y);
    }
}

void displaysusuwatari(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0, 0, 0);
    glPointSize(5.0);   

    glBegin(GL_POINTS);
    drawLineBresenham(296, 243, 200, 150);
    drawLineBresenham(200, 150, 200, 50);
    drawLineBresenham(200, 50, 155, 35);
    drawLineBresenham(200, 50, 195, 19);
    drawLineBresenham(200, 50, 231, 32);
    drawLineBresenham(472, 253, 550, 150);
    drawLineBresenham(550, 150, 550, 50);
    drawLineBresenham(550, 50, 510, 30);
    drawLineBresenham(550, 50, 551, 25);
    drawLineBresenham(550, 50, 578, 30);
    drawLineBresenham(206, 422, 43, 449);
    drawLineBresenham(43, 449, 0, 539);
    drawLineBresenham(547, 400, 686, 440);
    drawLineBresenham(686, 440, 700, 500);
    drawLineBresenham(700, 500, 641, 538);
    drawLineBresenham(700, 500, 678, 555);
    drawLineBresenham(700, 500, 650, 500);
    drawLineBresenham(0, 539, 59, 552);
    drawLineBresenham(0, 539, 43, 564);
    drawLineBresenham(0, 539, 13, 589);
    drawLineBresenham(206, 422, 100, 350);
    drawLineBresenham(100, 350, 204, 410);
    drawLineBresenham(204, 410, 104, 291);
    drawLineBresenham(104, 291, 207, 359);
    drawLineBresenham(207, 359, 129, 248);
    drawLineBresenham(129, 248, 229, 306);
    drawLineBresenham(229, 306, 195, 215);
    drawLineBresenham(195, 215, 245, 284);
    drawLineBresenham(245, 284, 237, 213);
    drawLineBresenham(237, 213, 296, 243);
    drawLineBresenham(296, 243, 292, 192);
    drawLineBresenham(292, 192, 318, 234);
    drawLineBresenham(318, 234, 333, 170);
    drawLineBresenham(333, 170, 355, 225);
    drawLineBresenham(355, 225, 400, 150);
    drawLineBresenham(400, 150, 421, 230);
    drawLineBresenham(421, 230, 450, 150);
    drawLineBresenham(450, 150, 472, 253);
    drawLineBresenham(472, 253, 560, 211);
    drawLineBresenham(560, 211, 522, 306);
    drawLineBresenham(522, 306, 577, 260);
    drawLineBresenham(577, 260, 539, 343);
    drawLineBresenham(539, 343, 592, 299);
    drawLineBresenham(592, 299, 547, 400);
    drawLineBresenham(206, 422, 147, 462);
    drawLineBresenham(147, 462, 209, 440);
    drawLineBresenham(209, 440, 163, 495);
    drawLineBresenham(163, 495, 228, 484);
    drawLineBresenham(228, 484, 193, 536);
    drawLineBresenham(193, 536, 273, 534);
    drawLineBresenham(273, 534, 224, 573);
    drawLineBresenham(224, 573, 300, 550);
    drawLineBresenham(547, 400, 599, 428);
    drawLineBresenham(599, 428, 525, 479);
    drawLineBresenham(525, 479, 609, 470);
    drawLineBresenham(609, 470, 502, 512);
    drawLineBresenham(502, 512, 585, 503);
    drawLineBresenham(585, 503, 450, 550);
    drawLineBresenham(450, 550, 500, 557);
    drawLineBresenham(500, 557, 400, 566);
    drawLineBresenham(300, 550, 285, 589);
    drawLineBresenham(285, 589, 328, 560);
    drawLineBresenham(328, 560, 324, 592);
    drawLineBresenham(324, 592, 354, 566);
    drawLineBresenham(354, 566, 350, 600);
    drawLineBresenham(350, 600, 365, 567);
    drawLineBresenham(365, 567, 378, 603);
    drawLineBresenham(378, 603, 384, 570);
    drawLineBresenham(384, 570, 400, 600);
    drawLineBresenham(400, 600, 400, 566);
    glEnd();

    glBegin(GL_POINTS);
    drawCirclePolar(317.18, 479.05, sqrt(1749.29));
    drawCirclePolar(434.23, 482.88, sqrt(1597.11));
    glVertex2f(317.18, 479.05);
    glVertex2f(300.55, 440.67);
    glVertex2f(434.23, 482.88);
    glVertex2f(403.53, 457.3);
    glEnd();

    glFlush();
}

void initsusuwatari(void)
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 700, 0, 700);
}