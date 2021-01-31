---
layout: single
title: \[Arduino Uno\] 7-Segment Display
date : 2021-01-11 00:23:45 +0900
last_modified_at: 2021-02-01 03:37:41 +0900
categories: [arduino]
tags: [arduino]
comments: true
public : true
use_math : true
---

# circuit
 7 segment is a module representing a number in an embedded system. The number is divided into seven segments and represented by one LED per segment. This means that seven LEDs represent a single number and this is called 7 segment display. One more LED is used to represent decimal point.(So, there are 8 leds in total).
 In order to use 7 LEDs, '+' and '-' pins are required of for each LED, so a total of 14 pins are required. Depending on the connection method, '+' or '-' pins are generally used in common. If '+' is used in common, it is called common anode, while '-' is used in common, it is called common cathode.
 The figure below show the general structure of 7 segment display, the left side show the common anode and the right side shows the common cathode. 
 
  ![7_segments](/assets/images/7_segments.png)
 
 In case of common anode, the LED of 7 segment is turns on if the '-' pin of LED is LOW, and it turns off if it HIGH.
 In case of common cathode, the LED of 7 segment is turns on if the '+' pin of LED is HIGH, and it turns off if it LOW.
 Since the circuit varies depending on the common anode and common cathode, so be careful not to make mistakes.

 For ex)
  - To represent '1' with the common anode type, the 'b' and 'c' segments must be 0, and the rest must be '1'.
  - To represent '1' with the common cathode type, the 'b' and 'c' segments must be 1, and the rest must be '0'. 
 
 __The pin number may vary depending of the manufacturer, so you must check the datasheet of the 7 segment.__
 
## Common Anode
### circuit
 This circut used 7 segment of common anode type, so "5V" is connected to the common pin, and a resistor for controlling the amount of current is connected to the pin of each segment. In case of each LED's forward voltage is 2V and to ensure the current per LED does not exceed 20mA, the calculation is done by the I = V/R formula. 0.02A = (5V-2V)/R,
 So, 150 ohm resistors were used here.
 
 __The forward voltage and the peak forward current that allowed for 7 segment differ according to the 7 segment type, so you must check them in the datasheet.__

 ![Common_anode_7segment_display](/assets/images/arduino_common_anode_7segment_display.png)

### code
 The below is a code that repeatedly prints the numbers from 0 to 9, increasing every second. There is a table for segments that should be on/off according to each number from 0 to 9.
 In case of common anode, it turns on when 0, and turns off when 1.
 In the code below, there are definitions for each number according to the 7 segment type, and by defining/undefining the macro definition "COMMON_CATHODE", only the table are changed and other codes are used the same.
 The "COMMON_CATHOD" was undefined in the code below.

 
```c
//#define COMMON_CATHODE
#if defined(COMMON_CATHODE)
#define NUM_0 {1, 1, 1, 1, 1, 1, 0}
#define NUM_1 {0, 1, 1, 0, 0, 0, 0}
#define NUM_2 {1, 1, 0, 1, 1, 0, 1}
#define NUM_3 {1, 1, 1, 1, 0, 0, 1}
#define NUM_4 {0, 1, 1, 0, 0, 1, 1}
#define NUM_5 {1, 0, 1, 1, 0, 1, 1}
#define NUM_6 {1, 0, 1, 1, 1, 1, 1}
#define NUM_7 {1, 1, 1, 0, 0, 1, 0}
#define NUM_8 {1, 1, 1, 1, 1, 1, 1}
#define NUM_9 {1, 1, 1, 1, 0, 1, 1}
#define DECIMAL_POINT (1)

#else
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

#endif

int num_array[10][7] = {
	NUM_0,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9,
};


int count = 0;

/* 7 segment pin number */
int seg_port[] = {4, 5, 6, 7, 8, 9, 10};
unsigned long prev_millis = 0;


void setup() {
	for (int i = 0; i < sizeof(seg_port)/sizeof(seg_port[0]); i++) {
		pinMode(seg_port[i], OUTPUT);
	}

	pinMode(11, OUTPUT);
    digitalWrite(11, DECIMAL_POINT); 
}

void loop() {
  for (int i = 0; i <7 ; i++) {
    digitalWrite(seg_port[i], num_array[count % 10][i]);
  }
  delay(1000);
  count++;
}

```

### execution
<video controls autoplay>
  <source type="video/mp4" src="/assets/videos/arduino_common_anode_7segment.mp4">
</video>

<br/>
## Common Cathode
### circuit
 This circut used 7 segment of common cathode type, so "GND" is connected to the common pin.
 So, 150 ohm resistors were used here.

 ![Common_cathode_7segment_display](/assets/images/arduino_common_cathode_7segment_display.png)

### code
 In the code below, the "COMMON_CATHODE" was defined. Other than that, the other codes are the same.
 In case of common cathode, it turns on when 1, and turns off when 0.
```c
#define COMMON_CATHODE
#if defined(COMMON_CATHODE)
#define NUM_0 {1, 1, 1, 1, 1, 1, 0}
#define NUM_1 {0, 1, 1, 0, 0, 0, 0}
#define NUM_2 {1, 1, 0, 1, 1, 0, 1}
#define NUM_3 {1, 1, 1, 1, 0, 0, 1}
#define NUM_4 {0, 1, 1, 0, 0, 1, 1}
#define NUM_5 {1, 0, 1, 1, 0, 1, 1}
#define NUM_6 {1, 0, 1, 1, 1, 1, 1}
#define NUM_7 {1, 1, 1, 0, 0, 1, 0}
#define NUM_8 {1, 1, 1, 1, 1, 1, 1}
#define NUM_9 {1, 1, 1, 1, 0, 1, 1}
#define DECIMAL_POINT (1)

#else

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

#endif

int num_array[10][7] = {
	NUM_0,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9,
};


int count = 0;

/* 7 segment pin number */
int seg_port[] = {4, 5, 6, 7, 8, 9, 10};
unsigned long prev_millis = 0;


void setup() {
	for (int i = 0; i < sizeof(seg_port)/sizeof(seg_port[0]); i++) {
		pinMode(seg_port[i], OUTPUT);
	}

	pinMode(11, OUTPUT);
    digitalWrite(11, DECIMAL_POINT); 
}

void loop() {
  for (int i = 0; i <7 ; i++) {
    digitalWrite(seg_port[i], num_array[count % 10][i]);
  }
  delay(1000);
  count++;
}
```
### execution
<video controls autoplay>
  <source type="video/mp4" src="/assets/videos/arduino_common_cathode_7segment.mp4">
</video>




