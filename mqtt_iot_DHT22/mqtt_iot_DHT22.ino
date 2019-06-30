// Bibliotecas
#include<WiFi.h>            // Gestão de WiFi Espressif
#include "DHTesp.h"         // DHT otimizada para ESP32
#include <ArduinoJson.h>    // Manipulação de dados JSON
#include <PubSubClient.h>   // MQTT Client
#include <time.h>

//Informações de Rede
//const char* ssid = "Iot Smart House";  // Enter SSID here
//const char* password = "IotSmartHousei8#!";  //Enter Password here

const char* ssid = "AsusDreh";  // Enter SSID here
const char* password = "stoniarigida";  //Enter Password here

//Valores de Referência
#define DHTPIN 4 // Pino Conectado do DHT22


//Variáveis Globais
uint32_t contador_loop = 0;
String client_id;
float temperature = 0;
float umidity = 0;
String datetime;

//Manipulação de Texto e Json
char serialMessage[200];
char jsonBuffer[1024];

// Informações de acesso MQTT
const char* mqttBroker = "iot.eclipse.org";
const int mqttPort = 1883;
const char* topic_pub = "/iot/senai/curvello/data";
const char* topic_sub = "/iot/senai/vinialves08/cmd";

//Objects
WiFiClient espClient;
DHTesp dht;
DynamicJsonDocument doc(1024);
PubSubClient mqttClient(espClient);

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  

  Serial.println("Inicializando componentes...");
  dht.setup(DHTPIN, DHTesp::DHT22);
  Serial.print("Sensor DHT22 Inicializado!!!\n\n ");
  
  Serial.print("Digite o ID do Cliente: ");
 while(Serial.available() == 0);
 while(Serial.available() > 0){
    client_id = Serial.readString();
 }

 Serial.print("Cliente ID: ");
 Serial.println(client_id);

 //Iniciando a conexão de rede

 Serial.print("Iniciando WiFi...");
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  Serial.print("Configurando acesso ao MQTT...");
  mqttClient.setServer(mqttBroker, mqttPort);
  while(!mqttClient.connected()){
    if(mqttClient.connect(client_id.c_str())){
      Serial.println("Conectado!");
    }else{
    Serial.print(".");
    delay(2000);      
    }
  }
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  contador_loop++; 
   temperature = dht.getTemperature();
   umidity = dht.getHumidity();

   if(isnan(temperature) || isnan(umidity) ){
      Serial.println("Falha na leitura do sensor!!");
      temperature = umidity = 9999; // Valor de exceção para envio dos dados
   }
   snprintf(serialMessage, sizeof(serialMessage),
    "Loop: %d \nTemp: %.2f \nUmid: %.2f \n",
    contador_loop, temperature, umidity
   );
   Serial.println(serialMessage);


   doc["ID"] = client_id;
   doc["TEMP"] = temperature;
   doc["UMID"] = umidity;
   doc["NR"] = contador_loop;
   
   serializeJson(doc, jsonBuffer);
   Serial.println(jsonBuffer);

   mqttClient.publish(topic_pub, jsonBuffer);
    
}
