#include "Noise.hpp"

double Noise::noise(double x, double y)
{
	int left = (int) x;
	if (x < 0) left--;
	int top = (int) y;
	if (y < 0) top--;
	int right = left + 1;
	int bottom = top + 1;

	double dx = x - left;
	double dy = y - top;

	auto corner00 = getNoise(left, top);
	auto corner10 = getNoise(right, top);
	auto corner01 = getNoise(left, bottom);
	auto corner11 = getNoise(right, bottom);
	
	auto iTop = interpolate(corner00, corner10, dx);
	auto iBottom = interpolate(corner01, corner11, dx);

	return interpolate(iTop, iBottom, dy);
}


double Noise::interpolate(double left, double right, double delta)
{
	//Algorithm taken from Unity's Mathf.SmoothStep
	delta = -2.f * delta * delta * delta + 3.f * delta * delta;
	return right * delta + left * (1.f - delta);
}

double Noise::getNoise(int x, int y)
{
	unsigned int num = m_seed + x + y * 100;
	char val = num ^ (num << 10) + 12236 + num * num;
	return (double) val / 128.f;
}
