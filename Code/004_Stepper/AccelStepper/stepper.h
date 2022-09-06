#ifndef _Stepper_H
#define _Stepper_H

typedef enum
{ FULL4WIRE = 4,
  HALF4WIRE = 8
} MotorInterfaceType;

typedef enum
{
  DIRECTION_CCW = 0,  // Counter-Clockwise
  DIRECTION_CW  = 1   // Clockwise
} Direction;

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

void AccelStepper_stepper(uint8_t interface);
void setMaxSpeed(float speed);
void computeNewSpeed(void);
long distanceToGo(void);
void setSpeed(float speed);
bool runSpeed(void);
void step(long step);
void step4(long step);
void step8(long step);
void setAcceleration(float acceleration);
long currentPosition();
bool run();
void moveTo(long absolute);
void runToNewPosition(long position);
void micros(void);

#endif
