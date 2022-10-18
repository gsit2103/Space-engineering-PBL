#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
//#include "SSD1306.h"
#include "images.h"
#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  923E6
unsigned int counter = 0;
//SSD1306 display(0x3c, 21, 22);
String rssi = "RSSI --";
String packSize = "--";
String packet ;
TinyGPSPlus gps;
HardwareSerial Serial0(2);
void setup() {
  pinMode(16,OUTPUT);
  pinMode(2,OUTPUT);
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Goodnight moon!");
  Serial0.begin(9600,SERIAL_8N1,34,12);
  Serial0.println("Hello, world?");
  Serial.println();
  Serial.println("LoRa Sender Test");
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(923E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //LoRa.onReceive(cbk);
//  LoRa.receive();
  Serial.println("init ok");
  //display.init();
  //display.flipScreenVertically();
  //display.setFont(ArialMT_Plain_10);
  delay(1500);
}
void loop() {
  int i=0;
 float ave1=0,ave2=0;
 float a[5];
 float b[5];
 while (Serial0.available() > 0){
  //Serial.println("Waiting...");
 char c = Serial0.read();
 //Serial.print(c);
 gps.encode(c);
 if (gps.location.isUpdated()){
   Serial.print("LAT=");
   Serial.println(gps.location.lat(), 6);
   Serial.print("LONG=");
   Serial.println(gps.location.lng(), 6);
   Serial.print("year=");
   Serial.println(gps.date.year());
   Serial.print("month=");
   Serial.println(gps.date.month());
   Serial.print("day=");
   Serial.println(gps.date.day());
   Serial.print("hour=");
   Serial.println(gps.time.hour());
   Serial.print("minute=");
   Serial.println(gps.time.minute());
   Serial.print("second=");
   Serial.println(gps.time.second());
   Serial.print("centisecond=");
   Serial.println(gps.time.centisecond());
   LoRa.beginPacket();
   LoRa.print(gps.location.lat(), 6); //LAT
   LoRa.print(",");
   LoRa.print(gps.location.lng(), 6); //LONG
   LoRa.print(",");
   LoRa.print(gps.date.year()); //year
   LoRa.print(",");
   LoRa.println(gps.date.month()); //month
   LoRa.print(",");
   LoRa.println(gps.date.day()); //day
   LoRa.print(",");
   LoRa.println(gps.time.hour()); //hour
   LoRa.print(",");
   LoRa.println(gps.time.minute()); //minute
   LoRa.print(",");
   LoRa.println(gps.time.second()); //second
   LoRa.print(",");
   LoRa.println(gps.time.centisecond()); //centisecond
   LoRa.endPacket();
 }
 }
  //display.clear();
  //display.setTextAlignment(TEXT_ALIGN_LEFT);
  //display.setFont(ArialMT_Plain_10);
  //display.drawString(0, 0, "Sending packet: ");
  //display.drawString(90, 0, String(counter));
  //display.display();
  // send packet
  LoRa.beginPacket();
  LoRa.print(gps.location.lat(), 6); //LAT
  LoRa.print(gps.location.lng(), 6); //LONG
  LoRa.endPacket();
  // counter++;
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
