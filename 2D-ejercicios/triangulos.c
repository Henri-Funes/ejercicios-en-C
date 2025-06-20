#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

extern int numTriangles;

static void drawSegment(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1, dy = y2 - y1;
    float dist = sqrt(dx * dx + dy * dy);
    int steps = (int)(dist);
    if (steps < 2)
        steps = 2;
    for (int i = 0; i <= steps; i++)
    {
        float t = (float)i / steps;
        float x = x1 + dx * t;
        float y = y1 + dy * t;
        glVertex2f(x, y);
    }
}

static void drawCell2(float cx, float cy, float cellW, float cellH)
{
    drawSegment(cx, cy + cellH, cx + cellW, cy + cellH);
    drawSegment(cx + cellW, cy + cellH, cx + cellW, cy);
    drawSegment(cx + cellW, cy, cx, cy);
    drawSegment(cx, cy, cx, cy + cellH);
    drawSegment(cx, cy + cellH, cx + cellW, cy);
}

static void drawCell3(float cx, float cy, float cellW, float cellH)
{
    float xA = cx, yA = cy + cellH;
    float xB = cx + cellW, yB = cy + cellH;
    float xC = cx + cellW / 2, yC = cy;
    float xD = cx, yD = cy;
    float xE = cx + cellW, yE = cy;

    drawSegment(xA, yA, xB, yB);
    drawSegment(xB, yB, xC, yC);
    drawSegment(xC, yC, xA, yA);
    drawSegment(xA, yA, xC, yC);
    drawSegment(xC, yC, xD, yD);
    drawSegment(xD, yD, xA, yA);
    drawSegment(xB, yB, xC, yC);
    drawSegment(xC, yC, xE, yE);
    drawSegment(xE, yE, xB, yB);
}

void displaytriangulos(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPointSize(5.0);
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_POINTS);

    if (numTriangles == 2)
    {
        drawCell2(0.0f, 0.0f, 700.0f, 700.0f);
        glEnd();
        glFlush();
        return;
    }
    if (numTriangles == 3)
    {
        drawCell3(0.0f, 0.0f, 700.0f, 700.0f);
        glEnd();
        glFlush();
        return;
    }

    int numCells = 0;
    if (numTriangles % 2 == 0)
    {
        numCells = numTriangles / 2;
    }
    else
    {
        numCells = ((numTriangles - 3) / 2) + 1;
    }

    int ncols = (int)ceil(sqrt((double)numCells));
    int nrows = (int)ceil((double)numCells / ncols);
    float cellWidth = 700.0f / ncols;
    float cellHeight = 700.0f / nrows;
    int totalCellsGrid = ncols * nrows;

    int cellCounter = 0;
    int cell3drawn = 0;

    for (int row = 0; row < nrows && cellCounter < numCells; row++)
    {
        for (int col = 0; col < ncols && cellCounter < numCells; col++)
        {
            float cx = col * cellWidth;
            float cy = row * cellHeight;

            if (cellCounter == numCells - 1 && totalCellsGrid > numCells)
            {
                float mergedW = 700.0f - cx;
                float mergedH = 700.0f - cy;
                if ((numTriangles % 2 != 0) && (cell3drawn == 0))
                {
                    drawCell3(cx, cy, mergedW, mergedH);
                    cell3drawn = 1;
                }
                else
                {
                    drawCell2(cx, cy, mergedW, mergedH);
                }
            }
            else
            {
                if ((numTriangles % 2 != 0) && (cell3drawn == 0))
                {
                    drawCell3(cx, cy, cellWidth, cellHeight);
                    cell3drawn = 1;
                }
                else
                {
                    drawCell2(cx, cy, cellWidth, cellHeight);
                }
            }
            cellCounter++;
        }
    }

    glEnd();
    glFlush();
}

void initTriangulos(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 700, 0, 700);
}
