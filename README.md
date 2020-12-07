# ESP8266-accesspoint_with_webui
The script opens a access point on the ESP and displays the assignd IPs via webui.
I needed a easy solution to connect a few devices on places without infrastructure and with low power consumption.
I used the sample script from [ESP8266 examples](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiAccessPoint/WiFiAccessPoint.ino) and modified it.

## Needed libraries:
There are no additional libraries needed for this project.
Only the esp libraries are required.


## Run the script:
Just download the file and change the wifi settings (wifi-ssid and wifi-password)

```
const char *ssid = "Mobile";
const char *pass = "password";
```

Compile and upload the file to your ESP and you are done :)

## Connect to the AP:
Search on your devices for the access point and connect with the wifi-password.  
After connecting the webinterface can be reached over 192.168.4.1




# have fun!
