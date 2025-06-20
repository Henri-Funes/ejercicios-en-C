#ifndef DGHY_H
#define DGHY_H

#include <GL/glut.h>
#include <math.h>

// Constantes generales
#ifndef PI
#define PI 3.14159265358979323846
#endif
#define DENSIDAD_PUNTOS 0.005f
#define FACTOR_ESCALA 0.25f

#define ANCHO_PALMA 4.0f
#define ALTO_PALMA 2.7f
#define PROFUNDIDAD_PALMA 0.5f

// Estructura para segmentos de dedos
typedef struct
{
    float x, y, z;
} Punto3D;

// Funciones principales
void drawPalma();
void drawLetterD();
void drawLetterG();
void drawLetterH();
void drawLetterY();
void drawLine3D(Punto3D p1, Punto3D p2);


#endif
