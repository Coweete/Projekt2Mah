/**
 * @author Jonatan Fridsten
 * I denna fil finns programmeringen för påbyggnaden som tillhör vikingarna. 
 */
#include <Servo.h>
#include <Wire.h>

//Servo objekt som tar han om styrningen av klon
Servo myservo;  

//Ingång och utgångs pinnar
#define PWM_B  11
#define Dir_b  13
#define Brake  8
#define CurSen  A1
#define stopTop  2
#define stopBot  4
#define servoPin  6

//State variabel för att hålla kol på i vilken case programmet skall vara i
int currentState = 1;
//Bufferten som kommer ifrån det inlästa värdet från TWI bussen
uint8_t rx_buf[3];
//Avståndet til objektet, första talet är avståndet i cm och andra vinkeln roboten behöver vara i. 
uint8_t avstand_objekt[] = {40,0};
//Avståndet roboten måsta stanna till från kanten till lådan, 1: Avståndet till lådan, 2: Vinkeln till lådan
uint8_t avstand_lada[] = {20,0};
//Status på om lyftet är klart eller inte
uint8_t lyft_status = 0;
//Testdata för att kontroller så att kommunikationen fungerar
uint8_t hasdata = 244;
//Boolean för om alla objekten skall tas upp eller ej
uint8_t tauppalla = 0;
//Bufferten som skall skickas på TWI bussen
uint8_t send_data[3];
//Det inkomande states 
uint8_t twi_state = 0;
//Vilket objekt som roboten befinner sig i
uint8_t objekt;
//Hur det går för roboten 2 = klar
uint8_t pickupStatus;

/**
 * Setup metoden som körs först i programmet
 */
void setup() {
  pinMode(Dir_b, OUTPUT);
  pinMode(Brake,OUTPUT);
  pinMode(stopTop, INPUT_PULLUP);
  pinMode(stopBot, INPUT_PULLUP);

  //Sätter pin 6 till servo pinnen och sätter den till 0 läget
  myservo.attach(servoPin);
  myservo.write(0);

  //Sätter riktningen och startar bromsen
  digitalWrite(Dir_b,HIGH);
  digitalWrite(Brake,HIGH);
  //Sätter hastigheten på motorn
  analogWrite(PWM_B,255);

  Wire.begin(2);                  //Startar upp TWI bibliotektet och sätter adressen till 2.
  Wire.onRequest(requestEvent);   //Sätter ihop ett avbrott för när mastern vill att slaven skall skicka information.
  Wire.onReceive(receiveEvent);   //Sätter ihop ett avbrott för när slaven skall ta imot information.
  Serial.begin(9600);             //Startar den seriella kommunikationen  
  Serial.println("Arduino start");
}
/**
 * Huvudloopen för programmet
 */
void loop() {
  switch(currentState){
    case 0x20:                              //Sätter klon till startpositionen
    Serial.println("Return to normal pos");
       if(digitalRead(stopTop) == LOW){     //Kontrollerar så att top positionen är nådd
          digitalWrite(Brake,HIGH);
          myservo.write(0);
       }else{
        digitalWrite(Dir_b,HIGH);
        digitalWrite(Brake,LOW);
       }
    break;
    case 0x21:
    //Dropp off start
       if(digitalRead(stopTop) == LOW){  //Kontrollera så att klon är i topen sedan släpper den av objeketet.
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
       if(digitalRead(stopTop) == LOW){     //kontrollerar så att den befinner sig i toppen och börjar köra nedåt
          digitalWrite(Dir_b,LOW);
          digitalWrite(Brake,LOW);
          pickupStatus = 5;
          currentState = 0x32;
       }else{
          pickupStatus = 6;
       }
    break;
    case 0x32:                          //Om boten positionen är nådd klämmer klon och försöker ta upp ett objekt
    Serial.println("Start grab");       //Börjar kör klon uppåt med
      if(digitalRead(stopBot) == LOW){
        digitalWrite(Brake,HIGH);
        if(4 == objekt){              //Speciallfall för glaset då klon åker upp lite innan den klämmer
          digitalWrite(Dir_b,HIGH);
          digitalWrite(Brake,LOW);
          delay(1000);
          digitalWrite(Brake,HIGH);
          myservo.write(180);
          delay(500);
          currentState = 0x33;
        }else{
        myservo.write(180);
        delay(500);
        digitalWrite(Dir_b,HIGH);
        currentState = 0x33;
        }

      }else{
        send_data[1] = 6;
      }
    break;
    case 0x33:
       Serial.println("Return to top pos"); //Körs tills det att klon har nått top positionen stannar då klon där
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
/**
 * En avbrotsrutin då det finns något på TWI bussen
 * Som slaven skall ta emot
 */
void receiveEvent(int howMany){
  int i = 0;
  while(Wire.available()){  //kontroller om det finns något på bussen och isf spara undan det
    twi_state = Wire.read();
    rx_buf[i] = twi_state;
    i++;
  }
  Serial.println("IN rec");
  Serial.println(rx_buf[0]);
  Serial.println(rx_buf[1]);
  switch(rx_buf[0]){ 
    case 0x20: // init kommer att returnera följande till huvudkortet
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
      }
    break;
    case 0x21: //Dropoff_start
    // här i detta stadiet skall roboten börja att släppa av sina objekt
    currentState = 0x21;
    break;
    case 0x22: //PICKUP START
      Serial.print("Pickup start");
      objekt = rx_buf[1];
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
/**
 * Abrottsrutin för att skicka data till Huvudkortet
 */
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
