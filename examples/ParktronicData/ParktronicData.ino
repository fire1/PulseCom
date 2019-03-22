

#define pulseCom_DataLength 49

#include "../../src/PulseCom.h"

//  sketch begin


PulseCom com(2, 180, B0, HIGH, 500, pulseCom_DataLength, true);

void setup() {
    com.begin();
    Serial.begin(250000);
    Serial.println("Starting ....");
}


const uint8_t allSensors = 6;
volatile uint16_t sensors[allSensors];
volatile uint8_t i = 0;

void loop() {


    if (com.available()) {
        Serial.println(" ");

        uint8_t byteOffset = 0, sensorOffset = 0;
        for ( i = 0; i < pulseCom_DataLength; ++i) {
            sensors[sensorOffset] |= com.read(i) << byteOffset;

            if (byteOffset > 7) {
                sensorOffset++;
                byteOffset = 0;
            }
            byteOffset++;
        }

        for (i = 0; i < allSensors; ++i) {
            Serial.print(sensors[i], HEX);
            Serial.print(":");
        }

    }

}

