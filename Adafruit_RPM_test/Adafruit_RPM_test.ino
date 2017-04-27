// Test the rpm setting of steppers on the Adafruit Motor Shield V2 driver software.
// There was a bad bug in the code due to the odd behavior of the Ardunio delayMicroseconds()
// function.  My fixed version of the Adafruit code can be found here:
// https://github.com/curtwelch/Adafruit_Motor_Shield_V2_Library
//
// This code tests the actual RPM value of the stepper by timing how long it takes to
// move a 200 steps/revolutio stepper.  This only checkes the timing of the code, not
// the actual motoion of the stepper.  You don't need to wire a stepper to the
// motor shield to run this test.
//
// More information about the issue at:
// https://forums.adafruit.com/viewtopic.php?f=31&t=115397&hilit=wrong+RPM%2C+irregular+motion
//
// 4-2017 Curt Welch <curt@kcwc.com>

#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2); // 200 step per revolution stepper wired to connector 2 (M3/M4)

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit RPM test!");

  AFMS.begin();  // create with the default frequency 1.6KHz

#if 0
  TWBR = ((F_CPU / 400000l) - 16) / 2; // Change the i2c clock from 100KHz to 400KHz
  // This code, from the Adafruit fourms, raises the i2c clock speed by a factor of 4.
  // It increases the max RPM this code can drive the stepper
  // by the same factor of 4 due to the the I2C communication overhead between the
  // Arduino and the motor shield. (change "#if 0" to "#if 1" to activate)
#endif

  rpmTest();

  myMotor->release();
}

void rpmTest() {
  int rpmValue[] = {5, 10, 20, 50, 100, 150, 300, 400, 0};
  int i;

  for (i = 0; rpmValue[i]; i++) {
    myMotor->setSpeed(rpmValue[i]); 
    long t0 = millis();
    myMotor->step(100, FORWARD, SINGLE); // I'm using a 200 stepper so this is 1/2 turn */
    myMotor->step(100, BACKWARD, SINGLE);
    long t1 = millis();
    Serial.print("RPM set to ");
    Serial.print(rpmValue[i]);
    Serial.print(" measured RPM is ");
    Serial.print(60000.0 / (t1 - t0));
    Serial.print(", steps per second is: ");
    Serial.print(200.0 * 1000.0 / (t1-t0));
    Serial.println();
  }
  Serial.println("Test Done.");
}

void loop() {
}

