Universal mute toggle button: Arduino Uno turned into a USB-HID that sends the mute toggle keyboard shortcuts.

\*Supported applications (MacOS only): Google Meets, Slack

### Development

- Prepare for dfu programming: https://arduino.stackexchange.com/questions/484/arduino-as-usb-hid
  - Use real Arduino Uno
  - Install dfu programmer
  - Reset device
- Upload program that sends keypresses over serial: http://mitchtech.net/arduino-usb-hid-keyboard/
- Flash `Arduino-keyboard-0.3.hex` firmware
  - `sudo dfu-programmer atmega16u2 erase`
  - `sudo dfu-programmer atmega16u2 flash Arduino-keyboard-0.3.hex`
  - `sudo dfu-programmer atmega16u2 reset`
- To upload a new program, flash the original `Arduino-usbserial-uno.hex` firmware

### References:

https://arduino.stackexchange.com/questions/484/arduino-as-usb-hid
http://mitchtech.net/arduino-usb-hid-keyboard/
https://www.arduino.cc/en/Hacking/DFUProgramming8U2
https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2#file-usb_hid_keys-h
