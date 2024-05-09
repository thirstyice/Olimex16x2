#include "Olimex16x2.h"

Olimex16x2::Olimex16x2(TwoWire* i2cInterface) {
	i2c = i2cInterface;
}

void Olimex16x2::begin() {
	i2c->begin();
	enableUART(false);
}

int Olimex16x2::request(uint8_t command) {
	i2c->beginTransmission(i2cAddr);
	i2c->write(command);
	i2c->endTransmission();
	delay(20);
	int value = -2;
	i2c->requestFrom(i2cAddr, (uint8_t)1);
	while (i2c->available()) {
		value = i2c->read();
	}
	return value;
}

void Olimex16x2::pinMode(uint8_t pin, uint8_t mode) {
	if (pin>=9 || mode>1) {
		return;
	}
	i2c->beginTransmission(i2cAddr);
	i2c->write(cmd[Commands::SET_TRIS]);
	i2c->write(pin+1);
	i2c->write(!mode);
	i2c->endTransmission();
	delay(20);
}

void Olimex16x2::digitalWrite(uint8_t pin, uint8_t level) {
	if (pin>=9 || level>1) {
		return;
	}
	i2c->beginTransmission(i2cAddr);
	i2c->write(cmd[Commands::SET_LAT]);
	i2c->write(pin+1);
	i2c->write(level);
	i2c->endTransmission();
	delay(20);
}

int Olimex16x2::digitalRead(uint8_t pin) {
	if (pin>=9) {
		return -1;
	}
	i2c->beginTransmission(i2cAddr);
	i2c->write(cmd[Commands::GET_PORT]);
	i2c->write(pin+1);
	i2c->endTransmission();
	delay(20);
	i2c->requestFrom(i2cAddr, (uint8_t)1);
	int value = -1;
	while (i2c->available()) {
		value = i2c->read();
	}
	return value;
}

bool Olimex16x2::readButton(uint8_t button) {
	if (button>=4) {
		return -1;
	}
	uint8_t values = readAllButtons();
	values = values>>button;
	values = values & 1;
	return !values;
}

int Olimex16x2::readAllButtons() {
	return request(cmd[Commands::GET_BUT]);
}

void Olimex16x2::clear() {
	i2c->beginTransmission(i2cAddr);
	i2c->write(cmd[Commands::LCD_CLR]);
	i2c->endTransmission();
	delay(20);
}

void Olimex16x2::drawChar(char character, uint8_t line, uint8_t pos) {
	if (character<32 || character>126) {
		return;
	}
	if (pos>15) {
		pos=15;
	}
	if (line>1) {
		line=1;
	}
	i2c->beginTransmission(i2cAddr);
	i2c->write(cmd[Commands::LCD_WR]);
	i2c->write(!line);
	i2c->write(pos);
	i2c->write(character);
	i2c->endTransmission();
	delay(20);
}

void Olimex16x2::setBacklight(uint8_t level) {
	i2c->beginTransmission(i2cAddr);
	i2c->write(cmd[Commands::SET_BL]);
	i2c->write(level);
	i2c->endTransmission();
	delay(20);
}

void Olimex16x2::drawLine(uint8_t line, const char* contents) {
	uint8_t posX = 0;
	while (contents[posX]!='\0' && posX<16) {
		drawChar(contents[posX], line, posX);
		posX++;
	}
	while (posX<16) {
		drawChar(' ', line, posX);
		posX++;
	}
}

void Olimex16x2::drawLine(uint8_t line, String contents) {
	drawLine(line, contents.c_str());
}

void Olimex16x2::clearLine(uint8_t line) {
	char end = '\0';
	drawLine(line, &end);
}

uint8_t Olimex16x2::getID() {
	return request(cmd[Commands::GET_ID]);
}

uint8_t Olimex16x2::getFW() {
	return request(cmd[Commands::GET_FRM]);
}

void Olimex16x2::enableUART(bool enabled) {
	i2c->beginTransmission(i2cAddr);
	i2c->write(cmd[Commands::UART_EN]);
	i2c->write(enabled?1:0);
	i2c->endTransmission();
	delay(20);
}