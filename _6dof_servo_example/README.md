# 6DOF robot arm control example
Simple example code and instruction is provided for controlling 6-DOF robot arm(model:ROB0036) with arduino due and ros.  
  
# Pre-requisite
1. Jetson TX1 board x 1ea
2. Aruino DUE x 1ea
3. Relay & Servo Shield v2.1 x 1ea
4. 6DOF robot arm x 1ea
5. Power supply (DC 9V, 1A) x 1ea
6. Keybord & mouse

# Step by step installation
1. Assemble arduino due and servo shield
2. Wiring lines
4. Upload 6motor_control.ino file to arduino
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
