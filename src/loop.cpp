#include "loop.h"
#define DHTPIN 5     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

float getBatteryVoltage(int pin){
  int sensorValue = analogRead(pin);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (1.1*5.3 / 1023.0);
  return voltage;
}

float getBatPercentage(float voltage){
 float percentage = (voltage-3.45)*208.3-22.9;
 return constrain(percentage,0,100);
}

void battery_loop(){
  float voltage= getBatteryVoltage(A0);
  float percentage=getBatPercentage(voltage);
  Serial.print(voltage);
  Serial.print (' ');
  Serial.println (percentage);
  bat_low=(percentage < 10);

}

void recording_loop(){
  if (digitalRead(4) == HIGH) {
    delay(200);
    if (!recording){
      digitalWrite(13, HIGH);
      Serial.println("recording");
      recording= true;
    } else {
        digitalWrite(13, LOW);// put your main code here, to run repeatedly:
        Serial.println("nonrecording");
        recording=false;
      }
    }
}

void init_loop(){
  dht.begin();
}


void sensor_loop(){
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" \t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}
