#pragma once
#include <SDL.h>
#include <stdio.h>

class Screen
{
public:
	const static int height = 600, width = 800;
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	Uint32* buffer;
	Uint32* buffer2;

public:
	Screen();
	bool init();
	void update();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	bool processEvents();
	void close();
	void boxBlur();
};

