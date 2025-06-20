#include "AEWK.h"
#include <stdbool.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Variables globales de colores
float blue_r = 0.1f, blue_g = 0.2f, blue_b = 1.0f;
float finger_blue_r = 0.3f, finger_blue_g = 0.5f, finger_blue_b = 1.0f;
float thumb_brown_r = 0.85f, thumb_brown_g = 0.65f, thumb_brown_b = 0.50f;
float nail_white_r = 0.95f, nail_white_g = 0.95f, nail_white_b = 0.95f;

// Función básica para dibujar un punto
void drawPoint(float x, float y, float z)
{
    glColor3f(SKIN_R, SKIN_G, SKIN_B);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
}

// Función para dibujar un punto con color específico
void drawPointWithColor(float x, float y, float z, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
}

// Función para dibujar una línea usando puntos
void drawLine(Point3D start, Point3D end, int segments)
{
    for (int i = 0; i <= segments; i++)
    {
        float t = (float)i / (float)segments;
        float x = start.x + t * (end.x - start.x);
        float y = start.y + t * (end.y - start.y);
        float z = start.z + t * (end.z - start.z);
        drawPoint(x, y, z);
    }
}

// funciones reutilizables //
//  Función para dibujar la palma común
void drawPalm(float palmSquareBottom, float palmSquareTop, // Función para dibujar la palma común
              float blue_r, float blue_g, float blue_b)
{
    float skin_r = 0.65f, skin_g = 0.45f, skin_b = 0.35f;                 // Colores para piel moreno - valores RGB realistas
    float pw2 = PALM_WIDTH / 2, palmH = palmSquareTop - palmSquareBottom, // Precálculo de valores constantes
        palmH2 = palmH / 2, centerY = palmSquareBottom + palmH2;
    for (float z = -0.45f; z <= 0.45f; z += 0.035f)
        for (float y = palmSquareBottom; y <= palmSquareTop; y += 0.035f)
            for (float x = -pw2; x <= pw2; x += 0.035f)
            {
                bool drawPoint = true;
                float distXZ = sqrt(x * x + z * z), maxR = sqrt(pw2 * pw2 + 0.45f * 0.45f), absX = fabs(x);
                if (y <= palmSquareBottom + 0.8f)
                { // Redondeo en la parte inferior
                    float rf = (palmSquareBottom + 0.65f - y) / 0.8f,
                          effR = maxR * (1 - rf * 1.10f);
                    if (distXZ > effR)
                        drawPoint = false;
                }
                if (drawPoint && y >= palmSquareTop - 0.45f)
                { // Redondeo en la parte superior
                    float rf = (y - (palmSquareTop - 0.45f)) / 0.45f,
                          effR = maxR * (1 - rf * 0.3f);
                    if (distXZ > effR)
                        drawPoint = false;
                }
                if (drawPoint && absX >= pw2 - 0.3f)
                { // Redondeo de bordes laterales
                    float srf = (absX - (pw2 - 0.4f)) / 0.4f,
                          allowedZ = 0.45f * (1 - srf * 0.25f);
                    if (fabs(z) > allowedZ)
                        drawPoint = false;
                }
                if (drawPoint && (x >= pw2 - 0.90f || x <= -pw2 + 0.90f))
                { // Combinación de lados derecho e izquierdo
                    float srf = (x >= 0 ? (x - (pw2 - 0.4f)) / 0.4f : ((-pw2 + 0.4f) - x) / 0.4f),
                          dSC = sqrt((y - centerY) * (y - centerY) + z * z),
                          maxSR = sqrt(palmH2 * palmH2 + 0.45f * 0.45f),
                          effSR = maxSR * (1 - srf * 0.70f);
                    if (dSC > effSR)
                        drawPoint = false;
                }
                if (drawPoint)
                { // Redondeo de esquinas
                    float cdist = sqrt(x * x + (y - centerY) * (y - centerY));
                    if (cdist >= PALM_WIDTH * 0.4f)
                    {
                        float crf = (cdist - PALM_WIDTH * 0.4f) / (PALM_WIDTH * 0.1f);
                        if (crf > 1)
                            crf = 1;
                        float az = 0.45f * (1 - crf * 0.2f);
                        if (fabs(z) > az)
                            drawPoint = false;
                    }
                }
                if (drawPoint)
                { // SUPERFICIE LISA - eliminamos modulación decorativa
                    float dv = 1.0f + 0.02f * sin(x * 2.0f) * cos(y * 2.0f);
                    drawPointWithColor(x, y, z, skin_r * dv, skin_g * dv, skin_b * dv);
                }
            }
}

void drawFinger(float fingerX, float maxHeight, float palmSquareTop,
                float finger_blue_r, float finger_blue_g, float finger_blue_b) // Función para dibujar un dedo enrollado completo con interior relleno
{
    float segmentHeight = maxHeight / 12.0f;                                      // altura por segmento
    float finger_brown_r = 0.85f, finger_brown_g = 0.65f, finger_brown_b = 0.50f, // Colores para el dedo moreno claro
        nail_white_r = 0.95f, nail_white_g = 0.95f, nail_white_b = 0.95f;         // Color blanco para las uñas

    // Segmento 0 (base)
    glPushMatrix();
    glTranslatef(fingerX, palmSquareTop, 0.0f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    for (float y = 0; y <= segmentHeight; y += 0.015f) // Mejor resolución
        for (float z = -0.5f; z <= 0.5f; z += 0.015f)
            for (float x = -0.5f; x <= 0.5f; x += 0.015f)
            {
                float fingerProgress = y / maxHeight, fingerRadius = 0.37f - fingerProgress * 0.006f;
                float dist = sqrt(x * x + z * z);
                if (dist <= fingerRadius && fingerRadius > 0.20f)
                { // RELLENO SÓLIDO
                    float sf;
                    if (dist >= fingerRadius - 0.08f)
                    {
                        sf = 1.0f - fabs(dist - fingerRadius) * 6.0f;
                        if (sf < 0.8f)
                            sf = 0.8f;
                    } // Superficie externa
                    else
                    {
                        float intF = dist / (fingerRadius - 0.08f);
                        sf = 0.5f + intF * 0.3f;
                    } // Interior
                    drawPointWithColor(x, y, z, finger_brown_r * sf, finger_brown_g * sf, finger_brown_b * sf);
                }
            }

    // Segmentos 1-5
    glTranslatef(0.0f, segmentHeight, 0.0f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    for (float y = 0; y <= segmentHeight * 5; y += 0.015f)
        for (float z = -0.5f; z <= 0.5f; z += 0.015f)
            for (float x = -0.5f; x <= 0.5f; x += 0.015f)
            {
                float fingerProgress = (segmentHeight + y) / maxHeight, fingerRadius;
                if (fingerProgress <= 0.154f)
                    fingerRadius = 0.35f - (fingerProgress - 0.077f) * 0.008f;
                else if (fingerProgress <= 0.231f)
                    fingerRadius = 0.34f - (fingerProgress - 0.154f) * 0.010f;
                else if (fingerProgress <= 0.308f)
                    fingerRadius = 0.33f - (fingerProgress - 0.231f) * 0.012f;
                else if (fingerProgress <= 0.385f)
                    fingerRadius = 0.32f - (fingerProgress - 0.308f) * 0.014f;
                else
                    fingerRadius = 0.31f - (fingerProgress - 0.385f) * 0.016f; // RELLENO SÓLIDO
                float dist = sqrt(x * x + z * z);
                if (dist <= fingerRadius && fingerRadius > 0.20f)
                {
                    float sf;
                    if (dist >= fingerRadius - 0.08f)
                    {
                        sf = 1.0f - fabs(dist - fingerRadius) * 6.0f;
                        if (sf < 0.8f)
                            sf = 0.8f;
                    } // Superficie externa
                    else
                    {
                        float intF = dist / (fingerRadius - 0.08f);
                        sf = 0.5f + intF * 0.3f;
                    } // Interior
                    drawPointWithColor(x, y, z, finger_brown_r * sf, finger_brown_g * sf, finger_brown_b * sf);
                }
            }
    glPopMatrix(); // fin segmentos 1-5

    // Segmento 6
    glPushMatrix();
    glTranslatef(fingerX, palmSquareTop, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, segmentHeight * 5, 0.0f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    for (float y = 0; y <= segmentHeight; y += 0.015f)
        for (float z = -0.5f; z <= 0.5f; z += 0.015f)
            for (float x = -0.5f; x <= 0.5f; x += 0.015f)
            {
                float fingerProgress = (segmentHeight * 5 + y) / maxHeight;
                float fingerRadius = 0.30f - (fingerProgress - 0.417f) * 0.018f; // RELLENO SÓLIDO
                float dist = sqrt(x * x + z * z);
                if (dist <= fingerRadius && fingerRadius > 0.20f)
                {
                    float sf;
                    if (dist >= fingerRadius - 0.08f)
                    {
                        sf = 1.0f - fabs(dist - fingerRadius) * 6.0f;
                        if (sf < 0.8f)
                            sf = 0.8f;
                    } // Superficie externa
                    else
                    {
                        float intF = dist / (fingerRadius - 0.08f);
                        sf = 0.5f + intF * 0.3f;
                    } // Interior
                    drawPointWithColor(x, y, z, finger_brown_r * sf, finger_brown_g * sf, finger_brown_b * sf);
                }
            }

    // Segmentos 7-9
    glTranslatef(0.0f, segmentHeight, 0.0f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    for (float y = 0; y <= segmentHeight * 3; y += 0.015f)
        for (float z = -0.5f; z <= 0.5f; z += 0.015f)
            for (float x = -0.5f; x <= 0.5f; x += 0.015f)
            {
                float fingerProgress = (segmentHeight * 6 + y) / maxHeight;
                float fingerRadius = (fingerProgress <= 0.5f ? 0.29f - (fingerProgress - 0.417f) * 0.020f : fingerProgress <= 0.583f ? 0.28f - (fingerProgress - 0.5f) * 0.022f
                                                                                                                                     : 0.27f - (fingerProgress - 0.583f) * 0.024f); // RELLENO SÓLIDO
                float dist = sqrt(x * x + z * z);
                if (dist <= fingerRadius && fingerRadius > 0.20f)
                {
                    float sf;
                    if (dist >= fingerRadius - 0.08f)
                    {
                        sf = 1.0f - fabs(dist - fingerRadius) * 6.0f;
                        if (sf < 0.8f)
                            sf = 0.8f;
                    } // Superficie externa
                    else
                    {
                        float intF = dist / (fingerRadius - 0.08f);
                        sf = 0.5f + intF * 0.3f;
                    } // Interior
                    drawPointWithColor(x, y, z, finger_brown_r * sf, finger_brown_g * sf, finger_brown_b * sf);
                }
            }

    // Segmento 10
    glTranslatef(0.0f, segmentHeight * 3, 0.0f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    for (float y = 0; y <= segmentHeight; y += 0.015f)
        for (float z = -0.5f; z <= 0.5f; z += 0.015f)
            for (float x = -0.5f; x <= 0.5f; x += 0.015f)
            {
                float fingerProgress = (segmentHeight * 9 + y) / maxHeight;
                float fingerRadius = 0.26f - (fingerProgress - 0.667f) * 0.026f; // RELLENO SÓLIDO
                float dist = sqrt(x * x + z * z);
                if (dist <= fingerRadius && fingerRadius > 0.20f)
                {
                    float sf;
                    if (dist >= fingerRadius - 0.08f)
                    {
                        sf = 1.0f - fabs(dist - fingerRadius) * 6.0f;
                        if (sf < 0.8f)
                            sf = 0.8f;
                    } // Superficie externa
                    else
                    {
                        float intF = dist / (fingerRadius - 0.08f);
                        sf = 0.5f + intF * 0.3f;
                    } // Interior
                    drawPointWithColor(x, y, z, finger_brown_r * sf, finger_brown_g * sf, finger_brown_b * sf);
                }
            }

    // Segmentos 11-12 (incluyendo la punta con uña blanca)
    glTranslatef(0.0f, segmentHeight, 0.0f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    for (float y = 0; y <= segmentHeight * 2; y += 0.015f)
        for (float z = -0.5f; z <= 0.5f; z += 0.015f)
            for (float x = -0.5f; x <= 0.5f; x += 0.015f)
            {
                float fingerProgress = (segmentHeight * 10 + y) / maxHeight, fingerRadius;
                if (fingerProgress <= 0.833f)
                    fingerRadius = 0.25f - (fingerProgress - 0.75f) * 0.028f;
                else if (fingerProgress <= 0.917f)
                    fingerRadius = 0.24f - (fingerProgress - 0.833f) * 0.030f;
                else
                    fingerRadius = 0.23f - (fingerProgress - 0.917f) * 0.06f; // Cálculo radio
                float d = sqrt(x * x + z * z);
                if (fingerProgress >= 0.917f)
                { // Punta curva - UÑAS BLANCAS
                    float yFromTip = y - segmentHeight, dt = sqrt(x * x + z * z + yFromTip * yFromTip), tipR = fingerRadius + 0.03f;
                    if (dt <= tipR)
                    {
                        float sf;
                        if (dt >= fingerRadius - 0.05f)
                        { // UÑA BLANCA superficie
                            sf = 1.0f - (dt / tipR) * 0.2f;
                            if (sf < 0.85f)
                                sf = 0.85f;
                            drawPointWithColor(x, y, z, nail_white_r * sf, nail_white_g * sf, nail_white_b * sf);
                        }
                        else
                        { // Interior moreno
                            float intF = dt / (fingerRadius - 0.05f);
                            sf = 0.6f + intF * 0.3f;
                            drawPointWithColor(x, y, z, finger_brown_r * sf, finger_brown_g * sf, finger_brown_b * sf);
                        }
                    }
                }
                else if (fingerProgress >= 0.85f)
                { // Transición hacia la uña - gradiente moreno a blanco
                    if (d <= fingerRadius && fingerRadius > 0.20f)
                    {
                        float t = (fingerProgress - 0.85f) / (0.917f - 0.85f), sf;
                        if (d >= fingerRadius - 0.08f)
                        {
                            sf = 1.0f - fabs(d - fingerRadius) * 6.0f;
                            if (sf < 0.8f)
                                sf = 0.8f;
                        } // superficie externa
                        else
                        {
                            float intF = d / (fingerRadius - 0.08f);
                            sf = 0.5f + intF * 0.3f;
                        } // interior
                        float r = (finger_brown_r * (1 - t) + nail_white_r * t) * sf, g = (finger_brown_g * (1 - t) + nail_white_g * t) * sf, b = (finger_brown_b * (1 - t) + nail_white_b * t) * sf;
                        drawPointWithColor(x, y, z, r, g, b);
                    }
                }
                else
                { // RELLENO SÓLIDO para segmentos normales - color moreno
                    if (d <= fingerRadius && fingerRadius > 0.20f)
                    {
                        float sf;
                        if (d >= fingerRadius - 0.08f)
                        {
                            sf = 1.0f - fabs(d - fingerRadius) * 6.0f;
                            if (sf < 0.8f)
                                sf = 0.8f;
                        } // superficie externa
                        else
                        {
                            float intF = d / (fingerRadius - 0.08f);
                            sf = 0.5f + intF * 0.3f;
                        } // interior
                        drawPointWithColor(x, y, z, finger_brown_r * sf, finger_brown_g * sf, finger_brown_b * sf);
                    }
                }
            }
    glPopMatrix(); // fin
}

// Función para dibujar un dedo recto con interior relleno
void drawStraightFinger(float fingerX, float maxHeight, float palmSquareTop,
                        float finger_blue_r, float finger_blue_g, float finger_blue_b) // Función para dibujar un dedo recto con RELLENO SÓLIDO
{
    float finger_brown_r = 0.85f, finger_brown_g = 0.65f, finger_brown_b = 0.50f, // Colores para el dedo moreno claro
        nail_white_r = 0.95f, nail_white_g = 0.95f, nail_white_b = 0.95f;         // Color blanco para las uñas
    glPushMatrix();
    glTranslatef(fingerX, palmSquareTop, 0.0f); // Posicionar dedo

    for (float y = 0; y <= maxHeight; y += 0.015f) // Mejor resolución
        for (float z = -0.5f; z <= 0.5f; z += 0.015f)
            for (float x = -0.5f; x <= 0.5f; x += 0.015f)
            {
                float fingerProgress = y / maxHeight, fingerRadius; // Cálculo progresivo del radio
                if (fingerProgress <= 0.083f)
                    fingerRadius = 0.37f - fingerProgress * 0.006f;
                else if (fingerProgress <= 0.167f)
                    fingerRadius = 0.35f - (fingerProgress - 0.083f) * 0.008f;
                else if (fingerProgress <= 0.25f)
                    fingerRadius = 0.34f - (fingerProgress - 0.167f) * 0.010f;
                else if (fingerProgress <= 0.333f)
                    fingerRadius = 0.33f - (fingerProgress - 0.25f) * 0.012f;
                else if (fingerProgress <= 0.417f)
                    fingerRadius = 0.32f - (fingerProgress - 0.333f) * 0.014f;
                else if (fingerProgress <= 0.5f)
                    fingerRadius = 0.31f - (fingerProgress - 0.417f) * 0.016f;
                else if (fingerProgress <= 0.583f)
                    fingerRadius = 0.30f - (fingerProgress - 0.5f) * 0.018f;
                else if (fingerProgress <= 0.667f)
                    fingerRadius = 0.29f - (fingerProgress - 0.583f) * 0.020f;
                else if (fingerProgress <= 0.75f)
                    fingerRadius = 0.28f - (fingerProgress - 0.667f) * 0.022f;
                else if (fingerProgress <= 0.833f)
                    fingerRadius = 0.27f - (fingerProgress - 0.75f) * 0.024f;
                else if (fingerProgress <= 0.917f)
                    fingerRadius = 0.25f - (fingerProgress - 0.833f) * 0.028f;
                else
                    fingerRadius = 0.23f - (fingerProgress - 0.917f) * 0.06f; // Punta curva - UÑAS BLANCAS

                float d = sqrt(x * x + z * z);
                if (fingerProgress >= 0.917f)
                { // RELLENO SÓLIDO para la punta con UÑA BLANCA
                    float yFromTip = y - maxHeight * 0.917f, tipR = fingerRadius + 0.03f;
                    float dt = sqrt(x * x + z * z + (yFromTip * 2.0f) * (yFromTip * 2.0f));
                    if (dt <= tipR)
                    {
                        float sf;
                        if (dt >= tipR - 0.05f)
                        { // Superficie externa de la punta - UÑA BLANCA
                            sf = 1.0f - (dt / tipR) * 0.2f;
                            if (sf < 0.85f)
                                sf = 0.85f;
                            drawPointWithColor(x, y, z, nail_white_r * sf, nail_white_g * sf, nail_white_b * sf);
                        }
                        else
                        { // Interior de la punta - moreno más claro
                            float intF = dt / (tipR - 0.05f);
                            sf = 0.6f + intF * 0.3f;
                            drawPointWithColor(x, y, z, finger_brown_r * sf, finger_brown_g * sf, finger_brown_b * sf);
                        }
                    }
                }
                else if (fingerProgress >= 0.85f && d <= fingerRadius && fingerRadius > 0.20f)
                { // Transición hacia la uña
                    float t = (fingerProgress - 0.85f) / (0.917f - 0.85f), sf;
                    if (d >= fingerRadius - 0.08f)
                    { // Superficie externa
                        sf = 1.0f - fabs(d - fingerRadius) * 6.0f;
                        if (sf < 0.8f)
                            sf = 0.8f;
                    }
                    else
                    { // Interior
                        float intF = d / (fingerRadius - 0.08f);
                        sf = 0.5f + intF * 0.3f;
                    }
                    float r = (finger_brown_r * (1 - t) + nail_white_r * t) * sf,
                          g = (finger_brown_g * (1 - t) + nail_white_g * t) * sf,
                          b = (finger_brown_b * (1 - t) + nail_white_b * t) * sf; // Mezclar colores moreno y blanco según la transición
                    drawPointWithColor(x, y, z, r, g, b);
                }
                else if (d <= fingerRadius && fingerRadius > 0.20f)
                { // Segmentos cilíndricos normales - COLOR MORENO
                    float sf;
                    if (d >= fingerRadius - 0.08f)
                    { // Superficie externa - más brillante
                        sf = 1.0f - fabs(d - fingerRadius) * 6.0f;
                        if (sf < 0.8f)
                            sf = 0.8f;
                    }
                    else
                    { // Interior - gradualmente más oscuro
                        float intF = d / (fingerRadius - 0.08f);
                        sf = 0.5f + intF * 0.3f;
                    }
                    drawPointWithColor(x, y, z, finger_brown_r * sf, finger_brown_g * sf, finger_brown_b * sf); // RELLENO SÓLIDO
                }
            }
    glPopMatrix(); // fin
}

// NUEVA FUNCIÓN CON OPCIÓN DOBLADO/RECTO
void drawCommonThumb(float posX, float posY, float posZ, float rotX, float rotY, float rotZ,
                     float thumb_brown_r, float thumb_brown_g, float thumb_brown_b,
                     float nail_white_r, float nail_white_g, float nail_white_b,
                     float connectionOffsetX, float connectionOffsetY, float connectionOffsetZ,
                     float connectionCurveX, float connectionCurveY, float connectionCurveZ, int isStraight)
{
    glPushMatrix(); // Transformaciones generales del pulgar
    glTranslatef(posX, posY, posZ);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);

    // Primer tramo - primeros 4 segmentos del pulgar
    for (float y = 0; y <= 1; y += 0.05f) // Reducido de 0.025f a 0.05f
    {
        float prog = y / 2, cx = 0, cz = 0, rad;
        if (!isStraight)
        {
            if (prog <= 0.4f)
            {
                cx = prog * 0.04f;
                cz = prog * 0.25f;
            }
            else
            {
                cx = 0.016f + prog * 0.025f;
                cz = 0.1f + (prog - 0.4f) * 0.4f;
            }
        }

        if (prog <= 0.125f)
            rad = 0.42f - prog * 0.01f;
        else if (prog <= 0.25f)
            rad = 0.41f - (prog - 0.125f) * 0.015f;
        else if (prog <= 0.375f)
            rad = 0.39f - (prog - 0.25f) * 0.02f;
        else
            rad = 0.37f - (prog - 0.375f) * 0.025f;

        for (float x = -0.85f; x <= 0.85f; x += 0.04f)   // Reducido de 0.02f a 0.04f
            for (float z = -0.5f; z <= 0.8f; z += 0.04f) // Reducido de 0.02f a 0.04f
            {
                float dx = x - cx, dz = z - cz, d = sqrt(dx * dx + dz * dz);
                if (d <= rad && rad > 0.25f)
                {
                    float sf, thr = rad - 0.08f;
                    sf = (d >= thr) ? fmax(0.8f, 1 - fabs(d - rad) * 6) : 0.5f + (d / thr) * 0.3f;
                    drawPointWithColor(x, y, z, thumb_brown_r * sf, thumb_brown_g * sf, thumb_brown_b * sf);
                }
            }
    }

    // Segundo tramo - últimos 4 segmentos (recto o doblado)
    glPushMatrix();
    if (isStraight)
        glTranslatef(0, 1, 0); // MODO RECTO
    else                       // MODO DOBLADO
    {
        glTranslatef(0.033f, 1, 0.22f);
        glRotatef(-70, 0, 0, 1);
        glRotatef(30, 1, 0, 0);
    }

    for (float y = 0; y <= 1; y += 0.05f) // Reducido de 0.025f a 0.05f
    {
        float prog = 0.5f + y / 2, rad;
        if (prog <= 0.625f)
            rad = 0.35f - (prog - 0.5f) * 0.03f;
        else if (prog <= 0.75f)
            rad = 0.33f - (prog - 0.625f) * 0.035f;
        else if (prog <= 0.875f)
            rad = 0.31f - (prog - 0.75f) * 0.04f;
        else
            rad = 0.29f - (prog - 0.875f) * 0.08f;

        for (float x = -0.85f; x <= 0.85f; x += 0.04f)   // Reducido de 0.02f a 0.04f
            for (float z = -0.5f; z <= 0.8f; z += 0.04f) // Reducido de 0.02f a 0.04f
            {
                float d = sqrt(x * x + z * z);
                if (prog >= 0.875f) // Punta curva - UÑA BLANCA
                {
                    float yt = (y - 0.875f) * 2, dt = sqrt(x * x + z * z + yt * yt), tipR = rad + 0.05f;
                    if (dt <= tipR)
                    {
                        float sf, thr = tipR - 0.08f;
                        sf = (dt >= thr) ? fmax(0.85f, 1 - dt / tipR * 0.2f) : 0.6f + (dt / thr) * 0.3f;
                        float r = (dt >= thr ? nail_white_r : thumb_brown_r) * sf;
                        float g = (dt >= thr ? nail_white_g : thumb_brown_g) * sf;
                        float b = (dt >= thr ? nail_white_b : thumb_brown_b) * sf;
                        drawPointWithColor(x, y, z, r, g, b);
                    }
                }
                else if (prog >= 0.8f && d <= rad) // Transición a uña
                {
                    float t = (prog - 0.8f) / 0.075f, sf, thr = rad - 0.08f;
                    sf = (d >= thr) ? fmax(0.8f, 1 - fabs(d - rad) * 6) : 0.5f + (d / thr) * 0.3f;
                    float r = (thumb_brown_r * (1 - t) + nail_white_r * t) * sf;
                    float g = (thumb_brown_g * (1 - t) + nail_white_g * t) * sf;
                    float b = (thumb_brown_b * (1 - t) + nail_white_b * t) * sf;
                    drawPointWithColor(x, y, z, r, g, b);
                }
                else if (d <= rad) // Cuerpo del pulgar
                {
                    float sf, thr = rad - 0.08f;
                    sf = (d >= thr) ? fmax(0.8f, 1 - fabs(d - rad) * 6) : 0.5f + (d / thr) * 0.3f;
                    drawPointWithColor(x, y, z, thumb_brown_r * sf, thumb_brown_g * sf, thumb_brown_b * sf);
                }
            }
    }
    glPopMatrix(); // Fin segundo tramo
    glPopMatrix(); // Fin pulgar

    // Conexión del pulgar - base
    for (int i = 0; i <= 15; i++) // Reducido de 20 a 15
    {
        float t = i / 15.0f, cx = connectionOffsetX + connectionCurveX * t,
              cy = connectionOffsetY + connectionCurveY * t, cz = connectionOffsetZ + t * 0.08f,
              rr = 0.5f - t * 0.08f;

        for (float x = cx - rr; x <= cx + rr; x += 0.03f)     // Reducido de 0.015f a 0.03f
            for (float z = cz - rr; z <= cz + rr; z += 0.03f) // Reducido de 0.015f a 0.03f
                for (float y = -0.2f; y <= 0.2f; y += 0.03f)  // Reducido de 0.015f a 0.03f
                {
                    float dx = x - cx, dz = z - cz, d = sqrt(dx * dx + dz * dz);
                    if (d <= rr)
                    {
                        float sf, thr = rr - 0.08f;
                        sf = (d >= thr) ? fmax(0.85f, 1 - d / rr * 0.15f) : 0.5f + (d / thr) * 0.35f;
                        drawPointWithColor(x, cy + y, z, thumb_brown_r * sf, thumb_brown_g * sf, thumb_brown_b * sf);
                    }
                }
    }
}

void drawLetterA()
{
    // Límites verticales de la palma
    float palmSquareBottom = -PALM_HEIGHT / 2;           // Base de la palma
    float palmSquareTop = palmSquareBottom + PALM_WIDTH; // Tope de la palma

    // Renderiza la palma con color azul
    drawPalm(palmSquareBottom, palmSquareTop, blue_r, blue_g, blue_b);

    // Posiciones horizontales y alturas de los cuatro dedos
    float fingerPositions[4] = {-PALM_WIDTH / 3, -PALM_WIDTH / 9, PALM_WIDTH / 9, PALM_WIDTH / 3};
    float fingerHeights[4] = {2.8f, 3.4f, 3.2f, 2.6f};

    // Dibuja cada dedo en su lugar sobre la palma
    for (int i = 0; i < 4; i++)
    {
        drawFinger(
            fingerPositions[i], // X
            fingerHeights[i],   // Altura del dedo
            palmSquareTop,      // Base en Y (tope de palma)
            finger_blue_r,      // Color R
            finger_blue_g,      // Color G
            finger_blue_b       // Color B
        );
    }

    // Ajustes específicos para el pulgar en la forma de letra "A"
    drawCommonThumb(
        // Posición inicial del pulgar (X, Y, Z)
        -PALM_WIDTH / 2 - 0.4f,  // X: junto al lado de la palma
        -PALM_HEIGHT / 5 + 0.8f, // Y: altura de unión
        0.3f,                    // Z: profundidad de unión

        0.0f, // rotX   // Rotaciones mínimas para situar el pulgar
        0.0f, // rotY
        0.0f, // rotZ

        thumb_brown_r, thumb_brown_g, thumb_brown_b, // Colores del pulgar y la uña
        nail_white_r, nail_white_g, nail_white_b,

        -PALM_WIDTH / 2 - 0.3f,  // X de conexión más fuera         // Parámetros de la conexión del pulgar
        -PALM_HEIGHT / 4 + 0.8f, // Y de conexión
        0.3f,                    // Z de conexión

        0.0f, // curveX         // Curvas de la unión (sin curvatura para pulgar recto)
        0.0f, // curveY
        0.0f, // curveZ

        1 // isStraight: pulgar extendido
    );
}

void drawLetterE()
{
    float palmSquareBottom = -PALM_HEIGHT / 2;
    float palmSquareTop = palmSquareBottom + PALM_WIDTH;

    drawPalm(palmSquareBottom, palmSquareTop, blue_r, blue_g, blue_b);

    float fingerPositions[4] = {-PALM_WIDTH / 3, -PALM_WIDTH / 9, PALM_WIDTH / 9, PALM_WIDTH / 3};
    float fingerHeights[4] = {2.8f, 3.4f, 3.2f, 2.6f};

    for (int i = 0; i < 4; i++)
        drawFinger(fingerPositions[i], fingerHeights[i], palmSquareTop,
                   finger_blue_r, finger_blue_g, finger_blue_b);

    drawCommonThumb(
        -PALM_WIDTH / 2 - 0.35f, -PALM_HEIGHT / 4 + 0.7f, 0.55f,
        25.0f, 0.0f, 0.0f,
        thumb_brown_r, thumb_brown_g, thumb_brown_b,
        nail_white_r, nail_white_g, nail_white_b,
        -PALM_WIDTH / 2 - 0.02f, -PALM_HEIGHT / 4 + 0.7f, 0.48f,
        -0.35f, 0.15f, 0.08f,
        0);
}

void drawLetterW()
{
    glPushMatrix();
    glRotatef(0, 180, 0, 1);

    float palmSquareBottom = -PALM_HEIGHT / 2;
    float palmSquareTop = palmSquareBottom + PALM_WIDTH;

    drawPalm(palmSquareBottom, palmSquareTop, blue_r, blue_g, blue_b);

    float fingerPositions[] = {-PALM_WIDTH / 3, -PALM_WIDTH / 9, PALM_WIDTH / 9, PALM_WIDTH / 3};
    float fingerHeights[] = {2.8f, 3.4f, 3.2f, 2.6f};

    for (int i = 0; i < 4; i++)
    {
        if (i == 3)
            drawFinger(fingerPositions[i], fingerHeights[i], palmSquareTop, finger_blue_r, finger_blue_g, finger_blue_b);
        else if (i == 0 || i == 2)
        {
            glPushMatrix();
            glTranslatef(fingerPositions[i], palmSquareTop, 0);
            glRotatef(i ? -20 : 20, 0, 0, 1);
            glTranslatef(-fingerPositions[i], -palmSquareTop, 0);
            drawStraightFinger(fingerPositions[i], fingerHeights[i], palmSquareTop, finger_blue_r, finger_blue_g, finger_blue_b);
            glPopMatrix();
        }
        else
            drawStraightFinger(fingerPositions[i], fingerHeights[i], palmSquareTop, finger_blue_r, finger_blue_g, finger_blue_b);
    }

    drawCommonThumb(
        -PALM_WIDTH / 2 - 0.35f, -PALM_HEIGHT / 4 + 0.7f, 0.55f,
        25, 0, 0,
        thumb_brown_r, thumb_brown_g, thumb_brown_b, nail_white_r, nail_white_g, nail_white_b,
        -PALM_WIDTH / 2 - 0.02f, -PALM_HEIGHT / 4 + 0.7f, 0.48f,
        -0.35f, 0.15f, 0.08f,
        0);

    glPopMatrix();
}

void drawLetterK()
{
    glPushMatrix();
    glRotatef(0, 90, 0, 1);

    float palmSquareBottom = -PALM_HEIGHT / 2;
    float palmSquareTop = palmSquareBottom + PALM_WIDTH;

    drawPalm(palmSquareBottom, palmSquareTop, blue_r, blue_g, blue_b);

    float fingerPositions[] = {-PALM_WIDTH / 3, -PALM_WIDTH / 9, PALM_WIDTH / 9, PALM_WIDTH / 3};
    float fingerHeights[] = {2.8f, 3.4f, 3.2f, 2.6f};

    for (int i = 0; i < 4; i++)
    {
        if (i >= 2)
            drawFinger(fingerPositions[i], fingerHeights[i], palmSquareTop, finger_blue_r, finger_blue_g, finger_blue_b);
        else
        {
            glPushMatrix();
            glTranslatef(fingerPositions[i], palmSquareTop, 0);
            glRotatef(i ? -15 : 15, 0, 0, 1);
            glTranslatef(-fingerPositions[i], -palmSquareTop, 0);
            drawStraightFinger(fingerPositions[i], fingerHeights[i], palmSquareTop, finger_blue_r, finger_blue_g, finger_blue_b);
            glPopMatrix();
        }
    }

    glPushMatrix();
    glRotatef(15, 0, 1, 0);
    drawCommonThumb(
        -PALM_WIDTH / 2 + 0.5f, -PALM_HEIGHT / 5 + 0.8f, 0.5f, 0, 0, 0,
        thumb_brown_r, thumb_brown_g, thumb_brown_b, nail_white_r, nail_white_g, nail_white_b,
        -PALM_WIDTH / 2 + 0.5f, -PALM_HEIGHT / 4 + 0.8f, 0.3f, 0, 0, 0, 1);
    glPopMatrix();
    glPopMatrix();
}