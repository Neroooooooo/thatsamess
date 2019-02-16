#pragma once

typedef struct RgbColor
{
	RgbColor();
	RgbColor(unsigned char, unsigned char, unsigned char);

	unsigned char r;
	unsigned char g;
	unsigned char b;
} RgbColor;

typedef struct HsvColor
{
	HsvColor();
	HsvColor(unsigned char, unsigned char, unsigned char);

	unsigned char h;
	unsigned char s;
	unsigned char v;
} HsvColor;

RgbColor HsvToRgb(HsvColor hsv);

HsvColor RgbToHsv(RgbColor rgb);