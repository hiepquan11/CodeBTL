#include "Variables.h"
#include<iostream>
// loop variable: biến vòng lặp
extern bool isRunning = false;
extern bool showmenu = false;
extern bool isChoosing = true;
extern bool mainLoop = true;
extern bool customMode = false;

// win or lose
extern bool isWinning = false;
extern bool lose = false;

// mines: mìn
extern int mineCountLeft = NumberOfMines;
extern int CountTileLeft = BOARD_SIZE_X * BOARD_SIZE_Y;

// images use in game 
extern LTexture menuTheme(NULL, 0, 0);
extern LTexture levelTheme(NULL, 0, 0);
extern LTexture easyTable(NULL, 0, 0);
extern LTexture mediumTable(NULL, 0, 0);
extern LTexture hardTable(NULL, 0, 0);
extern LTexture customStart(NULL, 0, 0);
extern LTexture back(NULL, 0, 0);
extern LTexture sound_on(NULL, 0, 0);
extern LTexture sound_off(NULL, 0, 0);

//image face
extern LTexture winFace(NULL, 0, 0);
extern LTexture playingFace(NULL, 0, 0);
extern LTexture loseFace(NULL, 0, 0);

// text
extern LTexture menu(NULL, 0, 0);
extern LTexture menu1(NULL, 0, 0);
extern LTexture menuColor(NULL, 0, 0);
extern LTexture menu1Color(NULL, 0, 0);
extern LTexture easyChoice(NULL, 0, 0);
extern LTexture mediumChoice(NULL, 0, 0);
extern LTexture hardChoice(NULL, 0, 0);
extern LTexture customChoice(NULL, 0, 0);
extern LTexture easyChoiceColor(NULL, 0, 0);
extern LTexture mediumChoiceColor(NULL, 0, 0);
extern LTexture hardChoiceColor(NULL, 0, 0);
extern LTexture customChoiceColor(NULL, 0, 0);
extern LTexture wInput(NULL, 0, 0);
extern LTexture hInput(NULL, 0, 0);
extern LTexture mInput(NULL, 0, 0);

// create board data: tạo dữ liệu bảng
extern std::vector <std::vector<int> > sBoard(3, std::vector<int>(2, 0));
extern std::vector <std::vector<int> > board(3, std::vector<int>(2, 0));

// Tiles in board: Gạch trong bảng
extern LTexture Tiles_image(NULL, 0, 0);
extern SDL_Rect Tilesprites[12] = {};

// audio
extern bool mute = false;
extern Mix_Chunk* click = NULL;
extern Mix_Music* loseMusic = NULL;
extern Mix_Music* winMusic = NULL;

// distance
extern int distance_x = 0;
extern int distance_y = 0;
extern int digit_x = 0;
extern int digit_y = 0;
extern int timeDigit_x = 0;

// digits image: hình ảnh chữ số
extern LTexture Digits(NULL, 0, 0);
extern SDL_Rect Digitsprites[10] = {};

// Board size: Kích thước bảng
extern int BOARD_SIZE_X = 0;
extern int BOARD_SIZE_Y = 0;
extern int NumberOfMines = 0;

// boolean 
extern bool playAgain = false;
extern bool saveScore = false;
extern bool start = false;
extern bool easy = false;
extern bool medium = false;
extern bool hard = false;
extern bool cus = false;
