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

//initialization func
bool LFunction::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not enabled!";
		}

		//Create window
		window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
					success = false;
				}
				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

bool LFunction::loadmedia()
{
	bool success = true;
	//Open image of tiles
	if (!Tiles_image.loadFromFile("res/images/tiles5.jpg"))
	{
		cout << "Can't load this image from file!";
		success = false;
	}
	else
	{
		//Set sprites
		for (int i = 0; i < 12; ++i)
		{
			Tilesprites[i].x = i * TILE_SIZE;
			Tilesprites[i].y = 0;
			Tilesprites[i].w = TILE_SIZE;
			Tilesprites[i].h = TILE_SIZE;
		}
	}
	//load digits
	if (!Digits.loadFromFile("res/images/Untitled1.png"))
	{
		cout << "Fail";
		success = false;
	}
	else
	{
		//Set sprites
		for (int i = 0; i < 10; i++)
		{
			Digitsprites[i].x = i * 28;
			Digitsprites[i].y = 0;
			Digitsprites[i].w = 28;
			Digitsprites[i].h = 46;
		}
	}
	//load easy table
	if (!easyTable.loadFromFile("res/images/easy.png"))
	{
		cout << "Fail";
		success = false;
	}
	//load medium table
	if (!mediumTable.loadFromFile("res/images/medium.png"))
	{
		cout << "Fail";
		success = false;
	}
	//load hard table
	if (!hardTable.loadFromFile("res/images/hard.png"))
	{
		cout << "Fail";
		success = false;
	}
	//load face
	if (!winFace.loadFromFile("res/images/winface.png"))
	{
		cout << "Fail";
		success = false;
	}
	if (!loseFace.loadFromFile("res/images/loseface.png"))
	{
		cout << "Fail";
		success = false;
	}
	if (!playingFace.loadFromFile("res/images/playingface.png"))
	{
		cout << "Fail";
		success = false;
	}
	if (!back.loadFromFile("res/images/backicon.png"))
	{
		success = false;
	}
	if (!sound_on.loadFromFile("res/images/unmute.png"))
	{
		success = false;
	}
	if (!sound_off.loadFromFile("res/images/mute.png"))
	{
		success = false;
	}
	//Open the font 
	gFont = TTF_OpenFont("res/font.ttf", 20);
	if (gFont == NULL)
	{
		cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}
	//load text
	SDL_Color textcolor1 = { 255,255,255 };
	if (!menu.loadFromRenderedText("START", textcolor1))
	{
		cout << "Fail";
	}
	if (!menu1.loadFromRenderedText("EXIT", textcolor1))
	{
		cout << "Fail";
	}
	SDL_Color color = { 255,0,0 };
	if (!menuColor.loadFromRenderedText("START", color))
	{
		cout << "Fail";
		success = false;
	}
	if (!menu1Color.loadFromRenderedText("EXIT", color))
	{
		cout << "Fail";
		success = false;
	}
	//Load music
	loseMusic = Mix_LoadMUS("res/audio/scratch.wav");
	if (loseMusic == NULL)
	{
		cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << endl;
		success = false;
	}

	//Load sound effects
	winMusic = Mix_LoadMUS("res/audio/beat.wav");
	if (winMusic == NULL)
	{
		cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << endl;
		success = false;
	}

	click = Mix_LoadWAV("res/audio/click.wav");
	if (click == NULL)
	{
		cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << endl;
		success = false;
	}
	return success;
}

bool LFunction::loadMenuMedia()
{
	bool success = true;
	//load background of menu
	if (!menuTheme.loadFromFile("res/images/menu.jpg"))
	{
		cout << "Fail";
		success = false;
	}
	//load level choice
	if (!levelTheme.loadFromFile("res/images/mode.jpg"))
	{
		cout << "Fail";
		success = false;
	}
	if (!customStart.loadFromFile("res/images/custom.png"))
	{
		cout << "Fail";
		success = true;
	}
	//load choice text
	SDL_Color textColor = { 255,255,255 };
	if (!easyChoice.loadFromRenderedText("EASY MODE", textColor))
	{
		cout << "Fail";
		success = false;
	}
	if (!mediumChoice.loadFromRenderedText("MEDIUM MODE", textColor))
	{
		cout << "Fail";
		success = false;
	}
	if (!hardChoice.loadFromRenderedText("HARD MODE", textColor))
	{
		cout << "Fail";
		success = false;
	}
	if (!customChoice.loadFromRenderedText("CUSTOM MODE", textColor))
	{
		cout << "Fail";
		success = false;
	}
	SDL_Color textcolor = { 255,0,0 };
	if (!easyChoiceColor.loadFromRenderedText("EASY MODE", textcolor))
	{
		cout << "Fail";
		success = false;
	}
	if (!mediumChoiceColor.loadFromRenderedText("MEDIUM MODE", textcolor))
	{
		cout << "Fail";
		success = false;
	}
	if (!hardChoiceColor.loadFromRenderedText("HARD MODE", textcolor))
	{
		cout << "Fail";
		success = false;
	}
	if (!customChoiceColor.loadFromRenderedText("CUSTOM MODE", textcolor))
	{
		cout << "Fail";
		success = false;
	}
	return success;
}

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
