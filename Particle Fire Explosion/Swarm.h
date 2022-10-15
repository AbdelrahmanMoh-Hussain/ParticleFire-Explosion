#pragma once

#include "Particle.h"

class Swarm
{
public:
	const static int nParticles = 5000;
private:
	Particle*  particles;
	int lastTime;
public:
	Swarm();
	~Swarm();
	void update(int elapced);
	const Particle*  const getParticles() {
		return particles;
	};
};

