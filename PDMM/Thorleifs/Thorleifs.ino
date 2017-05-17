//KOMMENTARER KOMMER UPP SEN!
//Kanal A Motorn(1).
#define PWM_A 3
#define DIR_A 12
#define BRAKE_A 9

//Kanal B Motorn(2).
#define PWM_B 11
#define DIR_B 13
#define BRAKE_B 8

//Knappar
#define KnappHissUppe 4 //PullUps.
#define KnappHissNere 7
int buttonStateUppe=0;      
int buttonStateNere=0;

//Olika tillstånd
enum State {Begin, Greppa, HissenUpp, LossaGreppet, HissenNer};

  State currentState = Begin;
  State nextState;

  
void setup() {
  Serial.begin(9600);
  pinMode(BRAKE_A, OUTPUT);  
  pinMode(DIR_A, OUTPUT);    
  pinMode(BRAKE_B, OUTPUT);   
  pinMode(DIR_B, OUTPUT);     
  pinMode(KnappHissUppe, INPUT_PULLUP);
  pinMode(KnappHissNere, INPUT_PULLUP);
}
 
void loop() {

 
  
  buttonStateUppe = digitalRead(KnappHissUppe); // 4
  buttonStateNere=digitalRead(KnappHissNere); // 7

  
  switch(currentState)
  {
   case Begin:
      if (buttonStateUppe == LOW) {
        digitalWrite(BRAKE_A, HIGH);
        analogWrite(PWM_A, 0);
       // analogWrite(PWM_B, 0);
       digitalWrite(DIR_B,HIGH);
        Serial.println("Hissen is up!");
        delay(5000);
        nextState = LossaGreppet;
      } else {
        Serial.println("Hissen on the way up");
        digitalWrite(DIR_A, HIGH);
        digitalWrite(BRAKE_A, LOW);
        analogWrite(PWM_A, 80);
      }
      break;


 case LossaGreppet:  
 if (buttonStateUppe == LOW) {
        Serial.println("Lossar upp greppet");
        digitalWrite(DIR_B,HIGH);
        analogWrite(PWM_B, 0);
        delay(5000);
        nextState = HissenNer;
      }
      break;

      case HissenNer:
      if (buttonStateNere == LOW) {
         Serial.println("HISSEN ÄR NERE");
        digitalWrite(DIR_A, LOW);
        digitalWrite(BRAKE_A, HIGH);
        delay(5000);
        nextState = Greppa;
      }else{
         Serial.println("HISSEN PÅVÄG NER");
       analogWrite(PWM_A,100);
       digitalWrite(DIR_A, LOW);
       digitalWrite(BRAKE_A, LOW);
      }
      break;

  case Greppa:
   if (buttonStateNere == LOW) {
     Serial.println("GREPPAR");
        digitalWrite(BRAKE_A, HIGH);
        delay(15);
        digitalWrite(DIR_B, HIGH);
        analogWrite(PWM_B,255);
        delay(2000);
      digitalWrite(DIR_B, LOW);
        analogWrite(PWM_B,255);
        delay(2000);
        nextState = HissenUpp;
   }
break;
   
  case HissenUpp:
    Serial.println("HISS UPP MED FÖREMÅLET");
      if (buttonStateUppe == LOW) {
        digitalWrite(BRAKE_A, HIGH);
        delay(2000);
        analogWrite(PWM_B,0);
      } else {
        digitalWrite(DIR_A, HIGH);
        digitalWrite(BRAKE_A, LOW);
        
        analogWrite(PWM_B,155);
        nextState = Begin;
      }
      nextState = Begin;
      break;
  


  default:
  Serial.println("default");
  return;
  }
  currentState = nextState;
}
