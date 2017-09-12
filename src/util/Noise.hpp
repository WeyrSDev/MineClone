#pragma once

class Noise
{
public:
	Noise(unsigned int seed): m_seed(seed) {};
	
	double noise(double x, double y);
private:
	double interpolate(double left, double right, double delta);
	double getNoise(int x, int y);

	unsigned int m_seed;
};
