#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
int led1 = 4;
int led2 = 5;
Servo microservo;
int pos = 0;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xAD, 0xEE, 0xBE }; //physical mac address
byte ip[] = { 192, 168, 0, 180 }; // IP address in LAN – need to change according to your Network address
byte gateway[] = { 192, 168, 0, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80);                             //server port
String readString;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  microservo.attach(7);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
        }

        //if HTTP request has ended
        if (c == '\n') {
          Serial.println(readString); //print to serial monitor for debuging

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();
          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
          client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
          client.println("<link rel='stylesheet' type='text/css' href='https://www.w3schools.com/w3css/4/w3.css' />");
          client.println("<TITLE>Casa do romario</TITLE>");
          client.println("</HEAD>");
          client.println("<style>.w3-button {width:300px; margin-left: 20%;}</style>");
          client.println("<BODY>");
          client.println("<hr />");
          client.println("<br />");
          client.println("<br />");
          client.println("<H1>Minha casa</H1>");
          client.println("<hr />");
          client.println("<br />");

          client.println("<br />");
          client.println("<hr />");
          client.println("<br />");

          client.println("<br />");
          client.println("<p><a href=\"/?button2on\" class=\"w3-button w3-deep-purple\" style=\"width:600px;height: 150px !important;font-size: 60px\">Portao</a></p>");
          client.println("<br />");
          client.println("<br />");

          client.println("<p><a href=\"/?button1on\"\" class=\"w3-button w3-blue\" style=\"width:600px;height: 150px !important;font-size: 60px\" >Area - Ligar</a></p>");
          client.println("<br />");
          client.println("<p><a href=\"/?button1off\"\"  class=\"w3-button w3-red\" style=\"width:600px;height: 150px !important;font-size: 60px\">Area - Desligar</a></p><br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
        
          client.println("<br />");
          client.println("<p><a class=\"w3-button w3-blue\" style=\"width:600px;height: 150px;150px !important;font-size: 60px\" href=\"/?button1on3\"\">Q-romario - L</a></p>");
          client.println("<br />");
          client.println("<p><a class=\"w3-button w3-red\" style=\"width:600px;height: 150px !important;font-size: 60px\" href=\"/?button1off3\"\" >Q-romario - D</a></p><br />");


          client.println("</BODY>");
          client.println("</HTML>");

          delay(1);
          //stopping client
          client.stop();
          //controls the Arduino if you press the buttons
          if (readString.indexOf("?button1on") > 0) {
            digitalWrite(led1, HIGH);
          }
          if (readString.indexOf("?button1off") > 0) {
            digitalWrite(led1, LOW);
          }
          if (readString.indexOf("?button1on3") > 0) {
            digitalWrite(led2, HIGH);
          }
          if (readString.indexOf("?button1off3") > 0) {
            digitalWrite(led2, LOW);
          }

          if (readString.indexOf("?button2on") > 0) {
          

              for (pos = 20; pos < 100; pos++)
              {
                microservo.write(pos);
                delay(15);
              }



          }
          //clearing string for next read
          readString = "";

        }
      }
    }
  }
}
