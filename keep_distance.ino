#include <AFMotor.h> // link library

#define Kp 8 // coefficient for P regulator of FWD
#define Kp_rot 7 // coefficient for P regulator of rotation

#define PORT_A 1 // set port of the first motor
#define PORT_B 2 // set port of the second motor
#define max_speed 100 // set max speed
#define f_speed 150 // set first speed
#define wait_time 25  // set delay time in ms
#define ECHO_PIN 14 // the number of the ECHO pin
#define TRIG_PIN 15 // the number of the TRIG pin
#define OUT_PIN 12 // set number of the encoder

AF_DCMotor RightMotor(PORT_A); // create object of right motor
AF_DCMotor LeftMotor(PORT_B); // create object of left motor

void OnFwd(int Speed, String Motor);
void reset_sensor(void);
void motor_control(int value);
void rot_control(void);
int ultrasonic(void);
int rotation_count(int pin);

int base_speed = 50; // in percent
int dist_cm = 0, pwm_A, pwm_B, D_rotA, D_rotB;
long i, angle, rotA, rotB, D_rotAB;
byte now, last;

void setup() 
{
  //Serial.begin(9600);
  base_speed = ((base_speed)/100) * max_speed; // conver base_speed to value in int
}

void loop() 
{
  rot_control(); // P regulator of both rotation motors
  OnFwd(f_speed + base_speed + pwm_A, "LEFT"); // supply speed
  OnFwd(f_speed + base_speed + pwm_B, "RIGHT"); // supply speed
  delay(wait_time); // wait 25 ms
}

// supply speed
void OnFwd(int Speed, String Motor)
{
  if (Motor == "RIGHT") // set right motor
  {
    motor_control(Speed); // control FWD
  }
  if (Motor == "LEFT") // set left motor
  {
    motor_control(Speed); // control FWD   
  }
}

// supply speed
void motor_control(int value)
{
  if (value > 0)
  {
    RightMotor.setSpeed(value);
    RightMotor.run(FORWARD); // set forward 
  }
  else
  {
    RightMotor.setSpeed(value);
    RightMotor.run(BACKWARD); // set backward            
  }  
}

// ckeck distance 
int ultrasonic(void)
{
  digitalWrite(TRIG_PIN, HIGH); // submit signal
  delayMicroseconds(10); // wait 10 mcs
  digitalWrite(TRIG_PIN, LOW); // stop
  int distance = pulseIn(ECHO_PIN, HIGH, 100000); // read the signal length and set timeout
  if (distance == 0) // check stuck
  { 
    reset_sensor(); // restart the sensor to remove stuck
  } else 
  {
    dist_cm = distance/58; // convert to cm
    //Serial.println(dist_cm); // print in com port   
  }
  return dist_cm;
}


// restart the rangefinder
void reset_sensor(void)
{
  pinMode(ECHO_PIN, OUTPUT); // change the INPUT on OUTPUT
  digitalWrite(ECHO_PIN, 0); // set LOW
  pinMode(ECHO_PIN, INPUT); // change the OUTPUT on INPUT 
  //Serial.println("Out of range!");  
}

// check rotation count
int rotation_count(int pin)
{
  now = digitalRead(pin); // set value at the moment. It can take a value 1 or 0
  if (last != now) 
  {
    i++; 
    angle = i * 9; // int to angle in deg
    //Serial.print(i);
    //Serial.print(" step");
    //Serial.print(" | ");
    //Serial.print(angle);
    //Serial.println(" deg");
  }
  last = digitalRead(pin); // save last value. It can take a value 1 or 0
  return angle;  
}

// control of motors rotation
void rot_control(void)
{
  rotA = rotation_count(OUT_PIN); // set rotation from first motor
  rotB = rotation_count(OUT_PIN);// set rotation from second motor
  D_rotAB = (rotA+rotB)/2; // calculate the average
  D_rotA = D_rotAB - rotA;
  D_rotB = D_rotAB - rotB;
  pwm_A = Kp_rot * D_rotA; // set speed
  pwm_B = Kp_rot * D_rotB; // set speed
}

