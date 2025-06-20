#include "DGHY.h"
#include "AEWK.h"
#include <GL/glut.h>
#include <math.h>

#define PASO 0.1f // Incrementado para mejor rendimiento

static const float local_finger_brown_r = 0.85f, local_finger_brown_g = 0.65f, local_finger_brown_b = 0.50f;
static const float local_nail_white_r = 0.95f, local_nail_white_g = 0.95f, local_nail_white_b = 0.95f;

// Función básica para dibujar un punto
void drawPunto(float x, float y, float z)
{
    glColor3f(local_finger_brown_r, local_finger_brown_g, local_finger_brown_b);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
}

// Función para dibujar una línea usando puntos
void drawLine3D(Punto3D start, Punto3D end)
{
    int segments = (int)(sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2) + pow(end.z - start.z, 2)) / PASO);
    if (segments < 1)
        segments = 1;

    for (int i = 0; i <= segments; i++)
    {
        float t = (float)i / (float)segments;
        float x = start.x + t * (end.x - start.x);
        float y = start.y + t * (end.y - start.y);
        float z = start.z + t * (end.z - start.z);
        drawPunto(x, y, z);
    }
}

void drawPalma()
{
    float w = ANCHO_PALMA / 2;
    float h = ALTO_PALMA / 2;
    float d = PROFUNDIDAD_PALMA / 2;

    // Densidad reducida para mejor rendimiento
    float densidad_optimizada = DENSIDAD_PUNTOS * 1.5f;

    glBegin(GL_POINTS);
    glColor3f(local_finger_brown_r, local_finger_brown_g, local_finger_brown_b);

    // Mitad inferior (media elipsoide)
    for (float x = -w; x <= w; x += densidad_optimizada)
    {
        for (float y = -h; y <= 0.0f; y += densidad_optimizada)
        {
            for (float z = -d; z <= d; z += densidad_optimizada)
            {
                float rx = x / w;
                float ry = y / h;
                float rz = z / d;
                float r = rx * rx + ry * ry + rz * rz;
                if (r <= 1.0f)
                {
                    glVertex3f(x, y, z);
                }
            }
        }
    }

    // Mitad superior (bloque rectangular)
    for (float x = -w; x <= w; x += densidad_optimizada)
    {
        for (float y = 0.0f; y <= h; y += densidad_optimizada)
        {
            for (float z = -d; z <= d; z += densidad_optimizada)
            {
                glVertex3f(x, y, z);
            }
        }
    }
    glEnd();
}

void drawLetterD()
{
    drawPalma();

    float palmSquareTop = ALTO_PALMA / 2;

    // Posiciones
    float fingerPositions[] = {
        ANCHO_PALMA / 3.0f,  // Meñique
        ANCHO_PALMA / 9.0f,  // Anular
        -ANCHO_PALMA / 9.0f, // Medio
        -ANCHO_PALMA / 3.0f  // Índice
    };

    // Alturas
    float fingerHeights[] = {
        1.8f, // Meñique
        1.9f, // Anular
        2.2f, // Medio
        3.0f  // Índice
    };

    // Dibujar los cuatro dedos
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();

        if (i == 3)
        { // Dedo índice (extendido hacia arriba)
            glTranslatef(fingerPositions[i], palmSquareTop, 0);
            glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
            glTranslatef(-fingerPositions[i], -palmSquareTop, 0);

            drawStraightFinger(
                fingerPositions[i],
                fingerHeights[i],
                palmSquareTop,
                local_finger_brown_r,
                local_finger_brown_g,
                local_finger_brown_b);
        }
        else
        { // Meñique, anular y medio (rotados hacia el pulgar)
            float rotationZ = -15.0f + (i * 5.0f);

            glTranslatef(fingerPositions[i], palmSquareTop, 0);

            if (i == 2)
            { // Dedo medio - curvatura adicional hacia el pulgar
                glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
                glRotatef(-25.0f, 0.0f, 0.0f, 1.0f);
            }
            else
            { // Meñique y anular
                glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
                glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);
            }

            glTranslatef(-fingerPositions[i], -palmSquareTop, 0);

            drawFinger(
                fingerPositions[i],
                fingerHeights[i],
                palmSquareTop,
                local_finger_brown_r,
                local_finger_brown_g,
                local_finger_brown_b);
        }
        glPopMatrix();
    }

    drawCommonThumb(
        -ANCHO_PALMA / 2 - 0.35f,
        -ALTO_PALMA / 4 + 0.7f,
        0.55f,
        45.0f,
        10.0f,
        -15.0f,
        local_finger_brown_r, local_finger_brown_g, local_finger_brown_b,
        local_nail_white_r, local_nail_white_g, local_nail_white_b,
        -ANCHO_PALMA / 2 - 0.02f,
        -ALTO_PALMA / 4 + 0.7f,
        0.48f,
        -0.35f, 0.15f, 0.08f,
        0);
}

void drawLetterY()
{
    drawPalma();

    float palmSquareTop = ALTO_PALMA / 2;

    // Posiciones
    float fingerPositions[] = {
        ANCHO_PALMA / 2.6f,  // Meñique
        ANCHO_PALMA / 8.0f,  // Anular
        -ANCHO_PALMA / 8.0f, // Medio
        -ANCHO_PALMA / 3.0f  // Índice
    };

    // Alturas
    float fingerHeights[] = {
        1.8f, // Meñique
        1.4f, // Anular
        1.4f, // Medio
        1.4f  // Índice
    };

    // Dibujar los cuatro dedos
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();

        if (i == 0)
        { // Meñique
            glTranslatef(fingerPositions[i], palmSquareTop, 0.0f);
            glRotatef(-5.0f, 0.0f, 0.0f, 1.0f);
            glTranslatef(-fingerPositions[i], -palmSquareTop, 0.0f);
            drawStraightFinger(
                fingerPositions[i],
                fingerHeights[i],
                palmSquareTop,
                local_finger_brown_r,
                local_finger_brown_g,
                local_finger_brown_b);
        }
        else
        { // Dedos flexionados
            glTranslatef(fingerPositions[i], palmSquareTop, 0.3f);
            glRotatef(50.0f, 1.0f, 0.0f, 0.0f);
            glTranslatef(-fingerPositions[i], -palmSquareTop, 0);

            drawFinger(
                fingerPositions[i],
                fingerHeights[i],
                palmSquareTop,
                local_finger_brown_r,
                local_finger_brown_g,
                local_finger_brown_b);
        }
        glPopMatrix();
    }

    // PULGAR COMPLETAMENTE HORIZONTAL
    drawCommonThumb(
        -ANCHO_PALMA / 2.0f,       // X
        -ALTO_PALMA / 4.0f + 0.5f, // Y
        0.0f,                      // Z
        5.0f,                      // rotX
        0.0f,                      // rotY
        35.0f,                     // rotZ
        local_finger_brown_r, local_finger_brown_g, local_finger_brown_b,
        local_nail_white_r, local_nail_white_g, local_nail_white_b,
        -ANCHO_PALMA / 2.0f - 0.05f,
        -ALTO_PALMA / 4.0f + 0.5f,
        0.0f,
        0.25f, 0.12f, 0.1f,
        1);
}

void drawLetterG()
{
    glPushMatrix();
    glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);

    drawPalma();

    float palmSquareTop = ALTO_PALMA / 2;

    // Posiciones
    float fingerPositions[] = {
        ANCHO_PALMA / 3.0f,  // Meñique
        ANCHO_PALMA / 9.0f,  // Anular
        -ANCHO_PALMA / 9.0f, // Medio
        -ANCHO_PALMA / 3.0f  // Índice
    };

    // Alturas
    float fingerHeights[] = {
        1.4f, // Meñique
        1.4f, // Anular
        1.4f, // Medio
        2.5f  // Índice
    };

    // Dibujar dedos con separación
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();

        glTranslatef(0.0f, 0.0f, 0.4f);

        if (i == 3)
        { // Índice
            drawStraightFinger(
                fingerPositions[i],
                fingerHeights[i],
                palmSquareTop,
                local_finger_brown_r,
                local_finger_brown_g,
                local_finger_brown_b);
        }
        else
        { // Dedos flexionados
            glTranslatef(fingerPositions[i], palmSquareTop, 0);
            glRotatef(50.0f, 1.0f, 0.0f, 0.0f);
            glTranslatef(-fingerPositions[i], -palmSquareTop, 0);

            drawFinger(
                fingerPositions[i],
                fingerHeights[i],
                palmSquareTop,
                local_finger_brown_r,
                local_finger_brown_g,
                local_finger_brown_b);
        }
        glPopMatrix();
    }

    // PULGAR
    drawCommonThumb(
        -ANCHO_PALMA / 2.0f + 0.2f,
        -ALTO_PALMA / 4.0f + 0.5f,
        0.4f,
        0.0f, 110.0f, 0.0f,
        local_finger_brown_r, local_finger_brown_g, local_finger_brown_b,
        local_nail_white_r, local_nail_white_g, local_nail_white_b,
        -ANCHO_PALMA / 2.0f + 0.5f,
        -ALTO_PALMA / 4.0f + 0.5f,
        0.3f,
        0.0f, 0.0f, 0.0f,
        1);

    glPopMatrix();
}

void drawLetterH()
{
    glPushMatrix();
    glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);

    drawPalma();

    float palmSquareTop = ALTO_PALMA / 2;

    float fingerPositions[] = {
        ANCHO_PALMA / 3.0f,  // Meñique
        ANCHO_PALMA / 9.0f,  // Anular
        -ANCHO_PALMA / 9.0f, // Medio
        -ANCHO_PALMA / 3.0f  // Índice
    };

    float fingerHeights[] = {
        1.4f, // Meñique
        1.4f, // Anular
        2.5f, // Medio
        2.5f  // Índice
    };

    // Dibujar dedos
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.4f);

        if (i >= 2)
        { // Índice y medio extendidos
            drawStraightFinger(
                fingerPositions[i],
                fingerHeights[i],
                palmSquareTop,
                local_finger_brown_r,
                local_finger_brown_g,
                local_finger_brown_b);
        }
        else
        { // Meñique y anular flexionados
            glTranslatef(fingerPositions[i], palmSquareTop, 0);
            glRotatef(50.0f, 1.0f, 0.0f, 0.0f);
            glTranslatef(-fingerPositions[i], -palmSquareTop, 0);

            drawFinger(
                fingerPositions[i],
                fingerHeights[i],
                palmSquareTop,
                local_finger_brown_r,
                local_finger_brown_g,
                local_finger_brown_b);
        }
        glPopMatrix();
    }

    // PULGAR
    drawCommonThumb(
        -ANCHO_PALMA / 2.0f + 0.3f,
        -ALTO_PALMA / 4.0f + 0.5f,
        0.4f,
        0.0f, 90.0f, 0.0f,
        local_finger_brown_r, local_finger_brown_g, local_finger_brown_b,
        local_nail_white_r, local_nail_white_g, local_nail_white_b,
        -ANCHO_PALMA / 2.0f + 0.5f,
        -ALTO_PALMA / 4.0f + 0.5f,
        0.3f,
        0.0f, 0.0f, 0.0f,
        1);

    glPopMatrix();
}