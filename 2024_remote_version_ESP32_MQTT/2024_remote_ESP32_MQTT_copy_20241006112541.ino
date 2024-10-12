#include <WiFi.h>
#include <PubSubClient.h>

// Credenciales Wi-Fi
const char* ssid = "INFINITUM2E26_78EXT";
const char* password = "237jQnRKYz80";
const char* mqtt_server = "192.168.1.105";

// Objetos WiFi y MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Pines de botones
const int btn1 = 32;
const int btn2 = 33;

// Variables de LEDs y estado
int Led1 = 2;
int Led2 = 4;
int Led3 = 5;
int Led4 = 18;
int Led5 = 19;
int Led6 = 21;

const int LedS[] = {2, 4, 5, 18, 19, 21};

// Variable global para almacenar el mensaje MQTT
String messageT;

void setup() {
  Serial.begin(115200);
  // Configuración de botones
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);

  // Configuración de LEDs
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);
  pinMode(Led5, OUTPUT);
  pinMode(Led6, OUTPUT);

  for (int i = 0; i < 6; i++) {
    pinMode(LedS[i], OUTPUT);
  }

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  // Conexión a la red Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

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

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  messageT = "";  // Limpiar el contenido anterior

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageT += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "esp32/homero") {
    Serial.print("Changing output to ");
  }
}

void reconnect() {
  // Reintentar conexión
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("Homero")) {
      Serial.println("connected");
      client.subscribe("esp32/homero");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // Procesar el contenido de messageT
  if(messageT == "7 0"){
    for(int x = 0; x < 6; x++) {
      digitalWrite(LedS[x], LOW);
    }
  }

  if(messageT == "7 1"){
    for(int x = 6; x > 0; x--) {
      digitalWrite(LedS[x], HIGH);
    }
  }
  
  // derecha a izquierda
  if(messageT == "8 0"){
    for(int x = 0; x < 6; x++) {
      digitalWrite(LedS[x], HIGH);
      delay(100);
      digitalWrite(LedS[x], LOW);
      delay(100);
    }
  }

  // izquierda a derecha
  if(messageT == "8 1"){
    for(int x = 6; x > -1; x--) {
      digitalWrite(LedS[x], HIGH);
      delay(100);
      digitalWrite(LedS[x], LOW);
      delay(100);
    }
  }
  if(messageT == "9 0"){
      digitalWrite(Led1, HIGH);
      delay(100);
      digitalWrite(Led2, HIGH);
          delay(100);
          digitalWrite(Led3, HIGH);
          delay(100);
          digitalWrite(Led4, HIGH);
          delay(100);
          digitalWrite(Led5, HIGH);
          delay(100);
          digitalWrite(Led6, HIGH);
          delay(100);
          digitalWrite(Led6, LOW);
          delay(100);
          digitalWrite(Led5, LOW);
          delay(100);
          digitalWrite(Led4, LOW);
          delay(100);
          digitalWrite(Led3, LOW);
          delay(100);
          digitalWrite(Led2, LOW);
          delay(100);
          digitalWrite(Led1, LOW);
          delay(100);

          digitalWrite(Led6, HIGH);
          delay(100);
          digitalWrite(Led5, HIGH);
          delay(100);
          digitalWrite(Led4, HIGH);
          delay(100);
          digitalWrite(Led3, HIGH);
          delay(100);
          digitalWrite(Led2, HIGH);
          delay(100);
          digitalWrite(Led1, HIGH);
          delay(100);
          digitalWrite(Led1, LOW);
          delay(100);
          digitalWrite(Led2, LOW);
          delay(100);
          digitalWrite(Led3, LOW);
          delay(100);
          digitalWrite(Led4, LOW);
          delay(100);
          digitalWrite(Led5, LOW);
          delay(100);
          digitalWrite(Led6, LOW);
          delay(100);
      
  }
// parpadean
    if(messageT == "9 1"){
        digitalWrite(LedS[0],HIGH);
        digitalWrite(LedS[1],HIGH);
        digitalWrite(LedS[2],HIGH);
        digitalWrite(LedS[3],HIGH);
        digitalWrite(LedS[4],HIGH);
        digitalWrite(LedS[5],HIGH);
        delay(100);
        digitalWrite(LedS[0],LOW);
        digitalWrite(LedS[1],LOW);
        digitalWrite(LedS[2],LOW);
        digitalWrite(LedS[3],LOW);
        digitalWrite(LedS[4],LOW);
        digitalWrite(LedS[5],LOW);
        delay(100);
    }
// impar y par
    if(messageT == "10 0"){
        digitalWrite(LedS[0],HIGH);
        digitalWrite(LedS[2],HIGH);
        digitalWrite(LedS[4],HIGH);
        delay(400);
        digitalWrite(LedS[0],LOW);
        digitalWrite(LedS[2],LOW);
        digitalWrite(LedS[4],LOW);
        delay(400);
        digitalWrite(LedS[1],HIGH);
        digitalWrite(LedS[3],HIGH);
        digitalWrite(LedS[5],HIGH);
        delay(400);
        digitalWrite(LedS[1],LOW);
        digitalWrite(LedS[3],LOW);
        digitalWrite(LedS[5],LOW);
        delay(200);
      
    }


    if(messageT == "1 1"){
      digitalWrite(Led1,1);

    }
    if(messageT == "1 0"){
      digitalWrite(Led1,0);

    }
    if(messageT == "2 1"){
      digitalWrite(Led2,1);

    }
      if(messageT == "2 0"){
      digitalWrite(Led2,0);

    }
      if(messageT == "3 1"){
      digitalWrite(Led3,1);

    }
    if(messageT == "3 0"){
      digitalWrite(Led3,0);
    }

    if(messageT == "4 1"){
      digitalWrite(Led4,1);
    }
    if(messageT == "4 0"){
      digitalWrite(Led4,0);
    }

    if(messageT == "5 1"){
      digitalWrite(Led5,1);
    }
    if(messageT == "5 0"){
      digitalWrite(Led5,0);
    }

    if(messageT == "6 1"){
      digitalWrite(Led6,1);
    }
    if(messageT == "6 0"){
      digitalWrite(Led6,0);
    }

  int btn1state = digitalRead(btn1);
  int btn2state = digitalRead(btn2);

  int A0state = analogRead(34);  // GPIO34 es un pin ADC
  int A1state = analogRead(35);  // GPIO35 es un pin ADC

  String myjson = "{\"ID\":\"HJ\", \"btn1\":" + String(btn1state) + ",\"btn2\":" + String(btn2state) + ", \"A0\":" + String(A0state) + ", \"A1\":" + String(A1state) + "}";
  Serial.println(myjson);

  client.publish("json/homero", myjson.c_str());

  delay(250);
}
