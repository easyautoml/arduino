#include<Servo.h>

Servo lr_servo;
Servo upd_servo;

const int MOVE_SPEED =1;

const int LR_PORT = 3;
const int UPD_PORT = 5;

int upd_servo_loc=10;
int lr_servo_loc=105;

int index = 0;
char strValue[10]; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lr_servo.attach(LR_PORT);
  upd_servo.attach(UPD_PORT);

  lr_servo.write(lr_servo_loc);
  upd_servo.write(upd_servo_loc);
}


void down(){
  if (upd_servo_loc < 160 - MOVE_SPEED){    
    upd_servo_loc = upd_servo_loc + MOVE_SPEED;
    upd_servo.write(upd_servo_loc);
  }
}

void up(){
  if (upd_servo_loc > 0 + MOVE_SPEED){
    upd_servo_loc = upd_servo_loc - MOVE_SPEED; 
    upd_servo.write(upd_servo_loc);
  }
}

void left(){
  if (lr_servo_loc < 160 - MOVE_SPEED){   
    lr_servo_loc = lr_servo_loc + MOVE_SPEED;
    lr_servo.write(lr_servo_loc);
  }
}

void right(){
  if (lr_servo_loc < 160 + MOVE_SPEED){
    lr_servo_loc = lr_servo_loc - MOVE_SPEED;   
    lr_servo.write(lr_servo_loc);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()){
    switch (Serial.read()){
      case '1': up();
                break;
      case '2': down();
                break;
      case '3': left();
                break;
      case '4': right();
                break;
      default: break;
      
    }
  } 
        
}
