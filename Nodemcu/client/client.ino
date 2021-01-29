#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
void handleroot();
void forward();
void left();
void right();

const char* ssid = "true_home2G_e4c";
const char* password = "7fxHhRyD";
String serverName = "http://171.99.252.255:5000";
unsigned long timerDelay = 30;
unsigned long lastTime = 0;
String x = "s";
void setup() 
{
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
}

void loop() 
{
  if(x=="f"){
    digitalWrite(D5,HIGH);
    digitalWrite(D6,HIGH);
    digitalWrite(D7,HIGH);
    digitalWrite(D8,HIGH);
  }else if(x=="l"){
      digitalWrite(D5,LOW);
    digitalWrite(D6,LOW);
    digitalWrite(D7,HIGH);
    digitalWrite(D8,HIGH);
  }else if(x=="r"){
      digitalWrite(D7,LOW);
    digitalWrite(D8,LOW);
     digitalWrite(D5,HIGH);
    digitalWrite(D6,HIGH);
  }else{
       digitalWrite(D5,LOW);
    digitalWrite(D6,LOW);
       digitalWrite(D7,LOW);
    digitalWrite(D8,LOW);
  }
if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName + "/state";
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0&&httpResponseCode<400) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        x=payload;
        Serial.println(x);
        );
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
