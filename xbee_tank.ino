#define FORWARD 0
#define LEFT 0
#define BACK 1
#define RIGHT 1

#include <SoftwareSerial.h>

SoftwareSerial xbee(6, 7); // RX, TX

void _move(int dir) {
  digitalWrite(12, dir); //Establishes direction of Channel A
  digitalWrite(13, dir); //Establishes direction of Channel B
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(3, 255);    //Spins the motor on Channel B at full speed
  analogWrite(11, 255);   //Spins the motor on Channel B at full speed
  
  Serial.println(dir);
}


void _turn(int dir) {
  int revDir =  dir ^ 1;
  digitalWrite(12, dir); //Establishes direction of Channel A
  digitalWrite(13,  revDir); //Establishes opposite direction of Channel B
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(3, 255);    //Spins the motor on Channel B at full speed
  analogWrite(11, 255);   //Spins the motor on Channel B at full speed
  
   Serial.println(dir);
}

void _stop() {
  digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  digitalWrite(8, HIGH);  //Engage the Brake for Channel B 
}

void setup() {
  delay(3000);
  Serial.begin(9600);  // For debugging
  xbee.begin(9600);  // For xbee serial
  Serial.println("Serial enabled");
  xbee.println("xbee serial enabled");
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  
}

void loop(){

  if (xbee.available()) {
    int cmd = xbee.read();
    switch (cmd) {
      case 'w':
        _move(FORWARD);
        Serial.print('w'); 
        break;
      case 's':
        _move(BACK);
         Serial.print('s');
        break;
      case 'a':
        _turn(LEFT);
         Serial.print('a');
        break;
      case 'd':
        _turn(RIGHT);
        Serial.print('d');
        break;
    }
    xbee.flush();
    delay(100);
  }
  else {
    _stop();
    //Serial.println("stop");
    delay(10);
  }
}

