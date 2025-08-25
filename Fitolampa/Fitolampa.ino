int Relay = 5; // Задаем пин для реле
int PhotosensorPin = A0; //Задаем пин для фоторезистора
unsigned int sensorValue = 0; //создаем переменную для хранения значений с фоторезистора

void setup()
{
  pinMode(Relay, OUTPUT); // Переводим пин в режим выхода
  Serial.begin(9600);
  pinMode(PhotosensorPin, INPUT); // Переводим пин в режим входа
}

void loop()
{
  sensorValue = analogRead(PhotosensorPin); //Считываем значение  с фоторезистора
  Serial.println(sensorValue);
  if(sensorValue<500) //задаем пороговое значене включения\выключения
  {
  digitalWrite(Relay, LOW); // Включаем реле
  }
  else
  {
   digitalWrite(Relay, HIGH); //Выключаем реле
  }
 delay(500); // Задержка пол секуды
}
