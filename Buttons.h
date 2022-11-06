#pragma once
#pragma once

#ifndef BUTTONS_H
#define BUTTONS_H
#include "Function.h"
#include <SDL.h>


class LButton : public LFunction
{
public:
	//Initializes internal variables: Khởi tạo các biến nội bộ
	LButton();

	//Sets top left position: Đặt vị trí trên cùng bên trái
	void setPosition(int x, int y);

	//set button in game
	void handleEventAgain(SDL_Event* e);
	void handleEventBack(SDL_Event* e);
	void handleEventMute(SDL_Event* e);

	//Handles mouse event: Xử lý sự kiện chuột
	void handleEvent(SDL_Event* e);

	//Shows button sprite: Hiển thị rút sprite
	void render(int i, int j);

	//Shows button sprite when we lose: Hiển thị nút sprite khi thua
	void loseRender(int i, int j);

private:
	//Top left position: Vị trí trên cùng bên trái
	SDL_Point mPosition;
};
#endif
