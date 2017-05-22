#include <Wire.h>

uint8_t rx_buf[5];
uint8_t send_data[5];
uint8_t twi_state;

void setup() {
  Wire.begin(3);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(115200);
  Serial.println("Arduino Due start");
}

void loop() {
  //do stuff
}

void requestEvent(){
  send_data[0] = 11;
  send_data[1] = 0;
  send_data[2] = 130;
  send_data[3] = 0;
  send_data[4] = 150;
  Wire.write(send_data,5);
}

void receiveEvent(int howMany){
  int i = 0;
    while(Wire.available()){
    twi_state = Wire.read();
    rx_buf[i] = twi_state;
    i++;
  }
  Serial.println(rx_buf[0]);

  
  
}

