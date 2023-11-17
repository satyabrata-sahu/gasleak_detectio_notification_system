#include "twilio.hpp"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

static const char *ssid = "ssid";
static const char *password = "123456789";

static const char *account_sid = "AC3eee1e3f908089786fhc";//give your sid & auth_token
static const char *auth_token = "49911f222dd68779779gghg";
static const char *from_number = "+1913888888";//TWILIO NO.
static const char *to_number = "+917890000000";// Your no.
static const char *message = "flammable gas detected";

Twilio *twilio;
int Sensor_input = 34;
int relay_out=15;

void setup() {
  
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relay_out,OUTPUT);
  digitalWrite(relay_out,HIGH);
  connecte();

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}

 

  void loop(){
digitalWrite(relay_out,HIGH);
  int sensor_Aout = analogRead(Sensor_input);
   Serial.print("Gas Sensor: ");  
  Serial.print(sensor_Aout); 
  Serial.print("\t");
  Serial.print("\t");

  display.clearDisplay();
    display.setCursor(0,0);  //oled display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Analog value ");
    display.setCursor(0,18);  //oled display
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.print(sensor_Aout);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println("");
    display.display();
    
   if(sensor_Aout>100){
    Serial.println("gas detect");
    digitalWrite(relay_out,LOW);
    mess();
   
    }
    else{
      Serial.println("errore");
      }
    delay(1000);
    
    }


void mess(){
  twilio = new Twilio(account_sid, auth_token);
  delay(200);
 String response;
  bool success = twilio->send_message(to_number,from_number,message,response);
  if (success) {
     display.setTextSize(1.5);
      display.setTextColor(WHITE);
      display.setCursor(0,50);
      display.println("Message sent"); // Print text
      display.display();
      delay(500);
    Serial.println("Sent message successfully!");
  } else {
    Serial.println(response);
  }
  }

  void connecte(){
    WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting..."); 
    blinking();      
    delay(500);
  }
  Serial.println("Connected!");
  
    }

    void blinking(){
   digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(600);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(600);                   
      }
