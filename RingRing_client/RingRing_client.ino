#include <ESP8266WiFi.h>

const char* ssid     = "Studio NAND";
const char* password = "popularheights";

const int LED_PIN = 16;
const int BUTTON_PIN = 0; 
int BUTTON_STATE = 0;

void connectToWifi(){
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN,OUTPUT);
  pinMode(BUTTON_PIN,INPUT);
  digitalWrite(LED_PIN,LOW);
  connectToWifi();
}

const char* host = "192.168.100.110";
const int   port = 80;
boolean buttonToggle = false;

void loop() {

  BUTTON_STATE = digitalRead(BUTTON_PIN);
  if(BUTTON_STATE != HIGH){
    digitalWrite(LED_PIN,HIGH);
    if(buttonToggle == false){
      connectToHostAndSendMessage("true");
      buttonToggle = true;
    }
  }else if(BUTTON_STATE == HIGH){
    digitalWrite(LED_PIN,LOW);
    if(buttonToggle == true){
      connectToHostAndSendMessage("false");
      buttonToggle = false;
    }
  }
  //delay(1000);
}


void connectToHostAndSendMessage(String msg){
  // put your main code here, to run repeatedly:
  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }

  Serial.print("conntected to: ");
  Serial.print(host);
  Serial.print(":");
  Serial.println(port);
  // finally send the message
  client.print(msg);
}

