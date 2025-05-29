
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

![alt text](<circuit_image(2).png>)
https://app.cirkitdesigner.com/project/e6c43994-44c0-48aa-b571-ad6e6937268a

Figure 1 : Wiring of the robot.

### Software development:

For the code, I developed 3 scenarios. They are each important for the basic functionality of the robot which is to follow the line. The first case is that if the sensor in the middle sees black while the others do not, it means the robot should go straight. If the left sensor sees white while the right one sees black, it means the robot should turn to the right. The same can be said about the left. 

```c++
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

For the sensors, I used an array of 5 Infrared TCRT5000L. They give a value of 1 when they see any light color, for example white. They output a value of 0 if they see a darker colour such as black. In order to make the robot turn left or right, I take the output of each sensor and run them through the aforementioned scenarios. 

```c++
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
  delay(50);
```
For the setup, I simply define the pins for each sensor, in order, as left1, left2, middle, right1, and right2. The code works based on if the reading is not equal to zero (!analogRead(xsensor)==0) or if it is equal to zero (digitalRead(xsensor)==0). 

```c++
// Define the pins for the infrared sensors
#define left1 A0
#define left2 A1
#define middle A2
#define right1 A3
#define right2 A4

```

## Results:

### Analysis:

From the data gathered, we can see that the left2 sensor actually does not work. 





![image](https://github.com/user-attachments/assets/0ce6d000-847b-4173-9583-36259709fdb1)

Figure 2: Graph of the readings of the left1 sensor vs Time. We can observe when the robot is turning and when it is going straight.

![image](https://github.com/user-attachments/assets/80760cd3-4b38-47cd-8c5e-c4cd9a4629db)

Figure 3: Graph of the readings of the left2 sensor vs Time. We can observe that is does not work.

![image](https://github.com/user-attachments/assets/bf7d4131-a6da-421c-a0d9-aa9c880b11e1)

Figure 4: Graph of the readings of the middle sensor vs Time. We can determine when the robot turned based on the values of the sensor.

![image](https://github.com/user-attachments/assets/7c49a064-e699-4419-b236-a8d0aceb484e)

Figure 5: Graph of the readings of right1 vs Time. We can see that since it is on the outside, it almost never sees the line which is what is expected.

![image](https://github.com/user-attachments/assets/4d057138-e7a0-426a-886a-e0ee5a9dc8ed)

Figure 6: Graph of the readings of right2 vs Time. We can see the same thing as in Figure 5 but even more extreme since it is further out.

For more information about the data used, go into the IRLOG.csv file.

Although it might impact results based on line thickness, for the track made for the robot, the lines are big enough for just the further sensors to work. We can also determine that the turns were effectuated from 2.344s to 4.577s, from 5.890s to 7.665s, from 11.159s to 13.333s, and from 14.843s to 16.951s. Thus, the objective of producing a data logging line follower robot was effective. We can now improve the robot based on the current infrared readings. For example, we can see that the right1 sensor was working, which means that, if we had a working sensor on the other side as well, we could have made a more accurate robot, needing a line half the thickness. From the data, we can also match the timing at which turns were made to the angle of the sensor, the current one being fairly accurate. I was also able to learn a lot about robotics as well as coding in general.

### Discussion and Conclusion:

The robot had a multitude of problems. The first being that some of the motors were actually dysfunctional, thus having to replace them. We then encountered the issue of the chassis being made for robots with only 2 motors instead of 4. I had to stack some components on top of another due to that issue. Then I realized that the robot did not have enough power to run using 4-wheel drive which meant that another battery box needed to be added, thus giving even less space for other components and ultimately needing to build a platform. I also had to re-solder some motors and solder the new battery box to the on-off switch. Finally, the code made the robot run backwards and since I was using the AdaFruit motors library which does not base itself on the pins of the Arduino, I had to rewrite the motor part of the code, using pins instead of the library. I also made an original version of the track using paper that had a lot of bumps and tape leading to decreased grip for the wheels and the bends in the paper making it so the motors had to use more power, leading the robot to sometimes get stuck. To remediate this, I made a new and improved track that did not have any bends and way less tape.

To summarize, this project's purpose was to create a line following robot capable of data logging. To create the project, I used an Arduino Uno, 4 DC motors, a L298N motor driver module, a 5 Infrared sensor array, a micro SD card reader, a breadboard, a few jumper wires and finally 2 battery packs. The logic behind the robot is that if the sensors on the right and left of the robot see white, while the middle one sees black, it should go forward. If the left one sees black, while the right one sees white, it should go left. Finally, if the right sees black while the left sees white, it should turn right. For the datalogging, I am saving all the data from the sensors along with the time they were collected. From the data obtained, we can see that the left2 sensor is actually dysfunctional, but we can also see that the angle at which the sensor is placed is relatively good. The robot thus has line following and data logging capabilities which means we achieved both of our objectives.

A lot could be improved on this robot. First, if we had all of the sensors working on the array, we could functionally transform it into a maze solver provided that the maze is made of lines on the ground. I had already coded a U-turn feature prior to the construction of the robot and other case scenarios, but due to hardware limitations, they remained unused. We could also add remote control by switching on or off the automatic readjustment made using the sensors in favor of manual control. This could be made possible by using an Infrared remote and an IR receiver.  

## References:

Trudeau, Joel. “Data Logging” Dawson Virtual Lab, englab.dawsoncollege.qc.ca/interns/Intro.html#exercise-3-data-logging-see-demo. Accessed 29 May 2025. 
Pasindu, Heshan. “Heshanpasindusankalpa/Basic-Arduino-Line-Following-Robot.” Basic Line Following Robot, github.com/heshanpasindusankalpa/Basic-Arduino-Line-Following-Robot. Accessed 29 May 2025. 

## Acknowledgements:

Thank you to Joel Trudeau for setting up the Internship and giving me the opportunity to make the robot as well as always being there to help and providing the ressources needed.
Thank you to Dawson College for giving the funding needed for all material needs.
