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
void runArm();

void setup() {
	// write your initialization code here
	Serial.begin(9600);
	
	// attaching servo pins
	base.attach(base_pin);
	shoulder.attach(shoulder_pin);
	elbow.attach(elbow_pin);
	wrist.attach(wrist_pin);
	gripper.attach(gripper_pin);
	
	// set Pins
	pinMode(led, OUTPUT);
	pinMode(switchPin, OUTPUT);
	
	/*----------RESET THE ARM POSITION-------------- */
	//base.write(0);
	//shoulder.write(90); // upright 90 deg
	//elbow.write(60); // upright 60 deg
	//wrist.write(110); // the gripper is straight when the wrist angle is 110 deg
	//gripper.write(90); // gripper teeth closed when the gripper motor is at 90 deg
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

/* Angle calculation functions. Cosine rule */
void inverseKinematics(){
	// Calculate the angles at the joints to pick the object
	
}