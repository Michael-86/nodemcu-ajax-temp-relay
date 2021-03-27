/*
  To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
*/

#include <ESP8266WiFi.h>

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "mainPage.h"

#include "DHTesp.h"

#define DHTpin 14   //D15 of ESP32 DevKit

DHTesp dht;

const int Load1 = 4;
const int Load2 = 5;
const int Load3 = 12;
const int Load4 = 13;


const char* host = "esp8266-webupdate";
const char* ssid = "prometheus";
const char* password = "gharib12";

ESP8266WebServer server(80);

//Check if header is present and correct
bool is_authentified() {
  Serial.println("Enter is_authentified");
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      Serial.println("Authentification Successful");
      return true;
    }
  }
  Serial.println("Authentification Failed");
  return false;
}

//login page, also called for disconnect
void handleLogin() {
  String msg;
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
  }
  if (server.hasArg("DISCONNECT")) {
    Serial.println("Disconnection");
    String header = "HTTP/1.1 301 OK\r\nSet-Cookie: ESPSESSIONID=0\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }
  if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")) {
    if (server.arg("USERNAME") == "admin" &&  server.arg("PASSWORD") == "admin" ) {
      String header = "HTTP/1.1 301 OK\r\nSet-Cookie: ESPSESSIONID=1\r\nLocation: /\r\nCache-Control: no-cache\r\n\r\n";
      server.sendContent(header);
      Serial.println("Log in Successful");
      return;
    }
    msg = "Wrong username/password! try again.";
    Serial.println("Log in Failed");
  }
  String content = "<html><body><form action='/login' method='POST'>To log in, please use : admin/admin<br>";
  content += "User:<input type='text' name='USERNAME' placeholder='user name'><br>";
  content += "Password:<input type='password' name='PASSWORD' placeholder='password'><br>";
  content += "<input type='submit' name='SUBMIT' value='Submit'></form>" + msg + "<br>";
  content += "You also can go <a href='/inline'>here</a></body></html>";
  server.send(200, "text/html", content);
}

//root page can be accessed only if authentification is ok
void handleRoot() {
  Serial.println("Enter handleRoot");
  if (!is_authentified()) {
    String header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }
  String s = FPSTR(MAIN_page);

  server.send(200, "text/html", s);

}

//no need authentification
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleUpdate() {
  Serial.println("Enter handleRoot");
  String header;
  if (!is_authentified()) {
    String header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }
  String content = "<form method='POST' action='/process' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";
  if (server.hasHeader("User-Agent")) {
    content += "the user agent used is : " + server.header("User-Agent") + "<br><br>";
  }
  content += "You can access this page until you <a href=\"/login?DISCONNECT=YES\">disconnect</a></body></html>";
  server.send(200, "text/html", content);
}

void handleForm() {

}

void handlebutton1() {
  String ledState1 = "OFF";
  String t_state = server.arg("LEDstate1"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
  Serial.println(t_state);
  if (t_state == "1")
  {
    digitalWrite(Load1, LOW); //LED ON
    ledState1 = "ON"; //Feedback parameter
  }
  else
  {
    digitalWrite(Load1, HIGH); //LED OFF
    ledState1 = "OFF"; //Feedback parameter
  }

  server.send(200, "text/plane", ledState1); //Send web page
}

void handlebutton2() {
  String ledState2 = "OFF";
  String t_state = server.arg("LEDstate2"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
  Serial.println(t_state);
  if (t_state == "1")
  {
    digitalWrite(Load2, LOW); //LED ON
    ledState2 = "ON"; //Feedback parameter
  }
  else
  {
    digitalWrite(Load2, HIGH); //LED OFF
    ledState2 = "OFF"; //Feedback parameter
  }

  server.send(200, "text/plane", ledState2); //Send web page
}

void handlebutton3() {
  String ledState3 = "OFF";
  String t_state = server.arg("LEDstate3"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
  Serial.println(t_state);
  if (t_state == "1")
  {
    digitalWrite(Load3, LOW); //LED ON
    ledState3 = "ON"; //Feedback parameter
  }
  else
  {
    digitalWrite(Load3, HIGH); //LED OFF
    ledState3 = "OFF"; //Feedback parameter
  }

  server.send(200, "text/plane", ledState3); //Send web page
}

void handlebutton4() {
  String ledState4 = "OFF";
  String t_state = server.arg("LEDstate4"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
  Serial.println(t_state);
  if (t_state == "1")
  {
    digitalWrite(Load4, LOW); //LED ON
    ledState4 = "ON"; //Feedback parameter
  }
  else
  {
    digitalWrite(Load4, HIGH); //LED OFF
    ledState4 = "OFF"; //Feedback parameter
  }

  server.send(200, "text/plane", ledState4); //Send web page
}

void handletempratur() {
  //delay(dht.getMinimumSamplingPeriod());

  Serial.println("temp");
  int a = dht.getTemperature();
  String tempratur = String(a);
  server.send(200, "text/plane", tempratur); //Send ADC value only to client ajax request
}

void handleluftfuktighet() {
  //delay(dht.getMinimumSamplingPeriod());
  Serial.println("fukt");
  int b = dht.getHumidity();
  String luftfuktighet = String(b);
  server.send(200, "text/plane", luftfuktighet); //Send ADC value only to client ajax request
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  digitalWrite(Load1, HIGH);
  digitalWrite(Load2, HIGH);
  digitalWrite(Load3, HIGH);
  digitalWrite(Load4, HIGH);

  pinMode(Load1, OUTPUT);
  pinMode(Load2, OUTPUT);
  pinMode(Load3, OUTPUT);
  pinMode(Load4, OUTPUT);

  dht.setup(DHTpin, DHTesp::DHT11);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    MDNS.begin(host);
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  server.on("/", handleRoot);
  server.on("/login", handleLogin);
  server.on("/update", handleUpdate);
  server.on("/form", handleForm);
  server.on("/button1", handlebutton1);
  server.on("/button2", handlebutton2);
  server.on("/button3", handlebutton3);
  server.on("/button4", handlebutton4);
  server.on("/readtemp", handletempratur);
  server.on("/readhum", handleluftfuktighet);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works without need of authentification");
  });

  server.onNotFound(handleNotFound);
  //here the list of headers to be recorded
  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  //ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize );

  server.on("/process", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.setDebugOutput(true);
      WiFiUDP::stopAll();
      Serial.printf("Update: %s\n", upload.filename.c_str());
      uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
      if (!Update.begin(maxSketchSpace)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
      Serial.setDebugOutput(false);
    }
    yield();
  });

  server.begin();
  MDNS.addService("http", "tcp", 80);
  Serial.println("HTTP server started");
  //server.send(200, "text/plain", "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n");
}

void loop(void) {
  server.handleClient();
  delay(1);
}
