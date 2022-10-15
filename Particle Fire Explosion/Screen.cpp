#include "Screen.h"
#include <SDL.h>
#include <stdio.h>
#include<iostream>
using namespace std;

	Screen::Screen() : window(NULL), renderer(NULL), texture(NULL), buffer(NULL), buffer2(NULL)
	{

	}

	bool Screen::init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		//WINDOW SCREEN
		window = SDL_CreateWindow("FIRE EXPLOSION", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			SDL_QUIT;
			return false;
		}

		//RENDERER (Screen Color)
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL)
		{
			SDL_DestroyWindow(window);
			SDL_QUIT;
			return false;
		}

		//TEXTURE
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
		if (texture == NULL)
		{
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_QUIT;
			return false;
		}

		//BUFFER (Store Memory)
		buffer = new Uint32[width * height];
		buffer2 = new Uint32[width * height];

		//SDL_memset(buffer, 0, width * sizeof(Uint32));
		for (int i = 0; i < (width * height); i++)
		{
			buffer[i] = 0x00000000;
		}
		for (int i = 0; i < (width * height); i++)
		{
			buffer2[i] = 0x00000000;
		}

		return true;
	}

	void Screen::boxBlur()
	{
		swap(buffer, buffer2);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{

				int redTotal = 0, greenTotal = 0, blueTotal = 0;

				for (int row = -1; row <= 1; row++)
				{
					for (int col = -1; col <= 1; col++)
					{
						int currentX = x + col;
						int currentY = y + row;

						if (currentX >= 0 && currentX < width && currentY >= 0 && currentY < height)
						{
							Uint32 color = buffer2[currentY*width+currentX];
							
							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							redTotal += red;
							greenTotal += green;
							blueTotal += blue;
						}
					}
				}

				Uint8 red = redTotal / 9;
				Uint8 green = greenTotal / 9;
				Uint8 blue = blueTotal / 9;

				setPixel(x, y, red, green, blue);
			}
		}
	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
	{
		if (x < 0 || x >= width || y < 0 || y >= height)
		{
			return;
		}

		Uint32 color = 0;
		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;

		buffer[(y * width) + x] = color;
	}

	void Screen::update()
	{
		SDL_UpdateTexture(texture, NULL, buffer, width * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	bool Screen::processEvents()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				return false;
		}
		return true;
	}

	

	void Screen::close()
	{
		delete[] buffer;
		delete[] buffer2;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(texture);
		SDL_DestroyWindow(window);
		SDL_QUIT;
	}
