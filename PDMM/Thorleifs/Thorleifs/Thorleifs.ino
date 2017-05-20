
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
enum State {Begin, HissenNer , Greppa, HissenUpp, LossaGreppet};

State currentState = Begin; // Börjar i tillståndet Begin
State nextState;

//Konfiguerar pinnar som Utgångar eller Ingångar / Pullups.
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
  //Avläsning av knappar för KnappUppe till Hiss samt KnappNere till hissen, tillförs buttonState.
  buttonStateUppe = digitalRead(KnappHissUppe); // 4
  buttonStateNere = digitalRead(KnappHissNere); // 7

  switch (currentState)
  {
    case Begin:
      if (buttonStateUppe == LOW) {
        digitalWrite(BRAKE_A, HIGH);
        analogWrite(PWM_A, 0); 
        analogWrite(PWM_B, 0);
        digitalWrite(DIR_B, HIGH);
        Serial.println("Hissen is up!");
        delay(5000);
        nextState = LossaGreppet;
      } else {
        Serial.println("Hissen on the way up");
        digitalWrite(DIR_A, HIGH);   // RÖD Kopplingstråd TILL + OCH BLÅ TILL -
        digitalWrite(BRAKE_A, LOW);
        analogWrite(PWM_A, 150);
      }
      break;

    case LossaGreppet:
      if (buttonStateUppe == LOW) {
        Serial.println("Lossar upp greppet");
        //digitalWrite(DIR_B, LOW);
        analogWrite(PWM_B, 0);
        delay(5000);
        nextState = HissenNer;
      }
      break;

    case HissenNer:
      if (buttonStateNere == LOW) {
        Serial.println("HISSEN ÄR NERE");
       // digitalWrite(DIR_A, LOW);
        digitalWrite(BRAKE_A, HIGH); // Brake på hissen.
        delay(5000); // Väntar i 5 sekunder.
        nextState = Greppa;
      } else {
        Serial.println("HISSEN PÅVÄG NER");
        analogWrite(PWM_A, 110); // Hastighet hiss ner.
        digitalWrite(DIR_A, LOW);// Hiss åker ner.
        digitalWrite(BRAKE_A, LOW);// Ingen Brake på hiss.
      }
      break;

    case Greppa:
      if (buttonStateNere == LOW) {
        Serial.println("GREPPAR OBJEKTET");
        digitalWrite(BRAKE_A, HIGH);// Brake på hissen.
        delay(15);
        digitalWrite(DIR_B, HIGH);// För att öppna klorna.  BLÅ TILL + OCH SVART TILL -
        analogWrite(PWM_B, 255); // Öppnar hela greppet.
        delay(3000);
        digitalWrite(DIR_B, LOW); // För att stänga klorna
        analogWrite(PWM_B, 255);  // Omsluter med full kraft.
        delay(5000);
        nextState = HissenUpp;
      }
      break;

    case HissenUpp:
      Serial.println("HISS UPP MED FÖREMÅLET");
      if (buttonStateUppe == LOW) {
        digitalWrite(BRAKE_A, HIGH); // Brake på hissen.
        delay(2000);
      //  analogWrite(PWM_B, 0); // Lossar om greppet för objektet.
      } else {
        digitalWrite(DIR_A, HIGH); // Hissen åker upp.
        digitalWrite(BRAKE_A, LOW);// Ingen Brake på hissen.
        digitalWrite(DIR_B, LOW); // För att stänga klorna
        analogWrite(PWM_B, 255);// Omsluter med full kraft.
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
