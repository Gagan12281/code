#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Network details
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };


const char* token  = " ";
const char* broker = "mqtt.thingsboard.cloud";
EthernetClient ethClient;
PubSubClient   client(ethClient);


void setup() 
{
  Serial.begin(9600);
  Ethernet.begin(mac);
  client.setServer(broker, 1883);
}

void reconnect()
{
  while (!client.connected())
  {
    if (client.connect("Arduino UNO", token, NULL))
    {
      Serial.println("Connected to ThingsBoard");
    }
    else
    {
      Serial.println("Retrying...");
      delay(2000);
    }
  }
}

void loop() 
{
  if (!client.connected()) reconnect();
  String msg = "{\"temperature\":24.5}";
  client.publish(
    "v1/devices/me/telemetry",
    msg.c_str());
  delay(5000);
}