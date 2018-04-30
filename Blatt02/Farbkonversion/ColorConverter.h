#pragma once

#include <algorithm>

enum class colorModel { RGB, CMY, HSV };

typedef struct color {
	colorModel m;
	float x, y, z;
} color;

color rgb2cmy(const color &in);
color rgb2hsv(const color &in);

color cmy2rgb(const color &in);
color cmy2hsv(const color &in);

color hsv2rgb(const color &in);
color hsv2cmy(const color &in);