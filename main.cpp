#include "Texture.h"
#include "Buttons.h"
#include "Variables.h"
#include "constant.h"
#include "function.h"
using namespace std;


int main(int argc, char* argv[])
{
	LFunction game;
	game.PlayGame();
	//Free resources and close SDL: giải phóng tài nguyên và đóng SDL
	game.close();
	return 0;
}



