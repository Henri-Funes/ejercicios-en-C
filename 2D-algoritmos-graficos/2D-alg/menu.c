#include <GL/glut.h>
#include "header.h"
#include <stdio.h>

// ==================== FUNCIÓN PARA DIBUJAR TEXTO EN PANTALLA ====================
// Muestra una cadena de texto en una posición (x, y) usando fuente bitmap.
void drawText(float x, float y, const char *text)
{
    glRasterPos2f(x, y); // Establece posición de inicio para el texto
    for (int i = 0; text[i] != '\0'; i++)
    {
        // Dibuja cada carácter con la fuente Helvetica de 18 puntos
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

// ==================== MENÚ PRINCIPAL ====================
void drawMenu()
{
    // Fondo del menú (color azul oscuro)
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Marco decorativo del menú
    glColor3f(0.8f, 0.8f, 0.9f);  // Color claro
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(150, 200);
        glVertex2f(650, 200);
        glVertex2f(650, 500);
        glVertex2f(150, 500);
    glEnd();
    glLineWidth(1.0f); // Restaurar grosor de línea

    // Título del juego
    glColor3f(1.0f, 0.9f, 0.7f); // Color crema
    drawText(220, 460, "JUEGO DE VEHICULOS 2D");

    // Subtítulo
    glColor3f(0.9f, 0.9f, 1.0f); // Blanco azulado
    drawText(250, 430, "SELECCIONA TU VEHICULO");

    // Opciones del menú
    drawText(200, 380, "1. Moto de Delivery");
    drawText(200, 350, "2. Kia Soul (Carro)");
    drawText(200, 320, "3. Microbus Coaster");
    drawText(200, 290, "4. Bus Urbano");

    // Opción para salir (en color diferente para destacarla)
    glColor3f(1.0f, 0.7f, 0.7f); // Rojo suave
    drawText(200, 250, "5. Salir del juego");

    // Instrucciones para el usuario
    glColor3f(0.8f, 0.8f, 0.8f);
    drawText(220, 210, "Presiona 1, 2, 3, 4 o 5");
}

// ==================== DIBUJAR ESCENA DEL JUEGO ====================
void drawGame()
{
    // No se limpia aquí porque ya se limpia en display()

    // Dibuja la carretera y todo el paisaje de fondo
    drawRoad();

    // Tampoco se hace glutSwapBuffers aquí — se hace en display()
}

// ==================== INFORMACIÓN EN PANTALLA DURANTE EL JUEGO ====================
void drawGameInfo()
{
    Vehicle *playerVehicle = getVehicle(0); // Obtiene el vehículo del jugador

    if (playerVehicle != NULL)
    {
        // Muestra información del vehículo: velocidad, carril y posición
        glColor3f(1.0f, 1.0f, 1.0f); // Texto blanco
        char info[100];

        sprintf(info, "Velocidad: %.1f", playerVehicle->speed);
        drawText(10, 580, info);

        sprintf(info, "Carril: %d", playerVehicle->currentLane + 1);
        drawText(10, 560, info);

        sprintf(info, "Pos: (%.0f, %.0f)", playerVehicle->x, playerVehicle->y);
        drawText(10, 540, info);

        // Controles en pantalla
        glColor3f(0.8f, 0.8f, 0.8f); // Gris claro
        drawText(10, 50, "WASD o Flechas: Mover");
        drawText(10, 30, "M: Menu  R: Reiniciar");
        drawText(10, 10, "P: Pausa");
        drawText(90, 10, "ESPACIO: Saltar");
    }
}
