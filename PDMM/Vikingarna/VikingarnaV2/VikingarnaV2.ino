#include <Servo.h>
#include <Wire.h>

Servo myservo;
#define PWM_B  11
#define Dir_b  13
#define Brake  8
#define CurSen  A1
#define stopTop  2
#define stopBot  4
#define servoPin  6

int currentState = 1,nextState = 0;
uint8_t rx_buf[3];
uint8_t id_nummer =  37;
//Avståndet til objektet, första talet är avståndet i cm och andra vinkeln roboten behöver vara i. 
uint8_t avstand_objekt[] = {10,5};
//Avståndet roboten måsta stanna till från kanten till lådan, 1: Avståndet till lådan, 2: Vinkeln till lådan
uint8_t avstand_lada[] = {11,6};
//Hastigheten som roboten kan röra sig med objektet i ett lyft ? 
uint8_t max_hastighet = 15;
//Justering av position, om roboten behöver åka fram eller bakåt för att kunna ta upp objektet.
int position_justering = 0;
//Status på om lyftet är klart eller inte
uint8_t lyft_status = 13;
uint8_t hasdata = 244;
uint8_t tauppalla = 1;
uint8_t send_data[3];
uint8_t twi_state = 0,request_state = 0;
uint8_t objekt;
uint8_t pickupStatus;

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

  Wire.begin(2);                  //Startar upp TWI bibliotektet och sätter adressen till 2.
  Wire.onRequest(requestEvent);   //Sätter ihop ett avbrott för när mastern vill att slaven skall skicka information.
  Wire.onReceive(receiveEvent);   //Sätter ihop ett avbrott för när slaven skall ta imot information.
  Serial.begin(9600);             
  Serial.println("Arduino start");
}

void loop() {
  switch(currentState){
    case 0x20:
    Serial.println("Return to normal pos");
       if(digitalRead(stopTop) == LOW){
          digitalWrite(Brake,HIGH);
          myservo.write(0);
       }else{
        digitalWrite(Dir_b,HIGH);
        digitalWrite(Brake,LOW);
       }
    break;
    case 0x21:
    //Dropp off start
       if(digitalRead(stopTop) == LOW){
          myservo.write(0);
          delay(5);
          send_data[1] = 2;
       }else{
          send_data[1] = 4;
       }
    break;
    case 0x22:
    //pickup start
       Serial.println("start pickup");
       Serial.println(digitalRead(stopTop));
       if(digitalRead(stopTop) == LOW){
          digitalWrite(Dir_b,LOW);
          digitalWrite(Brake,LOW);
          pickupStatus = 5;
          currentState = 0x32;
       }else{
          pickupStatus = 6;
       }
    break;
    case 0x23:
    //check dropp off status ?
    break;
    case 0x24:
    //check pickupp status
    break;
    case 0x25:
    //error ?
    break;
    case 0x32:
    Serial.println("Start grab");
      if(digitalRead(stopBot) == LOW){
        digitalWrite(Brake,HIGH);
        myservo.write(180);
        delay(2);
        digitalWrite(Dir_b,HIGH);
        currentState = 0x33;
      }else{
        //send_data[1] = 6;
      }
    break;
    case 0x33:
       Serial.println("Return to top pos");
       if(digitalRead(stopTop) == LOW){
          digitalWrite(Brake,HIGH);
          pickupStatus = 2;
       }else{
        digitalWrite(Dir_b,HIGH);
        digitalWrite(Brake,LOW);
       }
    break;
  }
  
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
          currentState = rx_buf[0];
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
    currentState = 0x21;
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
      currentState = 0x22;
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
