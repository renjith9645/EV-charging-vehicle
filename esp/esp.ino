#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

//////////////////////////////////////////////////
// WIFI SETTINGS
//////////////////////////////////////////////////

const char* ssid = "POCO C51";
const char* password = "amalendu1234";

String server = "http://192.168.241.231:5000/data";

//////////////////////////////////////////////////
// DHT11 SETTINGS
//////////////////////////////////////////////////

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

//////////////////////////////////////////////////
// VOLTAGE SENSOR PINS
//////////////////////////////////////////////////

#define BATTERY_PIN 34
#define COIL_PIN 35

//////////////////////////////////////////////////
// LED PINS
//////////////////////////////////////////////////

#define LED_LOW 25
#define LED_MED 26
#define LED_FULL 27

//////////////////////////////////////////////////
// MOTOR DRIVER PINS (L298N)
//////////////////////////////////////////////////

#define IN1 14
#define IN2 12
#define IN3 13
#define IN4 15

//////////////////////////////////////////////////
// VARIABLES
//////////////////////////////////////////////////

float temperature;
float humidity;
float batteryVoltage;
float coilVoltage;

//////////////////////////////////////////////////
// READ BATTERY VOLTAGE
//////////////////////////////////////////////////

float readBatteryVoltage()
{
  int value = analogRead(BATTERY_PIN);

  float voltage = value * (3.3 / 4095.0);

  voltage = voltage * 5.0;   // voltage divider correction

  return voltage;
}

//////////////////////////////////////////////////
// READ COIL VOLTAGE
//////////////////////////////////////////////////

float readCoilVoltage()
{
  int value = analogRead(COIL_PIN);

  float voltage = value * (3.3 / 4095.0);

  voltage = voltage * 5.2;

  return voltage;
}

//////////////////////////////////////////////////
// BATTERY LED INDICATOR
//////////////////////////////////////////////////

void updateBatteryLED(float voltage)
{

  digitalWrite(LED_LOW, LOW);
  digitalWrite(LED_MED, LOW);
  digitalWrite(LED_FULL, LOW);

  if(voltage < 7.5)
  digitalWrite(LED_LOW, HIGH);

  else if(voltage < 12.36)
  digitalWrite(LED_MED, HIGH);

  else
  digitalWrite(LED_FULL, HIGH);

}

//////////////////////////////////////////////////
// MOTOR CONTROL
//////////////////////////////////////////////////

void stopMotor()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void back()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

//////////////////////////////////////////////////
// SEND DATA AND RECEIVE COMMAND
//////////////////////////////////////////////////

void sendData()
{

  if(WiFi.status() != WL_CONNECTED)
  return;

  HTTPClient http;

  String url = server;

  url += "?temp=" + String(temperature);
  url += "&hum=" + String(humidity);
  url += "&battery=" + String(batteryVoltage);
  url += "&coil=" + String(coilVoltage);

  http.begin(url);

  int code = http.GET();

  if(code == 200)
  {

    String command = http.getString();

    Serial.print("Command: ");
    Serial.println(command);

    if(command == "forward")
    forward();

    else if(command == "back")
    back();

    else if(command == "left")
    left();

    else if(command == "right")
    right();

    else
    stopMotor();

  }

  http.end();
}

//////////////////////////////////////////////////
// WIFI CONNECT
//////////////////////////////////////////////////

void connectWiFi()
{

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());

}

//////////////////////////////////////////////////
// SETUP
//////////////////////////////////////////////////

void setup()
{

  Serial.begin(115200);

  pinMode(LED_LOW, OUTPUT);
  pinMode(LED_MED, OUTPUT);
  pinMode(LED_FULL, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  dht.begin();

  connectWiFi();

}

//////////////////////////////////////////////////
// LOOP
//////////////////////////////////////////////////

void loop()
{

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  batteryVoltage = readBatteryVoltage();
  coilVoltage = readCoilVoltage();

  updateBatteryLED(batteryVoltage);

  Serial.println("------ SENSOR DATA ------");

  Serial.print("Temperature: ");
  Serial.println(temperature);

  Serial.print("Humidity: ");
  Serial.println(humidity);

  Serial.print("Battery Voltage: ");
  Serial.println(batteryVoltage);

  Serial.print("Coil Voltage: ");
  Serial.println(coilVoltage);

  Serial.println("-------------------------");

  sendData();

  delay(2000);

}
