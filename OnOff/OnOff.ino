#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define rainAnalog A0
#define rainDigital D0

void esptoweb();
/* Wi-Fi setting connect to your smartphone Wi-Fi hotspot */
const char *ssid = "jizhelee";
const char *password = "leejizhe";
ESP8266WebServer server(80);

/* Variable for sending data to server */
String postData;
int httpCode;
String payload;

const char MAIN_page[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html> 
  <head>
    <title>MAIN GUI</title>
  </head>

  <body>
    <p><a href = "dataOn" target = "myIframe"> Click to turn ON </a></p>
    <p><a href = "dataOff" target = "myIframe"> Click to turn OFF </a></p>
    <p>System status: <iframe name = "myIframe" width = "200" height = "40" frameBorder = "0"></p>
  </body>
  </html>
  )=====";

int systemStatus;

void handleRoot(){
  Serial.println("Calling for page");
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void dataOn(){
  Serial.println("Data started collecting");
  systemStatus = 1;
  server.send(200, "text/html", "Data is collecting");
}

void dataOff(){
  Serial.println("Data stopped collecting");
  systemStatus = 2;
  server.send(200, "text/html", "Data is stop collecting");
}

void esptoweb(){
  delay(5000);
  /* Getting info from Rain Sensor */
  int rainAnalogVal = analogRead(rainAnalog);
  int rainDigitalVal = digitalRead(rainDigital);
  Serial.print(rainAnalogVal);
  Serial.print("\t");
  Serial.println(rainDigitalVal);
    
  /* Sending Rain Sensor value to server */
  HTTPClient http;
  String Rain;
  if (rainDigitalVal == 1){
    Rain = ("1");
  }
  else{
    Rain = ("-1");
  }
    
  postData = "Rain=" + Rain;
  http.begin("http://192.168.43.73/dbInsertRain.php");
  http.addHeader("Content-Type","application/x-www-form-urlencoded");
  httpCode = http.POST(postData);
  payload = http.getString();
  Serial.println(httpCode); //Print HTTP return code
  Serial.println(payload); //Print request response payload
  http.end();
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.println("");
  Serial.println("Connecting");
  /* If Wi-Fi hotspot is not found, show ..... in serial monitor */
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  /* If Wi-Fi hotspot is found, show IP address in serial monitor */
  Serial.println("");
  Serial.println("Connected to ");
  Serial.println(ssid);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/dataOn", dataOn);
  server.on("/dataOff", dataOff);
  server.begin();
  Serial.println("HTTP Server Start");
  
  pinMode(rainDigital,INPUT);
}

void loop() {
  server.handleClient();
  if (systemStatus == 1){
    esptoweb();
  }

  if (systemStatus == 2){
    
  }
}
