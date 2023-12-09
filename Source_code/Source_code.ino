#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"

#include <Wire.h>                                   // library for I2C comunication
#include "SSD1306Wire.h"                      // library for display
SSD1306Wire display(0x3c, SDA, SCL);   // I2C address of display

#define M_PI 3.14159265358979323846264338327950288
#define rxGPS 2
#define txGPS 14


const double fences[1][4][2] = {{{6.8204858983033505, 80.0393034902711},
                                  {6.819987095414002, 80.03894067632345},
                                  {6.8198425851495905, 80.03934932751609},
                                  {6.8203178072431125, 80.03965160673627},} };


const double fences2[1][4][2] = {{{6.820952193896416, 80.03918215794732},
                                  {6.820811219157185, 80.03835547007998},
                                  {6.819890334759238, 80.03879056895752},
                                  {6.82049288894821, 80.03933558755153},} };

const double fences3[1][4][2] = {{{6.821128788480717, 80.03923864356366},
                                  {6.8214645268922744, 80.03866190536056},
                                  {6.820983090606244, 80.03852665259612},
                                  {6.820943815519457, 80.0392054683573},} };

const double fences4[1][4][2] = {{{8.114391351597599, 80.28308381449742},
                                  {8.113505440104378, 80.28355692048575},
                                  {8.11381803226819, 80.28456686525602},
                                  {8.114443215866412, 80.28425111240831},} };



/*Variables to store AP credentials*/
String ssid = "Dialog 4G 005";
String password = "683fbDA7";
int WiFiConnectMode = 1; /* 0: smart config; 1: hard code*/

double latitude, longitude;
int sat;
String date;
String loca;
char lati[12];
char longi[12];
int targetStatus;
int fence;
char cumulativeAngle[12];
int deviceStatus = 0;
char my_str[5];


SoftwareSerial gpsSerial(rxGPS, txGPS);
TinyGPSPlus gps;
ESP8266WebServer gpsServer(80);

void connectWifi();
void updateLatLon();
void pip();
void pip2();
void pip3();
void pip4();
void handleRoot();
void fenceSelect();
void gps_data();

void setup(){
    Serial.begin(9600);
    gpsSerial.begin(9600);
    connectWifi();

    gpsServer.on("/", handleRoot);
    gpsServer.on("/status", fenceSelect);
    gpsServer.on("/values", gps_data);
    gpsServer.begin();

    display.init();                                         // initializing display
    display.flipScreenVertically();               //command to rotate orientation of display
    display.clear();                                     // clear any previous print on display
}
 
void loop(){

   
    
    // 1 sec loop delay 
  gps_data();

    while (gpsSerial.available()){
        deviceStatus = 1;
        updateLatLon();
        pip();  
        pip2();
        pip3(); 
        pip4();     
        gpsServer.handleClient();
    }
    gpsServer.handleClient();
}

void connectWifi(){
    if(WiFiConnectMode == 0){
        // Operate the ESP12E in wifi station mode for smart config
        WiFi.mode(WIFI_STA);

        // Begin the smart configuration to get the Access Point credentials
        WiFi.beginSmartConfig();
        Serial.println("------------------------------------------------");
        Serial.print("Waiting for SmartConfig ");
        while (!WiFi.smartConfigDone()) {
            delay(250);
            Serial.print(".");
        }
        Serial.println();
        Serial.println("SmartConfig done.");

        // Print the AP credentials to the serial monitor
        ssid = WiFi.SSID();
        password = WiFi.psk();
        Serial.println("------------------------------------------------");
        Serial.print("Acesspoint SSID : ");
        Serial.println(ssid);
        Serial.print("Acesspoint password : ");
        Serial.println(password);
        Serial.println("------------------------------------------------");

        // Connect the ESP12E to the AP
        Serial.print("Connecting to Access Point ");
        while (WiFi.status() != WL_CONNECTED) {
            delay(100);
            Serial.print(".");
        }
        Serial.println();
        Serial.println("Connected.");
        Serial.println("------------------------------------------------");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        Serial.println("------------------------------------------------");
    }
    else{
        String ssid = "Dialog 4G 005";
        String password = "683fbDA7";
        WiFi.begin(ssid,password);
        Serial.println("------------------------------------------------");
        Serial.print("Connecting to Access Point ");
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        Serial.println("------------------------------------------------");
    }
}

void updateLatLon(){
    if (gps.encode(gpsSerial.read()))
    {  
      sat = gps.satellites.value();
      latitude = gps.location.lat();
      longitude = gps.location.lng();
      dtostrf(latitude,9,7,lati);
      dtostrf(longitude,9,7,longi);
      Serial.print("SATS: ");
      Serial.println(sat);
      Serial.print("LAT: ");
      Serial.println(latitude,6);
      Serial.print("LONG: ");
      Serial.println(longitude,6);
      Serial.print("ALT: ");
      Serial.println(gps.altitude.meters());
      Serial.print("SPEED: ");
      Serial.println(gps.speed.mps());
 
      Serial.print("Date: ");
      date = String(gps.date.day())+"/"+gps.date.month()+"/"+gps.date.year();
      Serial.println(date);
 
      Serial.print("Hour: ");
      Serial.print(gps.time.hour()); Serial.print(":");
      Serial.print(gps.time.minute()); Serial.print(":");
      Serial.println(gps.time.second());
      Serial.println("---------------------------");
      Serial.println(my_str);
     
      delay(1000);
    }
}

void pip(){
    int fenceSize = sizeof(fences[0])/sizeof(fences[0][0]);
    double vectors[fenceSize][2];
    for(int i = 0; i < fenceSize; i++){
        vectors[i][0] = fences[0][i][0] - latitude;
        vectors[i][1] = fences[0][i][1] - longitude;
    }
    double angle = 0;
    double num, den;
    for(int i = 0; i < fenceSize; i++){
        num = (vectors[i%fenceSize][0])*(vectors[(i+1)%fenceSize][0])+ (vectors[i%fenceSize][1])*(vectors[(i+1)%fenceSize][1]);
        den = (sqrt(pow(vectors[i%fenceSize][0],2) + pow(vectors[i%fenceSize][1],2)))*(sqrt(pow(vectors[(i+1)%fenceSize][0],2) + pow(vectors[(i+1)%fenceSize][1],2)));
        angle = angle + (180*acos(num/den)/M_PI);
    }
    dtostrf(angle,9,7,cumulativeAngle);
    if(angle > 355 && angle < 365){
        
        Serial.println("You are at SOC ");
        display.clear();
        display.setFont(ArialMT_Plain_24);                        // initializing the font type and size
        display.drawString(0, 20, "SOC");               //(  row number , column number, "text")
        display.display();                                                   // order to display on screen 
         
        
        delay(1000);
        
        
        }
    
}

void pip2(){
    int fenceSize = sizeof(fences2[0])/sizeof(fences2[0][0]);
    double vectors[fenceSize][2];
    for(int i = 0; i < fenceSize; i++){
        vectors[i][0] = fences2[0][i][0] - latitude;
        vectors[i][1] = fences2[0][i][1] - longitude;
    }
    double angle = 0;
    double num, den;
    for(int i = 0; i < fenceSize; i++){
        num = (vectors[i%fenceSize][0])*(vectors[(i+1)%fenceSize][0])+ (vectors[i%fenceSize][1])*(vectors[(i+1)%fenceSize][1]);
        den = (sqrt(pow(vectors[i%fenceSize][0],2) + pow(vectors[i%fenceSize][1],2)))*(sqrt(pow(vectors[(i+1)%fenceSize][0],2) + pow(vectors[(i+1)%fenceSize][1],2)));
        angle = angle + (180*acos(num/den)/M_PI);
    }
    dtostrf(angle,9,7,cumulativeAngle);
    if(angle > 355 && angle < 365){
        Serial.println("You are at SOB ");
        display.clear();
        display.setFont(ArialMT_Plain_24);                        // initializing the font type and size
        display.drawString(0, 20, "SOB");               //(  row number , column number, "text")
        display.display();                                                   // order to display on screen 
         
        
        delay(1000);
        
        }
    
}

void pip3(){
    int fenceSize = sizeof(fences3[0])/sizeof(fences3[0][0]);
    double vectors[fenceSize][2];
    for(int i = 0; i < fenceSize; i++){
        vectors[i][0] = fences3[0][i][0] - latitude;
        vectors[i][1] = fences3[0][i][1] - longitude;
    }
    double angle = 0;
    double num, den;
    for(int i = 0; i < fenceSize; i++){
        num = (vectors[i%fenceSize][0])*(vectors[(i+1)%fenceSize][0])+ (vectors[i%fenceSize][1])*(vectors[(i+1)%fenceSize][1]);
        den = (sqrt(pow(vectors[i%fenceSize][0],2) + pow(vectors[i%fenceSize][1],2)))*(sqrt(pow(vectors[(i+1)%fenceSize][0],2) + pow(vectors[(i+1)%fenceSize][1],2)));
        angle = angle + (180*acos(num/den)/M_PI);
    }
    dtostrf(angle,9,7,cumulativeAngle);
    if(angle > 355 && angle < 365){
        Serial.println("You are at SOE ");
        display.clear();
        display.setFont(ArialMT_Plain_24);                        // initializing the font type and size
        display.drawString(0, 20, "SOE");               //(  row number , column number, "text")
        display.display();                                                   // order to display on screen 
         
        
        delay(1000);
        
        
        }
    
}

void pip4(){
    int fenceSize = sizeof(fences4[0])/sizeof(fences4[0][0]);
    double vectors[fenceSize][2];
    for(int i = 0; i < fenceSize; i++){
        vectors[i][0] = fences4[0][i][0] - latitude;
        vectors[i][1] = fences4[0][i][1] - longitude;
    }
    double angle = 0;
    double num, den;
    for(int i = 0; i < fenceSize; i++){
        num = (vectors[i%fenceSize][0])*(vectors[(i+1)%fenceSize][0])+ (vectors[i%fenceSize][1])*(vectors[(i+1)%fenceSize][1]);
        den = (sqrt(pow(vectors[i%fenceSize][0],2) + pow(vectors[i%fenceSize][1],2)))*(sqrt(pow(vectors[(i+1)%fenceSize][0],2) + pow(vectors[(i+1)%fenceSize][1],2)));
        angle = angle + (180*acos(num/den)/M_PI);
    }
    dtostrf(angle,9,7,cumulativeAngle);
    if(angle > 355 && angle < 365){
        Serial.println("silvooo ");
        display.clear();
        display.setFont(ArialMT_Plain_24);                        // initializing the font type and size
        display.drawString(0, 20, "MY HOME");               //(  row number , column number, "text")
        display.display();                                                   // order to display on screen 
         
        
        delay(1000);}
    
}
void handleRoot(){
    String s = webpage;
    gpsServer.send(200, "text/html", s);
}

void fenceSelect(){
    fence = gpsServer.arg("fenceValue").toInt();
    gpsServer.send(200, "text/plane", String(fence));
}

void gps_data(){
    String payload = String(sat) + "#" + date + "#" + lati + "#" + longi;
    if(targetStatus == 0)
        payload = payload + "#outside";
    else {
        payload = payload + "#INSIDE";
        char my_str[] = "Hello";
        Serial.println("locahh ");
        }

        
    payload = payload + "#" + cumulativeAngle;
    if(deviceStatus == 0)
        payload = payload + "#offline";
    else
        payload = payload + "#online";
    gpsServer.send(200, "text/plane", payload);
}
