#include "WiFi.h"
#include "VolAnalyzer.h"

VolAnalyzer analyzer(35);

template<class T>
T AbS(T x) {
  return (x < 0 ? -x : x);
}

WiFiClient client;
const char* ssid = "smartpark_service";
const char* password =  "smartpark_2021";

const char * host = "192.168.88.250";
const uint16_t port = 12345;

const int but = 4, btn2 = 2;
void setup() {
 
  Serial.begin(115200);
  pinMode(but, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);


  Serial.println("Connecting to WiFi...\n");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  Serial.println("WiFi connected\n");

  Serial.println("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("\n");

  Serial.println("Connecting to host...");
  while(!client.connect(host, port)) {
 
      Serial.println("Connection to host failed");
      delay(1000);
  }
  Serial.println("Connected to host...");
}
bool flag = false;
void loop() {
  unsigned long stTime = micros();
  
  bool btnState = !digitalRead(but);
  if(flag != btnState) {
    if(flag) {
      delay(100);
      client.print("-1 ");
    }
    else
      client.print("-2 ");
    
    flag^=1;
  }
  
  if(flag) {
    int data = analogRead(35);
    client.print(data);
    client.print(" ");
  }
  unsigned long enTime = micros();
  unsigned int z = enTime-stTime;
  unsigned int dl = 125 - z;
//  Serial.println(125 - z);
  delayMicroseconds(125 - z); // TODO: 70 min
}
