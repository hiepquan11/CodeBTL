#include "Texture.h"
#include "Variables.h"
using namespace std;

extern SDL_Window* window = NULL;
extern SDL_Renderer* renderer = NULL;
extern TTF_Font* gFont = NULL;

LTexture::LTexture(SDL_Texture* _mTexture, int _mWidth, int _mHeight)
{
	//Initialize: nhận dạng
	mTexture = _mTexture;
	mWidth = _mWidth;
	mHeight = _mHeight;
}

LTexture::~LTexture()
{
	//Deallocate: giải phóng
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture: Loại bỏ kết cấu có sẵn
	free();

	//The final texture: Kết cấu cuối cùng
	SDL_Texture* newTexture = NULL;

	//Load image at specified path: Tải hình ảnh tại đường dẫn được chỉ định
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Unable to load image %s! SDL_image Error: " << path.c_str() << IMG_GetError() << endl;
	}
	else
	{
		//Color key image: Hình ảnh phím màu
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels: Tạo kết cấu từ các pixel bề mặt
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Unable to create texture from %s! SDL Error: " << path.c_str() << SDL_GetError() << endl;
		}
		else
		{
			//Get image dimensions: Nhận kích thước hình ảnh
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface: Loại bỏ bề mặt đã tải cũ
		SDL_FreeSurface(loadedSurface);
	}

	//Return success: Trả lại thành công
	mTexture = newTexture;
	return mTexture != NULL;
}


bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture: Loại bỏ kết cấu có sẵn
	free();

	//Render text surface: Kết xuất bề mặt văn bản
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
	}
	else
	{
		//Create texture from surface pixels: Tạo kết cấu từ các pixel bề mặt
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
		}
		else
		{
			//Get image dimensions: Nhận kích thước hình ảnh
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface: Loại bỏ bề mặt cũ
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;
}


void LTexture::free()
{
	//Free texture if it exists: Kết cấu tự do nếu nó tồn tại
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen: Đặt không gian kết xuất và hiển thị ra màn hình
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions: Đặt kích thước kết xuất clip
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen: Kết xuất màn hình
	SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
