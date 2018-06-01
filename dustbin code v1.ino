

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "pinky"; // wifi name
const char* password = "0123456789";  // password
const char* mqtt_server = "34.226.134.195";   // broker 
const int trigPin = 5;  //D1
const int echoPin = 4;  //D2

int previousdistance=0;

// defines variables
int duration;
int distance;
WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];
int level = 0;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input     
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("connecting....");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
Serial.print("duration");
Serial.println(duration);

// Calculating the distance
distance= (duration*0.034)/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(2000);

Serial.println("PREVIOUS DISTANCE- BEFORE");
Serial.println(previousdistance);

if (distance != previousdistance);
  char mesg[20];
  String msg = String(distance);
  msg.toCharArray(mesg,20);
  Serial.print("MESG ::: ");  
  Serial.println(mesg);
  if (client.connect("c")){
    Serial.println("sending message");
    client.publish("smart-demo-T6", mesg);    
    }
  
  delay(5000);
previousdistance = distance;
Serial.println("PREVIOUS DISTANCE - AFTER");

delay(1000);

}


 
    
  

