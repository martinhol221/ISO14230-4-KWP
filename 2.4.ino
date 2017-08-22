#include <OLED_I2C.h>
OLED  myOLED(SDA, SCL, 8);
extern uint8_t BigNumbers[];
extern uint8_t SmallFont[];
int temp1;
int temp2;
int pmm;
int Speed;
#define K_line_RX 0 
#define K_line_TX 1 
int n; 
byte    init_obd[] = {0xC1,0x33,0xF1,0x81,0x66};      // инициализация K-line шины  C1 33 F1 81 66 
byte     pmm_obd[] = {0xC2,0x33,0xF1,0x01,0x0C,0xF3}; // запрос оборотов двигателя  C2 33 F1 01 0C F3
byte   temp1_obd[] = {0xC2,0x33,0xF1,0x01,0x05,0xEC}; // запрос температуры ож      C2 33 F1 01 05 EC
byte   temp2_obd[] = {0xC2,0x33,0xF1,0x01,0x0F,0xF6}; // запрос температуры воздуха C2 33 F1 01 0F F6
byte   speed_obd[] = {0xC2,0x33,0xF1,0x01,0x0D,0xF4}; // запрос скорости автомобиля C2 33 F1 01 0D F4

void setup() {
  myOLED.begin();
  myOLED.setFont(BigNumbers);
  pinMode(K_line_RX, INPUT); 
  pinMode(K_line_TX, OUTPUT); 
  myOLED.begin();
  myOLED.setFont(BigNumbers);
  digitalWrite(K_line_TX, HIGH), delay(300); 
  digitalWrite(K_line_TX, LOW), delay(25);   
  digitalWrite(K_line_TX, HIGH), delay(25); //-----------_-
  Serial.begin(10400);  // ------------_- ISO 14230-4 KWP 10.4 Kbaud
//  for(int i=0;i<5;i++) Serial.write(init_obd[i]), delay (10); // отправляем команду инициализации K-line шины 
//  delay(200);  
  
  
}

void loop() {  
  char bufer[30] = ""; // 
  n = Serial.available();
  if (n > 0) {
  for (int i=0;i<n;i++) bufer[i]=Serial.read();

  int byte1 = strtol(&bufer[0],0,16);  
  int byte5 = strtol(&bufer[12],0,16);  
 /* if (byte5 == 5 && byte1 == 131) */ temp1 = strtol(&bufer[15],0,16)-40 /* ,Serial.print("temp1 = "), Serial.println(temp1)*/;
  if (byte5 == 15 && byte1 == 131) temp2 = strtol(&bufer[15],0,16)-40 /*,Serial.print("temp2 = "), Serial.println(temp2)*/;
  if (byte5 == 13 && byte1 == 131) Speed = strtol(&bufer[15],0,16) /*,Serial.print("Speed = "), Serial.println(Speed)*/; 
  if (byte5 == 12 /* && byte1 == 132*/)  pmm = ((strtol(&bufer[15],0,16)*256)+strtol(&bufer[18],0,16))/4 /*,Serial.print("PMM = "), Serial.println(pmm)*/;

   myOLED.clrScr();                                    
   myOLED.setFont(BigNumbers);
   myOLED.printNumI(temp1, RIGHT, 10), myOLED.printNumI(temp2, RIGHT, 40);
 //  myOLED.printNumI(rpm, LEFT, 10),  myOLED.printNumI(spdeed, LEFT, 40);
   myOLED.update(); 
             }
}