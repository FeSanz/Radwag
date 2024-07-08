 #include <WiFi.h>

const char * ssid = "FN-WIFI"; 
const char * password = "R0u73rF354nz*";

//Totalplay-15A7-5G   Mi Poco     FN-WIFI          Plazteca5        WOW01       XA-SIS3 7485        CI&S Services
//SPACE2022!          1245678*0   R0u73rF354nz*    NoCompartir#24   wowwowwow   Porlomientras6590   CI&S2x20

WiFiServer wifiServer(4001);
String request;
float peso = 0;
float total = 0;
 

IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 101);

IPAddress subnet(255, 255, 254, 0);


void setup()
{
 
  Serial.begin(115200);
  //WiFi.mode(WIFI_STA);
  //WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, password);


  delay(100);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.println(WiFi.macAddress());
 
  Serial.print("WiFi conectado con IP: ");
  Serial.println(WiFi.localIP());
  wifiServer.begin();
}

void loop() {
  WiFiClient client = wifiServer.available();

  if (client) {
    while (client.connected()) {
        if (Serial.available() > 0) 
        {
          String inputText = Serial.readStringUntil('\n');
          peso = inputText.toFloat();
        }
      while (client.available()>0) {
        request = client.readString();
        char buffer[1024]="";
        if(request == "Z\r\n")
        {
          client.write("Z A\r\n");
          client.write("Z D\r\n");
        }
        if(request == "T\r\n")
        {
          client.write("T A\r\n");
          delay(1000);
          client.write("T D\r\n");
        }
        if(request == "OT\r\n")
        {
          sprintf(buffer, "OT_%9.2f_kg*_\r\n", peso);
          
          Serial.print(buffer);
          client.write(buffer);
          total = 0; //Regresar peso 0 cuando se ha obtenido tara
        }
        if(request == "S\r\n")
        {
          client.write("S A\r\n");
          delay(500);
          //total = peso + total;
          //sprintf(buffer, "S    +%f        _kg*\r\n", peso);
          //S    +      12.5_kg
          //double randomValue = 1 + static_cast<double>(random()) / RAND_MAX * (1500 - 1);
          sprintf(buffer, "S    +%9.2f_kg*\r\n",  peso);
          Serial.print(buffer);
          client.write(buffer);
          //client.write("S I\r\n");
        }
      }
    }
    client.stop();
    //Serial.println("¡¡Cliente desconectado!!");
  }
}