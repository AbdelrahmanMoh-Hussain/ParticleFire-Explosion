#include "Swarm.h"
#include "Particle.h"

Swarm::Swarm(): lastTime(0)
{
	particles = new Particle[nParticles];
}

Swarm::~Swarm()
{
	delete[] particles;
}

void Swarm::update(int elapced)
{
	int interval = elapced - lastTime;
	for (int i = 0; i < Swarm::nParticles; i++)
	{
		particles[i].update(interval);
	}
	lastTime = elapced;
}

