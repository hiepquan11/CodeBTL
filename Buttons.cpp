#include "Variables.h"
#include "constant.h"
#include "Buttons.h"
#include "function.h"

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEventAgain(SDL_Event* e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		//Mouse is left of the button: Chuột ở bên trái của nút
		if (x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button: Chuột ở bên phải của nút
		else if (x > mPosition.x + 42)
		{
			inside = false;
		}
		//Mouse above the button: Di chuyển chuột lên trên nút
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button: Di chuyển chuột bên dưới nút
		else if (y > mPosition.y + 42)
		{
			inside = false;
		}
		if (inside)
		{
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				PlayAgain();
			}
		}
	}
}

void LButton::handleEventBack(SDL_Event* e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		//Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mPosition.x + 50)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > mPosition.y + 50)
		{
			inside = false;
		}
		if (inside)
		{
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
				isRunning = false;
				customMode = false;
				isChoosing = true;
				isWinning = false;
				lose = false;
				easy = false;
				medium = false;
				hard = false;
				cus = false;
			}
		}
	}
}

void LButton::handleEventMute(SDL_Event* e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		//Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mPosition.x + 50)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > mPosition.y + 50)
		{
			inside = false;
		}
		if (inside)
		{
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				if (mute == true) mute = false;
				else mute = true;
			}
		}
	}
}

void LButton::handleEvent(SDL_Event* e)
{
	//If mouse event happened: Nếu sự kiện chuột xảy ra
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position: Nhận vị trí chuột
		int x, y;
		SDL_GetMouseState(&x, &y);

		int i = (x - distance_x) / TILE_SIZE;
		int j = (y - distance_y) / TILE_SIZE;

		//Check if mouse is in button: Kiểm tra xem chuột có ở nút không
		bool inside = true;

		//Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mPosition.x + TILE_SIZE)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > mPosition.y + TILE_SIZE)
		{
			inside = false;
		}

		//Mouse is inside button: Nút bên trong chuột
		if (inside)
		{
			if (e->type == SDL_MOUSEBUTTONDOWN)
			{

				//Set mouse clicked: Đặt được nhấp chuột
				switch (e->button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					reveal(i, j);
					if (CountTileLeft == NumberOfMines)
					{
						Mix_PlayMusic(winMusic, 1);
					}
					if (sBoard[i][j] == 9)
					{
						lose = true;
						Mix_PlayMusic(loseMusic, 1);
					}
					else
					{
						Mix_PlayChannel(-1, click, 0);
					}
					break;
				}
				case SDL_BUTTON_RIGHT:
				{
					Mix_PlayChannel(-1, click, 0);
					if (sBoard[i][j] >= 10)
					{
						if (sBoard[i][j] == 11)
						{
							sBoard[i][j] = 10;
							mineCountLeft++;
						}
						else
						{
							sBoard[i][j] = 11;
							mineCountLeft--;
						}
					}
					else break;
					break;
				}
				}
			}
		}
	}
}

void LButton::render(int i, int j)
{
	//Show current button sprite: Hiển thị sprite nút hiện tại
	Tiles_image.render(mPosition.x, mPosition.y, &Tilesprites[sBoard[i][j]]);
}
void LButton::loseRender(int i, int j)
{
	//Show all button sprite: Hiển thị tất cả sprite nút
	Tiles_image.render(mPosition.x, mPosition.y, &Tilesprites[board[i][j]]);
}