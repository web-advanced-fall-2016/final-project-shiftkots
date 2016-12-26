#include <Ethernet.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 };
EthernetClient client;

long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 250000;

const int trigPin = 13;
int echoPin = 12;
long safeZone = 12.5;
int tonePin = 4;
int proximity = 0;
int distance;
String data;

void setup() {
  Serial.begin(9600);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet");
    }

  delay(10000);

  data = "";

}

void loop() {
  long duration, cm;

  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  if (cm < safeZone)
  {
    data = "Discover a Celestial Body";
    }

  proximity = map(distance, 0, 45, 8, 0);

  if (proximity >= 7 && proximity <= 8){
    tone(tonePin, 200000, 200);
    }
  delay(200);
  noTone(tonePin);
  
  currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
  }

  if (client.connect("www.********.com",80)){
    client.println("POST /add.php HTTP/1.1");
    client.println("Host: ***.*****.com");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length");
    client.println(data.length());
    client.println();
    client.print(data);
  }

  if (client.connected()) {
    client.stop();
    }

  delay(300000);
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}
