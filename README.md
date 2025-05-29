# Arduino Line Follower Project

This project uses an array of Infrared sensors to make decisions based on its readings. It is able to accurately follow a line using an Arduino, the sensor array and 4 DC motors. It is also capable of saving those readings in a SD card and is thus able to datalog. 

## About This Project

This project follows a line using Infrared sensors and then stores the data into a SD card for later use. 1 means the sensor detects something whilst 0 means the sensor does not detect anything.

## Features

- Infrared detection
- Following a line
- Data logging to SD card
- Serial monitor output
- CSV file format for easy analysis

## Hardware Requirements

- Arduino Uno board
- 4x DC motors
- L298N dual H bridge motor driver module
- 2x 4 Battery boxes
- 5 Sensor array board using 5 TCRT5000L IR sensors
- SD card module
- SD card (formatted as FAT16 or FAT32)
- Jumper wires
- On-Off switch
- Breadboard

## Software Requirements

- Arduino IDE 2.3.6
- Libraries :
    - SD
    - SPI

## Code Explanation



## Files

- `datalogger.ino`: Main Arduino sketch for the data logger
- `WIringLineFollower.png`: Connection diagram for all components
- `README.md`: This documentation file

## Wiring Instructions

![alt text](circuit_image(2).png)
- This is a link containing the sketch:
https://app.cirkitdesigner.com/project/e6c43994-44c0-48aa-b571-ad6e6937268a

### SD Card Module:
- CS → Arduino Pin 10
- MOSI → Arduino Pin 11
- MISO → Arduino Pin 12
- SCK → Arduino Pin 13
- VCC → + Breadboard
- GND → - Breadboard

### IR Sensor Array (TCRT5000L):
- Out1 → Arduino A0
- Out2 → Arduino A1
- Out3 → Arduino A2
- Out4 → Arduino A3
- Out5 → Arduino A4
- VCC → + Breadboard 
- GND → - Breadboard

### L298N motor driver module :

- Out1 → - For both left side motors
- Out2 → + For both left side motors
- Out3 → + For both right side motors
- Out4 → - For both right side motors

- In1 → Arduino 9
- In2 → Arduino 8
- In3 → Arduino 7
- In4 → Arduino 6

- 12V → both positives of the battery boxes
- GND → - Breadboard and negative of both battery boxes
- 5V → + Breadboard

### Arduino Uno :

- 5V → + Breadboard
- GND → - Breadboard

- All aforementioned connections also apply


## How to Use

1. Connect the hardware as shown in the wiring diagram
2. Format an SD card as FAT16 or FAT32
3. Insert the SD card into the module
4. Upload the `linefollower.ino` sketch to your Arduino
5. Open the Serial Monitor (9600 baud) to view real-time readings to make sure the sensor is working
6. Data will be logged to IRLOG.CSV on the SD card
7. Disconnect the robot from your computer and turn it on (do not forget to reset the Arduino)
8. After collecting data, turn off the robot and remove the SD card 
9. Analyze the CSV file in a spreadsheet program such as Excel

