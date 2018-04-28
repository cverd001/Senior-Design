# SunE-Bot

## Project Description
This is a design for a basic autonomous robot capable of repositioning itself to an optimal sun-lit location to self-sustain off solar power. This is meant to be a basic core – an ideal “charging mode” function which any mobile solar-powered robot can implement. This functionality is geared towards rover-type robots which operate without the presence of humans. Robots with this self-sustaining design are free to explore and gather data on their own without any assistance. By developing the basic infrastructures of a light-search algorithm and solar-charging circuitry, our design can be applied to countless autonomous robots that exist and will be developed in the future. 

This design addresses current issues in renewable resource usage and in manpower. Development of this design implements and promotes a clean and reusable energy resource while also leaving the taxing, repetitive tasks of data-gathering to the robots. 

## Specification
![Block Diagram](https://i.imgur.com/wgcb6Uj.png)

The majority of the algorithms and computation are performed on a Teensy 3.6 microcontroller (Arduino variant) which sends signals out to all other peripherals. Light sensors in the form of photoresistors (4) and a solar panel send input to the Teensy, which uses the data in its algorithm to find an optimal bright location. The Teensy controls 2 motor drivers, which each control 2 motors to reposition the entire mobile car. Other sensors involved in repositioning include motor encoders, an Inertial Measurement Unit (IMU),  and an action camera attached to a Raspberry Pi microcontroller. The solar panel is also attached to a charge controller and voltage regulator to constantly charge a battery at all times. Configuration of the Teensy and Raspberry Pi are done in C++ and Python, respectively. 

The robot contains two different algorithms to detect light. The first is a Grid Search Algorithm (GSA). The robot traverses a set grid (x * y) and periodically reads voltages through its sensors. After the entire grid has been travelled through, the robot swivels and returns to the spot that returned the highest solar reading. The other algorithm is a Computer Vision Algorithm (CVA). This method has the robot spin in place and has the camera attached check for any bright spots before moving in that general bright direction. This method does not require the motors to be in use for as long, but requires more voltage to power the Raspberry Pi which in turn powers the camera. 

At start up, the user has the option of selecting the algorithm to use, as well as how big of a grid to set if the GSA is selected. This is done through turning of the back-left wheel and covering of the front photoresistors. 

A demo video of this project can be found [here.](https://www.youtube.com/watch?v=_fC8kR_6XM4)

## Authors
SunE-Bot was developed by [Christopher Verdegan](https://www.linkedin.com/in/christopher-verdegan-440b85119), [James Thi](https://www.linkedin.com/in/james-thi) and [Yidi Wang](https://www.linkedin.com/in/yidi-wang-315649119).

## References 
1. [Get Start with IMU (6 DOF)](https://create.arduino.cc/projecthub/Aritro/getting-started-with-imu-6-dof-motion-sensor-96e066)
2. [K66 Sub-Family Reference Manual](https://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/K66P144M180SF5RMV2.pdf)
3. [TP-4056](https://dlnmh9ip6v2uc.cloudfront.net/datasheets/Prototyping/TP4056.pdf)
4. [CalibrateMPU6050.](https://github.com/kkpoon/CalibrateMPU6050)
5. [Mobile Sun-Seeking Robot.](http://www.instructables.com/id/Mobile-Sun-Seeking-Robot/)
6. [LSM303 Accelerometer + Compass Breakout](https://learn.adafruit.com/lsm303-accelerometer-slash-compass-breakout?view=all)
7. [L298N H Bridge](https://www.sparkfun.com/datasheets/Robotics/L298_H_Bridge.pdf)
8. [MPU6050](https://store.invensense.com/datasheets/invensense/MPU-6050_DataSheet_V3%204.pdf)
9. [Raspberrypi](https://www.raspberrypi.org/documentation/hardware/computemodule/RPI-CM-DATASHEET-V1_0.pdf)
