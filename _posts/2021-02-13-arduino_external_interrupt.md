---
layout: single
title: \[Arduino Uno\] External interrupt
date : 2021-02-13 22:23:45 +0900
last_modified_at: 2021-02-14 23:32:35 +0900
categories: [arduino]
tags: [arduino]
comments: true
public : true
use_math : true
---

# External interrupt
 On the Arduino Uno board, digital input pin 2 and 3 can be used as interrupt pins. A interrupt handler for an interrupt can be registered with the attachInterrupt() and digitalPinToInterrupt() functions.

## circuit
 In this circuit, two input buttons are connected to digital input pins 2 and 3, and when the button connected to No.2 is pressed, the "count" variable in source code is increased, and when the button connected to No.3 is pressed, the "count" variable is decreased. The value of "count" variable is expressed as a single digit 7segment.\
 Each of the two buttons is connected to GND(0V) on one side and digital input pins 2 and 3 on the other. When the button is pressed, logic Low(0V) is input to the input pin, and to make the input pin logic High(5V) when the button is not pressed, it is set to use the internal pullup resistor of pins 2 and 3 in software instead of using a separate pullup resistor externally.\
 7segment used in this circuit is common anode type. For noise that may occur when pressing or releasing a button, the software ignores continuous input for a certain period of short time, and after that period read the digital input pin value and change "count" value according to its input value. So hardware components such as capacitor are not used here.
  
 ![Arduino external interrupt](/assets/images/arduino_external_interrupt.png){:width="100%"}


## code
 The interrupt handler countInc() and countDec() for input pins 2 and 3 are registered using attachInterrupt() and digitalPinToInterrupt() functions.\
  In the interrupt handlers, only the values of "incButtonPressed" and "decButtonPressed" are changed, and noise check for input, "count" value change and showing in 7segment are done in loop(). INPUT_PULLUP is activated for input pins 2 and 3, and if "incButtonPressed" or "decButtonPressed" is true in the isNoise() function, and if the difference between the current time and the time of previous input is within 10ms, it is regarded as noise and ignored. In the case of difference is more than 10ms, the values of input pins are read and the "count" value is changed accordingly.

```c
#define NUM_0 {0, 0, 0, 0, 0, 0, 1}
#define NUM_1 {1, 0, 0, 1, 1, 1, 1}
#define NUM_2 {0, 0, 1, 0, 0, 1, 0}
#define NUM_3 {0, 0, 0, 0, 1, 1, 0}
#define NUM_4 {1, 0, 0, 1, 1, 0, 0}
#define NUM_5 {0, 1, 0, 0, 1, 0, 0}
#define NUM_6 {0, 1, 0, 0, 0, 0, 0}
#define NUM_7 {0, 0, 0, 1, 1, 0, 1}
#define NUM_8 {0, 0, 0, 0, 0, 0, 0}
#define NUM_9 {0, 0, 0, 0, 1, 0, 0}
#define DECIMAL_POINT (0)

#define DEBOUNCE_TIME (10)

int num_array[10][7] = {
	NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
};

int count = 0;
unsigned int prev_ms = 0;
unsigned int current_ms = 0;
const int interruptIncreasePin = 2;
const int interruptDecreasePin = 3;
volatile bool incButtonPressed = false;
volatile bool decButtonPressed = false;

/* 7 segment pin number */
int seg_port[] = {4, 5, 6, 7, 8, 9, 10};

bool isNoise() {
	if (incButtonPressed || decButtonPressed) {
		incButtonPressed = false;
		decButtonPressed = false;
		current_ms = millis();

		if (current_ms - prev_ms > DEBOUNCE_TIME) {
			prev_ms = current_ms;
			return false;
		}
	}
	return true;
}

void readAndUpdateCountValue()
{
	if (digitalRead(interruptIncreasePin) == LOW) {
		count++;
	}
	if (digitalRead(interruptDecreasePin) == LOW) {
		if (count <= 0) {
			count = 10;
		}
		count--;
	}
}

void countInc()
{
	incButtonPressed = true;
}

void countDec()
{
	decButtonPressed = true;
}

void setup() {  
	for (int i = 0; i < sizeof(seg_port)/sizeof(seg_port[0]); i++) {
		pinMode(seg_port[i], OUTPUT);
	}

	pinMode(11, OUTPUT);
	digitalWrite(11, DECIMAL_POINT); 

	pinMode(interruptIncreasePin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(interruptIncreasePin), countInc, FALLING);

	pinMode(interruptDecreasePin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(interruptDecreasePin), countDec, FALLING);
}

void loop() {
	if (!isNoise()) {
		readAndUpdateCountValue();
	}

	for (int i = 0; i <7 ; i++) {
		digitalWrite(seg_port[i], num_array[count % 10][i]);
	}
}
```
 
## execution
<video controls autoplay width = "100%">
  <source type="video/mp4" src="/assets/videos/arduino_external_interrupt.mp4">
</video>
 In this video, I pressed left button(increase) 20 times, and then pressed right button(decrease) 20 times.


# reference

[https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)
