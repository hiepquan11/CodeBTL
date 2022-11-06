#pragma once
#pragma once
#ifndef VARIABLES_H
#define VARIABLES_H

#include "Texture.h"
#include "constant.h"
#include "Buttons.h"

// initialization: khởi tạo
extern SDL_Window* window;
extern SDL_Renderer* renderer;

// loop variable: biến vòng lặp
extern bool isRunning;
extern bool showmenu;
extern bool isChoosing;
extern bool mainLoop;
extern bool customMode;

//win or lose : thắng thua
extern bool isWinning;
extern bool lose;



// image use in game : ảnh trong game
extern LTexture menuTheme;
extern LTexture levelTheme;
extern LTexture easyTable;
extern LTexture mediumTable;
extern LTexture hardTable;
extern LTexture customStart;
extern LTexture back;
extern LTexture sound_on;
extern LTexture sound_off;

// image face: khuôn mặt hình ảnh
extern LTexture winFace;
extern LTexture playingFace;
extern LTexture loseFace;

// Tiles in board: Gạch trong bảng
extern LTexture Tiles_image;
extern SDL_Rect Tilesprites[12];

// text
extern LTexture menu;
extern LTexture menu1;
extern LTexture menuColor;
extern LTexture menu1Color;
extern LTexture easyChoice;
extern LTexture mediumChoice;
extern LTexture hardChoice;
extern LTexture customChoice;
extern LTexture easyChoiceColor;
extern LTexture mediumChoiceColor;
extern LTexture hardChoiceColor;
extern LTexture customChoiceColor;
extern LTexture wInput;
extern LTexture hInput;
extern LTexture mInput;
extern TTF_Font* gFont;

// Create board data: Tạo dữ liệu bảng
extern std::vector <std::vector<int> > sBoard;
extern std::vector <std::vector<int> > board;

// mines : mìn
extern int mineCountLeft;
extern int CountTileLeft;

// audio: âm thanh
extern bool mute;
extern Mix_Chunk* click;
extern Mix_Music* loseMusic;
extern Mix_Music* winMusic;

// distance: khoảng cách
extern int distance_x;
extern int distance_y;
extern int digit_x;
extern int digit_y;
extern int timeDigit_x;

// digits image: hình ảnh chữ số
extern LTexture Digits;
extern SDL_Rect Digitsprites[10];

// board size: Kích thước bảng
extern int BOARD_SIZE_X;
extern int BOARD_SIZE_Y;
extern int NumberOfMines;

// boolean
extern bool playAgain;
extern bool saveScore;
extern bool start;
extern bool easy;
extern bool medium;
extern bool hard;
extern bool cus;

#endif 
