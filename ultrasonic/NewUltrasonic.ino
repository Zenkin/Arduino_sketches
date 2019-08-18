/*

                        HC-SR04

  It's simple example, how works HC-SR04
  I don't use lib, just physics and integrated functions
  This program check stuck and restart sensor when it's stucking
  I use three LEDs: green, yellow, red and switch them on depending on the distance:
  (0;10] - red led
  (10;20) - yellow led
  [20;+inf) - green led. In theory +inf. In practice it's 2m - 2.5m
  after this value sketck write "Out of range!" becouse sticking occurs.

  version 1.0
  + write this sketch
  version 1.1 
  + write reset_sensor() and led_control() functions
  + size 1536 byte without Serial port (4%) and
  3298 byte with serial port (10%)
  
 */

#define ECHO_PIN 14 // the number of the ECHO pin
#define TRIG_PIN 15 // the number of the TRIG pin
#define ledPinGreen 11 // the number of the green led pin
#define ledPinYellow 4 // the number of the yellow led pin
#define ledPinRed 12 // the number of the red led pin
#define wait_time 25 // set delay time in ms

// functions prototypes
void reset_sensor(void);
void led_control(int dist);

void setup()  
{
  // initialize serial:
  Serial.begin(9600);
  // initialize the ECHO pin as an input:
  pinMode(ECHO_PIN, INPUT);
  /* initialize the TRIG, green led, 
  yellow led and red led pins as an output: */
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(ledPinRed, OUTPUT); 
}

void loop()  
{

  int dist_cm;
  
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
    Serial.println(dist_cm); // print in com port 
    led_control(dist_cm); // LED control   
  }
  delay(wait_time); // wait 25 ms
}

void reset_sensor(void)
{
  pinMode(ECHO_PIN, OUTPUT); 
  digitalWrite(ECHO_PIN, 0); 
  pinMode(ECHO_PIN, INPUT); 
  Serial.println("Out of range!");  
}

void led_control(int dist)
{
  if (dist <= 10)
  {
    digitalWrite(ledPinYellow, 0);
    digitalWrite(ledPinGreen, 0);
    digitalWrite(ledPinRed, 1);
  }
  else if (dist >= 20)
  {
    digitalWrite(ledPinYellow, 0);
    digitalWrite(ledPinRed, 0);      
    digitalWrite(ledPinGreen, 1); 
  }
  else
  {
    digitalWrite(ledPinGreen, 0);
    digitalWrite(ledPinRed, 0);
    digitalWrite(ledPinYellow, 1);   
  }     
}

