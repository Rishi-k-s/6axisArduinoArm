#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
uint16_t value = 0;  // Use uint16_t for a wider range of values
uint8_t counter = 0;

int homePosCheck =0;
int i =0;

const int numServos = 6;  

void setup() {
  Serial.begin(9600); 
  Serial.println("------------------------");
  Serial.println("6 Axis Robot Arm");
  Serial.println("------------------------");

  Serial.println("Format: sXYYY where X is the servo number (0-2) and YYY is the position (000-180)");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);

  homePos();
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); 
    Serial.println(input);

    if (input.length() == 5 && input[0] == 's' && isDigit(input[1]) && isDigit(input[2]) && isDigit(input[3]) && isDigit(input[4])) {
      int servoNum = input[1] - '0'; 
      int position = input.substring(2).toInt(); 

      // if (servoNum >= 0 && servoNum < numServos && position >= 0 && position <= 180) {
      if (servoNum >= 0 && servoNum < numServos) {
        // mappedPos = map(position,0,100,)
        // servos[servoNum].write(position); 
        Serial.print("Servo ");
        Serial.print(servoNum);
        Serial.print(" set to position ");
        Serial.println(position);
        pwm.setPWM(servoNum, 0, position);
      } else {
        Serial.println("Invalid command. Ensure servo number is within range and position is between 000 and 180.");
      }
    } else {
      Serial.println("Invalid command format. Use: sXYYY where X is the servo number (0-2) and YYY is the position (000-180).");
    }
  }
}



void homePos() {

  for(i=500;i>=395;i--){
    pwm.setPWM(0, 0, i);
    delay(5);
  }
  delay(100);
  pwm.setPWM(1, 0, 110);
  delay(100);
  pwm.setPWM(2, 0, 250);
  delay(100);
  pwm.setPWM(3, 0, 380);
  delay(100);
  pwm.setPWM(4, 0, 430);
  delay(100);
  pwm.setPWM(5, 0, 490);
}