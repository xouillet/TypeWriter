/* Mapping definition */
typedef enum {
	MOD_NO = 0,
	MOD_SHIFT = 1,
	MOD_CODE = 2,
	MOD_ACUTE = 4,
	MOD_AGRAVE = 8,
	MOD_ACIRC = 16
} Modifier;

typedef struct {
	char row;
	char col;
	char mod;
} Combi;

typedef struct {
	unsigned char latin1;
	Combi combi;

} MapElement;

const MapElement mapping[255] = {
	{49, {0, 0, MOD_NO}},		/* 1 */
	{50, {0, 1, MOD_NO}},		/* 2 */
	{114, {0, 2, MOD_NO}},		/* r */
	{82, {0, 2, MOD_SHIFT}},	/* R */
	{101, {0, 3, MOD_NO}},		/* e */
	{69, {0, 3, MOD_SHIFT}},	/* E */
	{103, {0, 4, MOD_NO}},		/* g */
	{71, {0, 4, MOD_SHIFT}},	/* G */
	{104, {0, 5, MOD_NO}},		/* h */
	{72, {0, 5, MOD_SHIFT}},	/* H */
	{35, {0, 7, MOD_NO}},		/* # */
	{113, {1, 2, MOD_NO}},		/* q */
	{81, {1, 2, MOD_SHIFT}},	/* Q */
	{119, {1, 3, MOD_NO}},		/* w */
	{87, {1, 3, MOD_SHIFT}},	/* W */
	{102, {1, 4, MOD_NO}},		/* f */
	{70, {1, 4, MOD_SHIFT}},	/* F */
	{100, {1, 5, MOD_NO}},		/* d */
	{68, {1, 5, MOD_SHIFT}},	/* D */
	{98, {1, 7, MOD_NO}},		/* b */
	{66, {1, 7, MOD_SHIFT}},	/* B */
	{110, {1, 8, MOD_NO}},		/* n */
	{78, {1, 8, MOD_SHIFT}},	/* N */
	{52, {2, 0, MOD_NO}},		/* 4 */
	{51, {2, 1, MOD_NO}},		/* 3 */
	{116, {2, 2, MOD_NO}},		/* t */
	{84, {2, 2, MOD_SHIFT}},	/* T */
	{122, {2, 3, MOD_NO}},		/* z */
	{90, {2, 3, MOD_SHIFT}},	/* Z */
	{107, {2, 4, MOD_NO}},		/* k */
	{75, {2, 4, MOD_SHIFT}},	/* K */
	{106, {2, 5, MOD_NO}},		/* j */
	{74, {2, 5, MOD_SHIFT}},	/* J */
	{44, {2, 7, MOD_NO}},		/* , */
	{109, {2, 8, MOD_NO}},		/* m */
	{77, {2, 8, MOD_SHIFT}},	/* M */
	{53, {3, 0, MOD_NO}},		/* 5 */
	{54, {3, 1, MOD_NO}},		/* 6 */
	{84, {3, 2, MOD_NO}},		/* T */
	{97, {3, 4, MOD_NO}},		/* a */
	{65, {3, 4, MOD_SHIFT}},	/* A */
	{115, {3, 5, MOD_NO}},		/* s */
	{83, {3, 5, MOD_SHIFT}},	/* S */
	{118, {3, 7, MOD_NO}},		/* v */
	{86, {3, 7, MOD_SHIFT}},	/* V */
	{99, {3, 8, MOD_NO}},		/* c */
	{67, {3, 8, MOD_SHIFT}},	/* C */
	{56, {6, 0, MOD_NO}},		/* 8 */
	{55, {6, 1, MOD_NO}},		/* 7 */
	{105, {6, 2, MOD_NO}},		/* i */
	{73, {6, 2, MOD_SHIFT}},	/* I */
	{117, {6, 3, MOD_NO}},		/* u */
	{85, {6, 3, MOD_SHIFT}},	/* U */
	{108, {6, 4, MOD_NO}},		/* l */
	{76, {6, 4, MOD_SHIFT}},	/* L */
	{246, {6, 5, MOD_NO}},		/* ö */
	{214, {6, 5, MOD_SHIFT}},	/* Ö */
	{46, {6, 7, MOD_NO}},		/* . */
	{45, {6, 8, MOD_NO}},		/* - */
	{57, {7, 0, MOD_NO}},		/* 9 */
	{48, {7, 1, MOD_NO}},		/* 0 */
	{111, {7, 2, MOD_NO}},		/* o */
	{79, {7, 2, MOD_SHIFT}},	/* O */
	{112, {7, 3, MOD_NO}},		/* p */
	{80, {7, 3, MOD_SHIFT}},	/* P */
	{121, {7, 7, MOD_NO}},		/* y */
	{89, {7, 7, MOD_SHIFT}},	/* Y */
	{120, {7, 8, MOD_NO}},		/* x */
	{88, {7, 8, MOD_SHIFT}},	/* X */
	{223, {8, 1, MOD_NO}},		/* ß */
	{43, {8, 2, MOD_NO}},		/* + */
	{252, {8, 3, MOD_NO}},		/* ü */
	{220, {8, 3, MOD_SHIFT}},	/* Ü */
	{228, {8, 5, MOD_NO}},		/* ä */
	{196, {8, 5, MOD_SHIFT}},	/* Ä */
	{33, {0, 0, MOD_SHIFT}},	/* ! */
	{34, {0, 1, MOD_SHIFT}},	/* " */
	{39, {0, 7, MOD_SHIFT}},	/* ' */
	{36, {2, 0, MOD_SHIFT}},	/* $ */
	{167, {2, 1, MOD_SHIFT}},	/* § */
	{59, {2, 7, MOD_SHIFT}},	/* ; */
	{37, {3, 0, MOD_SHIFT}},	/* % */
	{38, {3, 1, MOD_SHIFT}},	/* & */
	{181, {3, 1, MOD_CODE}},	/* µ */
	{40, {6, 0, MOD_SHIFT}},	/* ( */
	{47, {6, 1, MOD_SHIFT}},	/* / */
	{58, {6, 7, MOD_SHIFT}},	/* : */
	{95, {6, 8, MOD_SHIFT}},	/* _ */
	{41, {7, 0, MOD_SHIFT}},	/* ) */
	{61, {7, 1, MOD_SHIFT}},	/* = */
	{63, {8, 1, MOD_SHIFT}},	/* ? */
	{42, {8, 2, MOD_SHIFT}},	/* * */
	{233, {0, 3, MOD_ACUTE}},	/* é */
	{201, {0, 3, MOD_ACUTE | MOD_SHIFT}},	/* É */
	{232, {0, 3, MOD_AGRAVE}},	/* è */
	{200, {0, 3, MOD_AGRAVE | MOD_SHIFT}},	/* È */
	{234, {0, 3, MOD_ACIRC}},	/* ê */
	{225, {3, 4, MOD_ACUTE}},	/* á */
	{193, {3, 4, MOD_ACUTE | MOD_SHIFT}},	/* Á */
	{224, {3, 4, MOD_AGRAVE}},	/* à */
	{192, {3, 4, MOD_AGRAVE | MOD_SHIFT}},	/* À */
	{237, {6, 2, MOD_ACUTE}},	/* í */
	{205, {6, 2, MOD_ACUTE | MOD_SHIFT}},	/* Í */
	{236, {6, 2, MOD_AGRAVE}},	/* ì */
	{204, {6, 2, MOD_AGRAVE | MOD_SHIFT}},	/* Ì */
	{250, {6, 3, MOD_ACUTE}},	/* ú */
	{218, {6, 3, MOD_ACUTE | MOD_SHIFT}},	/* Ú */
	{249, {6, 3, MOD_AGRAVE}},	/* ù */
	{217, {6, 3, MOD_AGRAVE | MOD_SHIFT}},	/* Ù */
	{243, {7, 2, MOD_ACUTE}},	/* ó */
	{211, {7, 2, MOD_ACUTE | MOD_SHIFT}},	/* Ó */
	{242, {7, 2, MOD_AGRAVE}},	/* ò */
	{210, {7, 2, MOD_AGRAVE | MOD_SHIFT}},	/* Ò */
	{234, 0, 3, MOD_ACIRC},		/* ê */
	{202, 0, 3, MOD_ACIRC | MOD_SHIFT},	/* Ê */
	{226, 3, 4, MOD_ACIRC},		/* â */
	{194, 3, 4, MOD_ACIRC | MOD_SHIFT},	/* Â */
	{238, 6, 2, MOD_ACIRC},		/* î */
	{206, 6, 2, MOD_ACIRC | MOD_SHIFT},	/* Î */
	{251, 6, 3, MOD_ACIRC},		/* û */
	{219, 6, 3, MOD_ACIRC | MOD_SHIFT},	/* Û */
	{244, 7, 2, MOD_ACIRC},		/* ô */
	{212, 7, 2, MOD_ACIRC | MOD_SHIFT},	/* Ô */
	{10, {8, 4, MOD_NO}},		/* \n */
	{13, {8, 4, MOD_NO}},		/* \r */
	{32, {3, 9, MOD_NO}},		/* Space */
	{127, {9, 0, MOD_NO}},		/* Backspace */
	{12, {8, 4, MOD_CODE}},		/* Page feed */
	{17, {7, 0, MOD_CODE}},		/* Auto LF */
	{18, {0, 0, MOD_CODE}},		/* LSet */
	{19, {0, 1, MOD_CODE}},		/* RSet */
	{15, {6, 3, MOD_CODE}},		/* Underline */
	{14, {1, 7, MOD_CODE}},		/* Bold */
	{0, {0, 0, MOD_NO}}			/* Sentinel */
};

/* Control combinations */
const Combi SHIFT = { 8, 7, MOD_NO };
const Combi CODE = { 7, 9, MOD_NO };
const Combi ACUTE = { 8, 0, MOD_NO };
const Combi AGRAVE = { 8, 0, MOD_SHIFT };
const Combi SPACE = { 3, 9, MOD_NO };
const Combi BACKSPACE = { 9, 0, MOD_NO };
