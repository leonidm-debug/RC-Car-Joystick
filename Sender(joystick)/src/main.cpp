#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial hc12(9, 8); // RX, TX (підключено до TX и RX HC-12)

const int LRpin = A4;
const int FBpin = A2;

int LR = 0;
int FB = 0;

void setup() {
  Serial.begin(9600);     // Монітор порта
  hc12.begin(9600);       // HC-12
  Serial.println("Sender launched.");
}

void loop(){
  
  LR = map(analogRead(LRpin), 0, 1023, -255, 255);
  FB = map(analogRead(FBpin), 0, 1023, -255, 255);

  String dataToSend = String(FB) + "," + String(LR);

  String message = "Hello from sender!";
  hc12.println(String(dataToSend));
  Serial.println("Sent: " + message);
  Serial.println("FB: " + String(FB));
  Serial.println("LR: " + String(LR));
}
