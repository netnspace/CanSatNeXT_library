/*
  The analog-to-digital converters in ESP32 and Arduino are not very linear. This code uses a polynomial correction function, that correlates
  the input value to the real voltage, improving the linearity and making the conversion easier. Inside the dynamic range of 0.13-3.13 V,
  the RMS error is only 0.01 volts when using this function.
*/

#include "CanSatNeXT.h"

void setup() {
  Serial.begin(115200);
  CanSatInit();
}

void loop() {

    // This is the normal way to read the ADC in Arduino. We read the voltage from the LDR pin (34).
    int value = analogRead(LDR);

    // Convert the value to voltage. The function uses a third-degree polynomial to calculate the voltage
    float LDRVoltage = adcToVoltage(value);

    // We can also read directly the voltage value, this time from the BATT line. Note that the battery voltage is read from inside the resistor network. So this is not the real battery voltage.
    float batteryVoltage = analogReadVoltage(BATT);

    Serial.print("Value: ");
    Serial.print(value);
    Serial.print(", LDR voltage: ");
    Serial.print(LDRVoltage);
    Serial.print(", Battery voltage: ");
    Serial.println(batteryVoltage);


    // Let's also blink the LED, since blinking lights are fun
    delay(900);
    digitalWrite(LED, LOW);
    delay(100);
    digitalWrite(LED, HIGH);
}
