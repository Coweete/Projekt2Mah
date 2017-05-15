#include <Wire.h>

uint8_t rx_buf[3];
uint8_t send_data[3];
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
  send_data[0] = rx_buf[0];
  Wire.write(send_data,3);
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

  if(0x25 == rx_buf[0]){
    send_data[1] = 13;
    send_data[2] = 37;
  }
  
}

