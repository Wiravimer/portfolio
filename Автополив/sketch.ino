// Подключаем библиотеку для работы с HTTP-протоколом
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>                             // библиотека для протокола I2C
#include <LiquidCrystal_I2C.h>       // библиотека для LCD 1602 
LiquidCrystal_I2C LCD(0x27,20,2);  // присваиваем имя дисплею

#include "RotaryEncoder.h"      // библиотека для энкодера
RotaryEncoder encoder(12, 14);  // пины подключение энкодера (DT, CLK)
#define SW 13                              // пин подключения порты SW энкодера
byte scale = 16;  // указываем сколько символов должно быть в строке

// создаем массив из 65 символов
char massiv[65] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'G', 'K', 'L', 'M',
  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
  ' ', '-', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'g', 'k', 'l', 'm',
  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

String simvol;
String stroka;
byte w;
int pos;
int newPos;
boolean buttonWasUp = true;
HTTPClient http;// создаем объект для работы с HTTP
StaticJsonDocument<300> json;
String server="http://0.tcp.eu.ngrok.io:15210";
int id=3;
int save_status=0;
int power=1;
int new_pomp_status=0;
int old_pomp_status=0;
int soilMoistureValue=0;
int percentage=0;

void get_request(){
  // выполняем проверку подключения к беспроводной сети
  if ((WiFi.status() == WL_CONNECTED)) {
    http.begin(server+"/api/"+id);// подключаемся к веб-странице
    int httpCode = http.GET();// делаем GET запрос
    if (httpCode > 0) {    // проверяем успешность запроса
      if (httpCode == HTTP_CODE_OK) {
        // выводим ответ сервера
        String payload = http.getString();
        // Десериализация документа JSON
        DeserializationError error = deserializeJson(json, payload);
        // Проверьте, удастся ли выполнить синтаксический анализ.
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
        }

      }else {Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());}
    }
    else {Serial.print("Ошибка HTTP-запроса "); Serial.println(httpCode);}
    http.end();//  //Закрыть соединение(освобождаем ресурсы микроконтроллера)
  }
}

void post_request(String info, int value){
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin(server);
    
    http.addHeader("Content-Type", "application/json");
    // Data to send with HTTP POST
    StaticJsonDocument<100> jsonDocument;
    jsonDocument["id"] = id;

 
    jsonDocument["info"] = info;
    jsonDocument["value"] = value;


    char buffer[100];
    serializeJsonPretty(jsonDocument, buffer);
    
    // Send HTTP POST request
    int httpResponseCode = http.POST(buffer);

    http.end();
  }
}

void set_lcd(){
  LCD.init(); // инициализация дисплея
   LCD.backlight(); // включение подсветки
   LCD.blink();
   pinMode(SW, INPUT_PULLUP);  // подключаем пин SW
   pinMode(35, INPUT_PULLUP);
}

void output_text(String str){
   LCD.clear();
   LCD.setCursor(0, 0);
   LCD.setCursor(w, 0);
   LCD.print(str);
   // выводим первый символ в массиве на дисплей
   simvol = massiv[pos];
   LCD.setCursor(w, 1);
   LCD.print(simvol);
}

String input_text(){
  delay(10);
  while (digitalRead(35)==0) {
    
     // проверяем положение ручки энкодера
     encoder.tick(); newPos = encoder.getPosition();

     // указываем максимальный и минимальный диапазон энкодера
     if (newPos > 64) { encoder.setPosition(0); }
     if (newPos < 0) { encoder.setPosition(64); }

     // если положение энкодера изменилось  - выводим на монитор символ
     if (pos != newPos && newPos <= 64 && newPos >= 0) {
        pos = newPos;
        simvol = massiv[pos];
        LCD.setCursor(w, 1);
        LCD.print(simvol);
     }

     // узнаем, отпущена ли кнопка энкодера сейчас
     boolean buttonIsUp = digitalRead(SW);
     // если кнопка была отпущена и не отпущена сейчас
     if (buttonWasUp && !buttonIsUp) {
        // исключаем дребезг контактов кнопки энкодера
        delay(10);
        // узнаем состояние кнопки энкодера снова
        buttonIsUp = digitalRead(SW);
        // если кнопка была нажата, то сохраняем символ в строку
        if (!buttonIsUp) {
           w = w + 1;
           stroka = stroka + simvol;
           encoder.setPosition(0);
           LCD.setCursor(w, 1);
           LCD.print(simvol);
      }
    }
    // запоминаем состояние кнопки энкодера
    buttonWasUp = buttonIsUp;
    }
    w=0;
    return stroka;
}

void measureSoilMoisture(){
  soilMoistureValue = analogRead(33);
  percentage = map(soilMoistureValue, 0, 4095, 0, 100);
  Serial.println(percentage);
  post_request("measure",percentage);
  if (percentage < 10){digitalWrite(4,HIGH); new_pomp_status=1;}
  else if(percentage >80){digitalWrite(4,LOW);new_pomp_status=0;}
  if (new_pomp_status != old_pomp_status){
    post_request("pump_status", new_pomp_status);
    old_pomp_status=new_pomp_status;
  }
}


// Wokwi-GUEST
void wifi_connect(String ssid, String pass){
  // Serial.println();
  output_text("Connection Wi-Fi");
  WiFi.begin(ssid, pass, 6);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  // Serial.println("\Wi-Fi Connected");
  output_text("Wi-Fi Connected");
  // Serial.println("IP address: "+WiFi.localIP());
  
}

void setup() {
  pinMode (4, OUTPUT);
  pinMode (2, OUTPUT);
  Serial.begin(9600);
  set_lcd();
  output_text("Input SSID Wi-Fi");
  String ssid=input_text();
  ssid = "Wokwi-GUEST";
  output_text("Input PASS Wi-Fi");
  String pass=input_text();
  if (pass=="/"){pass="";}
  wifi_connect(ssid, pass);
  
  LCD.setCursor(0, 1);
  LCD.print("ID: "+String(id));

  Serial.println();
}

void loop() {

  get_request();
  int num = json["num"];
  if (save_status != num){
    if (num > 0){digitalWrite(2, HIGH); power=1;}
    else {digitalWrite(2, LOW);power=0;}
    save_status=num;
    post_request("power", num);
  }
  if (power == 1){measureSoilMoisture();}

  delay(10000);//Ждем 10 сек
}

