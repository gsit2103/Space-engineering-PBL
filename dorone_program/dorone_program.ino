//宇宙工学PBLドローンwifiお試し
#include <WiFi.h>
const char *ssid="ESP32-WiFi"; //SSID
const char *pass="use-esp32";  //password
const int port =11411;

const IPAddress local_ip(192,168,0,9); //サーバーのIPアドレス
const IPAddress server_ip(192,168,1,3);
const IPAddress subnet(255,255,255,0);
WiFiClient client;
//WiFiServer server(80);
void setup() {
   Serial.begin(115200);
   WiFi.softAP(ssid,pass);  //SSIDとパスの設定
   delay(100); //接続失敗防止
   WiFi.softAPConfig(local_ip,local_ip,subnet);  //IPアドレス、ゲートウェイ、サブネットマスクの設定
   
   Serial.print("AP IP address：");
   IPAddress myIP = WiFi.softAPIP(); //WiFi.softAPIP()でWiFi起動
   Serial.println(myIP);
   
   Serial.print("Loacl port:");
   Serial.println(port);
   client.connect(server_ip,port);
   Serial.println("Server start!");
   
}

void loop() {
   if (client.available()){
     int val =client.read();
     Serial.printf("%c\n",val);
   }
   if (Serial.available()){
     Serial.read();
     const char *write_data="a";
     Serial.printf("write\n");
     client.write(write_data,1);
   }
}
