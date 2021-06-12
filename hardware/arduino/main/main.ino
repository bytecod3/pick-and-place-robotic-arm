#include <Servo.h>

// constants
#define DELAY 20
#define PI 3.141592654

// Servo objects
Servo base, shoulder, elbow, wrist, gripper;

/* ------------- PINS -------------------- */
// conveyor belt pins
int led = 9;
int object_pin = A1;//

int movingLED = 11;

// switch pin
int switchPin;

// servo pins
int base_pin = 2;
int shoulder_pin = 3;
int elbow_pin = 4;
int wrist_pin = 5;
int gripper_pin = 8;

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
    pinMode(movingLED, OUTPUT);
    pinMode(switchPin, OUTPUT);

    // attaching servo pins
    base.attach(base_pin);
    shoulder.attach(shoulder_pin);
    elbow.attach(elbow_pin);
    wrist.attach(wrist_pin);
    gripper.attach(gripper_pin);


    // start the arm at a neutral position
    setNeutralPosition();

    shoulder.write(30);
//    elbow.write(70);
//    wrist.write(20);
//    gripper.write(0);

}

void loop() { 
   // open gripper
   // move base 180 
   // raise shoulder
   // lower elbow
   // close gripper to pick object
   // move base 0
   // lower shoulder
   // raise elbow
   // open gripper to place object

    for(int i = 0; i <180; i++){
      base.write(i);
      delay(DELAY);
    }

    for(int i = 30; i < 70; i++){
      shoulder.write(i);
      delay(DELAY);
    }


    for(int i = 180; i >0; i--){
      base.write(i);
      delay(DELAY);
    }

    for(int i = 70; i > 30; i--){
      shoulder.write(i);
      delay(DELAY);
    }

    

//==========================================
  
  
  
//
//  int sAngle = shoulder.read();
//  if(sAngle<70){
//    for(int s = sAngle; i < 70; i++){
//      shoulder.write(s);
//      delay(DELAY);
//    }
//  }else{
//    for(int s = sAngle; i > 70; i--){
//      shoulder.write(s);
//      delay(DELAY);
//    }
//  }
//
  
//
//  // lower elbow
//  for(int i = 70; i < 90; i++){
//    elbow.write(i);
//    delay(DELAY);
//  }

  // open gripper
//  for(int i = 70; i < 90; i++){
//    elbow.write(i);
//    delay(DELAY);
//  }


  
	// read the object pin to detect if an object is present
//	int object_detected = detectObject();
//	
//	Serial.println(object_detected);
//
//	if(object_detected < 200){
//		// Object blocking the infrared, meaning there is an object ready
//		// to be picked
//		digitalWrite(led, HIGH);
//		
//		// initiate object picking sequence
//		
//	}else{
//		// Object
//		digitalWrite(led, LOW);
//	}
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
    delay(DELAY);
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
	
//	// status message
//	Serial.println("Initializing servos...");
//	Serial.println();
//	
	// Read the current  motor angles to move slowly to avoid generating excess inertial momentum
//	int currentBaseAngle = base.read();
	int currentShoulderAngle = shoulder.read();
  Serial.print("Current shoulder angle: "); Serial.print(currentShoulderAngle); Serial.println();

	int currentElbowAngle = elbow.read();
  Serial.print("Current elbow angle: "); Serial.print(currentElbowAngle); Serial.println();
//	int currentWristAngle = wrist.read();
//	int currentGripperAngle = gripper.read();
//	
//	// neutral position for base servo is 0 degrees
//	if(currentBaseAngle > 0){
//		// base angle motor should start at 0
//		for (int a = currentBaseAngle; a > 0; a--) {
//			// write down to 0
//      Serial.print("Base: "); Serial.print(a); Serial.println("\n");
//			base.write(a);
//			delay(DELAY);
//		}
//		// else the motor is at 0
//	}
//	
	// neutral position for shoulder servo is 0 degrees
//	if (currentShoulderAngle > 0){
//		// write down to 0 degrees from the current position
//		for(int b = currentShoulderAngle; b > 0; b--){
//			shoulder.write(b);
//      Serial.print("shoulder: "); Serial.print(b); Serial.println("\n");
//			delay(DELAY);
//		}
//	}
//	
//	// neutral position for elbow servo is 90 degrees
//	if(currentElbowAngle > 90){
//		// write down to 90 degrees
//		for (int d = currentElbowAngle; d > 90 ; d--) {
//			elbow.write(d);
//      Serial.print("elbow: "); Serial.print(d); Serial.println("\n");
//			delay(DELAY);
//		}
//	}else{
//		// current elbow angle is less than 90 degrees
//		// write up to 90
//		for(int e = currentElbowAngle; e < 90; e++){
//			elbow.write(e);
//      Serial.print("elbow: "); Serial.print(e); Serial.println("\n");
//			delay(DELAY);
//		}
//	}
//	
//	// neutral position for wrist servo is 20 deg
//	// the gripper is horizontal at this angle
//	if(currentWristAngle > 20){
//		// write down to 20 degrees
//		for(int f = currentWristAngle; f > 20; f--){
//			wrist.write(f);
//      Serial.print("wrist: "); Serial.print(f); Serial.println("\n");
//			delay(DELAY);
//		}
//	}else{
//		// write up to 20 degrees
//		for(int f = currentWristAngle; f < 20; f++){
//			wrist.write(f);
//      Serial.print("wrist: "); Serial.print(f); Serial.println("\n");
//			delay(DELAY);
//		}
//	}
	
	// start the gripper in a closed position
//	if (currentGripperAngle > 90){
//		for(int g = currentGripperAngle; g > 90; g--){
//			// write down to 90 degrees to close it
//			gripper.write(g);
//			delay(DELAY);
//		}
//	}else{
//		for(int g = currentGripperAngle; g < 90; g++){
//			// write up to 90 degrees
//			gripper.write(g);
//			delay(DELAY);
//		}
//	}
}

/* Angle calculation functions. Cosine rule */
void inverseKinematics(){
	// Calculate the angles at the joints to pick the object
	
}
