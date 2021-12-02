#include <Stepper.h>
#include <Servo.h>

Servo myServo;

// defines pins numbers
const int stepPin = 4;
const int dirPin = 5;

int buttonPin = 8;

int buttonPressed = 0;

const int stepsPerRevolution = 200;

int currentSteps;
int maxSteps = 3200;

//in1 = pin8; in2 = pin 10; in3 = pin 9; in4 = pin 11
Stepper myStepper = Stepper (stepsPerRevolution, 5, 4);

//mapped values for pot
unsigned long mappedServoReading;
int potReading;

boolean currentButState = LOW;
boolean prevButState = LOW;
boolean isOn = LOW;

//boolean debounce;
int delayTime = 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //what pin your servo is attached to (note: must be PWM)
  myServo.attach (10);

  //this will be in loop if you want it to change over time
  myStepper.setSpeed (200);
  pinMode(buttonPin, INPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  currentButState = debounce (buttonPin, prevButState);

  //if the button is pressed this frame
  if (currentButState == HIGH && prevButState == LOW) {
    moveServo();
  }

  //update previous state
  prevButState = currentButState;
}

void moveServo () {
  while (currentSteps < maxSteps) {
    myStepper.step (-1);
    mappedServoReading = map(currentSteps, 0, 3200, 135, 0);
    myServo.write(mappedServoReading);
    currentSteps += 1;
  }



  Serial.println(potReading);


}

boolean debounce (int aButPin, int aPrevState) {

  //bouncy reading
  boolean aButState = digitalRead (aButPin);

  //if you just pressed the button, wait
  //debounces the signal

  if (aButState == HIGH && aPrevState == LOW) {
    delay (delayTime);
    moveServo();
  }

  //return results
  return aButState;
}
