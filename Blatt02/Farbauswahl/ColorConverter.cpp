#include <cmath>
#include "ColorConverter.h"

inline float sanitize(const float &in, const float &min, const float &max)
{
	return std::min(max, std::max(min, in));
}

color rgb2cmy(const color &in)
{
	color out = {
		colorModel::CMY,
		sanitize(1.f - in.x, 0.f, 1.f),
		sanitize(1.f - in.y, 0.f, 1.f),
		sanitize(1.f - in.z, 0.f, 1.f)
	};

	return out;
}

color rgb2hsv(const color &in)
{
	color out;
	out.m = colorModel::HSV;

	float r, g, b, h, s, v;

	r = sanitize(in.x, 0.f, 1.f);
	g = sanitize(in.y, 0.f, 1.f);
	b = sanitize(in.z, 0.f, 1.f);

	float min = std::min(r, std::min(g, b));
	float max = std::max(r, std::max(g, b));
	float delta = max - min;

	v = max;

	if (max == 0.0f) {
		s = 0;
		h = 0;
	}
	else if (max - min == 0.0f) {
		s = 0;
		h = 0;
	}
	else {
		s = delta / max;

		if (max == r) {
			h = 60 * ((g - b) / delta) + 0;
		}
		else if (max == g) {
			h = 60 * ((b - r) / delta) + 120;
		}
		else {
			h = 60 * ((r - g) / delta) + 240;
		}
	}

	if (h < 0) {
		h += 360.0f;
	}

	out.x = h;
	out.y = s;
	out.z = v;

	return out;
}

color cmy2rgb(const color &in)
{
	color out = {
		colorModel::RGB,
		sanitize(1.f - in.x, 0.f, 1.f),
		sanitize(1.f - in.y, 0.f, 1.f),
		sanitize(1.f - in.z, 0.f, 1.f)
	};
	
	return out;
}

color cmy2hsv(const color &in)
{
	return rgb2hsv(cmy2rgb(in));
}

color hsv2rgb(const color &in)
{
	color out;
	out.m = colorModel::RGB;

	float r, g, b, h, s, v;

	h = in.x;

	// 0 <= h < 360
	if (std::fabs(h) >= 360.f)
	{
		h = std::fmodf(h,360);
	}
	if (h < 0)
	{
		h = 360.f + h;
	}

	s = sanitize(in.y, 0.f, 1.f);
	v = sanitize(in.z, 0.f, 1.f);

	int   hi = (int)(h / 60.0f) % 6;
	float f = (h / 60.0f) - hi;
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));

	switch (hi) {
	case 0: r = v, g = t, b = p; break;
	case 1: r = q, g = v, b = p; break;
	case 2: r = p, g = v, b = t; break;
	case 3: r = p, g = q, b = v; break;
	case 4: r = t, g = p, b = v; break;
	case 5: r = v, g = p, b = q; break;
	}

	out.x = r;
	out.y = g;
	out.z = b;

	return out;
}

color hsv2cmy(const color &in)
{
	return rgb2cmy( hsv2rgb(in) );
}
