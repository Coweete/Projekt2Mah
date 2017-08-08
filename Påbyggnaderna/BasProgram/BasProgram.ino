#include <Wire.h>

uint8_t rx_buf[3];

//Pabyggnads nummert för att identifiering 
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

uint8_t data_packet[3];
uint8_t twi_state = 0,request_state = 0;

/**
 * Setup
 */
void setup() {
  Wire.begin(3);                  //Startar upp TWI bibliotektet och sätter adressen till 2.
  Wire.onRequest(requestEvent);   //Sätter ihop ett avbrott för när mastern vill att slaven skall skicka information.
  Wire.onReceive(receiveEvent);   //Sätter ihop ett avbrott för när slaven skall ta imot information.
  Serial.begin(9600);             
  Serial.println("Arduino start");
}
/**
 *  Main loop
 */
void loop() {
  //Serial.println("in loop");
  delay(100);
}

/**
 * Metod som kallas då mastern vill att slaven skall skicka information
 * till sig, detta sker över I2C.
 */
void requestEvent(){
  twi_state = rx_buf[0];
  switch(twi_state){
    case 0x10:                              //Identifiering skickar information om roboten vilket id pabyggnaden har
        data_packet[0] = twi_state;   
        data_packet[1] = id_nummer;         //idnummert
        Wire.write(data_packet,2);          //Skriver till slaven
      break;
    case 0x11:                              //Placering_relativt_objekt (Avståndet som roboten måste stanna innan objektet)
        data_packet[0] = twi_state;
        data_packet[1] = avstand_objekt[0]; // Avståndet mellan robot och objekt
        data_packet[2] = avstand_objekt[1]; // Vinkel mellan robot och objekt
        Wire.write(data_packet,3);
      break;
    case 0x12:                              //Placering_relativt_lada  (Avståndet som roboten måste stanna innan lådan)
        data_packet[0] = twi_state;
        data_packet[1] = avstand_lada[0];   // Avståndet mellan robot och lådan
        data_packet[2] = avstand_lada[1];   // Vinkeln mellan robot och lådan
        Wire.write(data_packet,3);
      break;
    case 0x13:                              //Maxhastighet som påbyggnaden klarar av
        data_packet[0] = twi_state;
        data_packet[1] = max_hastighet;     //Maxhastighet
        Wire.write(data_packet,2);
      break;
    case 0x14:                              //Lyckat lyft om roboten har lyckats lyfta objekte
        data_packet[0] = twi_state;
        data_packet[1] = lyft_status;       //3 = lyckat lyft, 4 = misslyckat lyft
        Wire.write(data_packet,2);
      break;
    case 0x15:                              //Misslyckat lyft, om roboten har misslyckat med att lyfta objektet
        data_packet[0] = twi_state;         
        Wire.write(data_packet,1);
      break;
    case 0x16:
        data_packet[0] = twi_state;
        Wire.write(data_packet,1);
      break;
    case 0x17:
    
      break;
    case 0x18:
    
      break;
    case 0x19:
    
      break;
  }
  
}
/**
 * Slaven tar emot information från mastern, detta sker genom ett avbrott
 * som mastern bestämmer när den vill skicka information till slaven.
 *  @param howMany Hur många bitar som packetet är på
 */
void receiveEvent(int howMany){
  Serial.println("TA EMOT");
  int i = 0;
  while(Wire.available()){
    //fixa så att ta emot medelandet är 3 bytes istället för 1
     twi_state = Wire.read(); // Läser in medelandet.
     rx_buf[i] = twi_state;
     i++;
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
}



