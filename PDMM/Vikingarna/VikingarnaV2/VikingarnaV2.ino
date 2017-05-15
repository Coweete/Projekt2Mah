#include <Servo.h>

Servo myservo;
#define PWM_B  11
#define Dir_b  13
#define Brake  8
#define CurSen  A1
#define stopTop  2
#define stopBot  4
#define servoPin  6

int currentState = 1,nextState = 0;
void setup() {
  //defines input output
  pinMode(Dir_b, OUTPUT);
  pinMode(Brake,OUTPUT);
  pinMode(stopTop, INPUT_PULLUP);
  pinMode(stopBot, INPUT_PULLUP);
  
  myservo.attach(servoPin);
  myservo.write(0);

  digitalWrite(Dir_b,HIGH);
  digitalWrite(Brake,HIGH);
  analogWrite(PWM_B,255);
  digitalWrite(Brake,LOW);

  Serial.begin(9600);
  Serial.println("Arduino Start");
}

void loop() {
  
  switch(currentState){
    case 1:
      Serial.println("START 1");
      //Serial.println()
      if(digitalRead(stopTop) == LOW){
        Serial.println("Brake high");
        digitalWrite(Brake,HIGH);
        nextState = 2;
      }else{
        Serial.println("Brake LOW");
        digitalWrite(Brake,LOW);
        nextState = currentState;
      }
      break;
      case 2:
        Serial.println("State 2");
        myservo.write(0);
        delay(
        if(digitalRead(stopTop) == LOW){
          digitalWrite(Dir_b,LOW);
          digitalWrite(Brake,LOW);
          nextState = 3;
        }else{
          nextState = currentState;
        }
      break;
      case 3:
        Serial.println("State 3");
        if(digitalRead(stopBot) == LOW){
          digitalWrite(Brake,HIGH);
          nextState = 4;
        }else{
          nextState = currentState;
        }
      break;
      case 4:
      Serial.println("State 4");
      if(digitalRead(stopBot) == LOW){
        myservo.write(180);
        delay(10);
        digitalWrite(Dir_b,HIGH);
        digitalWrite(Brake, LOW);
        nextState = 1;
      }else{
        nextState = currentState;
      }
      break;
  }
  currentState = nextState;
  delay(100);
  
}
