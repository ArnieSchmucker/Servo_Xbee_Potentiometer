//Note: SoftwareSerial does not work due to timer issues.



#include <Servo.h>
//#include <SoftwareSerial.h>
//SoftwareSerial XBee(2,3);
int servoPin = 9;
Servo myServo;
bool startReading = false;
bool endReading = false;
char incomingByte;
char msg[3];
byte index = 0;
int pos;
int startPos;

void setup() {
  Serial.begin(9600);
  //XBee.begin(9600);
  myServo.attach(servoPin);
  startPos = readXBee();
}

void loop() {
  readXBee();
  //Serial.println(pos);
  myServo.write(pos);
  filter(startPos);
  startPos = pos;
  delay(10);
}

int readXBee() {
  while(Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == '<') {
      //Serial.println(incomingByte);
      startReading = true;
      index = 0;
      msg[index] = '\0';
    }
    else if (incomingByte == '>') {
      //Serial.println(incomingByte);
      endReading = true;
      break;
    }
    else if (index < 4) {
      msg[index] = incomingByte;
      index++;
      msg[index] = '\0';
    }
  }

  if(startReading && endReading) { 
    pos = atoi(msg);
    //Serial.println(pos);
    index = 0;
    msg[index] = '\0';
    startReading = false;
    endReading = false;
  } 
  return pos;
}

int filter(int lastPos) {
  float alpha = 0.6;
  pos = alpha * pos + (1-alpha) * lastPos;
  return pos;
}


