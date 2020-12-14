# Knobster encoder

This is sample code for demonstrating the function and operation of a dual encoder with push button as part of the Knobster DIY project.

The Knobster is an aviation simulator knob product that mimics knobs often used on aircraft avionics. 
It's commercially available but can also be built using less expensive parts and some electronics knowledge.

This was my first Arduino project and first time in many years programming in C++ so it also served as a refresher and introduced some things I had not yet learned, particularly those specific to the Arduino environment.

## `rotor.h`
The `rotor.h` header file contains the class prototype for a single rotor. It exposes an arbitrary internal value as well as accepts a function pointer for a rotor change callback.

## Sketch functions

### Contact LEDS
Originally this project just turned on an LED for each encoder contact point so I could understand the necessary wiring and basic Arduino programming of GPIO.

### Encoder value tracking
I added the actual encoder tracking logic to understand how the state tracking of the contact inputs is used to determine the direction. This then tracks an arbitrary positive or negative integer that increases or decreases for each rotation step. The value is meaningless apart from seeing that the state tracking logic is valid.

### Blinking built-in LED
There is a simple blink operation on the built in LED with the outer encoder increasing or decreasing the blink rate.
This demonstrates capturing a change event for use by consuming code that doesn't necessarily care about the arbitrary rotor instance internal value, just that the rotor registered a change and in what direction. This was also a opportunity to learn function pointers as well as time based operations to prevent thread blocking on the main loop for actions (i.e. blink delay) that would otherwise halt code execution.

## Pinouts

### Nano
Here are the pinouts for an Arduino Nano

* D2 - D6 - Wired to LEDs (+ required resistors in series)
* D7 - D11 - Wired to dual encoder contact points and to pull-down resistors to bias pin to LOW state.

See constants at the top of `knobster-encoder.ino` file for specific pin mappings.