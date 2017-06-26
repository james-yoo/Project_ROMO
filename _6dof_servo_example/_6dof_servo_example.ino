/************************************************************* 
6 DOF robo-arm (dfrobot-ROB0036) control sample code 
  
original by Kyungho Yoo 
updated 2017.06.20   
*************************************************************/ 

#include <Servo.h> 

#define DOF_ARM 6

Servo servoBase;
Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3;
Servo servoMotor4;
Servo servoGripper;

String input_msg;
int number_msg;
int target_position[DOF_ARM] = {90};
int angle_position[DOF_ARM] = {90};

void servo_move(int motor, int target[], int current[]); // control servo motor
int stringSplit(String input, char delim, int params[], int number); // parse input string

void setup() {
  // put your setup code here, to run once:
  
  // start serial port at 9600 bps:
  Serial.begin(9600);
  Serial.print("Start serial connection..");
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("finished.\r\n");
  
  // pin 8: base
  // pin 9: motor1
  // pin 10: motor2
  // pin 11: motor3
  // pin 12: gripper1
  // pin 13: gripper2  
  Serial.print("Start servo motor pin mapping..");
  servoBase.attach(8); //attach it to pin 8
  servoMotor1.attach(9); //attach it to pin 9
  servoMotor2.attach(10); //attach it to pin 10
  servoMotor3.attach(11); //attach it to pin 11
  servoMotor4.attach(12); //attach it to pin 12
  servoGripper.attach(13); //attach it to pin 13
  Serial.print("finished.\r\n");

  Serial.print("Start servo motor calibration..");  
  // put your main code here, to run repeatedly: 
  servoBase.write(90); //set servo angle, should be from 0-180 
  delay(500);
  servoMotor1.write(90); //set servo angle, should be from 0-180 
  //angle_position = 90;  
  delay(500);
  servoMotor2.write(90); //set servo angle, should be from 0-180 
  delay(500);
  servoMotor3.write(90); //set servo angle, should be from 0-180 
  delay(500);
  servoMotor4.write(90); //set servo angle, should be from 0-180 
  delay(500);
  servoGripper.write(90); //set servo angle, should be from 0-180 
  delay(500);
  Serial.print("finished.\r\n");

  Serial.print("Start loop..\r\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  input_msg = "";
  number_msg = 0;
  
  while(Serial.available() > 0) {
    delay(5);
    char str = Serial.read();
    input_msg += str;
  }
    
  if(input_msg.length() > 0) {
    Serial.println(input_msg);
    // parse the line
    number_msg = stringSplit(input_msg,',', target_position, DOF_ARM);
    if(number_msg == (int) DOF_ARM){
       // print the extracted paramters
      for(int i=0; i < number_msg; i++) {
          //Serial.println(angle_position[i]);
          servo_move(i, target_position, angle_position);
      }
    }
    else
    {
      Serial.println("error while parsing message");
    }  

  }
 
   delay(1);
}

void servo_move(int index, int target[], int current[])
{
   int diff = target[index] - current[index];  

   while(target[index] != current[index]){
    if(diff > 0){
      current[index] += 1;
    }
    else{
      current[index] -= 1;
    }
    
    if(index == 0){
      servoBase.write(current[index]);
    }else if(index == 1){
      servoMotor1.write(current[index]);
    }
    else if(index == 2){
      servoMotor2.write(current[index]);
    }
    else if(index == 3){
      servoMotor3.write(current[index]);
    }
    else if(index == 4){
      servoMotor4.write(current[index]);
    }
    else if(index == 5){
      servoGripper.write(current[index]);
    }
    //angle_position = current;
    delay(20);
   
  }
}

int stringSplit(String sInput, char cDelim, int iParams[], int iMaxParams)
{
    int iParamCount = 0;
    int iPosDelim, iPosStart = 0;

    do {
        // Searching the delimiter using indexOf()
        iPosDelim = sInput.indexOf(cDelim,iPosStart);
        if (iPosDelim > iPosStart) {
            // Adding a new parameter using substring() 
            iParams[iParamCount] = sInput.substring(iPosStart,iPosDelim).toInt();
            iParamCount++;
            // Checking the number of parameters
            if (iParamCount >= iMaxParams) {
                return (iParamCount);
            }
            iPosStart = iPosDelim + 1;
        }
    } while (iPosDelim >= 0);
    if (iParamCount < iMaxParams) {
        // Adding the last parameter as the end of the line
        iParams[iParamCount] = sInput.substring(iPosStart).toInt();
        iParamCount++;
    }

    return (iParamCount);
}


