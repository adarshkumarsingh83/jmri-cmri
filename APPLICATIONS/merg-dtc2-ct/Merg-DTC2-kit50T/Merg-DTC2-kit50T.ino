#define X_SENSOR_PIN 7
#define Y_SENSOR_PIN 6
#define X_SENSOR_LED 13
#define Y_SENSOR_LED 12
void setup() {
  Serial.begin(9600);
  pinMode(X_SENSOR_PIN, INPUT);
  pinMode(Y_SENSOR_PIN, INPUT);
  pinMode(X_SENSOR_LED, OUTPUT);
  pinMode(Y_SENSOR_LED, OUTPUT);
}
void loop() {
  delay(1000);
  int X_SENSOR_VAL = digitalRead(X_SENSOR_PIN);
  Serial.print("X_SENSOR_VAL ");
  Serial.println(X_SENSOR_VAL);
  if (X_SENSOR_VAL < 1) {
    digitalWrite(X_SENSOR_LED, HIGH);
  } else {
    digitalWrite(X_SENSOR_LED, LOW);
  }
  int Y_SENSOR_VAL = digitalRead(Y_SENSOR_PIN);
  Serial.print("Y_SENSOR_VAL ");
  Serial.println(Y_SENSOR_VAL);
  if (Y_SENSOR_VAL < 1 ) {
    digitalWrite(Y_SENSOR_LED, HIGH);
  } else {
    digitalWrite(Y_SENSOR_LED, LOW);
  }
}
