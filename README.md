Пример скетча ардуино для чтения данных из К-лине шины разьема ОДБ автомобиля Ситроен С5 2003 года выпуска. Позволяет читать шину по протоколу ISO 14230-4 KWP 10.4 Kbaud и выводить на OLED I2C дисплей даные:

1. Температура охлаждающей жидкости двигателя 
2. Температура воздуха во впускном коллекторе 
3. Количество оборотов коленвала двигателя в минуту 
4. Скорость автомобиля
 
[Подробно о моих изысканиях читайте в посте на drive2.ru](https://www.drive2.ru/c/479335393737572613)

Для инициализации начала обмена c ЭБУ двигателя необходимо подать следующую последовательность уровней на K-линию:
HIGH (300ms), LOW (25ms), HIGH (25 ms), за тем на скорости 10400 необходимо отправить пять байт в HEX `C1 33 F1 81 66` с паузами между каждым байтом в 10ms. 

В ответ получите: 12 байт, из которых 5 это эхо зароса, 7 ответ.

`C1 33 F1 81 66 83 F1 10 C1 E9 8F BD` — ответ ЭБУ на запрос инициализации, `C1` значит ОК, `E9` и `8F` служебные, `BD` - контрольная сумма.

Ожидаем 100ms и отправляем зарос на температуру в `C2 33 F1 01 05 EC` (HEX). Получите 13 байт (6+7):

`C2 33 F1 01 05 EC 83 F1 10 41 05 49 13` — Эхо + ответ ЭБУ с температурой, где 49 (HEX) >> 73 (DEC) -40 = 33 град.

Ожидаем 100ms и отправляем зарос на температуру `C2 33 F1 01 0F F6` (HEX).  Получите 13 байт (6+7):

`C2 33 F1 01 0F F6 83 F1 10 41 0F 47 1B` — Эхо + ответ ЭБУ с температурой, где 47 (HEX) >> 71 (DEC) -40 = 31 град.

Ожидаем 100ms и отправляем зарос `C2 33 F1 01 0C F3` (HEX).  Получите 14 байт (6+8): 

`C2 33 F1 01 0C F3 84 F1 10 41 0C 0D 20 FF` — Эхо + ответ ЭБУ с оборотами, где 0D 20 (HEX) >> 3360 (DEC)/4 = 840 об/мин
 
Ожидаем 100ms и отправляем зарос `C2 33 F1 01 0D F4` (HEX). Получите 13 байт (6+7):

`C2 33 F1 01 0D F4 83 F1 10 41 0D 39 0B`  — Эхо + ответ ЭБУ , где 39 (HEX) >> 57 (DEC) = 57 км/ч где 0B -контрольная сумма

Example of an Arduino sketch for reading data from the K-line of the ODB car tire of the Citroen C5 of 2003 release. Allows you to read the bus using the ISO 14230-4 KWP 10.4 Kbaud protocol and display the following on the OLEI I2C display:

1. Engine Coolant Temperature
2. Intake manifold air temperature
3. The number of revolutions per engine
4. Vehicle speed

![Citroen](https://github.com/martinhol221/ISO14230-4-KWP/blob/master/K-Line_ISO_14230-4-KWP(Citroen_C5_2003).JPG?raw=true)
![Citroen2](https://github.com/martinhol221/ISO14230-4-KWP/blob/master/L9637%2BAduino.jpg?raw=true)
![Citroen](https://github.com/martinhol221/ISO14230-4-KWP/blob/master/L9637D%2BAduino.jpg?raw=true)

