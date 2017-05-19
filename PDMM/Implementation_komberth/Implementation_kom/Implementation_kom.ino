
#include <Wire.h>

//Motor 1,channel A
int PWM   = 3;
int DIR   = 12;
int BRAKE = 9;
//Motor 2, channel B
int PWM2 = 11; //
int DIR2 = 13;
int BRAKE2 = 8;
int RFID = 0;
int btnpin = 2;
char currentstate;
char nextstate=0;
uint8_t rx_buf[3];
uint8_t id_nummer =  37;
//Avståndet til objektet, första talet är avståndet i cm och andra vinkeln roboten behöver vara i. 
uint8_t avstand_objekt[] = {10,5};
//Avståndet roboten måsta stanna till från kanten till lådan, 1: Avståndet till lådan, 2: Vinkeln till lådan
uint8_t avstand_lada[] = {11,6};
//Justering av position, om roboten behöver åka fram eller bakåt för att kunna ta upp objektet.
int position_justering = 0;
//Status på om lyftet är klart eller inte
uint8_t lyft_status = 13;
uint8_t hasdata = 244;
uint8_t tauppalla = 1; //hur många objekt den tar upp per gång, 1= ta uppp alla på en gång 
uint8_t send_data[3];
uint8_t twi_state = 0,request_state = 0;
uint8_t objekt;
uint8_t pickupStatus;
uint8_t dropoffStatus;
unsigned long starttime= millis(); 
unsigned long endtime;
int buttonState;  
void setup() {  
  Serial.begin(9600);
  pinMode(BRAKE, OUTPUT);  // Brake pin för kanal A
  pinMode(DIR, OUTPUT);    // Direction pin för kanal A
  pinMode(BRAKE2, OUTPUT);  // Brake pin för kanal B
  pinMode(DIR2, OUTPUT);    // Direction pin för kanal B
  pinMode(btnpin, INPUT_PULLUP);
  Serial.println("Köra motorn");
  currentstate = '1';

  Wire.begin(2);                  //Startar upp TWI bibliotektet och sätter adressen till 2.
  Wire.onRequest(requestEvent);   //Sätter ihop ett avbrott för när mastern vill att slaven skall skicka information.
  Wire.onReceive(receiveEvent);   //Sätter ihop ett avbrott för när slaven skall ta imot information.
  Serial.begin(9600);             
  Serial.println("Arduino start");
}
void loop() {
  buttonState = digitalRead(btnpin);
  switch(currentstate)
  {
  case '0': //stop
    digitalWrite(BRAKE, HIGH); //båda motorerna av
    digitalWrite(BRAKE2, HIGH);
  break;
  case '1':
   endtime = millis();
     if(millis() == endtime){
           pickupStatus = 5;
     }else{
      pickupStatus=6;
    }
  Serial.println("Forward MOTOR 1");
  digitalWrite(BRAKE, LOW);  //sätta brake (stop) låg för att motorn ska köra
  digitalWrite(DIR, LOW);   // Sätta DIR till hög för att motor1 ska köras framåt alltså hela armen
  analogWrite(PWM, 255);     // Hastighet för motor, max 255
  digitalWrite(BRAKE2, LOW);  //sätta brake (stop) låg för att motorn ska köra
  digitalWrite(DIR2, HIGH);   // Sätta DIR till hög för att motor 2 ska köras framåt (klon) greppar
  analogWrite(PWM2, 110); 
   delay(4000);
   digitalWrite(BRAKE2, HIGH);
  delay(14000);     
//  delay(1000);     
  Serial.println("Motor stop");
  digitalWrite(BRAKE, HIGH);  // sätta brake till hög då stannar motorn 
 
  nextstate = '2';
    
  break;
  
  case '2':  //pickup start
  Serial.println("FORWARD MOTOR 2");
//  Serial.println(time);
  digitalWrite(BRAKE2, LOW);  //sätta brake (stop) låg för att motorn ska köra
  digitalWrite(DIR2, LOW);   // Sätta DIR till hög för att motor 2 ska köras framåt (klon) greppar
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
  digitalWrite(DIR, HIGH);    //ändra riktning på motor 1 genom att sätta dir till låg och då hela armen tillbax
  analogWrite(PWM, 200);     // Sätta hastighet till motor
  digitalWrite(BRAKE2, LOW);
  digitalWrite(DIR2, LOW);
  analogWrite(PWM2, 175);
  delay(25000);
  Serial.println("Motor 1 stop backward");
  digitalWrite(BRAKE, HIGH);  // sätta brake till hög då stannar motorn
  digitalWrite(BRAKE2, HIGH);
    endtime = millis();
  if(millis()==endtime){
  send_data[1] = 2;
  delay(5000);
  nextstate = '4';
  }else{
    send_data[1] = 4;
  }
  break;  

  case '4': //dropp off
  Serial.println("backward motor 2");
  digitalWrite(BRAKE2, LOW);  // sätta brake till låg igen
  digitalWrite(DIR2, HIGH);    //ändra riktning på motor genom att sätta dir till låg klon ska släppa
  analogWrite(PWM2, 255);     // Sätta hastighet till motor
  delay(3000);
  endtime = millis();
  if(millis() == endtime){
      Serial.println("Motor 2 stop backward");
  digitalWrite(BRAKE2, HIGH);  // sätta bakre till hög då stannar motorn
  pickupStatus = 2;
    nextstate = '6';
  }
  break; 
  
/*  case '5':
   endtime = millis();
     if(millis() == endtime){
           dropoffStatus = 3;
     }else{
      dropoffStatus=4;
    }
  Serial.println("start dropp off");
    if(millis()== endtime){
          delay(5000);
          send_data[1] = 2;
       }else{
          send_data[1] = 4;
       }
  digitalWrite(BRAKE, LOW);
  digitalWrite(DIR,HIGH);
  analogWrite(PWM,255);
  delay(3000);
    endtime = millis();
  if(millis() == endtime){
  digitalWrite(BRAKE, HIGH);  // sätta bakre till hög då stannar motorn
  dropoffStatus = 2;
    nextstate = '0';
  }*/
 // break;    
case'6':
   /*   endtime = millis();
      if(millis()==endtime){
      send_data[1] = 2;
      delay(5000);
      nextstate = '4';
      }else{
      send_data[1] = 4;
       }*/
Serial.println("button2");
  if(buttonState == LOW)
    {
     Serial.println("button");
     digitalWrite(BRAKE, LOW);
     digitalWrite(DIR,HIGH);
     analogWrite(PWM,255);
     delay(2000);
     digitalWrite(BRAKE, LOW);  
     digitalWrite(DIR, LOW);    
     analogWrite(PWM, 255); 
     delay(5000);
     digitalWrite(BRAKE,HIGH);
    }
  break;
  default:
  Serial.println("default");
  return;
  }
  currentstate = nextstate;
}
void receiveEvent(int howMany){
  int i = 0;
  while(Wire.available()){
    twi_state = Wire.read();
    rx_buf[i] = twi_state;
    i++;
  }
  Serial.println(rx_buf[0]);
  Serial.println(rx_buf[1]);
  switch(rx_buf[0]){
    case 0x20: // init
    
      if(2 == rx_buf[1]){
          currentstate = rx_buf[0];
          send_data[1] =  avstand_lada[0];
          send_data[2] =  avstand_lada[1];
      }else if(3 == rx_buf[1]){
          send_data[1] =  avstand_objekt[0];
          send_data[2] =  avstand_objekt[1];
      }else if(4 == rx_buf[1]){
          send_data[1] = tauppalla;
          send_data[2] = hasdata;
          // send motor to start pos
      }
    break;
    case 0x21: //Dropoff_start
    // här i detta stadiet skall roboten börja att släppa av sina objekt
    currentstate = '3';
    break;
    case 0x22: //PICKUP START
      Serial.print("Pickup start");
      if(2 == rx_buf[1]){
         objekt = 1;
      }else if(3 == rx_buf[1]){
          objekt = 2;
      }else if(4 == rx_buf[1]){
          objekt = 3;
      }
      currentstate = '1';
    break;
    case 0x23: //dropoff status
    /*
        DROPOFF_DONE = 2,
        DROPOFF_RUNNING = 3,
        DROPOFF_FAILED = 4,
        DROPOFF_IDLE = 5
     */
    break;
    case 0x24: 
    //pickuppstatus
    Serial.println("IN pick up");
      //skall returnera något av följande status:
      /*
          PICKUP_DONE = 2,
          PICKUP_FORWARD = 3,
          PICKUP_BACKWARD = 4,
          PICKUP_RUNNING = 5,
          PICKUP_FAILED = 6,
          PICKUP_DONE_DRIVE = 7,
          PICKUP_IDLE = 8
       */
    break;
    case 0x25: // error 
    //om något är fel skall detta kallas
    break;
  }
}

void requestEvent(){
  switch(rx_buf[0]){
    case 0x20:  // identifiering 
      Wire.write(send_data,3);
    break;
    case 0x21:   // Driopoff start
      Wire.write(send_data,3);
    break;
    case 0x22:   // pickup start
      Wire.write(send_data,3);
    break;
    case 0x23:   // dropoff status
      Wire.write(send_data,3);
    break;
    case 0x24:  // pickuppstatus
      Serial.println("send_data[1]");
      send_data[1] = pickupStatus;
      Serial.println(send_data[1]);
      Wire.write(send_data,3);
    break;
    case 0x25:  // error 
      Wire.write(send_data,3);
    break;
  }
}

