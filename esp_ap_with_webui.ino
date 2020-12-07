/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.
   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.
 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/* Modified by Kai Broeker (2020) */

/* Create a WiFi access point and provide a web server with the client IPs on it. */

/* load libs */
#include <ESP8266WiFi.h>

/* configuration  wifi */
const char *ssid = "Mobile";
const char *pass = "password";

/* configure webserver */
unsigned long previousTime = 0;
const long timeoutTime = 2000;
WiFiServer server(80);
String header;
unsigned long currentTime = millis();

/* AP client variables */
struct station_info *stat_info;
struct ip4_addr *IPaddress;
IPAddress address;
unsigned char num_clients

/* setup function */
void setup() {
  //delay(1000);
  WiFi.softAP(ssid, pass);

  IPAddress myIP = WiFi.softAPIP();
  //AP has the IP: 192.168.4.1

  server.begin();
}


void loop() {
  WiFiClient client = server.available();

  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("</head><body>");
            client.println("<div><h1>ESP AP</h1></div>");

            /*
            client.println("<div>Cleints connected: ");
            num_clients = wifi_softap_get_station_num();
            client.println(num_clients);
            client.println("</div>");
            client.println("<div><h3>IP list:</h3></div>");
            /* print client IPs and MACs */
            stat_info = wifi_softap_get_station_info();
            while (stat_info != NULL) {
              IPaddress = &stat_info->ip;
              address = IPaddress->addr;

              client.println("<div>");
              /* Client IP */
              client.print("IP= ");
              client.print((address));
              /* Client MAC Address */
              client.print(",  MAC= ");
              client.print(stat_info->bssid[0], HEX); client.print(":");
              client.print(stat_info->bssid[1], HEX); client.print(":");
              client.print(stat_info->bssid[2], HEX); client.print(":");
              client.print(stat_info->bssid[3], HEX); client.print(":");
              client.print(stat_info->bssid[4], HEX); client.print(":");
              client.print(stat_info->bssid[5], HEX); client.print("");
              client.println("</div>");

              stat_info = STAILQ_NEXT(stat_info, next);
            }

            // The HTTP response ends with another blank line
            client.println();
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

      }
    }
  }
  header = "";
  // Close the connection
  client.stop();

}
