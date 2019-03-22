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

```
if (com.available()) {
    com.read(); // com.read(index); or com.printData(); to print data
}
```
## Debug

Define "PulseComDEBUG" to get length of all pulses from "getDebug" method.


## Dependency

Consider to check "EnableInterrupt" library for available pins.
(https://github.com/GreyGnome/EnableInterrupt)
 
## License

Copyright (C) 2017  Arduino AG (http://www.arduino.cc/)

You should have received a copy of the GNU Lesser General Public License
along with this library.  If not, see <http://www.gnu.org/licenses/>.
