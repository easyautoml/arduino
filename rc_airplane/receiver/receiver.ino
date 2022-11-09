#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


// 1. Radio Setting
RF24 radio(9, 10);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001";

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;


// 2. Joy Stick Setting
struct JoyStick{
  byte x;
  byte y;
};

struct Spin{
  byte spin1;
  byte spin2;
};

struct Data{
  JoyStick joy_stick_1;
  JoyStick joy_stick_2;
  Spin spin;
};

// 3. Motor Setting
Servo MOTOR; 
#define MOTOR_PIN 6  // PWM PIN

// 4. Servo setting
Servo SERVO1, SERVO2;
#define SERVO1_PIN 3 // PWM PIN
#define SERVO2_PIN 5 // PWM PIN

void setup() 
{
  Serial.begin(9600);

  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver

  MOTOR.attach(MOTOR_PIN, 1000, 2000);
  SERVO1.attach(SERVO1_PIN);
  SERVO2.attach(SERVO2_PIN); 
}

void motor_control(int rotary_value){
  /* 
   *  MOTOR GET VALUE FROM 0 - 180.
   *  NEED PMW PINOUT TO CONTROL SERVO. ARDUINO MINI PMW OUTPUT PIN : D3, D5, D6, D9, D10, D11
  */
  rotary_value = map(rotary_value, 0, 255, 0, 180);

  // Limit motor performance
  if (rotary_value>170){
    rotary_value = 170;
  }
  
  MOTOR.write(rotary_value); 
}


void servo_control(JoyStick joy_stick, Spin spin){  
  /* 
   *  MINI SERVO ANGLE FROM 30 - 180. NOT FROM 0 - 180
   *  NEED PMW PINOUT TO CONTROL SERVO. ARDUINO MINI PMW OUTPUT PIN : D3, D5, D6, D9, D10, D11
  */
  
  //  byte servo_1_start_point = map(spin.spin1, 0, 255, 0, 140);
  //  byte servo_1 = map(joy_stick.y, 0, 255, 30 + servo_1_start_point, 180);
  //  byte servo_2 = map(joy_stick.y, 0, 255, 30 + spin.spin2, 180);
  //  

  byte left_right = map(joy_stick.y, 0, 255, 30, 180);

  joy_stick.x = joy_stick_convert_direction(joy_stick.x);
  
  byte up_down = map(joy_stick.x, 0, 255, 30, 180);
  
  byte midle_place = 124;

  Serial.print(" X : ");
  Serial.print(joy_stick.x);

  Serial.print(" Y : ");
  Serial.print(joy_stick.y);
  
  if (joy_stick.y != midle_place){
    // Turn Left and Right
//    Serial.println(left_right);
  
    SERVO1.write(left_right);
    SERVO2.write(left_right);
  }
  else{
    // Up and down   
    SERVO1.write(up_down);

   up_down = map(up_down, 30, 180, 180, 30);

   Serial.print(" UP DOWN : ");
   Serial.println(joy_stick.y);
  
    SERVO2.write(up_down);
  }
}


void loop()
{
  
  Data data;
  data.joy_stick_2.x = 0;
  
  if (radio.available()) {
    radio.read(&data, sizeof(Data)); // Read the whole data and store it into the 'data' structure
    lastReceiveTime = millis(); // At this moment we have received the data
  }

  // Revert derection for joy stick 2. Which used for motor
  data.joy_stick_2.x = joy_stick_convert_direction(data.joy_stick_2.x);
  data.joy_stick_2.x = joy_stick_convert_start_point_midle(data.joy_stick_2.x);
  
  
  // Check whether we keep receving data, or we have a connection between the two modules
  currentTime = millis();
  boolean lost_signal = currentTime - lastReceiveTime > 1000;
  
  if ( lost_signal ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
      Serial.println("LOSS SIGNAL ");
      motor_control(0);
  }
  else
  {
      servo_control(data.joy_stick_1, data.spin);
      motor_control(data.joy_stick_2.x);
  }
}

byte joy_stick_convert_direction(byte value){
  return map(value, 0, 255, 255, 0);
}

byte joy_stick_convert_start_point_midle(byte value){
  
  byte midle_point = 137;
  
  if (value < midle_point){
    return 0;
  }
  return map(value, midle_point, 255, 0, 255);
}
