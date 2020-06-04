#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "AndroidShaper";
const char* password = "b@ngl@desh54321";

void setup() {
  Serial.begin(115200);

  //TESTING JSON CREATION
  Serial.println("Starting JSON");
  StaticJsonBuffer<69> jsonBuffer;
  char json[] = "{\"sender\":\"558499999999\",\"content\":\"Just a message\",\"groupName\":\"Recipients_list\"}";
  JsonObject& root = jsonBuffer.parseObject(json);
  if(!root.success()) {
    Serial.println("parseObject() failed");
  } else {
    Serial.println("JSON OK");
  }


  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting... ");
  }


  //TESTING POST
  //headers={'content-type': 'application/json', 'auth-key': 'My_authentication_key'}
  String sms_service_URL = "http://my-json-server.typicode.com/rsherlocks/jesonapi/posts";
  //String sms_service_URL = "http://github.com/rsherlocks/jesonapi/blob/master/db.json";

  Serial.println("TESTING POST");
  //Declare an object of class HTTPClient
  HTTPClient http;

  if (WiFi.status() == WL_CONNECTED) {
    //Specify request destination
    http.begin(sms_service_URL);
    http.addHeader("Content-Type", "application/json");
    //http.addHeader("auth-key", "My_authentication_key");

    String data;
    root.printTo(data);
    //Send the request
    int httpCode = http.POST(data);

    //Check the returning code
    if (httpCode > 0) {
      //Get the request response payload
      String payload = http.getString();
      //Print the response payload
      Serial.println(payload);
    }
    //Close connection
    http.end();
    Serial.println(httpCode);
  }
}

void loop() {


}
