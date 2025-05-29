# Arduino Project : Line Follower Robot with Data Logging

## Introduction:

The project that I decided to do is a line follower robot that is able to data log the sensory data it receives. By doing so, we can optimize certain parts of the robot. For example, the angle of the sensor can be adjusted so that it is able to see further in front of it and thus make tighter corners. The project will include a summary of the construction of the robot, an explanation of the circuit created, the code that the robot is using and the logic behind it as well as some challenges faced during the realization of the robot. The goal was to introduce and immerse myself into the robotics world to better understand its basics as well as to further my programming skills. 

## Project description:

### Objective:

The goal of the project is to create a robot capable of using multiple sensors to understand the environment surrounding it and to thus be able to, in this case, follow a line. In order to further enhance the robot and its efficiency later on, it has data logging capabilities. The main objective was to create a base for myself to use later on when I will be working on more complex projects and to thus already have basic knowledge about hardware components as well as software development skills.

### Inspiration:

I first saw a line follower robot in primary school whilst my brother was searching for a suited place for his higher education. As I was already a creative kid, already being passionate about LEGOs, I wanted to try building one for myself. Unfortunately, the project never came to fruition as I did not even know where to start. This semester, I had taken a programming course as well as the engineering physics class. In it, we made another robot using ultrasonic sensors to detect its relative distance to a wall. With all the new knowledge I had acquired, I wanted to retry building it, this time my own way. I mainly took inspiration from projects found on YouTube (notably from Lee Curiosity) and from a hackathon organized by William Osman. 

### Design and Planning:

From the beginning, I already knew that I wanted to use DC motors instead of servos or any another mean of propulsion. I considered them more reliable, and I wanted to try my hand at soldering. From there on, I gave myself an idea of the track I wanted to make. Some of its challenging parts were inspired by the hackathon previously mentioned. From this, I knew that I needed an array of IR sensors since I needed a wider range of detection whilst still being divided into sperate sensors. The L298N motor driver is quite commonly used in these types of robots since it would be able to control the speed and direction of the motors. The assembly process was very straight forward as I had previous experience with the ultrasonic sensor robot.  

## Implementation:

### Hardware setup:

For the hardware setup, I used an Arduino Uno, a L298N motor driver module, 4 DC motors, 2 battery packs each containing 4 AA batteries, an infrared sensor array, a micro SD card reader, an on-off switch, and finally a breadboard. 

!(circuit_image.png)
https://app.cirkitdesigner.com/project/e6c43994-44c0-48aa-b571-ad6e6937268a

### Software development:

For the code, I developed 3 scenarios. They are each important for the basic functionality of the robot which is to follow the line. The first case is that if the sensor in the middle sees black while the others do not, it means the robot should go straight. If the left sensor sees white while the right one sees black, it means the robot should turn to the right. The same can be said about the left. 

```c++
  //If middle detect something and other detect nothing : go forward
  if((!analogRead(left1)==0)  && digitalRead(middle)==0 && ( !analogRead(right2)==0)) {
    moveForward();
  }
  

  //If right is on white and left is on black : turn right
  else if (digitalRead(left1)==0 && !analogRead(right2)==0){
    turnRight();
  }

  //If left is on white and right in on black : turn left
  else if (!analogRead(left1)==0 && digitalRead(right2)==0 ){
    turnLeft(); 
  }
  delay(50);
```



I first tried to use the Adafruit Motors library (AFMotor), but I realised that it would be simpler and more customizable easily if I simply used pinModes as well as digital and analog writing. Another improvment that I made was that I simply made functions to move forward, left, and right. It may seem obvious to do so, but I had not coded very much in C++ prior to this project, so I was very unfamiliar with it. 

```c++
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

```
For the data logging part of the code, I reused the code showed in class during the relevant lab. I made a few changes to include 5 sensors and to get the readings from the Infrared sensor instead of distance from an Ultrasonic sensor. I also changed the formatting a bit to fit my case scenario better.

```c++
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
```

### Sensor Documentation:

