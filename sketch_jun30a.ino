#define OUT_PIN 12

void rotation_count(int pin);

long i, angle;
byte now, last;

void setup() 
{
  Serial.begin(9600);
  pinMode(OUT_PIN, INPUT);
}

void loop() 
{
  rotation_count(OUT_PIN);
  delay(1);
}

void rotation_count(int pin)
{
  now = digitalRead(pin);
  if (last != now) 
  {
    i++;
    angle = i * 9;
    //Serial.print(i);
    //Serial.print(" step");
    //Serial.print(" | ");
    Serial.print(angle);
    Serial.println(" deg");
  }
  last = digitalRead(pin);
  //return angle;  
}

