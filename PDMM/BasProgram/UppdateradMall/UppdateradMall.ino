#include <Wire.h>

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

void setup() {
  Wire.begin(2);                  //Startar upp TWI bibliotektet och sätter adressen till 2.
  Wire.onRequest(requestEvent);   //Sätter ihop ett avbrott för när mastern vill att slaven skall skicka information.
  Wire.onReceive(receiveEvent);   //Sätter ihop ett avbrott för när slaven skall ta imot information.
  Serial.begin(9600);             
  Serial.println("Arduino start");
}

void loop() {
  //maincode here

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
      Wire.write(send_data,3);
    break;
    case 0x25:  // error 
      Wire.write(send_data,3);
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
    break;
    case 0x22: //PICKUP START
      if(2 == rx_buf[1]){
        //ta upp strumpa 
      }else if(3 == rx_buf[1]){
        //ta upp box
      }else if(4 == rx_buf[1]){
        //ta upp glas
      }
    break;
    case 0x23: //dropoff status
    /*
        DROPOFF_DONE = 2,
        DROPOFF_RUNNING = 3,
        DROPOFF_FAILED = 4,
        DROPOFF_IDLE = 5
     */
    break;
    case 0x24: //pickuppstatus
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


