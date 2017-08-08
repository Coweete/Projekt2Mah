#include <Wire.h>
/*
Identifiering             = 0x10,
Placering_relativt_objekt = 0x11,
Placering_relativt_lada   = 0x12,
Maxhastighet              = 0x13,
Lyckat_lyft               = 0x14,
Misslyckat_lyft           = 0x15,
Lyckad_avlamning          = 0x16,
Misslyckad_avlamning      = 0x17,
Justera_position          = 0x18,
Avbryt_justering          = 0x19,
Uppstart_pabyggnad        = 0x20,
Lyft_kloss                = 0x21,
Lyft_glas                 = 0x22,
Lyft_strumpa              = 0x23,
Avbryt_lyft               = 0x24,
Lamna_av_objekt           = 0x25,
Position_av_lada          = 0x30,
Aktuell_position_robot    = 0x31,
Start_position_strumpa    = 0x32,
Start_position_kloss      = 0x33,
Start_position_glas       = 0x34,
Uppstart_Position         = 0x40
*/
int twi_state = 0,request_state = 0;

void setup() {
  Wire.begin(2);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  delay(100);
}

void requestEvent(){
  Serial.println("On request method ");
  switch(twi_state){
    case 0x10:
    
      break;
    case 0x11:

      break;
    case 0x12:
    
      break;
    case 0x13:
    
      break;
    case 0x14:
    
      break;
    case 0x15:
    
      break;
    case 0x16:
    
      break;
    case 0x17:
    
      break;
    case 0x18:
    
      break;
    case 0x19:
    
      break;
  }
}

void receiveEvent(int howMany){
  while(Wire.available()){
     twi_state = Wire.read();
  }
  switch(twi_state){
    case 0x10:
      
      break;
    case 0x11:
    
      break;
    case 0x12:
    
      break;
    case 0x13:
    
      break;
    case 0x14:
    
      break;
    case 0x15:
    
      break;
    case 0x16:
    
      break;
    case 0x17:
    
      break;
    case 0x18:
    
      break;
    case 0x19:
    
      break;
    case 0x20:
    
      break;
    case 0x21:
    
      break;
    case 0x22:
    
      break;
    case 0x23:
    
      break;
    case 0x24:
    
      break;
    case 0x25:
    
      break;
  }
  Serial.println();
}

