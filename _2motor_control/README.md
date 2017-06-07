# 2-Wheeled robot control with Arduino+ROS 
Simple example code and instruction will be provided for DC motor control with arduino and ros. 'teleop_twist_keyboard' package and 'rosserial_python' package is used for controlling remotely.
  
# Pre-requisite
1. Jetson TX1 board x 1ea
2. Aruino UNO R3 x 1ea
3. Motor Shield 2ch x 1ea
4. DC motor x 2ea
5. External battery (motor & jetson board)
6. Wireless keybord & mouse

# Step by step installation
1. Assemble UNO and motor shield
2. Wiring power lines 
3. Wiring communication lines
4. Upload 2motor_control.ino file to arduino
5. Open terminal and command
```
$ roscore
```
6. Open new termainal and command (keyboard control)
```
$ rosrun teleop_twist_keyboard teleop_twist_keyboard.py
```
7. Open third terminal and command (assume that arduino port: '/dev/ttyACM0')
```
$ rosrun rosserial_python serial_node.py /dev/ttyACM0
```
