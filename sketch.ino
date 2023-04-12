#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, I Learn BMI Predicition");

  WiFi.begin(ssid, password);
  Serial.println("Wait Connecting");
  while(WiFi.status()!=WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }

  Serial.println("Koneksi Wifi IP");
  Serial.println(WiFi.localIP());

}

void loop() {
  String jsonbmi;
  const size_t CAPACITY = JSON_OBJECT_SIZE(8);
  StaticJsonDocument<CAPACITY> docpost;
  JsonObject obj = docpost.to<JsonObject>();
  obj["gender"] = 0;
  obj["height"] = 120;
  serializeJson(docpost, jsonbmi);

  Serial.println("["+jsonbmi+"]");

  HTTPClient http;

  http.begin("https://bmi-prediction.muhammad-ikhw16.repl.co/api/predict");
  http.addHeader("Content-Type", "application/json");

  int httpresp = http.POST("["+jsonbmi+"]");
  if(httpresp > 0){
    String response = http.getString();
    Serial.println(response);
    Serial.println(httpresp);
  }else{
    Serial.println(httpresp);
  }
  http.end();
  delay(1000);
}
