typedef unsigned short u16;

#define REG_DISPCNT *(unsigned short*) 0x4000000
#define MODE3 3
#define BG2_EN (1 << 10)

#define OFFSET(r, c, rowlen) ((r)*(rowlen)+(c))

extern const unsigned char fontdata_6x8[12288];

#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define RED COLOR(31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(13, 22, 31)
#define MAGENTA COLOR(31, 0,31)
#define WHITE COLOR(31, 31, 31)
#define YELLOW COLOR(31, 31, 0)
#define BLACK COLOR(0, 0, 0)

#define BUTTON_A (1<<0)
#define BUTTON_B (1<<1)
#define BUTTON_SELECT (1<<2)
#define BUTTON_START (1<<3)
#define BUTTON_RIGHT (1<<4)
#define BUTTON_LEFT (1<<5)
#define BUTTON_UP (1<<6)
#define BUTTON_DOWN (1<<7)
#define BUTTON_R (1<<8)
#define BUTTON_L (1<<9)

#define BUTTONS *(volatile unsigned int *)0x4000130
#define KEY_DOWN_NOW(key) ((~BUTTONS) & key)

const unsigned char fontdata_6x8[12288];

struct character {
	int x;
	int y;
	int coins;
};

struct coin {
	int x;
	int y;
	int value;
	int width;
	int height;
	const u16 * picture;
	int left;
};



extern unsigned short *videoBuffer;
extern const unsigned char fontdata_6x8[12288];

void setPixel(int x, int y, u16 color);
void drawRectangle(int x, int y, int width, int height, u16 color);
void drawHollowRect(int x, int y, int width, int height, u16 color);
void drawImage3(int x, int y, int width, int height, const u16 * picture);
void drawChar(int row, int col, char ch, unsigned short color);
void drawString(int row, int col, char *str, unsigned short color);
void drawNoWhite(int x, int y, int width, int height, const u16* picture);
void redrawSection(int x, int y, const u16 *background);
void drawBlue(int x, int y, int width, int height);
void drawNoWhiteNoWrap(int x, int y, int width, int height, const u16* picture);
void waitforVBlank();
