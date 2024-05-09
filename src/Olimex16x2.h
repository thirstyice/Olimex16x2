#pragma once

#include <Arduino.h>
#include <Wire.h>

class Olimex16x2 {
public:
	Olimex16x2(TwoWire* i2cInterface = &Wire);
	virtual void begin();
	virtual void pinMode(uint8_t pin, uint8_t mode);
	virtual void digitalWrite(uint8_t pin, uint8_t level); // HIGH = 3.3V
	virtual int digitalRead(uint8_t pin); // HIGH = 3.3V
	bool readButton(uint8_t button);
	virtual int readAllButtons();
	virtual void clear();
	virtual void drawChar(char character, uint8_t line, uint8_t pos);
	virtual void setBacklight(uint8_t level);
	void drawLine(uint8_t line, const char* contents);
	void drawLine(uint8_t line, String contents);
	void clearLine(uint8_t line);

	uint8_t getID();
	uint8_t getFW();

	void enableUART(bool enabled = true);

protected:
	struct Commands { enum : uint8_t {
		SET_TRIS,
		SET_LAT,
		GET_PORT,
		GET_BUT,
		GET_ID,
		GET_FRM,
		LCD_CLR,
		LCD_WR,
		SET_BL,
		UART_EN,
		End
	};};
	const uint8_t cmd[Commands::End] {
		0x01,
		0x02,
		0x03,
		0x05,
		0x20,
		0x21,
		0x60,
		0x61,
		0x62,
		0x10
	};
	int request(uint8_t command);
	const uint8_t i2cAddr = 0x30;
	TwoWire* i2c = nullptr;
};