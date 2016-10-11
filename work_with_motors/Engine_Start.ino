void Engine_start(int Speed, char Engine, char Direction) {
  int PWM = round(Speed * 2.55);
  if (Engine == 'L') {
    if (Speed != 0) {
      if (Direction == 'F') {
        LeftMotor.setSpeed(PWM);
        LeftMotor.run(FORWARD);    
      }
      if (Direction == 'B') {
        LeftMotor.setSpeed(PWM);
        LeftMotor.run(BACKWARD);  
      }
    }
    if (Speed == 0) { LeftMotor.run(RELEASE); }   
  }
  if (Engine == 'R') {
    if (Speed != 0) {
      if (Direction == 'F') {
        RightMotor.setSpeed(PWM);
        RightMotor.run(FORWARD);    
      }
      if (Direction == 'B') {
        RightMotor.setSpeed(PWM);
        RightMotor.run(BACKWARD);  
      }
    }
    if (Speed == 0) { RightMotor.run(RELEASE); }     
  }
}
