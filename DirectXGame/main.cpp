#include "MyGame.h"

// windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	TYFramework* game = new MyGame();

	game->Run();

	delete game;

	return 0;
}