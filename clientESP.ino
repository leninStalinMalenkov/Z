#include "WiFi.h"
#include "VolAnalyzer.h"
#include <driver/adc.h>

VolAnalyzer analyzer(35);

template<class T>
T AbS(T x) {
  return (x < 0 ? -x : x);
}

String answer;

String VOZOL(int x) {
  String rees;

  int xxx = 1000;
  while(xxx) {
    rees += String{(x/1000)%10+'0'};
    xxx/=10;
  }
  return rees;
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

  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);

  


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
  
}
bool flag = false;
int res = 0;
void loop() {
//  unsigned long stTime = micros();
  Serial.println("OK");
  bool btnState = !digitalRead(but);
  if(flag != btnState) {
    if(flag) {
      client.print(answer);
      answer = "";
      delay(100);
      client.print("-1 ");
      Serial.println(res);
      res = 0;
    }
    else
      client.print("-2 ");
    
    flag^=1;
  }
  
  if(flag) {
    int data = adc1_get_raw(ADC1_CHANNEL_0);
    answer += VOZOL(data);
    answer += " ";
    data&=0x0FFF;
    Serial.println(answer);
    res++;
    if(answer.length() >= 8000) {
      client.print(answer);
      answer = ""; 
    }
    Serial.println("OK");
  }
  delay(500);
//  delayMicroseconds(125); // TODO: 70 min
}
