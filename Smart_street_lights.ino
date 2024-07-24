#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

const char* ssid = "GITAM-5GHz";
const char* password = "Gitam$$123";
const int ldrPin = A0; // Defining LDR PIN
int input_val = 0; // Variable to store input values
const int ledPin = D1;
WiFiClient client;
long myChannelNumber = 2436935;
const char myWriteAPIKey[] = "YICOFEZQ1DOOKCIE";
void setup() {
   Serial.begin(9600);
   delay(1000);
   pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin, LOW); // Turn off LED initially
   pinMode(ldrPin, INPUT);
   Serial.println();
   Serial.println();
   Serial.print("Connecting to ");
   Serial.println(ssid);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) { 
      delay(200);
      Serial.print("...");
   }
   Serial.println("");
   Serial.println("WiFi connected");
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
   ThingSpeak.begin(client);
}

void loop() {
   input_val = analogRead(ldrPin);
   Serial.print("LDR Value: ");
   Serial.println(input_val);
   
   if (input_val < 600) { // Adjust threshold for darkness
      digitalWrite(ledPin, HIGH); // Turn on LED when it's dark
      Serial.println("LED is ON (Darkness detected)");
   } else {
      digitalWrite(ledPin, LOW); // Turn off LED when it's bright
      Serial.println("LED is OFF (Sufficient light detected)");
   }
   
   ThingSpeak.writeField(myChannelNumber, 1, input_val, myWriteAPIKey);
   delay(1000); // Wait for a second before reading again
}