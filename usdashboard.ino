#include <NinjaIoT.h>

NinjaIoT iot;

// Ultrasonic Sensor Pins
#define TRIG_PIN D5
#define ECHO_PIN D6

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Connect to WiFi and IoT account
  iot.connect("KRISHNAISA", "Udisa1111@", "UC11");   // https://iot.roboninja.in/
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;  // Convert to cm
  return distance;
}

void loop() {

  // Fetch cache values from cloud once per loop
  iot.ReadAll();

  // Read DISTANCE from cloud if needed (optional)
  String serverDistance = iot.SyncVar("distance");
  Serial.println("Distance from cloud: " + serverDistance);

  // Get actual ultrasonic value
  long distance = getDistance();
  Serial.print("Measured Distance: ");
  Serial.println(distance);

  // Send new distance value to dashboard
  iot.WriteVar("distance", String(distance));

  delay(5000); // 5 second update rate
}
