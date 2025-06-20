#ifndef HEADER_H
#define HEADER_H

// Librerías estándar necesarias para operaciones matemáticas, entrada/salida y control de tiempo
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definición de PI en caso de que no esté definida por la librería math.h
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ===================== FUNCIONES DE DIBUJO BÁSICO =====================

// Algoritmo clásico para dibujar líneas con puntos
void drawLineBresenham(int x0, int y0, int x1, int y1);

// ===================== VARIABLES GLOBALES DEL JUEGO =====================

// Control general del desplazamiento del fondo y puntos de carretera
extern float offset;
extern float pointOffset;
extern float landscapeOffset;

// Contador de cuadros renderizados (útil para animaciones o spawns)
extern int frameCount;

// Vehículo seleccionado por el jugador
extern int selectedVehicle;

// Estados del juego
extern bool enMenu;     // Indica si estamos en el menú principal
extern bool gamePaused; // Indica si el juego está en pausa
extern bool gameOver;   // Indica si el jugador ha perdido
extern int playerLives; // Vidas restantes del jugador

// Variables para invulnerabilidad tras colisión
extern bool isInvulnerable;
extern clock_t invulnerabilityTimer;

// ===================== ESTRUCTURAS PRINCIPALES =====================

// Información y estado de cada vehículo en el juego
typedef struct
{
    float x, y;
    float targetY;
    int vehicleType;
    bool isChangingLane;
    int currentLane;
    float speed;
    bool isJumping;
    float jumpHeight;
    float jumpSpeed;
} Vehicle;

// Información de cada obstáculo que aparece en el camino
typedef struct
{
    float x, y;
    int size;
    int type;
    int lane;
    bool active;
} Obstacle;

// ===================== FUNCIONES DEL MENÚ Y JUEGO =====================

void drawMenu();                                   // Dibuja la pantalla del menú principal
void drawGame();                                   // Dibuja todo lo necesario para una partida activa
void drawText(float x, float y, const char *text); // Dibuja texto en pantalla
void drawGameInfo();                               // Muestra vidas, puntuación, etc.
void drawPauseMessage();                           // Muestra mensaje cuando el juego está pausado

// ===================== FUNCIONES DE LA CARRETERA =====================

void drawRoad();
void drawRoadPoints();
void drawLaneLines(float y); // Dibuja líneas divisorias de carril
void drawSign();             // Señal decorativa

// ===================== FUNCIONES DEL PAISAJE =====================

void drawForest();   // Dibuja árboles del fondo
void drawMountain(); // Dibuja montañas al fondo

// ===================== PRIMITIVAS DE DIBUJO OPTIMIZADAS =====================

void drawTriangleStrip(float *vertices, int count);
void drawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void drawFilledCircle(float cx, float cy, float radius, int segments);
void drawFilledEllipse(float cx, float cy, float radiusX, float radiusY, int segments);
void drawThickLine(int x0, int y0, int x1, int y1, int thickness);
void drawFilledPolygon(float *vertices, int vertexCount);

// ===================== DIBUJO DE VEHÍCULOS =====================

void drawBus(int x, int y);
void drawCar(int x, int y);
void drawDelivery(int x, int y);
void drawCoaster(int x, int y);

// ===================== FUNCIONES AUXILIARES DE DIBUJO =====================

void drawCircle(float cx, float cy, float r, int segments);
void drawRect(float x1, float y1, float x2, float y2);
void drawRectOutline(float x1, float y1, float x2, float y2);
void drawWheel(float x, float y, float radius, float innerRadius);
void drawWindows(float startX, float y, float width, float height, int count, float spacing, float r, float g, float b);
void drawWindowsOutline(float startX, float y, float width, float height, int count, float spacing);
void drawLight(float x, float y, float width, float height, float r, float g, float b);
void drawHorizontalLines(float x, float y, float width, int count, float spacing);

// ===================== MOVIMIENTO DE VEHÍCULOS =====================

void initVehicle(int index, float x, float y, int type);
void clearVehicles();
void moveVehicleForward(int index);
void moveVehicleBackward(int index);
void moveVehicleLeft(int index);
void moveVehicleRight(int index);
void moveVehicleUp(int index);
void moveVehicleDown(int index);
void jumpVehicle(int index);
void controlVehicle(int index, unsigned char key);
void changeVehicleLane(int index);
void updateVehicles();
void renderVehicles();
bool isWithinRoadBounds(float x, float y);
bool checkCollision(int index, float newX, float newY);
float getLaneCenterY(int lane);
Vehicle *getVehicle(int index);
int getVehicleCount();

// ===================== MANEJO DE OBSTÁCULOS =====================

void initObstacles();
void clearObstacles();
void spawnObstacle(float x, int lane, int type);
void updateObstacles();
void renderObstacles();
void drawRockType1(float x, float y, float size);
void drawRockType2(float x, float y, float size);
void drawRockType3(float x, float y, float size);
void drawBitcoinLife(float x, float y, float size); // Vida con forma de bitcoin
bool checkObstacleCollision(float vehicleX, float vehicleY, float vehicleWidth, float vehicleHeight);
void renderInvulnerabilityBubble(float vehicleX, float vehicleY, float vehicleWidth, float vehicleHeight);
int getActiveObstacleCount();
Obstacle *getObstacle(int index);
void setObstacleDifficulty(int difficulty);

// ===================== CONSTANTES DEL JUEGO =====================

// Posiciones y dimensiones de la carretera
#define ROAD_BOTTOM 200
#define ROAD_TOP 400
#define ROAD_CENTER 300
#define ROAD_WIDTH 800
#define LANE_HEIGHT 100

// Velocidad estándar de los vehículos
#define VEHICLE_SPEED 2.0f
#define LANE_CHANGE_SPEED 1.5f

// Posiciones de aparición de vehículos
#define SPAWN_LEFT_X 50
#define SPAWN_RIGHT_X 700

// Coordenadas centrales para carriles (deben coincidir con renderizado)
#define LANE_0_CENTER_Y 250
#define LANE_1_CENTER_Y 350
#define LANE_BOUNDARY_Y 300

// Parámetros de generación y comportamiento de obstáculos
#define MAX_OBSTACLES 50
#define OBSTACLE_SPEED 2.0f
#define MIN_SPAWN_INTERVAL 25
#define OBSTACLE_SPAWN_CHANCE 35
#define DUAL_SPAWN_CHANCE 25
#define TRIPLE_SPAWN_CHANCE 15
#define MIN_OBSTACLE_DISTANCE 80
#define OBSTACLE_COLLISION_MARGIN 10

// Sistema de vidas e invulnerabilidad
#define MAX_LIVES 3
#define INVULNERABILITY_TIME 2.0f

// Parámetros del sistema de salto
#define JUMP_HEIGHT 50.0f
#define JUMP_SPEED 8.0f
#define GRAVITY 0.5f

// Configuraciones avanzadas de dificultad
#define BURST_SPAWN_CHANCE 10
#define MAX_BURST_OBSTACLES 4
#define PROGRESSIVE_DIFFICULTY 1

// Ajustes visuales para rendimiento
#define CIRCLE_SEGMENTS 16
#define TREE_DETAIL_LEVEL 8
#define MOUNTAIN_DETAIL_LEVEL 4
#define FOREST_DENSITY 80
#define FLOWER_SPACING 120

#endif
