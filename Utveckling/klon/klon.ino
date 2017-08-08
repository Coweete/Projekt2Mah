

//Motor 1,channel A
int PWM   = 3;
int DIR   = 12;
int BRAKE = 9;
//Motor 2, channel B
int PWM2 = 11;
int DIR2 = 13;
int BRAKE2 = 8;
int RFID = 0;
char currentstate;
char nextstate;
void setup() {
  Serial.begin(9600);
  pinMode(BRAKE, OUTPUT);  // Brake pin för kanal A
  pinMode(DIR, OUTPUT);    // Direction pin för kanal A
  pinMode(BRAKE2, OUTPUT);  // Brake pin för kanal B
  pinMode(DIR2, OUTPUT);    // Direction pin för kanal B
  Serial.println("Köra motorn");
  currentstate = '1';
}
 
void loop() {
  Serial.println("loop");
  
  switch(currentstate)
  {
  case '0':
    digitalWrite(BRAKE, HIGH); //båda motorerna av
    digitalWrite(BRAKE2, HIGH);
  break;
  case '1':
  Serial.println("Forward MOTOR 1");
  digitalWrite(BRAKE, LOW);  //sätta brake (stop) låg för att motorn ska köra
  digitalWrite(DIR, HIGH);   // Sätta DIR till hög för att motor1 ska köras framåt alltså hela armen
  analogWrite(PWM, 255);     // Hastighet för motor, max 255
  delay(5000);                
  Serial.println("Motor stop");
  digitalWrite(BRAKE, HIGH);  // sätta brake till hög då stannar motorn
  delay(5000);
  nextstate = '2';
  break;
  
  case '2':
  Serial.println("FORWARD MOTOR 2");
  digitalWrite(BRAKE2, LOW);  //sätta brake (stop) låg för att motorn ska köra
  digitalWrite(DIR2, HIGH);   // Sätta DIR till hög för att motor 2 ska köras framåt (klon) greppar
  analogWrite(PWM2, 255);     // Hastighet för motor, max 255  
  delay(5000);                
  Serial.println("Motor 2 stop");
  digitalWrite(BRAKE2, HIGH);  // sätta brake till hög då stannar motorn
  delay(5000);
  nextstate = '3';
  break;
  
  case '3':  
  Serial.println("backward motor 1");
  digitalWrite(BRAKE, LOW);  // sätta brake till låg igen
  digitalWrite(DIR, LOW);    //ändra riktning på motor 1 genom att sätta dir till låg och då hela armen tillbax
  analogWrite(PWM, 255);     // Sätta hastighet till motor
  delay(5000);
  Serial.println("Motor 1 stop backward");
  digitalWrite(BRAKE, HIGH);  // sätta brake till hög då stannar motorn
  delay(5000);
  nextstate = '4';
  break;  

  case '4':
  Serial.println("backward motor 2");
  digitalWrite(BRAKE2, LOW);  // sätta brake till låg igen
  digitalWrite(DIR2, LOW);    //ändra riktning på motor genom att sätta dir till låg klon ska släppa
  analogWrite(PWM2, 255);     // Sätta hastighet till motor
  delay(5000);
  Serial.println("Motor 2 stop backward");
  digitalWrite(BRAKE2, HIGH);  // sätta brake till hög då stannar motorn
  nextstate = '0';
  delay(5000);
  break; 
  
  
  default:
  Serial.println("default");
  return;
  }
  currentstate = nextstate;
}

