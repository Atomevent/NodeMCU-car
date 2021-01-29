#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
void handleroot();
void forward();
void left();
void right();

const char* ssid = "true_home2G_e4c";
const char* password = "7fxHhRyD";
bool forw = false;
bool leftt = false;
bool rightt = false;
bool stopp = true;
ESP8266WebServer server ( 5500 );

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
  server.on("/",handleroot);
  server.on("/f",forward);
  server.on("/l",left);
  server.on("/r",right);
  server.on("/s",stopping);
  server.begin();
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
  WiFi.hostname("MyESP8266");

}
void handleroot(){
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200,"text/plain","Hello World");
}
void forward(){

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200,"text/plain","Forward");
  Serial.println("forward");
  stopp = false;
  forw = true;
  leftt = false;
  rightt = false;

}
void stopping(){

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200,"text/plain","stop");
  Serial.println("stop");
  forw = false;
  leftt = false;
  rightt = false;
  stopp = true;

}
void left(){
 
server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200,"text/plain","Left");
  Serial.println("left");
   stopp = false;
  forw = false;
  leftt = true;
 rightt = false;

}
void right(){

  server.sendHeader("Access-Control-Allow-Origin", "*");
   server.send(200,"text/plain","Right");
  Serial.println("right");
   stopp = false;
   forw = false;
    leftt = false;
  rightt = true;

  }
void loop() 
{

  server.handleClient();
  if(forw){
    digitalWrite(D5,HIGH);
    digitalWrite(D6,HIGH);
    digitalWrite(D7,HIGH);
    digitalWrite(D8,HIGH);
  }else if(leftt){
      digitalWrite(D5,LOW);
    digitalWrite(D6,LOW);
    digitalWrite(D7,HIGH);
    digitalWrite(D8,HIGH);
  }else if(rightt){
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
}
