#include <GL/glut.h>
#include <stdbool.h>
#include "header.h"
#include <time.h>

// --- DEFINICIONES GENERALES DEL ENTORNO ---

#define ROAD_BOTTOM 200
#define ROAD_TOP 400
#define ROAD_CENTER 300
#define ROAD_WIDTH 800
#define LANE_HEIGHT 100

#define VEHICLE_SPEED 2.0f
#define LATERAL_SPEED 4.0f     // Desplazamiento lateral más rápido
#define LANE_CHANGE_SPEED 1.5f // Velocidad para cambiar de carril

// --- ESTADO GLOBAL DE LOS VEHÍCULOS ---

static Vehicle vehicles[10];
static int vehicleCount = 0;

// Variables para manejar el salto de cada vehículo
static bool vehicleJumping[10] = {false};
static clock_t jumpStartTime[10] = {0};
static float originalY[10] = {0.0f};

// --- INICIALIZACIÓN DE VEHÍCULOS ---

void initVehicle(int index, float x, float y, int type)
{
    if (index >= 0 && index < 10)
    {
        vehicles[index] = (Vehicle){x, y, y, type, false, VEHICLE_SPEED};

        vehicles[index].currentLane = (y < ROAD_CENTER) ? 0 : 1;

        // Reset de las variables de salto
        vehicleJumping[index] = false;
        jumpStartTime[index] = 0;
        originalY[index] = y;

        if (index >= vehicleCount)
            vehicleCount = index + 1;
    }
}

// --- FUNCIONES DE UTILIDAD ---

bool isWithinRoadBounds(float x, float y)
{
    return (x >= 0 && x <= ROAD_WIDTH &&
            y >= ROAD_BOTTOM + 20 && y <= ROAD_TOP - 20);
}

float getLaneCenterY(int lane)
{
    return (lane == 0)
               ? ROAD_BOTTOM + LANE_HEIGHT / 2
               : ROAD_CENTER + LANE_HEIGHT / 2;
}

// Detecta colisiones simples entre vehículos
bool checkCollision(int vehicleIndex, float newX, float newY)
{
    for (int i = 0; i < vehicleCount; i++)
    {
        if (i == vehicleIndex)
            continue;

        float dx = newX - vehicles[i].x;
        float dy = newY - vehicles[i].y;
        float distance = sqrtf(dx * dx + dy * dy);

        float minDistance = 60.0f;
        if (vehicles[i].vehicleType == 3 || vehicles[vehicleIndex].vehicleType == 3)
            minDistance = 80.0f;

        if (distance < minDistance)
            return true;
    }
    return false;
}

// --- MOVIMIENTO HORIZONTAL ---

void moveVehicleLeft(int index)
{
    if (index < 0 || index >= vehicleCount)
        return;

    float newX = vehicles[index].x - LATERAL_SPEED;
    if (newX >= 0 && !checkCollision(index, newX, vehicles[index].y))
        vehicles[index].x = newX;
}

void moveVehicleRight(int index)
{
    if (index < 0 || index >= vehicleCount)
        return;

    float vehicleWidth = 80;
    switch (vehicles[index].vehicleType)
    {
    case 0:
        vehicleWidth = 50;
        break; // Moto
    case 1:
        vehicleWidth = 80;
        break; // Carro
    case 2:
        vehicleWidth = 100;
        break; // Microbus
    case 3:
        vehicleWidth = 140;
        break; // Bus
    }

    float newX = vehicles[index].x + LATERAL_SPEED;
    if (newX + vehicleWidth <= ROAD_WIDTH &&
        !checkCollision(index, newX, vehicles[index].y))
    {
        vehicles[index].x = newX;
    }
}

// --- CAMBIO DE CARRIL (ARRIBA / ABAJO) ---

void changeVehicleLane(int index)
{
    if (index < 0 || index >= vehicleCount || vehicles[index].isChangingLane)
        return;

    int newLane = (vehicles[index].currentLane == 0) ? 1 : 0;
    float newTargetY = getLaneCenterY(newLane);

    if (!checkCollision(index, vehicles[index].x, newTargetY))
    {
        vehicles[index].targetY = newTargetY;
        vehicles[index].currentLane = newLane;
        vehicles[index].isChangingLane = true;
    }
}

void moveVehicleUp(int index)
{
    if (index >= 0 && index < vehicleCount && vehicles[index].currentLane == 0)
        changeVehicleLane(index);
}

void moveVehicleDown(int index)
{
    if (index >= 0 && index < vehicleCount && vehicles[index].currentLane == 1)
        changeVehicleLane(index);
}

// --- SALTO DE VEHÍCULO ---

void jumpVehicle(int index)
{
    if (index >= 0 && index < vehicleCount && !vehicleJumping[index])
    {
        vehicleJumping[index] = true;
        jumpStartTime[index] = clock();
        originalY[index] = vehicles[index].y;

        printf("Vehículo %d inició salto desde Y=%.2f\n", index, originalY[index]);
    }
}

// --- ACTUALIZACIÓN GENERAL DE VEHÍCULOS ---

void updateVehicles()
{
    clock_t currentTime = clock();

    for (int i = 0; i < vehicleCount; i++)
    {
        // Lógica de salto
        if (vehicleJumping[i])
        {
            double elapsed = (double)(currentTime - jumpStartTime[i]) / CLOCKS_PER_SEC;

            if (elapsed >= 0.3)
            {
                vehicleJumping[i] = false;
                vehicles[i].y = originalY[i];
                printf("Vehículo %d finalizó salto. Y=%.2f\n", i, vehicles[i].y);
            }
            else
            {
                float t = (float)(elapsed / 0.3f);
                float jumpOffset = 100.0f * (4.0f * t * (1.0f - t));
                vehicles[i].y = originalY[i] + jumpOffset;

                static int debugCounter = 0;
                if (debugCounter++ % 10 == 0)
                    printf("Vehículo %d en salto: t=%.2f, Y=%.2f\n", i, t, vehicles[i].y);
            }
        }

        // Lógica de cambio de carril
        if (vehicles[i].isChangingLane)
        {
            float dy = vehicles[i].targetY - vehicles[i].y;

            if (fabsf(dy) > LANE_CHANGE_SPEED)
            {
                float delta = (dy > 0) ? LANE_CHANGE_SPEED : -LANE_CHANGE_SPEED;
                vehicles[i].y += delta;
                if (!vehicleJumping[i])
                    originalY[i] += delta;
            }
            else
            {
                vehicles[i].y = vehicles[i].targetY;
                vehicles[i].isChangingLane = false;
                if (!vehicleJumping[i])
                    originalY[i] = vehicles[i].targetY;
            }
        }
        else if (!vehicleJumping[i])
        {
            originalY[i] = vehicles[i].y;
        }
    }
}

// --- RENDERIZACIÓN ---

void renderVehicles()
{
    for (int i = 0; i < vehicleCount; i++)
    {
        int x = (int)vehicles[i].x;
        int y = (int)vehicles[i].y;

        switch (vehicles[i].vehicleType)
        {
        case 0:
            drawDelivery(x, y);
            break;
        case 1:
            drawCar(x, y);
            break;
        case 2:
            drawCoaster(x, y);
            break;
        case 3:
            drawBus(x, y);
            break;
        }
    }
}

// --- CONTROL DESDE TECLADO ---

void controlVehicle(int index, unsigned char key)
{
    if (index < 0 || index >= vehicleCount)
        return;

    switch (key)
    {
    case 'w':
    case 'W':
        moveVehicleUp(index);
        break;
    case 's':
    case 'S':
        moveVehicleDown(index);
        break;
    case 'a':
    case 'A':
        moveVehicleLeft(index);
        break;
    case 'd':
    case 'D':
        moveVehicleRight(index);
        break;
    }
}

// --- FUNCIONES DE ACCESO Y UTILIDAD ---

Vehicle *getVehicle(int index)
{
    return (index >= 0 && index < vehicleCount) ? &vehicles[index] : NULL;
}

int getVehicleCount()
{
    return vehicleCount;
}

void clearVehicles()
{
    vehicleCount = 0;
    for (int i = 0; i < 10; i++)
    {
        vehicleJumping[i] = false;
        jumpStartTime[i] = 0;
        originalY[i] = 0.0f;
    }
}

// Alias para compatibilidad con controles previos
void moveVehicleForward(int index) { moveVehicleLeft(index); }
void moveVehicleBackward(int index) { moveVehicleRight(index); }
