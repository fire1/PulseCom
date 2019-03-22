# PulseCom
Provides universal library to read data from protocols that are using pulse length to define bytes. 
This library uses "EnableInterrupt" library in order to allow more pins to be used for communication.

## Basic usage

__Constructor:__
 *  inputPin      - Pin of input signal
 *  longBiteTime  - Time of longest pulse for bite to capture (shorter will be counted as invert state)
 *  biteValue     - Value of longest pulse (B1/B0)
 *  stateCapture  - HIGH or LOW state to be capture
 *  pulseTimeout  - Time out of the pulse
 *  isMicros      - By default is false and will use millis(), change to true to use micro seconds.
 
`
PulseCom com(uint8_t inputPin, uint16_t longBiteTime, uint16_t biteValue, byte stateCapture, uint16_t pulseTimeout, uint8_t dataLength, const boolean isMicros)
`

__Setup:__

`
com.begin();
`

__Loop:__

`
if (com.available()) {
    com.read(); // or com.printData(); to print data
}
`
## Debug

Define "PulseComDEBUG" to get length of all pulses from "getDebug" method.


## Dependency

Consider to check "EnableInterrupt" library for available pins.
(https://github.com/GreyGnome/EnableInterrupt)
 
## License

Copyright (C) 2017  Arduino AG (http://www.arduino.cc/)

Based on the TinyGSM library https://github.com/vshymanskyy/TinyGSM
Copyright (c) 2016 Volodymyr Shymanskyy

MKR WAN library is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MKR WAN library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with MKR WAN library.  If not, see <http://www.gnu.org/licenses/>.
