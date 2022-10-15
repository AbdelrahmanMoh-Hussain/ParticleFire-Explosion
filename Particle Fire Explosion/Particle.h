#pragma once
class Particle
{
public:
	double x;
	double y;
private:
	double speed;
	double direction;

public:
	Particle();
	void update(int interval);
private:
	void init();
};

