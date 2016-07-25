#include "mylib.h"

void setPixel(int row, int col, u16 color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRectangle(int x, int y, int width, int height, u16 color) {
	for (int i = y; i < height + y; i++) {
		for (int j = x; j < width + x; j++) {
			videoBuffer[i * 240 + j] = color;
		}
	}
}

void drawHollowRect(int x, int y, int width, int height, u16 color) {
	for (int i = y; i < height + y; i++) {
		videoBuffer[i * 240 + x] = color;
		videoBuffer[i * 240 + (x + width)] = color;
	}
	for (int j = x; j < width + x; j++) {
		videoBuffer[y * 240 + j] = color;
		videoBuffer[(y + height) * 240 + j] = color;
	}
}

void drawImage3(int x, int y, int width, int height, const u16* picture) {
	int counter = 0;
	for (int i = y; i < height + y; i++) {
		for (int j = x; j < width + x; j++) {
			setPixel(i, j, picture[counter]);
			counter++;
		}
	}
}

void drawBlue(int x, int y, int width, int height) {
	int counter = 0;
	for (int i = y; i < height + y; i++) {
		for (int j = x; j < width + x; j++) {
			videoBuffer[i * 240 + j] = BLUE;
			counter++;
		}
	}
}

void drawNoWhite(int x, int y, int width, int height, const u16* picture) {
	int counter = 0;
	for (int i = y; i < height + y; i++) {
		for (int j = x; j < width + x; j++) {
			u16 color = picture[counter];
			if (color != WHITE) {
				videoBuffer[i * 240 + j] = picture[counter];
			} else {
				videoBuffer[i * 240 + j] = BLUE;
			}
			counter++;
		}
	}
}

void drawNoWhiteNoWrap(int x, int y, int width, int height, const u16* picture) {
	int counter = 0;
	for (int i = y; i < height + y; i++) {
		for (int j = x; j < width + x; j++) {
			if(i >= 0 && j >=0 && i < 160 && j < 240) {
			u16 color = picture[counter];
			if (color != WHITE) {
				videoBuffer[i * 240 + j] = picture[counter];
			} else {
				videoBuffer[i * 240 + j] = BLUE;
			}
			}
			counter++;
		}
	}
}

void drawChar(int row, int col, char ch, u16 color){
	int r,c;
	for(r=0; r<8; r++){
		for(c=0; c<6; c++){
			if(fontdata_6x8[OFFSET(r,c,6) + 48*ch]){
				setPixel(r + row, c + col, color);
			}	
		}
	}
}

void drawString(int row, int col, char *str, u16 color){
	int chars_drawn = 0;
	while(*str){
		drawChar(row, col + 6*chars_drawn++, *str++, color);
	}
}

void waitforVBlank() {
	while(SCANLINECOUNTER > 1);
	while(SCANLINECOUNTER < 1);
}
