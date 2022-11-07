#pragma once
#pragma once
#include "Timer.h"
#include <SDL.h>

class LFunction {
public:
	//initialization func: khởi tạo func
	bool init();
	bool loadmedia();
	bool loadMenuMedia();

	//close SDL: đóng SDL
	void close();

	//initialization games: khởi tạo game
	void CreateBoard();
	void createMenu();
	void createModeMenu();
	void CustomMode();
	void showMenu();
	void showModeChoice();
	void setButtonPosition();

	//ingame func: func trong game
	void isPlayerWinning();
	void MineManager();
	void PlayAgain();
	void GameManager();
	void TimeManager();

	void getScore();
	void setGameMode(int x, int y, int n, int dx, int dy, int d1x, int d1y, int dtx, int& BOARD_SIZE_X, int& BOARD_SIZE_Y, int& NumberOfMines, int& mineCountLeft, int& CountTileLeft, int& distance_x, int& distance_y, int& digit_x, int& digit_y, int& timeDigit_x);
	void renderButton();
	void handleEvent();
	void reveal(int i, int j);
	void renderGame();
	void PlayGame();
private:
	std::string getTime();
	std::string getFileScoreName();
};

