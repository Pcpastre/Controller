

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include <WiFiAP.h>
#include "FS.h"
#include "SPIFFS.h"

#define FORMAT_SPIFFS_IF_FAILED true

const uint16_t port = 8090;
const char * host = "10.0.0.101";

int pinos[] = {27, 26, 25, 33, 32};
int pressed[] = {0, 0, 0, 0, 0};

String comandos[5][2] = {
  {"d","!d"},
  {"s","!s"},
  {"a","!a"},
  {"f","!f"},
  {"g","!g"}
};

WiFiClient client;
int arquivo = 0;                                                //Variavel responsavel pela manutenção dos efeitos

String reg = " ";
boolean waitB = true;
//const char* ssid = "Speers-41801";
//const char* password = "08816009";
WebServer server(80);


void handleInfo(){
  String ssid = server.arg("ssid");
  String senha = server.arg("senha");
  String value = ssid+';'+senha+"\n";
  writeFile(SPIFFS, "/info.txt", (value.c_str()));
  server.send(200, "text/plain", "ssid: " + ssid+ " senha: "+senha+ "\n" + "Restarting");
  ESP.restart();

}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("- file written");
    } else {
        Serial.println("- write failed");
    }
    file.close();
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\r\n", path);
    if(fs.remove(path)){
        Serial.println("- file deleted");
    } else {
        Serial.println("- delete failed");
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }
    
    Serial.println("- read from file:");
    while(file.available()){
        reg = file.readStringUntil('\n');
        //Serial.write(file.read());
    }
    file.close();
}

void sendPage(){
 

  String page = htmlPage(0,0);
  server.send(200, "text/html", page);
  

}

String htmlPage(float t, float p){
   String cd = "<!DOCTYPE html>\n";
   cd += "<html lang=\"pt-br\">\n";
  cd += "<head>\n";
  cd += "<meta charset=\"UTF-8\">\n";
  cd += "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
  cd += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  cd += "<title>Rede Wifi</title>\n";
  cd += "<style>\n";
  cd += "html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  cd += "body{margin-top: 50px;} \n";
  cd += "h1 {color: #444444; margin: 50px auto 30px;}\n";
  cd += "p {font-size: 24px; color: #444444; margin-bottom: 10px;}\n";
  cd += "</style>\n";
  cd += "</head>\n";
  cd += "<body>\n";
  cd += "<div id=\"webpage\">\n";
  cd += "<form action=\"/conexao\" method=\"GET\">\n";
  cd += "SSID:\n";
  cd += "<input name=\"ssid\" type=\"text\" value=\"Seu SSID\" />\n";
  cd += "SENHA:\n";
  cd += "<input name=\"senha\" type=\"text\" value=\"Sua Senha\" />\n";;
  cd += "<input type=\"submit\" value=\"Enviar\" /></form>\n";
  cd += "</div>\n";
  cd += "</body>\n";  
  cd += "</html>\n";
  return cd;             


}







void setup(void) {
  Serial.begin(115200);
   for(int i = 0; i < 5; i++){
    pinMode(pinos[i],INPUT_PULLUP);
  }
   if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");
        return;
    }

  readFile(SPIFFS, "/info.txt");
  String ssid = (reg.substring(0, reg.indexOf(';')));
  String password = (reg.substring((reg.indexOf(';')+1), reg.length()));
  Serial.print(ssid);Serial.print(' ');Serial.println(password);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.println("");
  int Cwait = 0;
  // Wait for connection
  while(WiFi.status() != WL_CONNECTED && waitB ) {
    delay(500);
    Serial.print(".");
    Cwait++;
    if(Cwait >= 10){
      waitB = false;
      WiFi.mode(WIFI_AP);
      WiFi.softAP("conf", "12345678");
      IPAddress myIP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(myIP);
      server.begin();

      Serial.println("Server started");
    }
  }
  
  if(waitB){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    
    if (MDNS.begin("esp32")) {
      Serial.println("MDNS responder started");
    }
  
  
    server.begin();
    Serial.println("HTTP server started");
  }else{
     server.on("/", sendPage);
     server.on("/conexao", handleInfo);
  }
}
 String serverPath = " ";
 String comand = " ";
 String serverName= "http://10.0.0.101:8080/send";
void loop(void) {
 if(waitB){
      HTTPClient http;
      for(int i = 0; i < 5; i++){
        if(digitalRead(pinos[i]) == 0 && pressed[i] == 0){
             pressed[i] = 1;
             comand = comandos[i][0];
             Serial.println(comandos[i][0]);
             serverPath = serverName + "?comand=" + comand;
             http.begin(serverPath.c_str());
             int httpResponseCode = http.GET();
             Serial.println(httpResponseCode);
            
        }else if(digitalRead(pinos[i]) == 1 && pressed[i] == 1){
            pressed[i] = 0;
            comand = comandos[i][1];
            Serial.println(comandos[i][1]);
             serverPath = serverName + "?comand=" + comand;
            http.begin(serverPath.c_str());
            int httpResponseCode = http.GET();
            Serial.println(httpResponseCode);
        }
        delay(5);
          

    }
   
  }
   else{
    server.handleClient();
 }
}
