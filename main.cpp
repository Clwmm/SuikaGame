#include "Game.h"
#include <windows.h>

int main()
{
	FreeConsole();

	int height = sf::VideoMode::getDesktopMode().height;
	int width = sf::VideoMode::getDesktopMode().width;
	int screen_size = 0;
	if (width > height)
		screen_size = height - 250;
	else
		screen_size = width - 250;

	Game game(screen_size);
}