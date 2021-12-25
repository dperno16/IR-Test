#include <Arduino.h>
#include <RemoteConstants.h>
#include <RBE1001Lib.h>
#include <IRDecoder.h>
#include "robot.h"

//navigation stuff
// Robot::Robot() : left_motor(MOTOR_LEFT_PWM, MOTOR_LEFT_DIR, MOTOR_LEFT_ENCA, MOTOR_LEFT_ENCB), right_motor(MOTOR_RIGHT_PWM, MOTOR_RIGHT_DIR, MOTOR_RIGHT_ENCA, MOTOR_RIGHT_ENCB){
// }

//instantiate Robot class with object robot
Robot robot;

//state stuff
ROBOT_STATE robotState = ROBOT_IDLE;

//IRDecoder Stuff
const uint8_t IR_DETECTOR_PIN = 15;
IRDecoder decoder(IR_DETECTOR_PIN);

//constant integers assigned to ir remote buttons from how the reciever reads the keypress 
const int zero = 0;
const int one = 1;
const int two = 2;
const int four = 4;
const int five = 5;
const int six = 6;
const int eight = 8;
const int nine = 9;
const int ten = 10;

//Servo Stuff
Servo lifter;
ESP32AnalogRead servoPositionFeedback;

//Ultrasonic Stuff
Rangefinder ultrasonic;
float distance;

void setup() {
  Serial.begin(9600);
  robot.initRobot();
  decoder.init();
}

void loop() {
  // Check for a key press on the remote 
  int16_t keyPress = decoder.getKeyCode(); 

  if(keyPress == zero){
  robot.blueMotorStop();
  robot.wheelStop();
  Serial.println("Robot Idle");
  robotState = ROBOT_IDLE;}

  else if(keyPress == one){
    robot.blueMotorUp();
    Serial.println("Robot Active");
    robotState = ROBOT_ACTIVE;}

  else if(keyPress == two){
    robot.blueMotorDown();
    Serial.println("Robot Lining");
    robotState = ROBOT_LINING;}

  else if(keyPress == four){
    robot.closeGripper();
    Serial.println("Robot turning, close gripper");
    robotState = ROBOT_TURNING;}

  else if(keyPress == five){
    robot.openGripper();
    Serial.println("Robot Searching, open gripper");
    robotState = ROBOT_SEARCHING;}

  else if(keyPress == six){
    robot.left_motor.startMoveFor(720,90);
    robot.right_motor.startMoveFor(720,90);
    Serial.println("Robot Feasting,");
    robotState = ROBOT_FEASTING;}

  else if (keyPress == eight){
    robot.turnLeft();
    Serial.println("uTurn");
    robotState = UTURN;}

  else if (keyPress == nine){
    robot.backUp();
    Serial.println("backup");
    robotState = BACKUP;}
  else if (keyPress ==ten){
    robot.rightTurn();

    robotState = RIGHTTURN;
  }
}
