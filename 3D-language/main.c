#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "AEWK.h"
#include "IRUV.h"
#include "DGHY.h"
#include "BFLS.h"
// Variables globales
float rotateX = 0.0f;
float rotateY = 0.0f;
float rotateZ = 0.0f;
char currentLetter = 'A';

void init()
{
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glPointSize(8.0f);

    // Configuración de la proyección
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Posicionar la cámara
    glTranslatef(0.0f, 0.0f, -15.0f);

    // Aplicar rotaciones
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotateZ, 0.0f, 0.0f, 1.0f);

    // Dibujar la letra actual
    switch (currentLetter)
    {
    case 'A':
    case 'a':
        drawLetterA();
        break;
    case 'E':
    case 'e':
        drawLetterE();
        break;
    case 'W':
    case 'w':
        drawLetterW();
        break;
    case 'K':
    case 'k':
        drawLetterK();
        break;
    case 'I':
    case 'i':
        drawLetterI();
        break;
    case 'R':
    case 'r':
        drawLetterR();
        break;
    case 'U':
    case 'u':
        drawLetterU();
        break;
    case 'V':
    case 'v':
        drawLetterV();
        break;
    case 'D':
    case 'd':
        drawLetterD();
        break;
    case 'G':
    case 'g':
        drawLetterG();
        break;
    case 'H':
    case 'h':
        drawLetterH();
        break;
    case 'Y':
    case 'y':
        drawLetterY();
        break;
    case 'B':
    case 'b':
        drawLetterB();
        break;
    case 'F':
    case 'f':
        drawLetterF();
        break;
    case 'L':
    case 'l':
        drawLetterL();
        break;
    case 'S':
    case 's':
        drawLetterS();
        break;
    default:
        break;
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'A':
    case 'a':
        currentLetter = 'A';
        printf("Mostrando letra A\n");
        break;
    case 'E':
    case 'e':
        currentLetter = 'E';
        printf("Mostrando letra E\n");
        break;
    case 'W':
    case 'w':
        currentLetter = 'W';
        printf("Mostrando letra W\n");
        break;
    case 'K':
    case 'k':
        currentLetter = 'K';
        printf("Mostrando letra K\n ");
        break;
    case 'I':
    case 'i':
        currentLetter = 'I';
        printf("Mostrando letra: I\n");
        break;
    case 'R':
    case 'r':
        currentLetter = 'R';
        printf("Mostrando letra: R\n");
        break;
    case 'V':
    case 'v':
        currentLetter = 'V';
        printf("Mostrando letra: V\n");
        break;
    case 'U':
    case 'u':
        currentLetter = 'U';
        printf("Mostrando letra: U\n");
        break;
    case 'D':
    case 'd':
        currentLetter = 'D';
        printf("Mostrando letra: D\n");
        break;
    case 'G':
    case 'g':
        currentLetter = 'G';
        printf("Mostrando letra: G\n");
        break;
    case 'H':
    case 'h':
        currentLetter = 'H';
        printf("Mostrando letra: H\n");
        break;
    case 'Y':
    case 'y':
        currentLetter = 'Y';
        printf("Mostrando letra: Y\n");
        break;
    case 'B':
    case 'b':
        currentLetter = 'B';
        printf("Mostrando letra: B\n");
        break;
    case 'F':
    case 'f':
        currentLetter = 'F';
        printf("Mostrando letra: F\n");
        break;
    case 'L':
    case 'l':
        currentLetter = 'L';
        printf("Mostrando letra: L\n");
        break;
    case 'S':
    case 's':
        currentLetter = 'S';
        printf("Mostrando letra: S\n");
        break;
    case 27: // ESC
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y)
{
    float rotationStep = 5.0f;

    switch (key)
    {
    case GLUT_KEY_UP:
        rotateX -= rotationStep;
        break;
    case GLUT_KEY_DOWN:
        rotateX += rotationStep;
        break;
    case GLUT_KEY_LEFT:
        rotateY -= rotationStep;
        break;
    case GLUT_KEY_RIGHT:
        rotateY += rotationStep;
        break;
    }

    // Mantener los ángulos en rango 0-360
    if (rotateX > 360)
        rotateX -= 360;
    if (rotateX < 0)
        rotateX += 360;
    if (rotateY > 360)
        rotateY -= 360;
    if (rotateY < 0)
        rotateY += 360;

    glutPostRedisplay();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (height == 0)
        height = 1;
    float aspect = (float)width / (float)height;

    gluPerspective(45.0f, aspect, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

void idle()
{
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(720, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Abecedario Manual 3D");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutIdleFunc(idle);

    printf("=== Lenguaje de Señas 3D ===\n");
    printf("Controles:\n");
    printf("A - Mostrar letra A\n");
    printf("B - Mostrar letra B\n");
    printf("D - Mostrar letra D\n");
    printf("E - Mostrar letra E\n");
    printf("F - Mostrar letra F\n");
    printf("G - Mostrar letra G\n");
    printf("H - Mostrar letra H\n");
    printf("I - Mostrar letra I\n");
    printf("K - Mostrar letra K\n");
    printf("L - Mostrar letra L\n");
    printf("R - Mostrar letra R\n");
    printf("S - Mostrar letra S\n");
    printf("U - Mostrar letra U\n");
    printf("V - Mostrar letra V\n");
    printf("W - Mostrar letra W\n");
    printf("Y - Mostrar letra Y\n");
    printf("Flechas - Rotar la mano\n");
    printf("ESC - Salir\n");
    printf("========================\n");

    glutMainLoop();

    return 0;
}