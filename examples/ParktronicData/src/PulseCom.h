//
// Created by Admin on 3/22/2019.
//

#ifndef PulseCOM_H
#define PulseCOM_H

#include <Arduino.h>
#include <EnableInterrupt.h>

#ifndef EnableInterrupt_h

#include "../../libraries/EnableInterrupt/EnableInterrupt.h"

#endif

static void pulseComISR();

//
// Change if is needed more pulses or lower to lower memory usage
#ifndef pulseCom_DataLength
#define pulseCom_DataLength 16
#endif

#ifndef pulseCom_Timeout
#define pulseCom_Timeout 3000
#endif


//
// Define "PulseComDEBUG" to get length of all pulses
// #define PulseComDEBUG

class PulseCom {

private:
    boolean isReceive;
    static boolean isMicros;
    static volatile boolean isNewPulse;
    static byte state;
    static uint8_t pin;
    static volatile uint16_t pulseTime;
    static volatile unsigned long startTime;


#ifdef PulseComDEBUG
    uint16_t debug[pulseCom_DataLength];
#endif
    uint8_t dataLength = pulseCom_DataLength;
    uint8_t dataOffset;
    uint16_t longBiteTime, biteValue, timeout = pulseCom_Timeout;
    byte dataBuffer[pulseCom_DataLength], dataReceive[pulseCom_DataLength];


    void copyBuffer(byte *buffer, byte *data, uint8_t len) {
        for (uint8_t i = 0; i < len; ++i) {
            data[i] = buffer[i];
            buffer[i] = '\0';
        }
    }


    static unsigned long getTime() {
        return isMicros ? micros() : millis();
    }

    byte getBiteV1(byte value) {
        return value == B1 ? B1 : B0;
    }

    byte getBiteV2(byte value) {
        return value == B1 ? B0 : B1;
    }

    void listener() {
        if (pulseTime > 10 && isNewPulse) {
            isNewPulse = false;

            if (pulseTime >= timeout) {
                copyBuffer(dataBuffer, dataReceive, dataLength);
                dataOffset = 0;
                isReceive = true;
                return;
            }
            isReceive = false;
#ifdef PulseComDEBUG
            debug[dataOffset] = pulseTime;
#endif
            dataBuffer[dataOffset] = (byte) ((pulseTime > longBiteTime) ? getBiteV1(biteValue) : getBiteV2(biteValue));
            dataOffset++;
        }
    }


public:
/**
 * Simple setup
 * @param inputPin      Pin of input signal
 * @param longBiteTime  Time of longest pulse for bite to capture (shorter will be counted as invert state)
 * @param biteValue     Value of longest pulse (B1/B0)
 */
    PulseCom(uint8_t inputPin, uint16_t longBiteTime, uint16_t biteValue) {
        PulseCom::pin = inputPin;
        this->longBiteTime = longBiteTime;
        this->biteValue = biteValue;
        PulseCom::state = HIGH;
    }

/**
 * Advance setup
 * @param inputPin      Pin of input signal
 * @param longBiteTime  Time of longest pulse for bite to capture (shorter will be counted as invert state)
 * @param biteValue     Value of longest pulse (B1/B0)
 * @param stateCapture  HIGH or LOW state to be capture
 */
    PulseCom(uint8_t inputPin, uint16_t longBiteTime, uint16_t biteValue, byte stateCapture, uint16_t pulseTimeout) {
        PulseCom::pin = inputPin;
        this->longBiteTime = longBiteTime;
        this->biteValue = biteValue;
        PulseCom::state = stateCapture;
        timeout = pulseTimeout;
    }

/**
 * Full setup
 * @param inputPin      Pin of input signal
 * @param longBiteTime  Time of longest pulse for bite to capture (shorter will be counted as invert state)
 * @param biteValue     Value of longest pulse (B1/B0)
 * @param stateCapture  HIGH or LOW state to be capture
 * @param pulseTimeout  Time out of the pulse
 * @param isMicros      By default is false and will use millis, change to true to use micro seconds.
 */
    PulseCom(uint8_t inputPin, uint16_t longBiteTime, uint16_t biteValue, byte stateCapture, uint16_t pulseTimeout,
             uint8_t dataLength, const boolean isMicros) {
        PulseCom::pin = inputPin;
        this->longBiteTime = longBiteTime;
        this->biteValue = biteValue;
        PulseCom::state = stateCapture;
        this->timeout = pulseTimeout;
        this->isMicros = isMicros;
        this->dataLength = dataLength;
    }
/**
 *  ISR method for enableInterrupt
 */
    static void isr() {
        if (digitalRead(pin) == state && startTime == 0) { // Listen the state
            startTime = getTime();
            pulseTime = 0;
        } else {
            pulseTime = (uint16_t) (getTime() - startTime);
            startTime = 0;
            isNewPulse = true;
        }
    }

/**
 * Setup the pin
 */
    void begin() {
        pinMode(pin, INPUT_PULLUP);
        enableInterrupt(pin, pulseComISR, CHANGE);
    }

/**
 * Capture the data over pin and return true when is available
 * @return boolean
 */
    boolean available() {
        listener();
        return isReceive;
    }

/**
 * Returns all received data
 * @return array
 */
    byte *read() {
        isReceive = false;
        return dataReceive;
    }

/**
 * Returns data from index
 * @return byte
 */
    byte read(uint8_t index) {
        if (isReceive)isReceive = false;
        return dataReceive[index];
    }
/**
 * Prints captured data
 */
    void printData() {
        for (uint8_t i = 0; i < dataLength; ++i) {
            Serial.print(read(i), BIN);
        }
    }

#ifdef PulseComDEBUG

    /**
     * Returns all pulses length
     * @return
     */
        uint16_t *getDebug() {
            return debug;
        }

    /**
     * Returns captured pulse length by index
     * @param index
     * @return
     */
        uint16_t getDebug(uint8_t index) {
            return debug[index];
        }

#endif

};

static volatile boolean PulseCom::isNewPulse;
static volatile uint16_t PulseCom::pulseTime;
static volatile unsigned long PulseCom::startTime;
static byte PulseCom::state;
static uint8_t PulseCom::pin;
boolean static PulseCom::isMicros = false;

void pulseComISR() {
    PulseCom::isr();
}


#endif //PulseCOM_H
