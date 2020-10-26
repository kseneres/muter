// http://mitchtech.net/arduino-usb-hid-keyboard/
// https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2#file-usb_hid_keys-h

#define KEY_MOD_LCTRL  0x01
#define KEY_MOD_LSHIFT 0x02
#define KEY_MOD_LALT   0x04
#define KEY_MOD_LMETA  0x08
#define KEY_MOD_RCTRL  0x10
#define KEY_MOD_RSHIFT 0x20
#define KEY_MOD_RALT   0x40
#define KEY_MOD_RMETA  0x80

#define KEY_A 0x04
#define KEY_D 0x07
#define KEY_M 0x10

const uint8_t PIN_BUTTON = 12;
const uint8_t PIN_LED = 13;

// keyboard report buffer 
uint8_t buf[8] = { 0 };  
  
bool buttonState = false; 
bool previousButtonState = false; 

uint32_t pushTime;
uint32_t releaseTime;
const uint32_t PTT_THRESHOLD_MILLIS = 500; 

void setup() {
  Serial.begin(9600);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(PIN_BUTTON);

  // exit early if button state hasn't changed
  if (buttonState == previousButtonState) {
    return;
  }

  // pull-up resistor means button logic is inverted, so LOW means pushed
  if (buttonState == LOW) {  
    pushTime = millis(); 
    digitalWrite(PIN_LED, HIGH);
    toggleMute();
  } else {
    releaseTime = millis();
    digitalWrite(PIN_LED, LOW);

    // toggle mute again after button was pushed for a while (act as push-to-talk)
    if (releaseTime > pushTime && releaseTime - pushTime > PTT_THRESHOLD_MILLIS) {
      toggleMute();  
    }
  }
  previousButtonState = buttonState;

  // short delay for "debouncing"
  delay(100);
}

void toggleMute() {
  // Serial.println("send"); 
  
  // google meets: cmd + d
  sendKey(KEY_MOD_LMETA, KEY_D);

  // zoom: cmd + shift + a
  // sendKey(KEY_MOD_LMETA | KEY_MOD_LSHIFT, KEY_A);

  // slack: m
  sendKey(0, KEY_M);
}

void sendKey(uint8_t mod, uint8_t key) {
  buf[0] = mod;
  buf[2] = key;
  Serial.write(buf, 8); 

  // send "release" key
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); 
}
