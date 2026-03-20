# Fire-Fighting-Robot
An autonomous fire detecting movable bot that can extinguish fires in its proximity.

The FireBot is an autonomous fire-fighting robot that operates using an Arduino-based control system.
It moves using DC motors driven by an L298N motor driver and continuously scans its surroundings using an ultrasonic sensor to avoid obstacles.
When the robot detects a fire using a flame or temperature sensor, it stops at a safe distance and activates a water pump through a relay module to extinguish the fire.
A servo mechanism can be used to direct the water spray toward the flame.
The system is powered by a battery, with a buck converter providing stable 5V supply to the Arduino and sensors.
Overall, the FireBot integrates sensing, motion control, and actuation to automatically detect, navigate, and suppress fire in small environments.
