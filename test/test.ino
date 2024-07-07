#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
uint16_t value = 0;  // Use uint16_t for a wider range of values
uint8_t counter = 0;

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)

bool homePosCheck = false;

void setup() {
  Serial.begin(9600);

  Serial.println("------------------------");
  Serial.println("Servo Tester v1.0a");
  Serial.println("Enter Servo Value");
  Serial.println("If its 2 digit values enter it with 0 as prefix");
  Serial.println("Eg: for 90, type 090");
  Serial.println("------------------------");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
}

void loop() {
  if (Serial.available() != 0) {
    // Read the incoming byte
    char incomingByte = Serial.read();
    
    // Print the incoming byte to the serial monitor
    Serial.print("received: ");
    Serial.println(incomingByte);

    // Convert ASCII to integer
    uint8_t digit = incomingByte - '0';

    // Validate that the input is a digit
    if (digit >= 0 && digit <= 9) {
      // Assuming that I only give 3 digit values
      if (counter == 0) {
        value = digit * 100;
      }
      else if (counter == 1) {
        value += digit * 10;
      }
      else if (counter == 2) {
        value += digit;
      }
      Serial.print("value: ");
      Serial.println(value);

      counter++;
    }
  }

  if (counter == 3) {
    Serial.println(value);
    pwm.setPWM(5, 0, value); // Arguement order => (PWM Driver Pin, 0, val of servo)
    // pwm.setPWM(0, 1024, 3072);
    counter = 0;
    value = 0; // Reset value after using it
  }
  
  if (homePosCheck ==0){
    homePos();
    homePosCheck =0;
  }



}


void homePos() {
  // (PWM Driver Pin, 0, val of servo)
  //motor1
  for(int i=500;i>=395;i--){
    pwm.setPWM(0, 0, i);
    delay(5);
  }
  delay(100);
  //motor2
  pwm.setPWM(1, 0, 110);
  delay(100);
  //motor3
  pwm.setPWM(2, 0, 250);
  delay(100);
  //motor4
  pwm.setPWM(3, 0, 380);
  delay(100);
  //motor5
  pwm.setPWM(4, 0, 430);
  delay(100);
  //motor6
  pwm.setPWM(5, 0, 490);

}
