#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

extern void displaysombrilla(void);
extern void displaytriangulos(void);
extern void displaysusuwatari(void);

int mode = 1;
int numTriangles = 0;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    switch (mode)
    {
    case 1:
        displaysombrilla();
        break;
    case 2:
        displaytriangulos();
        break;
    case 3:
        displaysusuwatari();
        break;
    default:
        break;
    }
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == '1')
        mode = 1;
    else if (key == '2')
        mode = 2;
    else if (key == '3')
        mode = 3;
    glutPostRedisplay();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 700, 0, 700);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Uso: %s <numTriangulos>\n", argv[0]);
        return 1;
    }
    numTriangles = atoi(argv[1]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Examen");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}