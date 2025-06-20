#ifndef SIGNLANGUAGE_H
#define SIGNLANGUAGE_H

#include <GL/glut.h>
#include <math.h>

// PI
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Constantes para el tamaño de la mano
#define PALM_WIDTH 4.0f
#define PALM_HEIGHT 5.0f
#define FINGER_LENGTH 3.0f
#define THUMB_LENGTH 2.5f
#define JOINT_SIZE 0.3f

// Colores
#define SKIN_R 0.9f
#define SKIN_G 0.7f
#define SKIN_B 0.6f
#define JOINT_R 0.8f
#define JOINT_G 0.6f
#define JOINT_B 0.5f

// Estructura para representar un punto 3D
typedef struct
{
    float x, y, z;
} Point3D;

// Funciones para dibujar componentes básicos de la mano
void drawPoint(float x, float y, float z);
void drawPointWithColor(float x, float y, float z, float r, float g, float b);
void drawLine(Point3D start, Point3D end, int segments);

// Funciones reutilizables (actualizadas)
void drawPalm(float palmSquareBottom, float palmSquareTop, float blue_r, float blue_g, float blue_b);
void drawFinger(float fingerX, float maxHeight, float palmSquareTop,
                float finger_blue_r, float finger_blue_g, float finger_blue_b);
void drawStraightFinger(float fingerX, float maxHeight, float palmSquareTop,
                        float finger_blue_r, float finger_blue_g, float finger_blue_b);
void drawCommonThumb(float posX, float posY, float posZ,
                     float rotX, float rotY, float rotZ,
                     float thumb_brown_r, float thumb_brown_g, float thumb_brown_b,
                     float nail_white_r, float nail_white_g, float nail_white_b,
                     float connectionOffsetX, float connectionOffsetY, float connectionOffsetZ,
                     float connectionCurveX, float connectionCurveY, float connectionCurveZ,
                     int isStraight);

// Funciones para dibujar las letras específicas
void drawLetterA();
void drawLetterE();
void drawLetterW();
void drawLetterK();

#endif