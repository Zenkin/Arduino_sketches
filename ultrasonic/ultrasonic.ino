/*

                        HC-SR04

  It's simple example, how works HC-SR04
  I don't use lib, just physics and integrated functions
  This program check stuck and restart sensor when it's stucking
  In practice it's 2m - 2.5m
  after this value sketck write "Out of range!" becouse sticking occurs.

  version 1.0
  + write this sketch
  version 1.1 
  + write reset_sensor() function
  version 2.0
  + add ultrasonic_result_in_cm() function
  + add multitasking
  
*/

const int EchoPin = 14; // the number of the ECHO pin
const int TrigPin = 15; // the number of the TRIG pin
const int wait_time = 7; // set delay time in ms
const int timer_for_ultrasonic = 25;

// functions prototypes
void reset_sensor(void);
int ultrasonic_result_in_cm(int trig_pin, int echo_pin);

unsigned long previousMillis;

void setup()  
{
  // initialize serial:
  Serial.begin(9600);
  // initialize the ECHO pin as an input:
  pinMode(EchoPin, INPUT);
  // initialize the TRIG:
  pinMode(TrigPin, OUTPUT); 
}

void loop()  
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > timer_for_ultrasonic)
  { 
    int dist_cm;
    dist_cm = ultrasonic_result_in_cm(TrigPin, EchoPin);
    Serial.println(dist_cm," cm"); // print in com port
  } 
  delay(wait_time); // wait 7 ms
}

void reset_sensor(void)
{
  pinMode(EchoPin, OUTPUT); 
  digitalWrite(EchoPin, 0); 
  pinMode(EchoPin, INPUT); 
  Serial.println("Out of range!");  
}

int ultrasonic_result_in_cm(int trig_pin, int echo_pin)
{ 
  digitalWrite(trig_pin, HIGH); // submit signal
  delayMicroseconds(10); // wait 10 mcs
  digitalWrite(echo_pin, LOW); // stop
  int distance = pulseIn(echo_pin, HIGH, 100000); // read the signal length and set timeout
  if (distance == 0) // check stuck
  { 
    reset_sensor(); // restart the sensor to remove stuck
  } else 
  {
    return(distance/58); // convert to cm
  }   
}

