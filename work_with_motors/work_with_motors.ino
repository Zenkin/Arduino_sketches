/*

  Function Engine_start(int Speed, char Engine, char Direction);
  Speed: 0 - 100 in percent;
  Engine: L - left motor, R - right motor;
  Direction: F - forward, B - backward;
    
*/
#include <AFMotor.h>

const byte left_motor = 1;
const byte right_motor = 2;

AF_DCMotor RightMotor(right_motor);
AF_DCMotor LeftMotor(left_motor);

void Engine_start(int Speed, char Engine, char Direction);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Engine_start(100, 'R', 'F');
  Engine_start(100, 'R', 'F');  
}

