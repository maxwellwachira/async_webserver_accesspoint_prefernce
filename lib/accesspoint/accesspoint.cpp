#include "accesspoint.h"

// Set web server port number to 80
AsyncWebServer server(80);

Preferences preferences;

void handleJsonPost(AsyncWebServerRequest *request, JsonVariant &json);

void accessPointInit (bool debug){
  // Connect to Wi-Fi network with SSID and password
  if(debug) Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(WIFI_SSID, WIFI_PWD);
  delay(2000); //to avoid crash on WiFi Connection
  IPAddress IP = WiFi.softAPIP();
  if(debug){
    Serial.print("AP IP address: ");
    Serial.println(IP);
  }
  
}

void serveHTML(bool debug){
  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }

  if(debug) Serial.println("SPIFFS mounted");


  // Start the server
  server.begin();
  if(debug) Serial.println("Server started");

  // Serve the HTML, CSS, and JS files
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Not found");
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
  server.on("/logo.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/logo.png", "image/png");
  });
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/script.js", "application/javascript");
  });

  AsyncCallbackJsonWebHandler *handler = new AsyncCallbackJsonWebHandler("/submit", [](AsyncWebServerRequest *request, JsonVariant &json) {
    handleJsonPost(request, json);
  });
  server.addHandler(handler);

}


void handleJsonPost(AsyncWebServerRequest *request, JsonVariant &json) {
  // Read the JSON data from the request body
  if (json.is<JsonObject>()) {
    JsonObject jsonObj = json.as<JsonObject>();
    // Access the parsed JSON data
    String firstName = jsonObj["firstName"].as<String>();
    String lastName = jsonObj["lastName"].as<String>();
    String email = jsonObj["email"].as<String>();
    String username = jsonObj["username"].as<String>();
    String telephone = jsonObj["telephone"].as<String>();
    String registrationNumber = jsonObj["registrationNumber"].as<String>();
    String whatsappTelephone = jsonObj["whatsappTelephone"].as<String>();
    String vehicleRegistrationNumber = jsonObj["vehicleRegistrationNumber"].as<String>();
    String vehicleMake = jsonObj["vehicleMake"].as<String>();
    String model = jsonObj["model"].as<String>();
    String yearOfMake = jsonObj["yearOfMake"].as<String>();
    String vehicleTelephone = jsonObj["vehicleTelephone"].as<String>();
    String chasisNumber = jsonObj["chasisNumber"].as<String>();
    String imei = jsonObj["imei"].as<String>();

    // Save the data to Preferences
    preferences.begin("ScanMax", false); // Open the preferences with the specified namespace
    preferences.putString("firstName", firstName);
    preferences.putString("lastName", lastName);
    preferences.putString("email", email);
    preferences.putString("username", username);
    preferences.putString("telephone", telephone);
    preferences.putString("regNumber", registrationNumber);
    preferences.putString("WhatsappNo", whatsappTelephone);
    preferences.putString("vehicleReg", vehicleRegistrationNumber);
    preferences.putString("vehicleMake", vehicleMake);
    preferences.putString("model", model);
    preferences.putString("yearOfMake", yearOfMake);
    preferences.putString("vehicleNo", vehicleTelephone);
    preferences.putString("chasisNumber", chasisNumber);
    preferences.putString("imei", imei);
    preferences.putBool("IS_INITIALIZED", true);
    preferences.end(); // Close the preferences

    Serial.println("Data Saved to preference");
    // Send a response
    request->send(200, "text/plain", "Data received successfully");
  }else {
    //Failed to parse JSON
    Serial.println("Invalid Json");
    request->send(400, "text/plain", "Invalid JSON data");
  }
}