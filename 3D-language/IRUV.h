#ifndef IRUV_H
#define IRUV_H
#define PI 3.14159265f
// dimensiones  de la palma de la mano
#define PALM_WIDTHH (2.4f * SCALE_FACTOR)
#define PALM_HEIGHTT (2.3f * SCALE_FACTOR)
#define PALM_DEPTH (0.8f * SCALE_FACTOR)

#define POINT_DENSITY 0.015f
//num max de segmentos por dedo
#define MAX_FINGER_SEGMENTS 6

// escala general para agrandar o achicar toda la mano
#define SCALE_FACTOR 1.6f
// segmento de dedo 
typedef struct
{
    float length;
    float baseRadius;
    float tipRadius;
    float bendX, bendY, bendZ;
    float offsetz;
} FingerSegment;
// dedo completo comuesto por varios segmentos
typedef struct
{
    int numSegments;
    FingerSegment segments[MAX_FINGER_SEGMENTS];
    float baseX, baseY, baseZ;
    float globalBendX, globalBendY, globalBendZ;
} Finger;

extern Finger fingers[5];


//func generales
void scaleFingers(float scale);
void configureFinger(int index, int numSegments, float baseX, float baseY, float baseZ, FingerSegment segments[]);
void poseFinger_Folded(int index);
void poseFinger4_Folded();
void drawStraightFingerSegment(float baseX, float baseY, float baseZ, FingerSegment segment);
void drawArticulatedFinger(int fingerIndex);
void filpPalm();
void drawHand(void (*poseFunc)());
//inic general de dedos
void initializeFingersGeneric(void (*meniqueFunc)(), void (*postConfig)());
void configR();
void configV();

//iniciar individuales de dedos
void i_finger0();
void menique_Finger0();
void anular_Finger1();
void medio_Finger2();
void indice_Finger3();
void pulgar_Finger4();

//fnc de pose
void applyPunchPose();
void applyPunchPose_i();

//Bibujar letras
void drawLetterI();
void drawLetterR();
void drawLetterU();
void drawLetterV();
#endif
