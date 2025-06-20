#ifndef BFLS_H
#define BFLS_H

#include <GL/glut.h>
#include <math.h>

#define BFLS_PI 3.14159265f
#define BFLS_POINT_DENSITY 0.015f
#define BFLS_MAX_SEGMENTS 6
#define BFLS_SCALE_FACTOR 1.6f

#define BFLS_PALM_WIDTH (2.4f * BFLS_SCALE_FACTOR)
#define BFLS_PALM_HEIGHT (2.3f * BFLS_SCALE_FACTOR)
#define BFLS_PALM_DEPTH (0.8f * BFLS_SCALE_FACTOR)

// Segmento del dedo
typedef struct {
    float length;
    float baseRadius;
    float tipRadius;
    float bendX, bendY, bendZ;
    float offsetz;
} BFLS_FingerSegment;

// Dedo completo
typedef struct {
    int numSegments;
    BFLS_FingerSegment segments[BFLS_MAX_SEGMENTS];
    float baseX, baseY, baseZ;
    float globalBendX, globalBendY, globalBendZ;
} BFLS_Finger;

extern BFLS_Finger bfls_fingers[5];

// Configuración de dedos
void bfls_configureFinger(int index, int numSegments, float baseX, float baseY, float baseZ, BFLS_FingerSegment segments[]);
void bfls_scaleFingers(float scale);

// Inicialización de dedos para la letra B (extendidos)
void bfls_initializeFingersB();

// Inicialización de dedos para la letra F (extendidos, sin doblar)
void bfls_initializeFingersF();

// Inicialización de dedos para la letra L (extendidos, sin doblar)
void bfls_initializeFingersL();

// Inicialización de dedos para la letra S (extendidos, sin doblar)
void bfls_initializeFingersS();

// Funciones para doblar los dedos
void bfls_poseFinger_Folded(int index);
void bfls_poseFinger4_Folded();

// Funciones de dibujo para dedos y palma
void bfls_drawStraightSegment(float baseX, float baseY, float baseZ, BFLS_FingerSegment segment);
void bfls_drawFinger(int fingerIndex);
void bfls_drawPalm();
void bfls_drawHand(void (*poseFunc)());

// Funciones para dibujar las letras específicas
void drawLetterB();
void drawLetterF();
void drawLetterL();
void drawLetterS();

#endif
