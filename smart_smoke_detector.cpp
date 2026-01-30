#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


const int Input = 34;      
const int R_LED = 2;
const int G_LED = 4;
const int Buzzer = 5;


const char* ssid = "Realme G";
const char* password = "lanka123";
const char* botToken = "7634986263:AAFngw69cmMdTQxfvIpxp2Edzbxw-r6qI2I";
const char* chatId = "5660988484";


const int THRESHOLD_HIGH = 700; 
const int THRESHOLD_LOW  = 600; 

bool gasLeak = false;
bool messageSent = false;

void setup() {
  Serial.begin(115200);

 
  pinMode(Input, INPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);

 

  Serial.println("Warming up gas sensor...");
  delay(120000); 

  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
}


void sendMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.telegram.org/bot" + String(botToken) + "/sendMessage";
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> doc;
    doc["chat_id"] = chatId;
    doc["text"] = message;

    String requestBody;
    serializeJson(doc, requestBody);

    int responseCode = http.POST(requestBody);
    if (responseCode > 0) {
      Serial.println("Telegram message sent");
      Serial.println(http.getString());
    } else {
      Serial.print("Telegram error: ");
      Serial.println(responseCode);
    }
    http.end();
  } else {
    Serial.println("Wi-Fi not connected");
  }
}


int getSmoothedReading(int samples = 20) {
  long total = 0;
  for (int i = 0; i < samples; i++) {
    total += analogRead(Input);
    delay(5); 
  }
  return total / samples;
}

void loop() {
  int val = getSmoothedReading();
  Serial.print("Gas sensor value: ");
  Serial.println(val);

  if (!gasLeak && val >= THRESHOLD_HIGH) {
    gasLeak = true;
    digitalWrite(R_LED, HIGH);
    digitalWrite(Buzzer, HIGH);
    digitalWrite(G_LED, LOW);
    Serial.println("🚨 GAS LEAK DETECTED");

    if (!messageSent) {
      sendMessage("⚠️ Warning! Gas leak detected!");
      messageSent = true;
    }

  } else if (gasLeak && val <= THRESHOLD_LOW) {
    gasLeak = false;
    digitalWrite(R_LED, LOW);
    digitalWrite(Buzzer, LOW);
    digitalWrite(G_LED, HIGH);
    Serial.println("✅ Environment normal");
    messageSent = false;
  }

  delay(500); 
}
