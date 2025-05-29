//Line follower robot

//include libraries
#include <SD.h>
#include <SPI.h>


// Define the chip select pin for the SD card
const int chipSelect=10;

// Define the pins for the infrared sensors
#define left1 A0
#define left2 A1
#define middle A2
#define right1 A3
#define right2 A4


//Define motors
const int ENA = 5; // PWM pin for Motor A for speed control
const int IN1 = 8;  // IN1 pin for Motor A
const int IN2 = 9;  // IN2 pin for Motor A
#define s 150 //base speed
#define t 225//turning speed

const int ENB = 3; // PWM pin for Motor B for speed control
const int IN3 = 6;  // IN3 pin for Motor B
const int IN4 = 7;  // IN4 pin for Motor B

File dataFile;
String fileName = "IRLOG.CSV"; 





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Set the pins for the sensors
  pinMode(left1,INPUT);
  pinMode(left2,INPUT);
  pinMode(middle,INPUT);
  pinMode(right1,INPUT);
  pinMode(right2,INPUT);
  
  //Set the pins for the motors
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);


  //Intialize the chip
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)){
    Serial.println("SD card initialization failed!");
    while(1);

  }
  Serial.println("SD card initialized successfully.");

  //Open the file and create headings
  dataFile = SD.open(fileName, FILE_WRITE);
  if (dataFile){
    if (dataFile.size()==0){
      dataFile.println("Time(ms), Infrared reading");
    }
    dataFile.close();
    Serial.println("Data file ready.");

  } else {
    Serial.println("Error opening data file!");

  }

}


void loop() {
  // put your main code here, to run repeatedly:

    // Read the current time and sensor values
  unsigned long currentTime = millis();
  int l1 = digitalRead(left1);
  int l2 = digitalRead(left2);
  int mid = digitalRead(middle);
  int r1 = digitalRead(right1);
  int r2 = digitalRead(right2);


  // Print to Serial Monitor
  Serial.print("Time: ");
  Serial.print(currentTime);
  Serial.print(" | IR Readings: ");
  Serial.print(l1); Serial.print(" ");
  Serial.print(l2); Serial.print(" ");
  Serial.print(mid); Serial.print(" ");
  Serial.print(r1); Serial.print(" ");
  Serial.println(r2);
  
  // Open file and log data
  dataFile = SD.open(fileName, FILE_WRITE);
  
  if (dataFile) {
    dataFile.print(currentTime);
    dataFile.print(",");
    dataFile.print(l1);
    dataFile.print(",");
    dataFile.print(l2);
    dataFile.print(",");
    dataFile.print(mid);
    dataFile.print(",");
    dataFile.print(r1);
    dataFile.print(",");
    dataFile.println(r2);
    dataFile.close();
  } else {
    Serial.println("Error opening data file!");
  }
  


  //If middle detect something and other detect nothing : go forward
  if((!analogRead(left1)==0 || !analogRead(left2)==0 )  && digitalRead(middle)==0 && ( !analogRead(right1)==0 || !analogRead(right2)==0)) {
    moveForward();
  }
  

  //If right is on white and left is on black : turn right
  else if ((digitalRead(left1)==0 || digitalRead(left2)==0 )&& (!analogRead(right1)==0 || !analogRead(right2)==0)){
    turnRight();
  }

  //If left is on white and right in on black : turn left
  else if ((!analogRead(left1)==0 || !analogRead(left2)==0) && (digitalRead(right1)==0 || digitalRead(right2)==0)){
    turnLeft(); 
  }
  // Wait before next reading
  delay(50);
}
//Activate both motors to move forward
void moveForward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, s); // Adjust speed here

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, s); // Adjust speed here

}


//Activate the right motor forward and the left motor backward to turn left
void turnLeft(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, t); // Adjust speed here

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, t); // Adjust speed here
}


//Activate the left motor forward and the right motor backward to turn right
void turnRight(){

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, t); // Adjust speed here

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, t); // Adjust speed here

}

//Function to stop both motors if needed
void stopMotors(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0); // Stop motor

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0); // Stop motor

}

