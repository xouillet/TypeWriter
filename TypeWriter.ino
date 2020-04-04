void setup()
{
	//Start serial connection
	Serial.begin(9600);

	//Configure pins (30-49 even for input, odd for output)
	for (int i = 30; i < 49; i++) {
		pinMode(i, (i % 2 == 0) ? INPUT : OUTPUT);
	}

	Serial.println("~ TypeWriter Panasonic R191 by Xou ~");

}

/* Mapping definition */
typedef enum {
	MOD_NO = 0,
	MOD_SHIFT = 1,
	MOD_CODE = 2
} Modifier;

typedef enum {
	KEY_UP,
	KEY_DOWN
} Direction;

typedef struct {
	unsigned char latin1;

	char row;
	char col;
	Modifier mod;				/* Code:2, Shift:1 */
} mapelement;

const mapelement mapping[255] = {
	{49, 0, 0, MOD_NO},			/* 1 */
	{50, 0, 1, MOD_NO},			/* 2 */
	{114, 0, 2, MOD_NO},		/* r */
	{82, 0, 2, MOD_SHIFT},		/* R */
	{101, 0, 3, MOD_NO},		/* e */
	{69, 0, 3, MOD_SHIFT},		/* E */
	{103, 0, 4, MOD_NO},		/* g */
	{71, 0, 4, MOD_SHIFT},		/* G */
	{104, 0, 5, MOD_NO},		/* h */
	{72, 0, 5, MOD_SHIFT},		/* H */
	{35, 0, 7, MOD_NO},			/* # */
	{124, 1, 0, MOD_NO},		/* | */
	{113, 1, 2, MOD_NO},		/* q */
	{81, 1, 2, MOD_SHIFT},		/* Q */
	{119, 1, 3, MOD_NO},		/* w */
	{87, 1, 3, MOD_SHIFT},		/* W */
	{102, 1, 4, MOD_NO},		/* f */
	{70, 1, 4, MOD_SHIFT},		/* F */
	{100, 1, 5, MOD_NO},		/* d */
	{68, 1, 5, MOD_SHIFT},		/* D */
	{98, 1, 7, MOD_NO},			/* b */
	{66, 1, 7, MOD_SHIFT},		/* B */
	{110, 1, 8, MOD_NO},		/* n */
	{78, 1, 8, MOD_SHIFT},		/* N */
	{52, 2, 0, MOD_NO},			/* 4 */
	{51, 2, 1, MOD_NO},			/* 3 */
	{116, 2, 2, MOD_NO},		/* t */
	{84, 2, 2, MOD_SHIFT},		/* T */
	{122, 2, 3, MOD_NO},		/* z */
	{90, 2, 3, MOD_SHIFT},		/* Z */
	{107, 2, 4, MOD_NO},		/* k */
	{75, 2, 4, MOD_SHIFT},		/* K */
	{106, 2, 5, MOD_NO},		/* j */
	{74, 2, 5, MOD_SHIFT},		/* J */
	{44, 2, 7, MOD_NO},			/* , */
	{109, 2, 8, MOD_NO},		/* m */
	{77, 2, 8, MOD_SHIFT},		/* M */
	{53, 3, 0, MOD_NO},			/* 5 */
	{54, 3, 1, MOD_NO},			/* 6 */
	{84, 3, 2, MOD_NO},			/* T */
	{97, 3, 4, MOD_NO},			/* a */
	{65, 3, 4, MOD_SHIFT},		/* A */
	{115, 3, 5, MOD_NO},		/* s */
	{83, 3, 5, MOD_SHIFT},		/* S */
	{118, 3, 7, MOD_NO},		/* v */
	{86, 3, 7, MOD_SHIFT},		/* V */
	{99, 3, 8, MOD_NO},			/* c */
	{67, 3, 8, MOD_SHIFT},		/* C */
	{56, 6, 0, MOD_NO},			/* 8 */
	{55, 6, 1, MOD_NO},			/* 7 */
	{105, 6, 2, MOD_NO},		/* i */
	{73, 6, 2, MOD_SHIFT},		/* I */
	{117, 6, 3, MOD_NO},		/* u */
	{85, 6, 3, MOD_SHIFT},		/* U */
	{108, 6, 4, MOD_NO},		/* l */
	{76, 6, 4, MOD_SHIFT},		/* L */
	{246, 6, 5, MOD_NO},		/* ö */
	{214, 6, 5, MOD_SHIFT},		/* Ö */
	{46, 6, 7, MOD_NO},			/* . */
	{45, 6, 8, MOD_NO},			/* - */
	{57, 7, 0, MOD_NO},			/* 9 */
	{48, 7, 1, MOD_NO},			/* 0 */
	{111, 7, 2, MOD_NO},		/* o */
	{79, 7, 2, MOD_SHIFT},		/* O */
	{112, 7, 3, MOD_NO},		/* p */
	{80, 7, 3, MOD_SHIFT},		/* P */
	{121, 7, 7, MOD_NO},		/* y */
	{89, 7, 7, MOD_SHIFT},		/* Y */
	{120, 7, 8, MOD_NO},		/* x */
	{88, 7, 8, MOD_SHIFT},		/* X */
	{96, 8, 0, MOD_NO},			/* ` */
	{223, 8, 1, MOD_NO},		/* ß */
	{43, 8, 2, MOD_NO},			/* + */
	{252, 8, 3, MOD_NO},		/* ü */
	{220, 8, 3, MOD_SHIFT},		/* Ü */
	{228, 8, 5, MOD_NO},		/* ä */
	{196, 8, 5, MOD_SHIFT},		/* Ä */
	{10, 8, 4, MOD_NO},			/* \n */
	{13, 8, 4, MOD_NO},			/* \r */
	{32, 3, 9, MOD_NO},			/* Space */
	{0, 0, 0, 0}				/* Sentinel */
};

void key(char row, char col, Direction direction)
{
	Serial.println(row);
	Serial.println(col);
	Serial.println(direction);
	Serial.println("");
}

void write_character(int character)
{
	/* We assume the character is latin-1 encoded */
	Serial.println(character);
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
		if (mapping[i].mod & MOD_SHIFT) {
			key(8, 7, KEY_DOWN);
		}
		if (mapping[i].mod & MOD_CODE) {
			key(7, 9, KEY_DOWN);
		}

		key(mapping[i].row, mapping[i].col, KEY_DOWN);
		key(mapping[i].row, mapping[i].col, KEY_UP);

		if (mapping[i].mod & MOD_CODE) {
			key(7, 9, KEY_UP);
		}

		if (mapping[i].mod & MOD_SHIFT) {
			key(8, 7, KEY_UP);
		}
	} else {
		Serial.println("Not found :(");
	}

}

void loop()
{
	if (Serial.available()) {
		write_character(Serial.read());
	}
}
