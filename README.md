# Olimex16x2
### A library for interfacing with the Olimex SHIELD-LCD16x2
===

API:
```cpp
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
```
