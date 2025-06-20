#include "IRUV.h"
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Finger fingers[5];

// aplica  escala uniforme a todos  dedos y segmentos
void scaleFingers(float scale)
{
    for (int i = 0; i < 5; i++)
    {
        fingers[i].baseX *= scale;
        fingers[i].baseY *= scale;
        fingers[i].baseZ *= scale;
        for (int j = 0; j < fingers[i].numSegments; j++)
        {
            fingers[i].segments[j].length *= scale;
            fingers[i].segments[j].baseRadius *= scale;
            fingers[i].segments[j].tipRadius *= scale;
        }
    }
}
// funcion para dibujar dedos
void configureFinger(int index, int numSegments, float baseX, float baseY, float baseZ, FingerSegment segments[])
{
    fingers[index].numSegments = numSegments;
    fingers[index].baseX = baseX;
    fingers[index].baseY = baseY;
    fingers[index].baseZ = baseZ;
    fingers[index].globalBendX = 0.0f;
    fingers[index].globalBendY = 0.0f;
    fingers[index].globalBendZ = 0.0f;

    for (int i = 0; i < numSegments; i++)
    {
        fingers[index].segments[i] = segments[i];
    }
}

// dedo anular

void anular_Finger1()
{
    FingerSegment segments[4] = {
        {0.5f, 0.26f, 0.23f, 0, 0, 0, 0},
        {0.4f, 0.23f, 0.20f, 0, 0, 0, 0},
        {0.35f, 0.20f, 0.17f, 0, 0, 0, 0},
        {0.8f, 0.17f, 0.14f, 0, 0, 0, 0}};

    configureFinger(1, 4, -0.25f, 1.1f, 0.02f, segments);
}
// dedo pulgar
void pulgar_Finger4()
{ // para las cuatro letras
    FingerSegment segments[3] = {
        {0.4f, 0.30f, 0.26f, 0, 0, 0, 0},
        {0.5f, 0.26f, 0.22f, 0, 0, 0, 0},
        {0.9f, 0.22f, 0.15f, 0, 0, 0, 0}};

    configureFinger(4, 3, -PALM_WIDTHH / 2 + 3.1f, -PALM_HEIGHTT / 6, 0.2f, segments);
}
// dedo meñique
void menique_Finger0()
{ // para u, v, r
    FingerSegment segments[4] = {
        {0.4f, 0.23f, 0.20f, 0, 0, 0, 0},
        {0.35f, 0.20f, 0.17f, 0, 0, 0, 0},
        {0.45f, 0.17f, 0.14f, 0, 0, 0, 0},
        {0.45f, 0.17f, 0.14f, 0, 0, 0, 0}};

    configureFinger(0, 4, -0.7f, 1.1f, 0.0f, segments);
}

void i_finger0()
{
    FingerSegment segments[4] = {
        {0.4f, 0.23f, 0.20f, 0, 0, 0, 0},
        {0.35f, 0.20f, 0.17f, 0, 0, 0, 0},
        {0.45f, 0.17f, 0.14f, 0, 0, 0, 0},
        {0.0f, 0.0f, 0.0f, 0, 0, 0, 0}};

    configureFinger(0, 4, -0.7f, 1.1f, 0.0f, segments);
}
// dedo medio
void medio_Finger2()
{
    FingerSegment segments[5] = {
        {0.6f, 0.28f, 0.24f, 0, 0, 0, 0},
        {0.45f, 0.25f, 0.21f, 0, 0, 0, 0},
        {0.35f, 0.22f, 0.18f, 0, 0, 0, 0},
        {0.3f, 0.18f, 0.15f, 0, 0, 0, 0},
        {0.5f, 0.18f, 0.12f, 0, 0, 0, 0}};

    configureFinger(2, 5, 0.22f, 1.1f, 0.02f, segments);
}
// dedo indice
void indice_Finger3()
{
    FingerSegment segments[4] = {
        {0.55f, 0.27f, 0.23f, 0, 0, 0, 0},
        {0.42f, 0.23f, 0.20f, 0, 0, 0, 0},
        {0.33f, 0.20f, 0.17f, 0, 0, 0, 0},
        {0.8f, 0.17f, 0.14f, 0, 0, 0, 0}};

    configureFinger(3, 4, 0.7f, 1.1f, 0.02f, segments);
}
// funciones para doblar los dos primeros segmentos por dedo
void poseFinger_Folded(int index)
{
    fingers[index].segments[0].bendX = 90.0f;
    fingers[index].segments[1].bendX = 90.0f;
}

void poseFinger4_Folded()
{
    fingers[4].segments[0].bendX = 90.0f;
    fingers[4].segments[1].bendZ = 90.0f;
}
// inicializa todos los dedos de la mano
void initializeFingersGeneric(void (*meniqueFunc)(), void (*postConfig)())
{
    if (meniqueFunc != NULL)
        i_finger0();
        menique_Finger0();
        anular_Finger1();
        medio_Finger2();
        indice_Finger3();
        pulgar_Finger4();
    if (postConfig != NULL)
        postConfig();

    scaleFingers(SCALE_FACTOR); // mantiene el tamaño
}
void configR()
{
    fingers[2].globalBendZ = -10.0f;
    fingers[3].baseZ = 0.2f;
    fingers[3].globalBendZ = 20.0f;
}

void configV()
{
    fingers[2].globalBendZ = 10.0f;
    fingers[3].globalBendZ = -10.0f;
}

//  segmento del dedo como una especie de cilindro
void drawStraightFingerSegment(float baseX, float baseY, float baseZ, FingerSegment segment)
{
    glBegin(GL_POINTS);

    // color calido
    const float baseR = 0.95f;
    const float baseG = 0.75f;
    const float baseB = 0.55f;
    // numde pasos alrededor del eje del dedo
    int radialSteps = 86;
    float angleStep = 2 * PI / radialSteps;

    for (float y = 0; y <= segment.length; y += POINT_DENSITY * 2.0f)
    {
        float t = y / segment.length;
        // interpolacion entre base y punta para cambiar el radio
        float currentRadius = segment.baseRadius - (segment.baseRadius - segment.tipRadius) * t;
        float segmentR = baseR - t * 0.1f;
        float segmentG = baseG - t * 0.05f;
        float segmentB = baseB - t * 0.02f;

        for (int i = 0; i < radialSteps; i++)
        {
            float rad = i * angleStep;
            float x = currentRadius * cos(rad);
            float z = currentRadius * sin(rad);
            float lightFactor = 0.7f + 0.3f * (cos(rad) + 1.0f) / 2.0f;

            // Color con iluminación
            float finalR = segmentR * fmax(0.7f, lightFactor);
            float finalG = segmentG * fmax(0.7f, lightFactor);
            float finalB = segmentB * fmax(0.7f, lightFactor);

            glColor3f(finalR, finalG, finalB);
            glVertex3f(baseX + x, baseY + y, baseZ + z);

            // puntos dentro del cilindro relleno interno
            for (float innerR = currentRadius * 0.7f; innerR > 0; innerR -= POINT_DENSITY * 1.5f)
            {
                float innerFactor = 0.8f - 0.2f * (innerR / currentRadius);
                glColor3f(finalR * innerFactor, finalG * innerFactor, finalB * innerFactor);
                glVertex3f(baseX + innerR * cos(rad), baseY + y, baseZ + innerR * sin(rad));
            }
        }
    }
    glEnd();
}
// dedo completo aplicando dobleces entre segmentos
void drawArticulatedFinger(int fingerIndex)
{
    Finger *finger = &fingers[fingerIndex];

    glPushMatrix();
    // posicion inicial del dedo sobre la palma
    glTranslatef(finger->baseX, finger->baseY, finger->baseZ);

    glRotatef(finger->globalBendX, 1.0f, 0.0f, 0.0f);
    glRotatef(finger->globalBendY, 0.0f, 1.0f, 0.0f);
    glRotatef(finger->globalBendZ, 0.0f, 0.0f, 1.0f);

    for (int i = 0; i < finger->numSegments; i++)
    {
        glPushMatrix();

        // aplica desplazamiento en Z
        if (finger->segments[i].offsetz != 0.0f)
        {
            glTranslatef(0.0f, 0.0f, finger->segments[i].offsetz);
        }

        drawStraightFingerSegment(0.0f, 0.0f, 0.0f, finger->segments[i]);

        glPopMatrix();

        // avanza  siguiente segmento
        glTranslatef(0.0f, finger->segments[i].length, 0.0f);

        // rotacion rectaas
        glRotatef(finger->segments[i].bendX, 1.0f, 0.0f, 0.0f);
        glRotatef(finger->segments[i].bendY, 0.0f, 1.0f, 0.0f);
        glRotatef(finger->segments[i].bendZ, 0.0f, 0.0f, 1.0f);
    }

    glPopMatrix();
}
// dibuja la palma
void filpPalm()
{
    glColor3f(0.95f, 0.8f, 0.65f);
    glBegin(GL_POINTS);

    float spacing = POINT_DENSITY * 2.0f;

    for (float y = -PALM_HEIGHTT / 2; y <= PALM_HEIGHTT / 2; y += spacing)
    {
        for (float x = -PALM_WIDTHH / 2; x <= PALM_WIDTHH / 2; x += spacing)
        {
            float z1 = -PALM_DEPTH / 2;
            float z2 = PALM_DEPTH / 2;

            int steps = (int)((z2 - z1) / spacing);
            float dz = (z2 - z1) / steps;

            float px = x;
            float py = y;
            float pz = z1;

            //  para textura
            float u = (x + PALM_WIDTHH / 2) / PALM_WIDTHH;
            float v = (y + PALM_HEIGHTT / 2) / PALM_HEIGHTT;

            for (int i = 0; i <= steps; i++)
            {
                // forma y grosorpalma
                float shape = 1.2f - (x * x / (PALM_WIDTHH * PALM_WIDTHH / 4) +
                                      pow((y - 0.3f) / PALM_HEIGHTT, 2) * 1.5f);

                float thickness = 1.0f - (pz * pz / (PALM_DEPTH * PALM_DEPTH / 4));

                if (shape * thickness > 0.3f)
                {
                    float palmLine = 0.5f + 0.5f * sin(u * PI * 3.0f);

                    // Color con variaciones
                    float r = 0.95f - 0.1f * fabs(py / PALM_HEIGHTT);
                    float g = 0.8f - 0.15f * fabs(px / PALM_WIDTHH);
                    float b = 0.65f - 0.1f * (1.0f - thickness);
                    glColor3f(r, g, b);
                    glVertex3f(px, py, pz);
                }
                pz += dz;
            }
        }
    }
    glEnd();
}
// ******* letra de cada mano, para la pose de cada segmento de dedo, dependiendo de la letra que sea
void applyPunchPose_i()
{
    poseFinger_Folded(1);
    poseFinger_Folded(2);
    poseFinger_Folded(3);
    poseFinger4_Folded();
}

void applyPunchPose()
{
    poseFinger_Folded(0);
    poseFinger_Folded(1);
    poseFinger4_Folded();
}
// mano
void drawHand(void (*poseFunc)())
{
    filpPalm();
    if (poseFunc != NULL)
        poseFunc();
    for (int i = 0; i < 5; i++)
        drawArticulatedFinger(i);
}

/// *************** DIBUJA LAS 4 LETRAS ********* //////
void drawLetterI()
{
    initializeFingersGeneric(i_finger0, NULL);
    drawHand(applyPunchPose_i);
}

void drawLetterR()
{
    initializeFingersGeneric(menique_Finger0, configR);
    drawHand(applyPunchPose);
}

void drawLetterU()
{
    initializeFingersGeneric(menique_Finger0, NULL);
    drawHand(applyPunchPose);
}

void drawLetterV()
{
    initializeFingersGeneric(menique_Finger0, configV);
    drawHand(applyPunchPose);
}