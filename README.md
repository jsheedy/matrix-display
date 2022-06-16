## layout
24 x 24

## microcontroller

itsy bitsy 5v 32u4 16mhz

https://www.adafruit.com/product/3677

To upload sketch in Arduino IDE:

- use usb 2 hub
- Need to press reset button twice rapidly after initiating sketch upload

## gifs
convert gif and place into paste buffer:
```
python tools/image_to_bytes.py assets/amiga-logo.gif amiga | pbcop
```
Then paste into `gifs.h`


gifs from https://www.pouet.net/userlist.php?page=12


## arduino-cli

getting there

```
 arduino-cli compile --fqbn adafruit:avr:itsybitsy32u4_5V  .

/Users/velotron/project/u-cube/arduino/u_cube/driver.cpp:1:10: fatal error: iostream: No such file or directory
 #include <iostream>
          ^~~~~~~~~~
compilation terminated.


Used library Version Path
FastLED      3.5.0   /Users/velotron/Documents/Arduino/libraries/FastLED

Used platform Version Path
adafruit:avr  1.4.15  /Users/velotron/Library/Arduino15/packages/adafruit/hardware/avr/1.4.15
arduino:avr   1.8.5   /Users/velotron/Library/Arduino15/packages/arduino/hardware/avr/1.8.5

Error during build: exit status 1



---
config

❯ arduino-cli config init  -v
INFO[0000] Using config file: /Users/velotron/Library/Arduino15/arduino-cli.yaml
INFO[0000] arduino-cli version 0.23.0
INFO[0000] Executing `arduino-cli config init`
Config file already exists, use --overwrite to discard the existing one.
ERRO[0000] Config file already exists, use --overwrite to discard the existing one.
```


```
changed /Users/velotron/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/USBAPI.h
SERIAL_BUFFER_SIZE 64 -> 16 according to adafruit memory guide
