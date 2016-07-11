#include <AFMotor.h> // link library

// set pins
const int PORT_A = 1; // set port of the first motor
const int PORT_B = 2; // set port of the second motor
const int ECHO_PIN_1 = 14; // the number of the ECHO pin
const int TRIG_PIN_1 = 15; // the number of the TRIG pin
const int ECHO_PIN_2 = 14; // the number of the ECHO pin
const int TRIG_PIN_2 = 15; // the number of the TRIG pin
const int crit_dist = 15; // set the red line in cm
const int OUT_PIN_LEFT = 12; // set number of the encoder
const int OUT_PIN_RIGHT = 13; // set number of the encoder

//set constants
const int Kp = 8; // coefficient for P regulator of FWD
const int Kp_rot = 7; // coefficient for P regulator of rotation
const int max_speed = 100; // set max speed
const int f_speed = 150; // set first speed
const int wait_time = 25;  // set delay time in ms

AF_DCMotor RightMotor(PORT_A);
AF_DCMotor LeftMotor(PORT_B);

void OnFwd(int Speed, String Motor);
void reset_sensor(int echo_pin);
void motor_control(int value);
void rot_control(int out_pin_1, int out_pin_2);
int ultrasonic(int trig_pin, int echo_pin);
int rotation_count(int pin);

int base_speed = 50; // in percent
int dist_cm = 0, dist_left, dist_right, pwm;
int pwm_A, pwm_B, D_rotA, D_rotB;
long i, angle, rotA, rotB, D_rotAB;
byte now, last;

void setup() 
{
  Serial.begin(9600); // set serial com port
  base_speed = ((base_speed)/100) * max_speed; // conver base_speed to value in int
}

void loop() 
{
  dist_left = ultrasonic(TRIG_PIN_1, ECHO_PIN_1); // distance to the left sensor
  dist_right = ultrasonic(TRIG_PIN_2, ECHO_PIN_2); // distance to the right sensor

  if ((dist_left < crit_dist) || (dist_right < crit_dist))
  {
    if (dist_left > dist_right)
    {
      pwm = Kp * (crit_dist - dist_left);
    } 
    else
    {
      pwm = Kp * (crit_dist - dist_right);
    }
  }
  else
  {
    pwm = 0;
  }

  if (pwm = 0)
  {
    rot_control(OUT_PIN_LEFT, OUT_PIN_RIGHT); // P regulator of both rotation motors
    OnFwd(f_speed + base_speed + pwm_A, "LEFT"); // supply speed
    OnFwd(f_speed + base_speed + pwm_B, "RIGHT"); // supply speed
  }
  else
  {
    OnFwd(f_speed + base_speed + pwm, "LEFT"); // supply speed
    OnFwd(f_speed + base_speed + pwm, "RIGHT"); // supply speed
  }
  
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
int ultrasonic(int trig_pin, int echo_pin)
{
  digitalWrite(trig_pin, HIGH); // submit signal
  delayMicroseconds(10); // wait 10 mcs
  digitalWrite(trig_pin, LOW); // stop
  int distance = pulseIn(echo_pin, HIGH, 100000); // read the signal length and set timeout
  if (distance == 0) // check stuck
  { 
    reset_sensor(echo_pin); // restart the sensor to remove stuck
    dist_cm = 40;
  } else 
  {
    dist_cm = distance/58; // convert to cm
    Serial.println(dist_cm); // print in com port   
  }
  return dist_cm;
}

// restart the rangefinder
void reset_sensor(int echo_pin)
{
  pinMode(echo_pin, OUTPUT); 
  digitalWrite(echo_pin, 0); 
  pinMode(echo_pin, INPUT); 
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
void rot_control(int out_pin_1, int out_pin_2)
{
  rotA = rotation_count(out_pin_1); // set rotation from first motor
  rotB = rotation_count(out_pin_2);// set rotation from second motor
  D_rotAB = (rotA+rotB)/2; // calculate the average
  D_rotA = D_rotAB - rotA;
  D_rotB = D_rotAB - rotB;
  pwm_A = Kp_rot * D_rotA; // set speed
  pwm_B = Kp_rot * D_rotB; // set speed
}

