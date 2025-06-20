#include "BFLS.h"
#include <GL/glut.h>
#include <math.h>

BFLS_Finger bfls_fingers[5];

void bfls_scaleFingers(float scale)
{
    for (int i = 0; i < 5; i++)
    {
        bfls_fingers[i].baseX *= scale;
        bfls_fingers[i].baseY *= scale;
        bfls_fingers[i].baseZ *= scale;
        for (int j = 0; j < bfls_fingers[i].numSegments; j++)
        {
            bfls_fingers[i].segments[j].length *= scale;
            bfls_fingers[i].segments[j].baseRadius *= scale;
            bfls_fingers[i].segments[j].tipRadius *= scale;
        }
    }
}

void bfls_configureFinger(int index, int numSegments, float baseX, float baseY, float baseZ, BFLS_FingerSegment segments[])
{
    bfls_fingers[index].numSegments = numSegments;
    bfls_fingers[index].baseX = baseX;
    bfls_fingers[index].baseY = baseY;
    bfls_fingers[index].baseZ = baseZ;
    bfls_fingers[index].globalBendX = 0.0f;
    bfls_fingers[index].globalBendY = 0.0f;
    bfls_fingers[index].globalBendZ = 0.0f;

    for (int i = 0; i < numSegments; i++)
    {
        bfls_fingers[index].segments[i] = segments[i];
    }
}

void bfls_poseFinger_Folded(int index)
{
    bfls_fingers[index].segments[0].bendX = 90.0f;
    bfls_fingers[index].segments[1].bendX = 90.0f;
}

void bfls_poseFinger4_Folded()
{
    bfls_fingers[4].segments[0].bendX = 90.0f;
    bfls_fingers[4].segments[1].bendZ = 90.0f;
}

void bfls_initializeFingersB()
{
    // Meñique
    BFLS_FingerSegment pinkySegments[4] = {
        {0.5f, 0.25f, 0.22f, 0, 0, 0, 0},
        {0.4f, 0.22f, 0.18f, 0, 0, 0, 0},
        {0.3f, 0.18f, 0.14f, 0, 0, 0, 0},
        {0.25f, 0.14f, 0.10f, 0, 0, 0, 0}
    };

    // Anular
    BFLS_FingerSegment ringSegments[4] = {
        {0.6f, 0.26f, 0.22f, 0, 0, 0, 0},
        {0.45f, 0.22f, 0.18f, 0, 0, 0, 0},
        {0.35f, 0.18f, 0.14f, 0, 0, 0, 0},
        {0.3f, 0.14f, 0.10f, 0, 0, 0, 0}
    };

    // Medio
    BFLS_FingerSegment middleSegments[4] = {
        {0.65f, 0.28f, 0.24f, 0, 0, 0, 0},
        {0.5f, 0.24f, 0.20f, 0, 0, 0, 0},
        {0.4f, 0.20f, 0.16f, 0, 0, 0, 0},
        {0.35f, 0.16f, 0.12f, 0, 0, 0, 0}
    };

    // Índice
    BFLS_FingerSegment indexSegments[4] = {
        {0.6f, 0.26f, 0.22f, 0, 0, 0, 0},
        {0.45f, 0.22f, 0.18f, 0, 0, 0, 0},
        {0.35f, 0.18f, 0.14f, 0, 0, 0, 0},
        {0.3f, 0.14f, 0.10f, 0, 0, 0, 0}
    };

    // Configuración de los dedos extendidos
    bfls_configureFinger(0, 4, 0.7f, 1.1f, 0.0f, pinkySegments);    // indice
    bfls_configureFinger(1, 4, 0.22f, 1.1f, 0.0f, ringSegments);   // medio
    bfls_configureFinger(2, 4, -0.25f, 1.1f, 0.0f, middleSegments);  // anular
    bfls_configureFinger(3, 4, -0.7f, 1.1f, 0.0f, indexSegments);   // meñique

    // Pulgar inclinado más hacia la palma
    BFLS_FingerSegment thumbSegments[3] = {
        {0.5f, 0.30f, 0.26f, 0, 0, 0, 0},
        {0.4f, 0.26f, 0.22f, 0, 0, 0, 0},
        {0.35f, 0.22f, 0.18f, 0, 0, 0, 0}
    };

    bfls_configureFinger(4, 3, -0.9f, 0.2f, 0.2f, thumbSegments);
    bfls_fingers[4].globalBendZ = -65.0f;

    bfls_scaleFingers(BFLS_SCALE_FACTOR);
}

void bfls_applyPoseB()
{
    for (int i = 0; i < 4; i++){
        /*bfls_poseFinger_Folded(i);*/
    /*bfls_poseFinger4_Folded();*/
    }
}

void bfls_initializeFingersF()
{
    // Meñique
    BFLS_FingerSegment pinkySegments[4] = {
        {0.5f, 0.25f, 0.22f, 0, 0, 0, 0},
        {0.4f, 0.22f, 0.18f, 0, 0, 0, 0},
        {0.3f, 0.18f, 0.14f, 0, 0, 0, 0},
        {0.25f, 0.14f, 0.10f, 0, 0, 0, 0}
    };

    // Anular
    BFLS_FingerSegment ringSegments[4] = {
        {0.6f, 0.26f, 0.22f, 0, 0, 0, 0},
        {0.45f, 0.22f, 0.18f, 0, 0, 0, 0},
        {0.35f, 0.18f, 0.14f, 0, 0, 0, 0},
        {0.3f, 0.14f, 0.10f, 0, 0, 0, 0}
    };

    // Medio
    BFLS_FingerSegment middleSegments[4] = {
        {0.65f, 0.28f, 0.24f, 0, 0, 0, 0},
        {0.5f, 0.24f, 0.20f, 0, 0, 0, 0},
        {0.4f, 0.20f, 0.16f, 0, 0, 0, 0},
        {0.35f, 0.16f, 0.12f, 0, 0, 0, 0}
    };

    // Índice
    BFLS_FingerSegment indexSegments[4] = {
        {0.6f, 0.26f, 0.22f, 0, 0, 0, 0},
        {0.45f, 0.22f, 0.18f, 0, 0, 0, 0},
        {0.35f, 0.18f, 0.14f, 0, 0, 0, 0},
        {0.3f, 0.14f, 0.10f, 0, 0, 0, 0}
    };

    // Configuración de los dedos extendidos
    bfls_configureFinger(0, 4, 0.7f, 1.1f, 0.0f, pinkySegments);    // indice
    bfls_configureFinger(1, 4, 0.22f, 1.1f, 0.0f, ringSegments);   // medio
    bfls_configureFinger(2, 4, -0.25f, 1.1f, 0.0f, middleSegments);  // anular
    bfls_configureFinger(3, 4, -0.7f, 1.1f, 0.0f, indexSegments);   // meñique

    // Pulgar inclinado más hacia la palma
    BFLS_FingerSegment thumbSegments[3] = {
        {0.5f, 0.30f, 0.26f, 0, 0, 0, 0},
        {0.4f, 0.26f, 0.22f, 0, 0, 0, 0},
        {0.35f, 0.22f, 0.18f, 0, 0, 0, 0}
    };

    bfls_configureFinger(4, 3, -0.9f, 0.2f, 0.2f, thumbSegments);
    bfls_fingers[4].globalBendZ = -65.0f;

    bfls_scaleFingers(BFLS_SCALE_FACTOR);
}

void bfls_applyPoseF()
{
    for (int i = 0; i < 4; i++)
        /*bfls_poseFinger_Folded(i);*/
        bfls_poseFinger_Folded(3);
    // Dejar el dedo índice extendido
    bfls_fingers[3].globalBendX = 90.0f;  // El índice está extendido

    bfls_poseFinger4_Folded();
}

void bfls_initializeFingersL()
{
    // Meñique
    BFLS_FingerSegment pinkySegments[4] = {
        {0.5f, 0.25f, 0.22f, 0, 0, 0, 0},
        {0.4f, 0.22f, 0.18f, 0, 0, 0, 0},
        {0.3f, 0.18f, 0.14f, 0, 0, 0, 0},
        {0.25f, 0.14f, 0.10f, 0, 0, 0, 0}
    };

    // Anular
    BFLS_FingerSegment ringSegments[4] = {
        {0.6f, 0.26f, 0.22f, 0, 0, 0, 0},
        {0.45f, 0.22f, 0.18f, 0, 0, 0, 0},
        {0.35f, 0.18f, 0.14f, 0, 0, 0, 0},
        {0.3f, 0.14f, 0.10f, 0, 0, 0, 0}
    };

    // Medio
    BFLS_FingerSegment middleSegments[4] = {
        {0.65f, 0.28f, 0.24f, 0, 0, 0, 0},
        {0.5f, 0.24f, 0.20f, 0, 0, 0, 0},
        {0.4f, 0.20f, 0.16f, 0, 0, 0, 0},
        {0.35f, 0.16f, 0.12f, 0, 0, 0, 0}
    };

    // Índice
    BFLS_FingerSegment indexSegments[4] = {
        {0.6f, 0.26f, 0.22f, 0, 0, 0, 0},
        {0.45f, 0.22f, 0.18f, 0, 0, 0, 0},
        {0.35f, 0.18f, 0.14f, 0, 0, 0, 0},
        {0.3f, 0.14f, 0.10f, 0, 0, 0, 0}
    };

    // Configuración de los dedos extendidos
    bfls_configureFinger(0, 4, 0.7f, 1.1f, 0.0f, pinkySegments);    // indice
    bfls_configureFinger(1, 4, 0.22f, 1.1f, 0.0f, ringSegments);   // medio
    bfls_configureFinger(2, 4, -0.25f, 1.1f, 0.0f, middleSegments);  // anular
    bfls_configureFinger(3, 4, -0.7f, 1.1f, 0.0f, indexSegments);   // meñique

    // Pulgar inclinado más hacia la palma
    BFLS_FingerSegment thumbSegments[3] = {
        {0.5f, 0.30f, 0.26f, 0, 0, 0, 0},
        {0.4f, 0.26f, 0.22f, 0, 0, 0, 0},
        {0.35f, 0.22f, 0.18f, 0, 0, 0, 0}
    };

    bfls_configureFinger(4, 3, -0.9f, 0.2f, 0.2f, thumbSegments);
    bfls_fingers[4].globalBendZ = 75.0f;

    bfls_scaleFingers(BFLS_SCALE_FACTOR);
}

void bfls_applyPoseL()
{
    for (int i = 0; i < 4; i++)
        bfls_poseFinger_Folded(0);
        bfls_poseFinger_Folded(1);
        bfls_poseFinger_Folded(2);
        
    // Dejar el dedo índice extendido
    //bfls_fingers[3].globalBendX = 90.0f;  // El índice está doblado

    /*bfls_poseFinger4_Folded();*/
}

void bfls_initializeFingersS()
{
    // Meñique
    BFLS_FingerSegment pinkySegments[4] = {
        {0.5f, 0.25f, 0.22f, 0, 0, 0, 0},
        {0.4f, 0.22f, 0.18f, 0, 0, 0, 0},
        {0.3f, 0.18f, 0.14f, 0, 0, 0, 0},
        {0.25f, 0.14f, 0.10f, 0, 0, 0, 0}
    };

    // Anular
    BFLS_FingerSegment ringSegments[4] = {
        {0.6f, 0.26f, 0.22f, 0, 0, 0, 0},
        {0.45f, 0.22f, 0.18f, 0, 0, 0, 0},
        {0.35f, 0.18f, 0.14f, 0, 0, 0, 0},
        {0.3f, 0.14f, 0.10f, 0, 0, 0, 0}
    };

    // Medio
    BFLS_FingerSegment middleSegments[4] = {
        {0.65f, 0.28f, 0.24f, 0, 0, 0, 0},
        {0.5f, 0.24f, 0.20f, 0, 0, 0, 0},
        {0.4f, 0.20f, 0.16f, 0, 0, 0, 0},
        {0.35f, 0.16f, 0.12f, 0, 0, 0, 0}
    };

    // Índice
    BFLS_FingerSegment indexSegments[4] = {
        {0.6f, 0.26f, 0.22f, 0, 0, 0, 0},
        {0.45f, 0.22f, 0.18f, 0, 0, 0, 0},
        {0.35f, 0.18f, 0.14f, 0, 0, 0, 0},
        {0.3f, 0.14f, 0.10f, 0, 0, 0, 0}
    };

    // Configuración de los dedos extendidos para la letra S
    bfls_configureFinger(0, 4, 0.7f, 1.1f, 0.0f, pinkySegments);    // indice
    bfls_configureFinger(1, 4, 0.22f, 1.1f, 0.0f, ringSegments);   // medio
    bfls_configureFinger(2, 4, -0.25f, 1.1f, 0.0f, middleSegments);  // anular
    bfls_configureFinger(3, 4, -0.7f, 1.1f, 0.0f, indexSegments);   // meñique

    // Pulgar extendido
    BFLS_FingerSegment thumbSegments[3] = {
        {0.5f, 0.30f, 0.26f, 0, 0, 0, 0},
        {0.4f, 0.26f, 0.22f, 0, 0, 0, 0},
        {0.35f, 0.22f, 0.18f, 0, 0, 0, 0}
    };
    bfls_configureFinger(4, 3, -0.9f, 0.2f, 0.2f, thumbSegments);  // Pulgar
    bfls_fingers[4].globalBendZ = -65.0f;  // Pulgar doblado hacia adentro

    bfls_scaleFingers(BFLS_SCALE_FACTOR);
}




void bfls_applyPoseS()
{
    // Aseguramos que todos los dedos de arriba estén doblados
    for (int i = 0; i < 4; i++) 
    {
        bfls_poseFinger_Folded(i); 
        bfls_fingers[i].globalBendX = 60.0f; // Doblar los dedos (meñique, anular, medio, índice)
    }

    // El pulgar sigue doblado hacia adentro como estaba
    bfls_fingers[4].globalBendZ = -65.0f;  // Pulgar doblado hacia adentro
    /*bfls_poseFinger4_Folded(); */ // Aplica la pose doblada para el pulgar
}



void bfls_drawStraightFingerSegment(float baseX, float baseY, float baseZ, BFLS_FingerSegment segment)
{
    glBegin(GL_POINTS);

    int radialSteps = 86;
    float angleStep = 2 * BFLS_PI / radialSteps;
    const float baseR = 0.88f, baseG = 0.60f, baseB = 0.40f;

    for (float y = 0; y <= segment.length; y += BFLS_POINT_DENSITY * 2.0f)
    {
        float t = y / segment.length;
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

            float finalR = segmentR * fmax(0.7f, lightFactor);
            float finalG = segmentG * fmax(0.7f, lightFactor);
            float finalB = segmentB * fmax(0.7f, lightFactor);

            glColor3f(finalR, finalG, finalB);
            glVertex3f(baseX + x, baseY + y, baseZ + z);

            for (float innerR = currentRadius * 0.7f; innerR > 0; innerR -= BFLS_POINT_DENSITY * 1.5f)
            {
                float innerFactor = 0.8f - 0.2f * (innerR / currentRadius);
                glColor3f(finalR * innerFactor, finalG * innerFactor, finalB * innerFactor);
                glVertex3f(baseX + innerR * cos(rad), baseY + y, baseZ + innerR * sin(rad));
            }
        }
    }
    glEnd();
}

void bfls_drawArticulatedFinger(int fingerIndex)
{
    BFLS_Finger *finger = &bfls_fingers[fingerIndex];

    glPushMatrix();
    glTranslatef(finger->baseX, finger->baseY, finger->baseZ);
    glRotatef(finger->globalBendX, 1.0f, 0.0f, 0.0f);
    glRotatef(finger->globalBendY, 0.0f, 1.0f, 0.0f);
    glRotatef(finger->globalBendZ, 0.0f, 0.0f, 1.0f);

    for (int i = 0; i < finger->numSegments; i++)
    {
        glPushMatrix();

        if (finger->segments[i].offsetz != 0.0f)
            glTranslatef(0.0f, 0.0f, finger->segments[i].offsetz);

        bfls_drawStraightFingerSegment(0.0f, 0.0f, 0.0f, finger->segments[i]);

        glPopMatrix();
        glTranslatef(0.0f, finger->segments[i].length, 0.0f);
        glRotatef(finger->segments[i].bendX, 1.0f, 0.0f, 0.0f);
        glRotatef(finger->segments[i].bendY, 0.0f, 1.0f, 0.0f);
        glRotatef(finger->segments[i].bendZ, 0.0f, 0.0f, 1.0f);
    }

    glPopMatrix();
}

// dibuja la palma para letra B con mayor detalle
void bfls_drawPalm()
{
    glColor3f(0.90f, 0.55f, 0.30f);

    glBegin(GL_POINTS);

    float spacing = BFLS_POINT_DENSITY * 2.0f;

    for (float y = -BFLS_PALM_HEIGHT / 2; y <= BFLS_PALM_HEIGHT / 2; y += spacing)
    {
        for (float x = -BFLS_PALM_WIDTH / 2; x <= BFLS_PALM_WIDTH / 2; x += spacing)
        {
            float z1 = -0.4f;
            float z2 = 0.4f;
            int steps = (int)((z2 - z1) / spacing);
            float dz = (z2 - z1) / steps;

            float px = x;
            float py = y;
            float pz = z1;

            float u = (x + BFLS_PALM_WIDTH / 2) / BFLS_PALM_WIDTH;
            float v = (y + BFLS_PALM_HEIGHT / 2) / BFLS_PALM_HEIGHT;

            for (int i = 0; i <= steps; i++)
            {
                float shape = 1.2f - (x * x / (BFLS_PALM_WIDTH * BFLS_PALM_WIDTH / 4) +
                                      pow((y - 0.3f) / BFLS_PALM_HEIGHT, 2) * 1.5f);

                float thickness = 1.0f - (pz * pz / (0.8f * 0.8f / 4));

                if (shape * thickness > 0.3f)
                {
                    glVertex3f(px, py, pz);
                }
                pz += dz;
            }
        }
    }
    glEnd();
}

void drawLetterB()
{
    bfls_initializeFingersB();
    bfls_drawPalm();
    bfls_applyPoseB();

    for (int i = 0; i < 5; i++)
        bfls_drawArticulatedFinger(i);
}


void drawLetterF()
{
    bfls_initializeFingersF();
    bfls_drawPalm();
    bfls_applyPoseF();

    for (int i = 0; i < 5; i++)
        bfls_drawArticulatedFinger(i);
}

void drawLetterL()
{
    bfls_initializeFingersL();
    bfls_drawPalm();
    bfls_applyPoseL();

    for (int i = 0; i < 5; i++)
        bfls_drawArticulatedFinger(i);
}

void drawLetterS()
{
    bfls_initializeFingersS();
    bfls_drawPalm();
    bfls_applyPoseS();

    for (int i = 0; i < 5; i++)
        bfls_drawArticulatedFinger(i);
}
