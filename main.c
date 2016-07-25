#include "title.h"
#include "mylib.h"
#include "bag.h"
#include "gameback.h"
#include "startbutton.h"
#include "coin.h"
#include "font.c"
#include "blackball.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

u16 *videoBuffer = (u16*) 0x6000000;

int main();
void createCharacter();
void limitCheck(struct character * thischar);
void updateCoin(struct coin * thiscoin);
void coinLimitCheck(struct coin * thiscoin);
void collisionCheck(struct character * thischar, struct coin *thiscoin);
void ballLimitCheck(struct coin * thiscoin);
void ballBagCollision(struct character * thischar, struct coin *thiscoin, int * pointer, int * pointer2);
void coinBallCollision(struct coin * thiscoin1, struct coin * thisball);


int main() {
	struct character characterStruct = {120, 110, 0};
	struct coin coin1 = {120, 0, 30, COIN_WIDTH, COIN_HEIGHT, coin, 1};
	struct coin coin2 = {135, 45, 60, COIN_WIDTH, COIN_HEIGHT, coin, 0};
	struct coin ball = {240, 35, -1000, BLACKBALL_WIDTH, BLACKBALL_HEIGHT, blackball, 0};
	int endScreen = 0;
	int gameStarted = 0;
	int counter = 0;
	int counter2 = 0;
	REG_DISPCNT = MODE3 | BG2_EN;
	drawImage3(0, 0, TITLE_WIDTH, TITLE_HEIGHT, title);
	drawImage3(140, 0, STARTBUTTON_WIDTH, STARTBUTTON_HEIGHT, startbutton);
	while(1) {
		if (KEY_DOWN_NOW(BUTTON_START)) {
			gameStarted = 1;
			counter = 1;
			//drawImage3(0, 0, GAMEBACK_WIDTH, GAMEBACK_HEIGHT, gameback);
		}
		if (gameStarted) {
			if (counter) {
				drawRectangle(0, 0, 240, 160, BLUE);
				counter = 0;
			} 
			drawNoWhiteNoWrap(coin1.x, coin1.y, COIN_WIDTH, COIN_HEIGHT, coin);
			drawNoWhiteNoWrap(coin2.x, coin2.y, COIN_WIDTH, COIN_HEIGHT, coin);
			drawNoWhiteNoWrap(ball.x, ball.y, ball.width, ball.height, blackball);
			drawNoWhite(characterStruct.x, characterStruct.y, BAG_WIDTH, BAG_HEIGHT, bag);
			if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
				characterStruct.x ++;
			} else if (KEY_DOWN_NOW(BUTTON_LEFT)) {
				characterStruct.x --;
				limitCheck(&characterStruct);
			} else if (KEY_DOWN_NOW(BUTTON_UP)) {
				characterStruct.y --;
			} else if (KEY_DOWN_NOW(BUTTON_DOWN)) {
				characterStruct.y ++;
			}
			limitCheck(&characterStruct);
			updateCoin(&coin1);
			coinLimitCheck(&coin1);
			updateCoin(&coin2);
			coinLimitCheck(&coin2);
			collisionCheck(&characterStruct, &coin1);
			ball.x -= 3;
			ballLimitCheck(&ball);
			collisionCheck(&characterStruct, &coin2);
			ballBagCollision(&characterStruct, &ball, &gameStarted, &endScreen);
			coinBallCollision(&coin1, &ball);
			coinBallCollision(&coin2, &ball);
			char score[15];
			sprintf(score, "Score: %i", characterStruct.coins);
			//drawRectangle(170, 120, 40, 40, BLUE);
			drawString(120, 170, score, RED);
			waitforVBlank();
			counter2++;
		}
		if (endScreen && !counter) {
			//char buffer[100] = "hello";
			drawImage3(0, 0, GAMEBACK_WIDTH, GAMEBACK_HEIGHT, gameback);
			counter = 1;
			drawRectangle(0, 110, 240, 50, BLACK);
			drawString(120, 170, "GAME OVER", RED);
			char score[15];
			sprintf(score, "Score: %i", characterStruct.coins);
			drawString(140, 170, score, RED);
			drawHollowRect(160, 130, 75, 40, RED);
		}
		if (KEY_DOWN_NOW(BUTTON_SELECT)) {
				gameStarted = 0;
				main();
		}
	}
	return 0;
}

void limitCheck(struct character * thischar) {
	if ((*thischar).x > 205) {
	(*thischar).x = 205;
	} else if((*thischar).x < 0) {
	(*thischar).x = 0;
	}
	if ((*thischar).y > 110) {
		(*thischar).y = 110;
	} else if ((*thischar).y < 0) {
		(*thischar).y = 0;
	}
}

void updateCoin(struct coin * thiscoin) {
	if ((*thiscoin).left) {
		(*thiscoin).x--;
	} else {
		(*thiscoin).x++;
	}
	(*thiscoin).y ++;
}
	

void coinLimitCheck(struct coin * thiscoin) {
	if((*thiscoin).y > 230) {
		(*thiscoin).y = 0;
		(*thiscoin).x = rand() % 239;
		(*thiscoin).left = rand() % 2;
	}
	if((*thiscoin).x < 0) {
		(*thiscoin).left = 0;
	}
	if((*thiscoin).x > 215) {
		(*thiscoin).left = 1;
	}
}

void ballLimitCheck(struct coin *thiscoin) {
	if((*thiscoin).x < -20) {
		drawBlue((*thiscoin).x, (*thiscoin).y, (*thiscoin).width, (*thiscoin).height);
		(*thiscoin).x = 240;
		(*thiscoin).y = rand() % 150;
	}
}

void collisionCheck(struct character * thischar, struct coin *thiscoin) {
	if((*thischar).x - (*thiscoin).x < 17 && (*thischar).x - (*thiscoin).x > -32) {
		if ((*thischar).y - (*thiscoin).y < 20 && (*thischar).y - (*thiscoin).y > -20) {
			drawBlue((*thiscoin).x, (*thiscoin).y, (*thiscoin).width, (*thiscoin).height);
			(*thiscoin).y = -20;
			(*thiscoin).x = rand() % 239;
			(*thiscoin).left = rand() % 2;
			(*thischar).coins += (*thiscoin).value;
			drawRectangle(170, 120, 80, 80, BLUE);
		}
	}
}

void ballBagCollision(struct character * thischar, struct coin *thiscoin, int * pointer, int * pointer2) {
	if((*thischar).x - (*thiscoin).x < 25 && (*thischar).x - (*thiscoin).x > -25) {
		if ((*thischar).y - (*thiscoin).y < 20 && (*thischar).y - (*thiscoin).y > -42) {
			*pointer = 0;
			*pointer2 = 1;
		}
	}
}

void coinBallCollision(struct coin * thiscoin, struct coin * thisball) {
	if((*thiscoin).x - (*thisball).x < 15 && (*thiscoin).x - (*thisball).x > -15) {
		if ((*thiscoin).y - (*thisball).y < 15 && (*thiscoin).y - (*thisball).y > -15) {		
 			drawBlue((*thiscoin).x, (*thiscoin).y, (*thiscoin).width, (*thiscoin).height);
			(*thiscoin).y = -20;
			(*thiscoin).x = rand() % 239;
			(*thiscoin).left = rand() % 2;
		}
	}
}
