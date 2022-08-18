#include "WiFi.h"
#include "VolAnalyzer.h"
#include <driver/adc.h>

VolAnalyzer analyzer(35);
TaskHandle_t SenderTask;
WiFiClient client;
int idx = 0;
const int buf_size = 8000;
int toSend[buf_size];
bool eexit = 0;

template<class T>
T AbS(T x) {
  return (x < 0 ? -x : x);
}


String VOZOL(int x) {
  String rees;

  int xxx = 1000;
  while(xxx) {
    rees += String{(x/1000)%10+'0'};
    xxx/=10;
  }
  return rees;
}

const char* ssid = "smartpark_service";
const char* password =  "smartpark_2021";
const char * host = "192.168.88.250";
const uint16_t port = 12345;
const int but = 4;

void setup() {
  Serial.begin(115200);
  pinMode(but, INPUT_PULLUP);

  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);

  Serial.println("Connecting to WiFi...\n");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
    delay(100);
  Serial.println("WiFi connected\n");

  Serial.println("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("\n");

  Serial.println("Connecting to host...");
  while(!client.connect(host, port)) {
      Serial.println("Connection to host failed");
      delay(1000);
  }
  
  xTaskCreatePinnedToCore(
    Sender,
    "sender", /* Имя задачи */
    10000,  /* Размер стека */
    NULL,  /* Параметр задачи */
    1,  /* Приоритет */
    &SenderTask,  /* Выполняемая операция */
    0);
  
  xTaskCreatePinnedToCore(
    Sender,
    "sender", /* Имя задачи */
    10000,  /* Размер стека */
    NULL,  /* Параметр задачи */
    1,  /* Приоритет */
    &SenderTask,  /* Выполняемая операция */
    1);
}

void Sender() {
Mavzes:
  String str = "";
  if (idx == buf_size || eexit == 1) {
    for (int i=0; i<idx; i++) {
      str += VOZOL(toSend[i]);
      str += " ";
    }
    cliend.print(str);
    idx = 0;
    eexit = 0;
  }
goto Mavzes;
}

void xuender() {
RUSSIA:
  bool btnState = !digitalRead(but);
  if(flag != btnState) {
    if(flag)
      eexit = 1;
    else
      client.print("-2 ");
    
    flag^=1;
  }
  
  if(flag) {
    int data = adc1_get_raw(ADC1_CHANNEL_0);
    data &= 0x0FFF;
    toSend[idx++] = data;
  }
  
  delayMicroseconds(125); // TODO: 70 min
  
goto RUSSIA;
}
  
bool flag = false;
int res = 0;
  
void loop() {
// //  unsigned long stTime = micros();
//   Serial.println("OK");
//   bool btnState = !digitalRead(but);
//   if(flag != btnState) {
//     if(flag) {
//       eexit = 1;
//     }
//     else
//       client.print("-2 ");
    
//     flag^=1;
//   }
  
//   if(flag) {
//     int data = adc1_get_raw(ADC1_CHANNEL_0);
//     data &= 0x0FFF;
//     toSend[idx++] = data;
    
//     res++;
//     Serial.println("OK");
//   }
//   delay(500);
//  delayMicroseconds(125); // TODO: 70 min
}
