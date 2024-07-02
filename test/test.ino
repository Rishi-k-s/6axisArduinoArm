#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Servo Tester");
  Serial.println("Choose Servo");
  Serial.println("1");
  Serial.println("2");
  Serial.println("3");
  Serial.println("4");
  Serial.println("5");
  Serial.println("6");
  
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
    if (){}

    pwm.setPWM(servonum, 0, pulselen);

  }

}
