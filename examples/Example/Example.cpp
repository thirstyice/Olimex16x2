#include <Arduino.h>

#include <Olimex16x2.h>

Olimex16x2 lcd;
String greeting = "Hello World!";

void setup() {
	Serial.begin(9600);
	lcd.begin();
	lcd.setBacklight(255);
	lcd.drawLine(0, greeting);
}

void loop() {
	Serial.println(lcd.readAllButtons());
	for (uint8_t i=0; i<4; i++) {
		bool buttonValue = lcd.readButton(i);
		lcd.drawChar(buttonValue?'I':'O', 1, i*5);
	}
}