/*************************************************************
Motor Shield 2-Channel DC Motor Demo with ros integration

original by Randy Sarafan
modified by Kyungho Yoo
updated 2017.06.07

For more information see:
https://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/

*************************************************************/
#include <ros.h>
#include <geometry_msgs/Twist.h> 

ros::NodeHandle nh;

void cbKeyTeleop( const geometry_msgs::Twist& msg){
  if(msg.linear.x > 0) // received forward command
  {    
    //Motor A forward @ half speed
    digitalWrite(12, LOW); //Establishes forward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 123);   //Spins the motor on Channel A at half speed

    //Motor B backward @ half speed
    digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 123);    //Spins the motor on Channel B at half speed
  }  
  else if(msg.linear.x < 0) // received backward command
  {         
    //Motor A backward @ half speed
    digitalWrite(12, HIGH); //Establishes forward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 123);   //Spins the motor on Channel A at half speed

    //Motor B forward @ half speed
    digitalWrite(13, LOW);  //Establishes backward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 123);    //Spins the motor on Channel B at half speed
  }
  else if(msg.angular.z > 0) // received pivot(CCW) command
  {
    //Motor A forward @ half speed
    digitalWrite(12, LOW); //Establishes forward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 123);   //Spins the motor on Channel A at half speed

    //Motor B backward @ half speed
    digitalWrite(13, LOW);  //Establishes backward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 123);    //Spins the motor on Channel B at half speed
  } 
  else if(msg.angular.z < 0) // received pivot(CW) command
  {
     //Motor A forward @ half speed
    digitalWrite(12, HIGH); //Establishes forward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 123);   //Spins the motor on Channel A at half speed

    //Motor B backward @ half speed
    digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 123);    //Spins the motor on Channel B at half speed
  }  
  else if(msg.linear.x == 0 && msg.angular.z == 0) // received break command
  {
    digitalWrite(9, HIGH);  //Engage the Brake for Channel A
    digitalWrite(8, HIGH);  //Engage the Brake for Channel B
    
    delay(100);
  }

}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &cbKeyTeleop );

void setup() {
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  
  Serial.begin(57600); // ros-teleop-twist-keybord defualt baud-rate

  delay(1000);
  
  nh.getHardware()->setBaud(57600);
  nh.initNode();
  nh.subscribe(sub);  
}

void loop(){  
  nh.spinOnce();
  delay(10);   // every 10ms 
}

