
#include <Wire.h>

//Kanal A Motorn(1) För drivning av hissen.
#define PWM_A 3
#define DIR_A 12
#define BRAKE_A 9

//Kanal B Motorn(2) För drivning av klorna.
#define PWM_B 11
#define DIR_B 13
#define BRAKE_B 8

//Knappar
#define KnappHissUppe 4 //För Kanal A Motorn.
#define KnappHissNere 7 //För Kanal A Motorn.
int buttonStateUppe = 0;
int buttonStateNere = 0;


//Olika tillstånd för Armen
enum State {Begin, HissenNer, Greppa, HissenUpp, LossaGreppet};

State currentState = Begin; // Börjar i tillståndet Begin
State nextState;

uint8_t rx_buf[3];
uint8_t id_nummer =  37;
//Avståndet til objektet, första talet är avståndet i cm och andra vinkeln roboten behöver vara i.
uint8_t avstand_objekt[] = {10, 0};
//Avståndet roboten måsta stanna till från kanten till lådan, 1: Avståndet till lådan, 2: Vinkeln till lådan
uint8_t avstand_lada[] = {11, 6};

//Hastigheten som roboten kan röra sig med objektet i ett lyft ?
//uint8_t max_hastighet = 15;

//Justering av position, om roboten behöver åka fram eller bakåt för att kunna ta upp objektet.
int position_justering = 0;
//Status på om lyftet är klart eller inte
uint8_t lyft_status = 13;
uint8_t hasdata = 244;
uint8_t tauppalla = 0; //hur många objekt den tar upp per gång, 1= ta uppp alla på en gång
uint8_t send_data[3];
uint8_t twi_state = 0, request_state = 0;
uint8_t objekt;
uint8_t pickupStatus;
uint8_t dropoffStatus;

void setup() {
  Serial.begin(9600);
  pinMode(BRAKE_A, OUTPUT);
  pinMode(DIR_A, OUTPUT);
  pinMode(BRAKE_B, OUTPUT);
  pinMode(DIR_B, OUTPUT);
  pinMode(KnappHissUppe, INPUT_PULLUP);
  pinMode(KnappHissNere, INPUT_PULLUP);

  Wire.begin(2);                  //Startar upp TWI bibliotektet och sätter adressen till 2.
  Wire.onRequest(requestEvent);   //Sätter ihop ett avbrott för när mastern vill att slaven skall skicka information.
  Wire.onReceive(receiveEvent);   //Sätter ihop ett avbrott för när slaven skall ta imot information.
  Serial.begin(9600);
  Serial.println("Start of Arduino");
}

void loop() {
  buttonStateUppe = digitalRead(KnappHissUppe); // 4
  buttonStateNere = digitalRead(KnappHissNere); // 7
  switch (currentState) {
    case Begin:  // Körs bara en gång , annars "0x20".
      Serial.println("Return to normal pos");
      if (buttonStateUppe == LOW) {
        digitalWrite(BRAKE_A, HIGH);
        analogWrite(PWM_A, 0);
        analogWrite(PWM_B, 0);
        digitalWrite(DIR_B, HIGH);
        Serial.println("Hissen is up!");
        delay(5000);
        //     nextState = LossaGreppet;
      } else {
        Serial.println("Hissen on the way up");
        digitalWrite(DIR_A, HIGH);   // RÖD Kopplingstråd TILL + OCH BLÅ TILL -
        digitalWrite(BRAKE_A, LOW);
        analogWrite(PWM_A, 150);
      }
      break;

    case HissenNer:
      //pickup start
      Serial.println("start pickup");
      Serial.println(buttonStateUppe);
      if (buttonStateUppe == LOW) {
        digitalWrite(DIR_A, LOW);
        digitalWrite(BRAKE_A, LOW);
        pickupStatus = 5;
        currentState = Greppa;
      } else {
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

    case Greppa:
      Serial.println("Start grab");
      if (buttonStateNere == LOW) {
        digitalWrite(BRAKE_A, HIGH);
        digitalWrite(PWM_B, 255);
        delay(3000);
        digitalWrite(DIR_A, HIGH);
        currentState = HissenUpp;
      } else {
        //send_data[1] = 6;
      }
      break;


    case HissenUpp:
      Serial.println("Return to top pos");
      if (buttonStateUppe == LOW) {
        digitalWrite(BRAKE_A, HIGH);
        pickupStatus = 2;
      } else {
        digitalWrite(DIR_A, HIGH);
        digitalWrite(BRAKE_A, LOW);
        analogWrite(PWM_A, 150);
      }
      break;



    case LossaGreppet:
      //Dropp off start
      if (buttonStateUppe == LOW) {
        analogWrite(PWM_B, 0);
        delay(5000);
        send_data[1] = 2;
        //  nextState = HissenNer;
      } else {
        send_data[1] = 4;
      }
      break;


  }
}


void receiveEvent(int howMany) {
  int i = 0;
  while (Wire.available()) {
    twi_state = Wire.read();
    rx_buf[i] = twi_state;
    i++;
  }
  Serial.println("IN rec");
  Serial.println(rx_buf[0]);
  Serial.println(rx_buf[1]);
  switch (rx_buf[0]) {
    case 0x20: // init
      if (2 == rx_buf[1]) {
        currentState = rx_buf[0];
        send_data[1] =  avstand_lada[0];
        send_data[2] =  avstand_lada[1];
      } else if (3 == rx_buf[1]) {
        send_data[1] =  avstand_objekt[0];
        send_data[2] =  avstand_objekt[1];
      } else if (4 == rx_buf[1]) {
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
      if (2 == rx_buf[1]) {
        objekt = 1;
      } else if (3 == rx_buf[1]) {
        objekt = 2;
      } else if (4 == rx_buf[1]) {
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

void requestEvent() {
  switch (rx_buf[0]) {
    case 0x20:  // identifiering
      Wire.write(send_data, 3);
      break;
    case 0x21:   // Driopoff start
      Wire.write(send_data, 3);
      break;
    case 0x22:   // pickup start
      Wire.write(send_data, 3);
      break;
    case 0x23:   // dropoff status
      Wire.write(send_data, 3);
      break;
    case 0x24:  // pickuppstatus
      Serial.println("send_data[1]");
      send_data[1] = pickupStatus;
      Serial.println(send_data[1]);
      Wire.write(send_data, 3);
      break;
    case 0x25:  // error
      Wire.write(send_data, 3);
      break;
  }
}
