#include <Arduino.h>
#include <Servo.h>

// constants
#define DELAY 40
#define PI 3.141592654

// Servo objects
Servo base, shoulder, elbow, wrist, gripper;

/* ------------- PINS -------------------- */
// conveyor belt pins
int led = 9;
int object_pin = A1;

// switch pin
int switchPin;

// servo pins
int base_pin = 2;
int shoulder_pin = 3;
int elbow_pin = 4;
int wrist_pin = 5;
int gripper_pin = 6;

/* Set up Inverse Kinematics variables */
float shoulderLength = 6.0;
float elbowLength = 4.0;
float wristLength = 4.0;
float hypotenuse, slope, circlePointX, circlePointY;

// functions prototypes
int detectObject();
void setNeutralPosition();

void setup() {
	// write your initialization code here
	Serial.begin(9600);
	
	// set Pins
	pinMode(led, OUTPUT);
	pinMode(switchPin, OUTPUT);
	
	// attaching servo pins
	base.attach(base_pin);
	shoulder.attach(shoulder_pin);
	elbow.attach(elbow_pin);
	wrist.attach(wrist_pin);
	gripper.attach(gripper_pin);
	
	
	// start the arm at a neutral position
	setNeutralPosition();
	
	
}

void loop() {
	// read the object pin to detect if an object is present
	int object_detected = detectObject();
	
	Serial.println(object_detected);

	if(object_detected < 200){
		// Object blocking the infrared, meaning there is an object ready
		// to be picked
		digitalWrite(led, HIGH);
		
		// initiate object picking sequence
		
	}else{
		// Object
		digitalWrite(led, LOW);
	}
}

int detectObject(){
	// detect if an object has been placed by the conveyor belt
	int is_object = analogRead(object_pin);
	return is_object;
}

/*===================SERVO MOVEMENT FUNCTIONS========================*/

// BASE MOTOR MOVEMENT
void moveBaseToPick(){
	/* Move the base to the object to be picked*/
	for(int pos = 0; pos < 180; pos++){
		// todo : define a neutral position from where the base should start running from
		base.write(pos);
		delay(15); // todo: change this delay value to a variable to be changed online
	}
}

void moveBaseToPlace(){
	/* Move the base from the picking position to placing position */
	for(int pos = 180; pos >= 0; pos-- ){
		base.write(pos);
		delay(15);
	}
}

// SHOULDER MOTOR MOVEMENT
void moveShoulderToPick(){
	// set the shoulder angle to pick the object
	for(int pos = 100; pos <= 160; pos++){
		// todo: change this range because it will not be a full 100-160 deg sweep
		shoulder.write(pos);
		delay(15);
	}
}

void moveShoulderToPlace(){
	// set the shoulder position to place the object
	for(int pos = 160; pos >=0; pos--){
		shoulder.write(pos);
		delay(15);
	}
}

// ELBOW MOTOR MOVEMENT
void moveElbowToPick(){
	// set the elbow angle to pick the object
	for (int pos = 80; pos <= 180; pos++) {
		elbow.write(pos);
	}
}

void moveElbowToPlace(){
	// set the elbow angle to pick the object
	for (int pos = 180; pos >= 80; pos--) {
		// todo: change this range to the suitable range
		elbow.write(pos);
	}
}

// GRIPPER SETTING
void openGripper(){
	// open the gripper to pick an object
	
	// this function will receive the width of the object from the camera and set the
	// appropriate angle to set the jaws
	for(int pos=100; pos <=138; pos++){
		gripper.write(pos);// todo: change these angles according to the calibration of the environment
	}
}

void closeGripper(){
	// close the gripper to pick the object
	for (int pos = 138; pos < 100; pos--) {
		gripper.write(pos);
	}
}

/*=====================OTHER FUNCTIONS====================*/
// TURN THE WHOLE SYSTEM ON OR OFF
void genesis(int pin){
	// function to start the system
	// logic: apply a positive signal at the pin set as the switch
	
	digitalWrite(switchPin, HIGH);
	
}

void setNeutralPosition(){
	/* set the servos at a neutral position  */
	
	// status message
	Serial.println("Initializing servos...");
	Serial.println();
	
	// Always read the current  motor angles to move slowly to avoid generating excess inertial momentum
	int currentBaseAngle = base.read();
	int currentShoulderAngle = shoulder.read();
	int currentElbowAngle = elbow.read();
	int currentWristAngle = wrist.read();
	int currentGripperAngle = gripper.read();
	
	// neutral position for base servo is 0 degrees
	if(currentBaseAngle > 0){
		// base angle motor should start at 0
		for (int a = currentBaseAngle; a > 0; a--) {
			// write down to 0
			base.write(a);
			delay(DELAY);
		}
		// else the motor is at 0
	}
	
	// neutral position for shoulder servo is 90 degrees
	if (currentShoulderAngle > 90){
		// write down to 90 degrees from the current position
		for(int b = currentShoulderAngle; b > 90; b--){
			shoulder.write(b);
			delay(DELAY);
		}
	} else{
		// the current angle is less than 90 degrees
		// write up to 90 degrees
		for(int c = currentShoulderAngle; c < 90; c++){
			shoulder.write(c);
			delay(DELAY);
		}
	}
	
	// neutral position for elbow servo is 60 degrees
	if(currentElbowAngle > 60){
		// write down to 60 degrees
		for (int d = currentElbowAngle; d > 60 ; d--) {
			elbow.write(d);
			delay(DELAY);
		}
	}else{
		// current elbow angle is less than 60 degrees
		// write up to 60
		for(int e = currentElbowAngle; e < 60; e++){
			elbow.write(e);
			delay(DELAY);
		}
	}
	
	// neutral position for wrist servo is 110 deg
	// the gripper is horizontal at this angle
	if(currentWristAngle > 110){
		// write down to 110 degrees
		for(int f = currentWristAngle; f > 110; f--){
			wrist.write(f);
			delay(DELAY);
		}
	}else{
		// write up to 110 degrees
		for(int f = currentElbowAngle; f < 110; f++){
			wrist.write(f);
			delay(DELAY);
		}
	}
	
	// start the gripper in a closed position
	if (currentGripperAngle > 90){
		for(int g = currentGripperAngle; g > 90; g--){
			// write down to 90 degrees to close it
			gripper.write(g);
			delay(DELAY);
		}
	}else{
		for(int g = currentGripperAngle; g < 90; g++){
			// write up to 90 degrees
			gripper.write(g);
			delay(DELAY);
		}
	}
}

/* Angle calculation functions. Cosine rule */
void inverseKinematics(){
	// Calculate the angles at the joints to pick the object
	
}