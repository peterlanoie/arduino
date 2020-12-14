#include "rotor.h"

const byte KNOB_ROTA_O = 2;
const byte KNOB_ROTB_O = 3;
const byte KNOB_ROTa_O = 4;
const byte KNOB_ROTb_O = 5;
const byte KNOB_BUTT_O = 6;

const byte KNOB_ROTA_I = 7;
const byte KNOB_ROTB_I = 8;
const byte KNOB_ROTa_I = 9;
const byte KNOB_ROTb_I = 10;
const byte KNOB_BUTT_I = 11;

const byte BLINKLED = LED_BUILTIN;

unsigned long _lastMs = 0;
int _blinkDelay = 250;
byte _blinkState = LOW;

byte _buttonState = LOW;
Rotor _inner(KNOB_ROTA_I, KNOB_ROTB_I);
Rotor _outer(KNOB_ROTa_I, KNOB_ROTb_I);

void setup() {
  for(byte i = KNOB_ROTA_O; i <= KNOB_BUTT_O; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
    delay(100);
    digitalWrite(i, LOW);
  }
  pinMode(BLINKLED, OUTPUT);
  digitalWrite(BLINKLED, LOW);

  _outer.setOnChangeCallback(&outerRotorOnChange);
  
  for(byte i = 7; i <= 11; i++){
    pinMode(i, INPUT);
  }
  _buttonState = digitalRead(KNOB_BUTT_I);
  Serial.begin(9600);
  Serial.println("hello world");
}

void loop() {

  for(byte i = KNOB_ROTA_I; i <= KNOB_BUTT_I; i++){
    digitalWrite(i-5, digitalRead(i));
  }

  byte buttonStateNew = digitalRead(KNOB_BUTT_I);
  if(_buttonState != buttonStateNew){
    if(buttonStateNew == HIGH){
      Serial.println("button PRESSED");
    } else {
      Serial.println("button RELEASED");
    }
    _buttonState = buttonStateNew;
  }

  unsigned long currentMs = millis();
  
  if(_lastMs + _blinkDelay <= currentMs){
//    Serial.println(currentMs);
    _blinkState = _blinkState == HIGH ? LOW : HIGH;
    digitalWrite(BLINKLED, _blinkState);
    
    _lastMs = currentMs;
  }
  
  bool innerChanged = _inner.checkState();
  bool outerChanged = _outer.checkState();
  if(innerChanged || outerChanged){
    Serial.print("outer rotor: ");
    Serial.print(_outer.getValue());
    Serial.print(" inner rotor: ");
    Serial.print(_inner.getValue());
    Serial.println();
  }
  
}

void outerRotorOnChange(int dir){
//  Serial.print("outer rotor changed: ");
//  Serial.print(dir);
  _blinkDelay = min(max(_blinkDelay + (dir * -25), 25), 2000);
//  Serial.print(" blink delay now: ");
//  Serial.println(_blinkDelay);
}
