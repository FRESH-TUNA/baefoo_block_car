#include "RemotePuppy.h"

PuppyRC::PuppyRC(uint8_t receivePin, uint8_t transmitPin, uint8_t ia1,uint8_t ib1,uint8_t ia2,uint8_t ib2) {
  btSerial = new SoftwareSerial(receivePin, transmitPin);
  leftSpeed = ia1;
  leftWheel = ib1;
  rightSpeed = ia2;
  rightWheel = ib2;
  pinMode(leftSpeed, OUTPUT);
  pinMode(leftWheel, OUTPUT);
  pinMode(rightSpeed, OUTPUT);
  pinMode(rightWheel, OUTPUT);
  setSpeed(L_SPEED,R_SPEED);
}

void PuppyRC::begin(long baudrate) {
  btSerial->begin(baudrate);
}

void PuppyRC::setSpeed(uint8_t l_speed_, uint8_t r_speed_ ) {
  lspeed = l_speed_;
  rspeed = r_speed_;
}


void PuppyRC::run() {
  if (btSerial->available()) {
    char c = btSerial->read();

    if(c != 'S') digitalWrite(LED_RUN,HIGH);
    
    switch (c) {
      
      case 'F':
        forward();
        break;
      case 'B':
        backward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      
      /*
      case '0':
        setSpeed(0);
        break;
      case '1':
        setSpeed(25);
        break;
      case '2':
        setSpeed(50);
        break;
      case '3':
        setSpeed(75);
        break;
      case '4':
        setSpeed(100);
        break;
      case '5':
        setSpeed(125);
        break;
      case '6':
        setSpeed(150);
        break;
      case '7':
        setSpeed(175);
        break;
      case '8':
        setSpeed(200);
        break;
      case '9':
        setSpeed(225);
        break;
      case 'q':
        setSpeed(255);
        break;
       */
      default:  
        stop();
        break;
    
    }
  }
}

void PuppyRC::forward() {
  digitalWrite(leftWheel, LOW);
  analogWrite(leftSpeed, lspeed);
  digitalWrite(rightWheel, LOW);
  analogWrite(rightSpeed, rspeed);
}

void PuppyRC::backward() {
  digitalWrite(leftWheel, HIGH);
  analogWrite(leftSpeed, 0);
  digitalWrite(rightWheel, HIGH);
  analogWrite(rightSpeed, 0);
}

void PuppyRC::turnLeft() {
  digitalWrite(leftWheel, LOW);
  analogWrite(leftSpeed, lspeed);
  digitalWrite(rightWheel, HIGH);
  analogWrite(rightSpeed, 0);
}

void PuppyRC::turnRight() {
  digitalWrite(leftWheel, HIGH);
  analogWrite(leftSpeed, 0);
  digitalWrite(rightWheel, LOW);
  analogWrite(rightSpeed, rspeed);
}

void PuppyRC::stop() {
  digitalWrite(leftWheel, LOW);
  digitalWrite(rightWheel, LOW);
  analogWrite(leftSpeed,0);
  analogWrite(rightSpeed,0);

  digitalWrite(LED_RUN,LOW);
}
