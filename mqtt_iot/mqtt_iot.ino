// Bibliotecas
#include<WiFi.h>

//Informações de Rede
//const char* ssid = "Iot Smart House";  // Enter SSID here
//const char* password = "IotSmartHousei8#!";  //Enter Password here

const char* ssid = "AsusDreh";  // Enter SSID here
const char* password = "stoniarigida";  //Enter Password here


uint32_t contador_loop = 0;
String client_id;

//Objects
WiFiClient espClient;


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  Serial.println("Inicializando componente...");
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

  
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  contador_loop++;
  Serial.printf("Loop: %d\n", contador_loop);
}
