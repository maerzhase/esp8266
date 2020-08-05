#include <ESP8266WiFi.h>

const char* ssid     = "Studio NAND";
const char* password = "popularheights";
WiFiServer server(80);
WiFiClient client;


int soundPin = 0;

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
  pinMode(soundPin, OUTPUT);
  connectToWifi();
  server.begin();
  analogWriteFreq(200);
}


boolean buttonPressed = false;


void loop() {
 if (!client.connected()) {
    // try to connect to a new client
    client = server.available();
  } else {
    // read data from the connected client
    if (client.available() > 0) {
      String line = client.readStringUntil('\r');
      Serial.println(line);
      if(line == true){
        buttonPressed = true; 
      }
      if(line == false){
         buttonPressed = false;
      }
    }
    if(buttonPressed){
      digitalWrite(soundPin,HIGH);
      delayMicroseconds(1136);
      digitalWrite(soundPin,LOW);
      delayMicroseconds(1136);
    }
  }
}
