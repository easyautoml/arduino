/*
    DIY Arduino based RC Transmitter Project
              == Receiver Code ==
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>


// 1. Other init
int count = 0;

// 2. Define variable for Radio Module
RF24 radio(8, 10);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001"; // Address


// 3. Define variable for joy stick 
// Init for JoyStick
#define STICK1_X  A0 // Arduino pin connected to VRX pin
#define STICK1_Y  A1 // Arduino pin connected to VRY pin

#define STICK2_X  A2 // Arduino pin connected to VRX pin
#define STICK2_Y  A3 // Arduino pin connected to VRY pin

// 4. Define variable for spin control
#define SPIN1 A4
#define SPIN2 A5

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

void setup() 
{
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  
}

void send_data(){

  struct Data data;
  data.joy_stick_1 = read_joy_stick(1);
  data.joy_stick_2 = read_joy_stick(2);
  data.spin = read_spin();

  Serial.print(data.spin.spin1);
  Serial.print(" SPIN 2  : B" );
  Serial.println(data.spin.spin2);
  
  radio.write(&data, sizeof(Data));
}

JoyStick read_joy_stick(int stick_num){

  struct JoyStick stick;

  switch (stick_num){
    case 1:
      stick.x =  map(analogRead(STICK1_X), 0, 1023, 0, 255);
      stick.y =  map(analogRead(STICK1_Y), 0, 1023, 0, 255);
      break;
    case 2:
      stick.x =  map(analogRead(STICK2_X), 0, 1023, 0, 255);
      stick.y =  map(analogRead(STICK2_Y), 0, 1023, 0, 255);
      break;
  }
  return stick;
}

Spin read_spin(){
  struct Spin spin;
  spin.spin1 = map(analogRead(SPIN1), 0, 1023, 0, 255);
  spin.spin2 = map(analogRead(SPIN2), 0, 1023, 0, 255);

  return spin;
}

 
void loop()
{
  send_data();
}