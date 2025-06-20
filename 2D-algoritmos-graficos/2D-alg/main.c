#include <GL/glut.h>
#include "header.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Variables para el estado del juego
int selectedVehicle = 0;
bool enMenu = true;
bool gameInitialized = false;
bool gamePaused = false;
bool gameOver = false;
int playerLives = MAX_LIVES;
bool isInvulnerable = false;
clock_t invulnerabilityTimer = 0;

// Variables para animaciones
float offset = 0.0f;
float pointOffset = 0.0f;
float landscapeOffset = 0.0f;
int frameCount = 0;

// Función para iniciar el juego
void initGame()
{
    if (!gameInitialized)
    {
        // Restablecer valores iniciales
        playerLives = MAX_LIVES;
        isInvulnerable = false;
        gameOver = false;

        srand(time(NULL)); // Activar aleatoriedad

        // Limpiar vehículos y obstáculos anteriores
        clearVehicles();
        clearObstacles();

        // Crear solo el vehículo que eligió el jugador
        switch (selectedVehicle)
        {
        case 1:
            initVehicle(0, 50, 250, 0);
            break;
        case 2:
            initVehicle(0, 50, 250, 1);
            break;
        case 3:
            initVehicle(0, 50, 300, 2);
            break;
        case 4:
            initVehicle(0, 50, 300, 3);
            break;
        default:
            initVehicle(0, 50, 250, 0);
            selectedVehicle = 1;
            break;
        }

        initObstacles(); // Preparar obstáculos
        gameInitialized = true;
        printf("Juego inicializado con vehiculo tipo %d en posicion izquierda (x=50)\n", selectedVehicle);
    }
}

// Mostrar mensaje de "Game Over"
void drawGameOverMessage()
{
    glEnable(GL_BLEND);
    glColor4f(0.3f, 0.0f, 0.0f, 0.7f);
    drawRect(0, 0, 800, 600);

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(350, 320);
    char gameOverText[] = "GAME OVER";
    for (int i = 0; gameOverText[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gameOverText[i]);

    glRasterPos2f(300, 280);
    char instructionText[] = "Presiona 'R' para reiniciar";
    for (int i = 0; instructionText[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, instructionText[i]);

    glDisable(GL_BLEND);
}

// Dibujar las vidas del jugador
void drawLives()
{
    float startX = 700;
    float y = 580;
    float spacing = 40;

    for (int i = 0; i < playerLives; i++)
        drawBitcoinLife(startX + i * spacing, y, 20);
}

// Función principal de dibujo
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (enMenu)
    {
        drawMenu(); // Mostrar menú
    }
    else
    {
        if (!gameInitialized)
            initGame(); // Preparar juego si no está listo

        drawGame();  // Fondo, pistas, decoraciones
        drawLives(); // Mostrar vidas

        // Solo actualizar si no está pausado ni en game over
        if (!gamePaused && !gameOver)
        {
            updateVehicles();
            updateObstacles();

            // Revisar colisiones solo si no está invulnerable
            if (!isInvulnerable)
            {
                Vehicle *playerVehicle = getVehicle(0);
                if (playerVehicle != NULL)
                {
                    float vehicleWidth, vehicleHeight;

                    switch (playerVehicle->vehicleType)
                    {
                    case 0:
                        vehicleWidth = 44;
                        vehicleHeight = 32;
                        break;
                    case 1:
                        vehicleWidth = 70;
                        vehicleHeight = 50;
                        break;
                    case 2:
                        vehicleWidth = 100;
                        vehicleHeight = 85;
                        break;
                    case 3:
                        vehicleWidth = 140;
                        vehicleHeight = 70;
                        break;
                    default:
                        vehicleWidth = 50;
                        vehicleHeight = 40;
                    }

                    // Detectar colisión
                    if (checkObstacleCollision(playerVehicle->x, playerVehicle->y, vehicleWidth, vehicleHeight))
                    {
                        playerLives--;
                        isInvulnerable = true;
                        invulnerabilityTimer = clock();
                        printf("¡Colisión! Vidas restantes: %d\n", playerLives);

                        if (playerLives <= 0)
                        {
                            gameOver = true;
                            gamePaused = true;
                            printf("GAME OVER\n");
                        }
                    }
                }
            }
        }

        // Verificar si se acabó el tiempo de invulnerabilidad
        if (isInvulnerable)
        {
            clock_t currentTime = clock();
            double elapsed = (double)(currentTime - invulnerabilityTimer) / CLOCKS_PER_SEC;
            if (elapsed >= 2.0)
            {
                isInvulnerable = false;
                printf("Fin de invulnerabilidad\n");
            }
        }

        renderVehicles();
        renderObstacles();
        drawGameInfo();

        // Dibujar burbuja de invulnerabilidad si está activa
        if (isInvulnerable && !enMenu && gameInitialized)
        {
            Vehicle *playerVehicle = getVehicle(0);
            if (playerVehicle != NULL)
            {
                float w, h;
                switch (playerVehicle->vehicleType)
                {
                case 0:
                    w = 44;
                    h = 32;
                    break;
                case 1:
                    w = 70;
                    h = 50;
                    break;
                case 2:
                    w = 100;
                    h = 85;
                    break;
                case 3:
                    w = 140;
                    h = 70;
                    break;
                default:
                    w = 50;
                    h = 40;
                }
                renderInvulnerabilityBubble(playerVehicle->x, playerVehicle->y, w, h);
            }
        }

        // Mostrar mensajes si el juego está pausado o terminó
        if (gamePaused)
        {
            if (gameOver)
                drawGameOverMessage();
            else
                drawPauseMessage();
        }
    }

    glutSwapBuffers();
}

// Cambiar tamaño de ventana
void reshape(int w, int h)
{
    printf("Ventana redimensionada a: %dx%d\n", w, h);
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / (float)h;
    if (aspect >= (800.0f / 600.0f))
    {
        float newWidth = 600.0f * aspect;
        gluOrtho2D(-(newWidth - 800.0f) / 2.0f, 800.0f + (newWidth - 800.0f) / 2.0f, 0, 600);
    }
    else
    {
        float newHeight = 800.0f / aspect;
        gluOrtho2D(0, 800, -(newHeight - 600.0f) / 2.0f, 600.0f + (newHeight - 600.0f) / 2.0f);
    }

    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

// Teclas comunes (como letras)
void keyHandler(unsigned char key, int x, int y)
{
    if (enMenu)
    {
        if (key >= '1' && key <= '4')
        {
            selectedVehicle = key - '0';
            enMenu = false;
            gameInitialized = false;
            printf("Vehiculo seleccionado: %d\n", selectedVehicle);
        }
        else if (key == '5')
        {
            printf("Saliendo del juego...\n");
            exit(0);
        }
    }
    else
    {
        if (key == 'm' || key == 'M')
        {
            enMenu = true;
            selectedVehicle = 0;
            gameInitialized = false;
            clearVehicles();
            printf("Volviendo al menu...\n");
        }
        else if (key == 'r' || key == 'R')
        {
            playerLives = MAX_LIVES;
            isInvulnerable = false;
            gamePaused = false;
            gameInitialized = false;
            gameOver = false;
            printf("Reiniciando juego...\n");
        }
        else if ((key == 'p' || key == 'P') && !gameOver)
        {
            gamePaused = !gamePaused;
            printf(gamePaused ? "Juego PAUSADO\n" : "Juego REANUDADO\n");
        }
        else if (key == ' ')
        {
            if (!gamePaused && getVehicleCount() > 0)
            {
                jumpVehicle(0);
                printf("¡Salto activado para vehiculo 0!\n");
            }
        }
        else
        {
            if (!gamePaused && !gameOver)
                controlVehicle(0, key);
        }
    }

    glutPostRedisplay();
}

// Teclas especiales como flechas
void specialKeyHandler(int key, int x, int y)
{
    if (!enMenu && getVehicleCount() > 0 && !gamePaused)
    {
        switch (key)
        {
        case GLUT_KEY_UP:
            moveVehicleUp(0);
            break;
        case GLUT_KEY_DOWN:
            moveVehicleDown(0);
            break;
        case GLUT_KEY_LEFT:
            moveVehicleLeft(0);
            break;
        case GLUT_KEY_RIGHT:
            moveVehicleRight(0);
            break;
        }
    }

    glutPostRedisplay();
}

// Función idle: redibuja constantemente
void idle()
{
    if (!enMenu)
        glutPostRedisplay();
}

// Temporizador para mantener el juego fluido (~60 FPS)
void timer(int value)
{
    if (!enMenu)
        glutPostRedisplay();

    glutTimerFunc(16, timer, 0);
}

// Dibujar mensaje de pausa
void drawPauseMessage()
{
    glEnable(GL_BLEND);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    drawRect(0, 0, 800, 600);

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(350, 320);
    char pauseText[] = "JUEGO PAUSADO";
    for (int i = 0; pauseText[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pauseText[i]);

    glRasterPos2f(300, 280);
    char instructionText[] = "Presiona 'P' para continuar";
    for (int i = 0; instructionText[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, instructionText[i]);

    glDisable(GL_BLEND);
}

// Punto de entrada del juego
int main(int argc, char **argv)
{
    printf("Iniciando juego de vehiculos 2D...\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Juego 2D");

    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Cielo azul
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyHandler);
    glutSpecialFunc(specialKeyHandler);
    glutIdleFunc(idle);
    glutTimerFunc(16, timer, 0);

    printf("Configuracion completada. Entrando al bucle principal...\n");
    printf("Controles en el menu: 1-4 para seleccionar vehiculo, 5 para salir\n");
    printf("Controles en el juego: WASD o flechas para mover, ESPACIO para saltar, P para pausar, M para menu, R para reiniciar\n");

    glutMainLoop();
    return 0;
}
