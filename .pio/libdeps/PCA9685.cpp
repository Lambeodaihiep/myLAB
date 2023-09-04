#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN  90 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // this is the 'maximum' pulse length count (out of 4096)

// up -> left -> right -> down
#define segm3_up 0
#define segm2_up 1
#define segm1_up 2

#define segm3_left 3
#define segm2_left 4
#define segm1_left 5

#define segm3_right 6
#define segm2_right 7
#define segm1_right 8

#define segm3_down 9
#define segm2_down 10
#define segm1_down 11

int current_pos_segm3_up = 0;
int current_pos_segm2_up = 0;
int current_pos_segm1_up = 0;

int current_pos_segm3_left = 0;
int current_pos_segm2_left = 0;
int current_pos_segm1_left = 0;

int current_pos_segm3_right = 0;
int current_pos_segm2_right = 0;
int current_pos_segm1_right = 0;

int current_pos_segm3_down = 0;
int current_pos_segm2_down = 0;
int current_pos_segm1_down = 0;

int continuum[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int bias[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int angleToPulse(int ang, int add) {
   int pulse = map(ang, 0, 180, SERVOMIN + add, SERVOMAX + add);// map angle of 0 to 180 to Servo min and Servo max 
   return pulse;
}

int analogToPulse(int analog, int add) {
   int pulse = map(analog, 0, 4096, SERVOMIN + add, SERVOMAX + add);// map angle of 0 to 180 to Servo min and Servo max 
   return pulse;
}

void Homming() {
  for(current_pos_segm3_up; current_pos_segm3_up >= 0; current_pos_segm3_up--) {
    pwm.setPWM(segm3_up, 0, angleToPulse(current_pos_segm3_up, 4));
    delay(25);
  }
  for(current_pos_segm2_up; current_pos_segm2_up >= 0; current_pos_segm2_up--) {
    pwm.setPWM(segm2_up, 0, angleToPulse(current_pos_segm2_up, 8));
    delay(25);
  }
  for(current_pos_segm1_up; current_pos_segm1_up >= 0; current_pos_segm1_up--) {
    pwm.setPWM(segm1_up, 0, angleToPulse(current_pos_segm1_up, 0));
    delay(25);
  }

  for(current_pos_segm3_left; current_pos_segm3_left >= 0; current_pos_segm3_left--) {
    pwm.setPWM(segm3_left, 0, angleToPulse(current_pos_segm3_left, 0));
    delay(25);
  }
  for(current_pos_segm2_left; current_pos_segm2_left >= 0; current_pos_segm2_left--) {
    pwm.setPWM(segm2_left, 0, angleToPulse(current_pos_segm2_left, 0));
    delay(25);
  }
  for(current_pos_segm1_left; current_pos_segm1_left >= 0; current_pos_segm1_left--) {
    pwm.setPWM(segm1_left, 0, angleToPulse(current_pos_segm1_left, 8));
    delay(25);
  }

  for(current_pos_segm3_right; current_pos_segm3_right >= 0; current_pos_segm3_right--) {
    pwm.setPWM(segm3_right, 0, angleToPulse(current_pos_segm3_right, -8));
    delay(25);
  }
  for(current_pos_segm2_right; current_pos_segm2_right >= 0; current_pos_segm2_right--) {
    pwm.setPWM(segm2_right, 0, angleToPulse(current_pos_segm2_right, -8));
    delay(25);
  }
  for(current_pos_segm1_right; current_pos_segm1_right >= 0; current_pos_segm1_right--) {
    pwm.setPWM(segm1_right, 0, angleToPulse(current_pos_segm1_right, -12));
    delay(25);
  }

  for(current_pos_segm3_down; current_pos_segm3_down >= 0; current_pos_segm3_down--) {
    pwm.setPWM(segm3_down, 0, angleToPulse(current_pos_segm3_down, -8));
    delay(25);
  }
  for(current_pos_segm2_down; current_pos_segm2_down >= 0; current_pos_segm2_down--) {
    pwm.setPWM(segm2_down, 0, angleToPulse(current_pos_segm2_down, -12));
    delay(25);
  }
  for(current_pos_segm1_down; current_pos_segm1_down >= 0; current_pos_segm1_down--) {
    pwm.setPWM(segm1_down, 0, angleToPulse(current_pos_segm1_down, -4));
    delay(25);
  }

  current_pos_segm3_up = 0;
  current_pos_segm2_up = 0;
  current_pos_segm1_up = 0;

  current_pos_segm3_left = 0;
  current_pos_segm2_left = 0;
  current_pos_segm1_left = 0;

  current_pos_segm3_right = 0;
  current_pos_segm2_right = 0;
  current_pos_segm1_right = 0;

  current_pos_segm3_down = 0;
  current_pos_segm2_down = 0;
  current_pos_segm1_down = 0;
}

