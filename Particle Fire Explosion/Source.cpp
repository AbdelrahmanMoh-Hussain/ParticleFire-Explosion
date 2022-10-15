#include <iostream>
#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include"Screen.h"
#include"Swarm.h"
#include"Particle.h"
using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));

	Screen screen;
	if (screen.init() == false)
		cout << "ERROR" << endl;

	Swarm swarm;

	//Game Loop
	while (true)
	{
		//Draw Particles:
		//change colors
		int elapced = SDL_GetTicks();

		swarm.update(elapced);

		unsigned char red = (unsigned char)((1 + sin(elapced * 0.0005) * 120));
		unsigned char green = (unsigned char)((1 + sin(elapced * 0.0002) * 120));
		unsigned char blue = (unsigned char)((1 + sin(elapced * 0.0003) * 120));
		//create particles
		const Particle* const particles = swarm.getParticles();
		for (int i = 0; i < swarm.nParticles; i++)
		{
			Particle particle = particles[i];
			int x = (particle.x + 1) * Screen::width/ 2;
			int y = particle.y * Screen::width / 2 + 300;
			
			screen.setPixel(x, y, red, green, blue);
		}
		screen.boxBlur();

		//Update the Texture with the info in the Buffer, then Passing the Buffer to thr Renderer
		screen.update();
		//Check Events(Quitting)
		if (!screen.processEvents())
		{
			break;
		}
	}


	//End the Program
	screen.close();
	return 0;
}