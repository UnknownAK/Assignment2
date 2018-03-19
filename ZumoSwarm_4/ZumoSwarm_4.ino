#include <ZumoMotors.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <EEPROM.h>

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;
char zumoId = 4;
char zumoAll = 'z';
bool isActive4 = false;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);  
  
  delay(20);

}

void loop() {
  if(Serial.available()){
  char command = Serial.read();

    if(command == '4'){
//      Serial.println("pressed 4");
//      Serial.println("connected to 4"); 
      isActive4 = true;
      delay(15);     
      
//      Serial.println("Zumo 4 active");
    }
    if(command == '3'){
//      Serial.println("pressed 3");
//      Serial.println("Not connected to 4");
      delay(15); 
      isActive4 = false;
//      Serial.println("zumo 4 deactive");
    }
    if(command == '2'){
//      Serial.println("pressed 2");
//      Serial.println("Not connected to 4");
      delay(15); 
      isActive4 = false;
//      Serial.println("zumo 4 deactive");
    }
    if(command == zumoAll){
//      Serial.println("connected to all");
      delay(15); 
      isActive4 = true;
    }
    if(isActive4 != false){
      if (command == 'w') {
        motors.setSpeeds(100, 100);
//        Serial.println("Forward");
      }

      if (command == 'a') {
        motors.setSpeeds(100, 0);
//        Serial.println("Turn Left");
      }

      if (command == 's') {
        motors.setSpeeds(-100, -100);
//        Serial.println("Backwards");
      }

      if (command == 'd') {
        motors.setSpeeds(0, 100);
//        Serial.println("Turn Right");
      }
    
      if (command == 'f') {
        motors.setSpeeds(0, 0);
//        Serial.println("Stop");
      }
    }
  }
}

