#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial hc12(9, 8); // RX, TX (подключено к TX и RX HC-12)

int pinsMotor1[] = {A2, A3};
int pinsMotor2[] = {A0, A5};

// Задача контрювати двигуни відповідно до значень x та y від джойстика
// x, y - значення від -255 до 255
// Y - вперед/назад
// X - ліво/право
// Якщо x або y дорівнює 0, то двигуни не рухаються

void controlMotors(int x, int y){
  int speed1 = y + x;
  int speed2 = y - x;
  speed1 = constrain(speed1, -255, 255);
  speed2 = constrain(speed2, -255, 255);
  if(speed1 > 0){
    analogWrite(pinsMotor1[0], speed1);
    analogWrite(pinsMotor1[1], 0);
  }else{
    analogWrite(pinsMotor1[0], 0);
    analogWrite(pinsMotor1[1], -speed1);
  }
  if(speed2 > 0){
    analogWrite(pinsMotor2[0], speed2);
    analogWrite(pinsMotor2[1], 0);
  }else{
    analogWrite(pinsMotor2[0], 0);
    analogWrite(pinsMotor2[1], -speed2);
  }
}


void setup() {
  Serial.begin(9600);
  hc12.begin(9600);
  Serial.println("Receiver launched.");
}

void loop() {
  if (hc12.available()) {



    String receivedData = hc12.readStringUntil('\n'); // Чтение до символа новой строки

    // Разделение строки по запятой
    int separatorIndex = receivedData.indexOf(',');

    if (separatorIndex > 0) {
      String var1Str = receivedData.substring(0, separatorIndex);
      String var2Str = receivedData.substring(separatorIndex + 1);

      int FB = var1Str.toInt();
      int LR = var2Str.toInt();

      // Вывод полученных значений в монитор порта
      Serial.print("FB: ");
      Serial.print(FB);
      Serial.print(" | LR: ");
      Serial.println(LR);
      controlMotors(FB, LR);
    }
  }
}
