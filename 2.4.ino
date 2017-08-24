#include <OLED_I2C.h>
OLED  myOLED(SDA, SCL, 8);
extern uint8_t BigNumbers[];
extern uint8_t SmallFont[];

#include <SoftwareSerial.h>
SoftwareSerial UART_FT232(7, 8); // RX, TX
#define K_line_RX 0 
#define K_line_TX 1 
int n; 
int Temp1 = 1;
int Temp2 = 2;
int PMM = 3;
int SPEED = 4;
String s;
int pac =1;
byte    init_obd[] = {0xC1,0x33,0xF1,0x81,0x66};      // инициализация K-line шины  C1 33 F1 81 66 
byte     pmm_obd[] = {0xC2,0x33,0xF1,0x01,0x0C,0xF3}; // запрос оборотов двигателя  C2 33 F1 01 0C F3
byte   temp1_obd[] = {0xC2,0x33,0xF1,0x01,0x05,0xEC}; // запрос температуры ож      C2 33 F1 01 05 EC
byte   temp2_obd[] = {0xC2,0x33,0xF1,0x01,0x0F,0xF6}; // запрос температуры воздуха C2 33 F1 01 0F F6
byte   speed_obd[] = {0xC2,0x33,0xF1,0x01,0x0D,0xF4}; // запрос скорости автомобиля C2 33 F1 01 0D F4
String Str = "";
//char byfer[];

void setup()  { 
  pinMode(K_line_RX, INPUT); 
  pinMode(K_line_TX, OUTPUT); 
 // UART_FT232.begin (9600);
   Serial.begin(10400);  // ------------_- ISO 14230-4 KWP 10.4 Kbaud
  myOLED.begin();
  myOLED.clrScr();


    s = String(0x0D,HEX) + String(0x20,HEX); // как получить из двух байт 0x0D и 0x20  инотовое 3360 ?  0D20 как раз 3360
  //  Temp2 = s.toInt() /* /4*/;
  // myOLED.setFont(SmallFont), myOLED.printNumI(Temp2, 85, 40),myOLED.update();
    myOLED.setFont(SmallFont), myOLED.print(String(s), 85, 40),myOLED.update(); 
 
              } 

void loop(){  
 
           } 

   