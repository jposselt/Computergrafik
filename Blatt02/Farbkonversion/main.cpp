#include <stdio.h>
#include <stdlib.h>
#include "ColorConverter.h"

// Macro zum Pausieren der Anwendung unter Windows
#ifdef _WIN32
	#define WINPAUSE system("pause")
#endif

int main()
{
	printf("Farbkonvertierer\n");

	// Farmodell auswählen
	printf("Eingabefarbmodell angeben\n");
	printf("1) RGB\n");
	printf("2) CMY\n");
	printf("3) HSV\n");
	printf("Auswahl: ");

	int modelIn;
	scanf_s("%d", &modelIn);

	// Feedback
	switch (modelIn)
	{
	case 1:
		printf("RGB Modell\n");
		break;
	case 2:
		printf("CMY Modell\n");
		break;
	case 3:
		printf("HSV Modell\n");
		break;
	default:
		printf("ungueltige Auswahl\n");
		WINPAUSE;
		return 0;
	}

	// Farbwerte eingeben
	float x, y, z;
	int result;

	printf("Farbwerte eingeben (float Werte):\n");
	result = scanf_s("%f %f %f", &x, &y, &z);
	
	// Umrechenen und Ausgabe
	color rgb, cmy, hsv;
	if(modelIn == 1)
	{
		rgb = { colorModel::RGB, x, y, z };
		cmy = rgb2cmy(rgb);
		hsv = rgb2hsv(rgb);

		printf("CMY Farbwerte: %.4f %.4f %.4f\n", cmy.x, cmy.y, cmy.z);
		printf("HSV Farbwerte: %.4f %.4f %.4f\n", hsv.x, hsv.y, hsv.z);
	}
	else if (modelIn == 2)
	{
		cmy = { colorModel::CMY, x, y, z };
		rgb = cmy2rgb(cmy);
		hsv = cmy2hsv(cmy);

		printf("RGB Farbwerte: %.4f %.4f %.4f\n", rgb.x, rgb.y, rgb.z);
		printf("HSV Farbwerte: %.4f %.4f %.4f\n", hsv.x, hsv.y, hsv.z);
	}
	else
	{
		hsv = { colorModel::HSV, x, y, z };
		rgb = hsv2rgb(hsv);
		cmy = hsv2cmy(hsv);

		printf("RGB Farbwerte: %.4f %.4f %.4f\n", rgb.x, rgb.y, rgb.z);
		printf("CMY Farbwerte: %.4f %.4f %.4f\n", cmy.x, cmy.y, cmy.z);
	}

	WINPAUSE;
	return 0;
}