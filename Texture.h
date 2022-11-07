#pragma once
#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include<iostream>
#include<time.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<string>
#include<vector>

class LTexture
{
public:
	//Initializes variables: Khởi tạo các biến
	LTexture(SDL_Texture* _mTexture, int _mWidth, int _mHeight);

	//Deallocates memory: Phân bổ bộ nhớ
	~LTexture();

	//Loads image at specified path: Tải hình ảnh tại đường dẫn được chỉ định
	bool loadFromFile(std::string path);

	//Creates image from font string: Tạo hình ảnh từ chuỗi phông chữ
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	//Deallocates texture: Phân bổ kết cấu
	void free();

	//Renders texture at given point: Hiển thị kết cấu tại điểm đã cho
	void render(int x, int y, SDL_Rect* clip = NULL);

	//Gets image dimensions: Nhận kích thước hình ảnh
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture: Kết cấu phần cứng thực tế
	SDL_Texture* mTexture;

	//Image dimensions: Kích thước hình ảnh
	int mWidth;
	int mHeight;
};
#endif
