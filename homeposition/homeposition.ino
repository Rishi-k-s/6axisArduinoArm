#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
uint16_t value = 0;  // Use uint16_t for a wider range of values
uint8_t counter = 0;

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)

int homePosCheck =0;
int i =0;
void setup() {
  Serial.begin(9600);

  Serial.println("------------------------");
  Serial.println("Servo Home Position v1.0a");
  // Serial.println("Enter Servo Value");
  // Serial.println("If its 2 digit values enter it with 0 as prefix");
  // Serial.println("Eg: for 90, type 090");
  Serial.println("------------------------");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  
  homePos();
}

void loop() {
  // while(homePosCheck == 0){
  //   homePos();
  //   homePosCheck++;
  // }
}


void homePos() {
  // (PWM Driver Pin, 0, val of servo)
  //motor1
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
  // //motor2
  // for(i=0;i<=85;i++){
  //   pwm.setPWM(1, 0, i);
  //   delay(10);
  // }
  // //motor3
  // for(i=0;i<=250;i++){
  //   pwm.setPWM(2, 0, i);
  //   delay(10);
  // }
  // //motor4
  // for(i=0;i<=380;i++){
  //   pwm.setPWM(3, 0, i);
  //   delay(10);
  // }
  // //motor5
  // for(i=0;i<=450;i++){
  //   pwm.setPWM(4, 0, i);
  //   delay(10);
  // }

  // pwm.setPWM(0, 0, 395);
}
