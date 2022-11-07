#include "Texture.h"
#include "Variables.h"
#include "constant.h"
#include "Buttons.h"
#include "function.h"
#include "Timer.h"
#include <sstream>
#include <fstream>
using namespace std;
vector <vector<LButton> > Buttons(3, vector<LButton>(2));
LButton face;
LButton goBack;
LButton sound;
LTimer timer;

void LFunction::handleEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			isRunning = false;
			mainLoop = false;
		}
		face.handleEventAgain(&e);
		goBack.handleEventBack(&e);
		sound.handleEventMute(&e);
		for (int i = 0; i < BOARD_SIZE_X; i++)
		{
			for (int j = 0; j < BOARD_SIZE_Y; j++)
			{
				Buttons[i][j].handleEvent(&e);
			}
		}

	}
}

void LFunction::reveal(int i, int j)
{
	if (sBoard[i][j] == 10 || sBoard[i][j] == 11)
	{
		if (sBoard[i][j] == 11)
		{
			return;
		}
		sBoard[i][j] = board[i][j];
		if (sBoard[i][j] != 9) CountTileLeft--;
		if (sBoard[i][j] == 0)
		{
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					int xpos = i + x;
					int ypos = j + y;
					if (xpos<0 || xpos>BOARD_SIZE_X - 1 || ypos<0 || ypos>BOARD_SIZE_Y - 1) continue;
					reveal(xpos, ypos);
				}
			}
		}
	}
}

void LFunction::isPlayerWinning()
{
	if (CountTileLeft == NumberOfMines) isWinning = true;
}

void LFunction::GameManager()
{
	if (playAgain == true) PlayAgain();
	//if we lose 
	if (lose == true)
	{
		timer.pause();
		loseFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
		for (int i = 0; i < BOARD_SIZE_X; i++)
		{
			for (int j = 0; j < BOARD_SIZE_Y; j++)
			{
				Buttons[i][j].loseRender(i, j);
			}
		}
	}
	//if we win
	if (isWinning == true)
	{
		timer.pause();
		winFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
		if (isRunning == false && isWinning) getScore();
	}
}

std::string LFunction::getTime()
{
	stringstream Time{};
	if (isWinning == true)
	{
		int n = timer.getTicks() / 1000;
		int h, m, s;
		h = n / 3600;
		m = (n - h * 3600) / 60;
		s = (n - h * 3600 - m * 60);
		Time.str("");
		Time << h << ":" << m << ":" << s;
		return Time.str();
	}
}

std::string LFunction::getFileScoreName()
{
	stringstream os;
	os.str("");
	os << "score/" << BOARD_SIZE_X << "x" << BOARD_SIZE_Y << "x" << NumberOfMines << ".txt";
	return os.str();
}

void LFunction::getScore()
{
	ofstream outFile;
	outFile.open(getFileScoreName().c_str(), ios::app);
	outFile << getTime() << endl;
	outFile.close();
}

void LFunction::PlayAgain()
{
	//timer.stop();
	if (isWinning) getScore();
	timer.start();
	CreateBoard();
	Mix_HaltMusic();
	mineCountLeft = NumberOfMines;
	CountTileLeft = BOARD_SIZE_X * BOARD_SIZE_Y;
	isWinning = false;
	lose = false;
	playAgain = false;
}

void LFunction::MineManager()
{
	int n = mineCountLeft;
	if (mineCountLeft < 10)
	{
		Digits.render(digit_x, digit_y, &Digitsprites[0]);
		for (int i = 0; i <= 9; i++)
		{
			if (i == mineCountLeft) Digits.render(digit_x + 28, digit_y, &Digitsprites[i]);
		}
	}

	else
	{
		int i = 0;
		while (n > 0)
		{
			int x = n % 10;
			n /= 10;
			Digits.render(digit_x + (1 - i) * 28, digit_y, &Digitsprites[x]);
			i++;
		}
	}
}

void LFunction::TimeManager()
{
	int n = timer.getTicks() / 1000;
	if (n < 10)
	{
		for (int i = 0; i <= 9; i++)
		{
			if (i == n) Digits.render(timeDigit_x, digit_y, &Digitsprites[n]);
		}
	}
	else
	{
		int i = 0;
		while (n > 0)
		{
			int x = n % 10;
			n /= 10;
			Digits.render(timeDigit_x - i * 28, digit_y, &Digitsprites[x]);
			i++;
		}
	}

}

void LFunction::setGameMode(int x, int y, int n, int dx, int dy, int d1x, int d1y, int dtx, int& BOARD_SIZE_X, int& BOARD_SIZE_Y, int& NumberOfMines, int& mineCountLeft, int& CountTileLeft, int& distance_x, int& distance_y, int& digit_x, int& digit_y, int& timeDigit_x)
{
	BOARD_SIZE_X = x;
	BOARD_SIZE_Y = y;
	NumberOfMines = n;
	mineCountLeft = n;
	CountTileLeft = x * y;
	distance_x = dx;
	distance_y = dy;
	digit_x = d1x;
	digit_y = d1y;
	timeDigit_x = dtx;

	Buttons.resize(BOARD_SIZE_X);
	for (int i = 0; i < BOARD_SIZE_X; i++)
	{
		Buttons[i].resize(BOARD_SIZE_Y);
	}
	sBoard.resize(BOARD_SIZE_X);
	for (int i = 0; i < BOARD_SIZE_X; i++)
	{
		sBoard[i].resize(BOARD_SIZE_Y);
	}
	board.resize(BOARD_SIZE_X);
	for (int i = 0; i < BOARD_SIZE_X; i++)
	{
		board[i].resize(BOARD_SIZE_Y);
	}
}

void LFunction::renderButton()
{
	for (int i = 0; i < BOARD_SIZE_X; i++)
	{
		for (int j = 0; j < BOARD_SIZE_Y; j++)
		{
			Buttons[i][j].render(i, j);
		}
	}
}

void LFunction::renderGame()
{
	if (mute == false)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		sound_on.render(timeDigit_x - 10, 0);
		loseMusic = Mix_LoadMUS("res/audio/scratch.wav");
		winMusic = Mix_LoadMUS("res/audio/beat.wav");
		click = Mix_LoadWAV("res/audio/click.wav");
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		sound_off.render(timeDigit_x - 10, 0);
		click = NULL;
		winMusic = NULL;
		loseMusic = NULL;
	}
	if (easy == true || medium == true || hard == true || cus == true)
	{
		if (easy == true)
		{
			easyTable.render(0, 50);
		}
		if (medium == true)
		{
			mediumTable.render(0, 50);
		}
		if (hard == true)
		{
			hardTable.render(0, 50);
		}
		if (cus == true)
		{
			//SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}
	}
	playingFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
	renderButton();
	back.render(0, 0);
	MineManager();
	isPlayerWinning();
	TimeManager();
	GameManager();
	SDL_RenderPresent(renderer);
}
//Play Minesweeper
void LFunction::PlayGame() {
	// Start up SDL and create window : Khởi động SDL và tạo cửa sổ
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (loadmedia())
		{
			if (loadMenuMedia())
			{
				showMenu();
				while (mainLoop)
				{
					if (isChoosing)
					{
						showModeChoice();
					}
					if (customMode) CustomMode();
					while (isRunning)
					{
						handleEvent();
						setButtonPosition();
						renderGame();
					}
				}
			}
		}
	}
}
//close SDL
void LFunction::close()
{
	//Free loaded images
	Tiles_image.free();
	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;
	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}