#include <GL/glut.h>
#include <math.h>
#include "header.h"

// Dibuja un círculo relleno usando un TRIANGLE_FAN
void drawFilledCircle(float cx, float cy, float radius, int segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Empieza desde el centro
    // Genera vértices alrededor en forma de abanico
    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * M_PI * i / segments;
        float x = cx + radius * cos(angle);
        float y = cy + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Dibuja una elipse rellena de forma similar al círculo
void drawFilledEllipse(float cx, float cy, float radiusX, float radiusY, int segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Centro de la elipse
    // Recorre cada segmento ajustando radio X y Y
    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * M_PI * i / segments;
        float x = cx + radiusX * cos(angle);
        float y = cy + radiusY * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Dibuja un cuadrilátero como dos triángulos
void drawQuad(float x1, float y1, float x2, float y2,
              float x3, float y3, float x4, float y4)
{
    glBegin(GL_TRIANGLES);
    // Primer triángulo
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    // Segundo triángulo
    glVertex2f(x1, y1);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}

// ================= PAISAJE: BOSQUE, ARBUSTOS, FLORES =================

void drawForest()
{
    // Troncos de los árboles como rectángulos delgados
    glColor3f(0.4f, 0.2f, 0.1f); // Color madera
    for (float x = 50; x < 1000; x += FOREST_DENSITY)
    {
        float tx = x + landscapeOffset;
        float w = 8.0f; // Ancho del tronco

        // Dos triángulos forman el rectángulo del tronco
        glBegin(GL_TRIANGLES);
        glVertex2f(tx - w / 2, 50);
        glVertex2f(tx + w / 2, 50);
        glVertex2f(tx + w / 2, 120);

        glVertex2f(tx - w / 2, 50);
        glVertex2f(tx + w / 2, 120);
        glVertex2f(tx - w / 2, 120);
        glEnd();
    }

    // Copas de los árboles con muchos círculos pequeños
    glColor3f(0.1f, 0.6f, 0.1f); // Verde oscuro
    for (float x = 50; x < 1000; x += FOREST_DENSITY)
    {
        float bx = x + landscapeOffset;
        // Malla de círculos para dar forma de copa
        for (int i = -20; i <= 20; i += TREE_DETAIL_LEVEL)
        {
            for (int j = 0; j <= 30; j += TREE_DETAIL_LEVEL)
            {
                if (abs(i) + j < 35)
                    drawFilledCircle(bx + i, 120 + j, 6.0f, 8);
            }
        }
    }

    // Arbustos hechos con círculos más pequeños
    glColor3f(0.2f, 0.7f, 0.2f); // Verde claro
    for (float x = 20; x < 1000; x += 45)
    {
        float bx = x + landscapeOffset;
        for (int i = -10; i <= 10; i += 6)
        {
            float ly = 35 + (abs(i) % 10);
            drawFilledCircle(bx + i, ly, 3.0f, 6);
        }
    }

    // Flores variadas en el suelo
    for (float x = 30; x < 1000; x += FLOWER_SPACING)
    {
        float fx = x + landscapeOffset;

        // Roja como elipses finas
        glColor3f(1.0f, 0.2f, 0.2f);
        drawFilledEllipse(fx, 25, 2.5f, 2.0f, 6);

        // Amarilla y azul con círculos
        glColor3f(1.0f, 1.0f, 0.0f);
        drawFilledCircle(fx + 20, 30, 2.0f, 6);
        glColor3f(0.2f, 0.2f, 1.0f);
        drawFilledCircle(fx + 40, 28, 2.0f, 6);

        // Centros blancos para más realismo
        glColor3f(1.0f, 1.0f, 1.0f);
        drawFilledCircle(fx, 25, 0.8f, 4);
        drawFilledCircle(fx + 20, 30, 0.8f, 4);
        drawFilledCircle(fx + 40, 28, 0.8f, 4);
    }
}

// ================= PAISAJE: MONTAÑAS ANIMADAS =================

void drawMountain()
{
    // Capa de fondo de montañas
    glColor3f(0.3f, 0.5f, 0.2f); // Verde oscuro-amarillento
    glBegin(GL_TRIANGLE_STRIP);
    for (float x = 0; x < 1200; x += MOUNTAIN_DETAIL_LEVEL)
    {
        float ax = x + landscapeOffset;
        // Altura varía con seno/coseno para naturalidad
        float h = 500 + 40 * sin(ax * 0.02f) + 20 * sin(ax * 0.05f) + 15 * cos(ax * 0.08f);
        glVertex2f(ax, h);
        glVertex2f(ax, 600); // Línea superior fuera de pantalla
    }
    glEnd();

    // Capa media de montañas
    glColor3f(0.4f, 0.6f, 0.3f);
    glBegin(GL_TRIANGLE_STRIP);
    for (float x = 0; x < 1200; x += MOUNTAIN_DETAIL_LEVEL)
    {
        float ax = x + landscapeOffset;
        float h = 480 + 35 * sin((ax + 50) * 0.025f) + 25 * cos((ax + 30) * 0.04f) + 10 * sin(ax * 0.1f);
        glVertex2f(ax, h);
        glVertex2f(ax, 580);
    }
    glEnd();

    // Capa frontal de montañas
    glColor3f(0.5f, 0.7f, 0.4f);
    glBegin(GL_TRIANGLE_STRIP);
    for (float x = 0; x < 1200; x += MOUNTAIN_DETAIL_LEVEL)
    {
        float ax = x + landscapeOffset;
        float h = 460 + 30 * sin((ax + 100) * 0.03f) + 20 * sin((ax + 80) * 0.06f) + 12 * cos((ax + 20) * 0.09f);
        glVertex2f(ax, h);
        glVertex2f(ax, 560);
    }
    glEnd();

    // Toques de vegetación en la montaña
    glColor3f(0.2f, 0.4f, 0.1f);
    for (float x = 20; x < 1200; x += 25)
    {
        float vx = x + landscapeOffset;
        float baseH = 470 + 25 * sin(vx * 0.03f);
        // Pequeños triángulos como arbustos
        for (int i = 0; i < 8; i++)
        {
            float lx = vx + (i % 3) * 3;
            float ly = baseH + i * 2;
            glBegin(GL_TRIANGLES);
            glVertex2f(lx - 1.5f, ly);
            glVertex2f(lx + 1.5f, ly);
            glVertex2f(lx, ly + 3);
            glEnd();
        }
    }

    // Rocas en caída en primer plano
    glColor3f(0.4f, 0.3f, 0.2f);
    for (float x = 20; x < 1000; x += 45)
    {
        float rx = x + landscapeOffset;
        float ry = 450 + ((int)(x + frameCount) % 50); // Mueve rocas con el tiempo

        // Cada roca es un triángulo o un pequeño grupo de triángulos
        glBegin(GL_TRIANGLES);
        glVertex2f(rx - 2, ry - 2);
        glVertex2f(rx + 3, ry - 1);
        glVertex2f(rx + 1, ry + 3);

        glVertex2f(rx + 6, ry - 4);
        glVertex2f(rx + 10, ry - 2);
        glVertex2f(rx + 8, ry + 1);

        glVertex2f(rx + 2, ry + 1);
        glVertex2f(rx + 6, ry + 3);
        glVertex2f(rx + 4, ry + 4);
        glEnd();
    }
}