#define Trig_pin 15
#define Echo_pin 14
#include <AFMotor.h>
#define Kp 8
#define need_dist 10

AF_DCMotor RightMotor(1);
AF_DCMotor LeftMotor(2);

unsigned long millis_old_Ir, millis_old_Ult, millis_old_LED, millis_old_dir, micros_old_Ult = 0;
long dist_cm, s_r, s_l, s, ang_sum = 0;
int u, u1;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);

  pinMode(Trig_pin, OUTPUT);
  pinMode(Echo_pin, INPUT); //инициируем как вход 

}

void loop() {
  // put your main code here, to run repeatedly:
  Ultrasound();
  Serial.println(dist_cm); // Выводим на порт
  u = Kp * (dist_cm - need_dist);
  //OnFwd(1.5*80, 2, 2); // 1 - Right & 1 - FORWARD
  //OnFwd(80, 2, 1); // 2 - Left & 2 - BACKWARD 
  if (u > 250) { u = 250; }
  if (u < -250) { u = -250; }
  if (u>0) {
  OnFwd(u, 1, 2); // 1 - Right & 1 - FORWARD
  OnFwd(u+20, 1, 1); // 2 - Left & 2 - BACKWARD
  }
  if (u<=0)  {
  OnFwd(u, 2, 2); // 1 - Right & 1 - FORWARD
  OnFwd(u-20, 2, 1); // 2 - Left & 2 - BACKWARD 
  }
  delay(100);
}

void Ultrasound(){
  if(millis()-millis_old_Ult > 100){
    digitalWrite(Trig_pin, HIGH);
    delayMicroseconds(4);
    digitalWrite(Trig_pin, LOW);
    micros_old_Ult = micros();
    while(!digitalRead(Echo_pin) && micros()-micros_old_Ult < 500){
    }
    micros_old_Ult = micros();
    while(digitalRead(Echo_pin) && micros()-micros_old_Ult < 20000){
    }
    dist_cm = (micros() - micros_old_Ult)/29.0/2;
    millis_old_Ult = millis();
  }
}

void OnFwd(int Speed, int FWD, int Motor)
{
  if (Motor == 1)
  {
    // RIGHT MOTOR SET
    if (FWD == 1)
    {
      // SET FORWARD
      RightMotor.setSpeed(Speed);
      RightMotor.run(FORWARD); 
    }
    if (FWD == 2)
    {
      // SET BACKWARD
      RightMotor.setSpeed(Speed);
      RightMotor.run(BACKWARD); 
    }
  }
  if (Motor == 2)
  {
    // LEFT MOTOR SET
    if (FWD == 1)
    {
      // SET FORWARD
      LeftMotor.setSpeed(Speed);
      LeftMotor.run(FORWARD); 
    }
    if (FWD == 2)
    {
      // SET BACKWARD
      LeftMotor.setSpeed(Speed);
      LeftMotor.run(BACKWARD); 
    }
  }
}

