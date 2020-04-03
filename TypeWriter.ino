void setup()
{
	//Start serial connection
	Serial.begin(9600);

	//Configure pins (30-49 even for input, odd for output)
	//for (int i = 30; i < 49; i++) {
	//  pinMode(i, (i % 2 == 0) ? INPUT : OUTPUT);
	//}

	Serial.println("~ TypeWriter Panasonic R191 by Xou ~");

}

/* Mapping definition */

typedef struct {
	unsigned char latin1;

	char row;
	char col;
	char modifier;				/* Code:2, Shift:1 */
} mapelement;

const mapelement mapping[255] = {
	{49, 0, 0, 0},				/* 1 */
	{50, 0, 1, 0},				/* 2 */
	{114, 0, 2, 0},				/* r */
	{82, 0, 2, 1},				/* R */
	{101, 0, 3, 0},				/* e */
	{69, 0, 3, 1},				/* E */
	{103, 0, 4, 0},				/* g */
	{71, 0, 4, 1},				/* G */
	{104, 0, 5, 0},				/* h */
	{72, 0, 5, 1},				/* H */
	{35, 0, 7, 0},				/* # */
	{124, 1, 0, 0},				/* | */
	{113, 1, 2, 0},				/* q */
	{81, 1, 2, 1},				/* Q */
	{119, 1, 3, 0},				/* w */
	{87, 1, 3, 1},				/* W */
	{102, 1, 4, 0},				/* f */
	{70, 1, 4, 1},				/* F */
	{100, 1, 5, 0},				/* d */
	{68, 1, 5, 1},				/* D */
	{98, 1, 7, 0},				/* b */
	{66, 1, 7, 1},				/* B */
	{110, 1, 8, 0},				/* n */
	{78, 1, 8, 1},				/* N */
	{52, 2, 0, 0},				/* 4 */
	{51, 2, 1, 0},				/* 3 */
	{116, 2, 2, 0},				/* t */
	{84, 2, 2, 1},				/* T */
	{122, 2, 3, 0},				/* z */
	{90, 2, 3, 1},				/* Z */
	{107, 2, 4, 0},				/* k */
	{75, 2, 4, 1},				/* K */
	{106, 2, 5, 0},				/* j */
	{74, 2, 5, 1},				/* J */
	{44, 2, 7, 0},				/* , */
	{109, 2, 8, 0},				/* m */
	{77, 2, 8, 1},				/* M */
	{53, 3, 0, 0},				/* 5 */
	{54, 3, 1, 0},				/* 6 */
	{84, 3, 2, 0},				/* T */
	{97, 3, 4, 0},				/* a */
	{65, 3, 4, 1},				/* A */
	{115, 3, 5, 0},				/* s */
	{83, 3, 5, 1},				/* S */
	{118, 3, 7, 0},				/* v */
	{86, 3, 7, 1},				/* V */
	{99, 3, 8, 0},				/* c */
	{67, 3, 8, 1},				/* C */
	{56, 6, 0, 0},				/* 8 */
	{55, 6, 1, 0},				/* 7 */
	{105, 6, 2, 0},				/* i */
	{73, 6, 2, 1},				/* I */
	{117, 6, 3, 0},				/* u */
	{85, 6, 3, 1},				/* U */
	{108, 6, 4, 0},				/* l */
	{76, 6, 4, 1},				/* L */
	{246, 6, 5, 0},				/* ö */
	{214, 6, 5, 1},				/* Ö */
	{46, 6, 7, 0},				/* . */
	{45, 6, 8, 0},				/* - */
	{57, 7, 0, 0},				/* 9 */
	{48, 7, 1, 0},				/* 0 */
	{111, 7, 2, 0},				/* o */
	{79, 7, 2, 1},				/* O */
	{112, 7, 3, 0},				/* p */
	{80, 7, 3, 1},				/* P */
	{121, 7, 7, 0},				/* y */
	{89, 7, 7, 1},				/* Y */
	{120, 7, 8, 0},				/* x */
	{88, 7, 8, 1},				/* X */
	{96, 8, 0, 0},				/* ` */
	{223, 8, 1, 0},				/* ß */
	{43, 8, 2, 0},				/* + */
	{252, 8, 3, 0},				/* ü */
	{220, 8, 3, 1},				/* Ü */
	{228, 8, 5, 0},				/* ä */
	{196, 8, 5, 1},				/* Ä */
	{10, 8, 4, 0},				/* \n */
	{13, 8, 4, 0},				/* \r */
	{32, 3, 9, 0},				/* Space */
	{0, 0, 0, 0}				/* Sentinel */
};

void go(char row, char col, char modifier)
{
	Serial.print("Will write to row ");
	Serial.print(row, DEC);
	Serial.print(" and col ");
	Serial.print(col, DEC);
	Serial.print(" with modifier ");
	Serial.print(modifier, DEC);
	Serial.println();
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
		go(mapping[i].row, mapping[i].col, mapping[i].modifier);
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
