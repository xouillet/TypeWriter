#include "TypeWriter.h"

bool buffer;

// Mapping pin <-> row/col
// 0 is top, 10 is bottom
// cols are input (left connector)
// rows are output (right connector)
char get_pin_col(char col)
{
	return 33 - col;
}

char get_pin_row(char row)
{
	return 23 - row;
}



void setup()
{
	//Start serial connection
	Serial.begin(9600);

	//Configure pins
	for (char i = 0; i < 10; i++) {
		pinMode(get_pin_col(i), INPUT_PULLUP);
	}
	for (char i = 0; i < 10; i++) {
		if (i == 4 || i == 5) {
			continue;
		}
		pinMode(get_pin_row(i), OUTPUT);
		digitalWrite(get_pin_row(i), HIGH);
	}
	// Row 4 is GND
	pinMode(get_pin_row(4), OUTPUT);
	digitalWrite(get_pin_row(4), LOW);

	Serial.println("~ TypeWriter Panasonic R191 by Xou ~");
	buffer = true;
}

const char shiftWritePin = get_pin_row(SHIFT.row);

void activate(char row, char col, bool shift_same_col)
{
	char readPin = get_pin_col(col);
	char writePin = get_pin_row(row);

	//Serial.println("Waiting for low on ");
	//Serial.print(readPin);
	while (1) {
		if (digitalRead(readPin) == LOW) {
			break;
		}
	}
	digitalWrite(writePin, LOW);
	if (shift_same_col) {
		digitalWrite(shiftWritePin, LOW);
	}

	while (1) {
		if (digitalRead(readPin) == HIGH) {
			break;
		}
	}
	digitalWrite(writePin, HIGH);
	if (shift_same_col) {
		digitalWrite(shiftWritePin, HIGH);
	}
}

void key(Combi combi)
{
	if (combi.mod & MOD_ACUTE) {
		key(ACUTE);
	}
	if (combi.mod & MOD_AGRAVE) {
		key(AGRAVE);
	}

	if (combi.mod & MOD_ACIRC) {
		key(ACUTE);
		key(SPACE);
		key(BACKSPACE);
		key(AGRAVE);
	}
	for (int i = 0; i < 2; i++) {
		if (combi.mod & MOD_SHIFT) {
			activate(SHIFT.row, SHIFT.col, false);
		}
		if (combi.mod & MOD_CODE) {
			activate(CODE.row, CODE.col, false);
		}
		activate(combi.row, combi.col, (combi.mod & MOD_SHIFT)
				 && combi.col == SHIFT.col);
	}
	if (combi.row == 8 && combi.col == 4) {
		/* return, let it breathe */
		delay(300);
	} else {
		delay(75);
	}
}

void write_character(int character)
{
	/* We assume the character is latin-1 encoded */
	int i;
	for (i = 0; i < 255; i++) {
		if (mapping[i].latin1 == character) {
			break;
		}

		if (mapping[i].latin1 == 0) {
			i = 255;
			break;
		}
	}

	if (i < 255) {
		key(mapping[i].combi);
	} else {
		key(SPACE);				/* Default to space if char is not found */
	}

}

void loop()
{
	if (Serial.available()) {
		buffer = true;
		write_character(Serial.read());
	} else {
		if (buffer) {
			buffer = false;
			Serial.print('.');
		}
	}
}
