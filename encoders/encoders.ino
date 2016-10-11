const int out_pin = 12;
const int wait_time = 1;

long rotation_count(int encoder_pin);
long i, angle;
byte current_angle, previous_angle;

void setup() 

{
  Serial.begin(9600);
  pinMode(out_pin, INPUT);
}

void loop() 
{
  long rot_count;
  
  rot_count = rotation_count(out_pin);
  Serial.print(rot_count);
  Serial.println(" deg");
  delay(wait_time);
}

long rotation_count(int encoder_pin)
{
  current_angle = digitalRead(encoder_pin);
  if (previous_angle != current_angle) 
  {
    i++;
    angle = i * 9;
  }
  previous_angle = digitalRead(encoder_pin);
  return angle;  
}
