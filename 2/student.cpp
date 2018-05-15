/******************************************************************************
 * Laborator 02 - Zaklady pocitacove grafiky - IZG
 * isolony@fit.vutbr.cz
 *
 * $Id: $
 *
 * Popis: Hlavicky funkci pro funkce studentu
 *
 * Opravy a modifikace:
 * ivelas@fit.vutbr.cz
 * itomesek@fit.vutbr.cz
 * Dominik Harmim <harmim6@gmail.com>
 */


#include "student.h"
#include "globals.h"


#define FRAC_BITS 8


/******************************************************************************
 ******************************************************************************
 Funkce vraci pixel z pozice x, y. Je nutne hlidat frame_bufferu, pokud
 je dana souradnice mimo hranice, funkce vraci barvu (0, 0, 0).*/
S_RGBA getPixel(int x, int y)
{
	// kontrola souřadnic
	if (x < 0 || x >= width || y < 0 || y >= height) return COLOR_BLACK;

	// vrácení barvy na vypočítaném indexu
	return *(frame_buffer + y * width + x);
}


/******************************************************************************
 ******************************************************************************
 Funkce vlozi pixel na pozici x, y. Je nutne hlidat frame_bufferu, pokud
 je dana souradnice mimo hranice, funkce neprovadi zadnou zmenu.*/
void putPixel(int x, int y, S_RGBA color)
{
	// kontrola souřadnic
	if (x < 0 || x >= width || y < 0 || y >= height) return;

	// nastavení barvy na vypočítaném indexu
	*(frame_buffer + y * width + x) = color;
}


////////////////////////////////////////////////////////////////////////////////
// Ukol za 2b
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 ******************************************************************************
 Vykreslení úsečky algoritmem DDA s FX aritmetikou každým směrem.*/
void drawLine(int x1, int y1, int x2, int y2)
{
	// Předpokládám, že úsečka leží v prvním kvadrantu, protože SDL
	// surface by asi měl být pouze první kvadrant.

	// Pokud je počáteční bod shodný s koncovým, tak vykreslíme pouze bod.
	if (x1 == x2 && y1 == y2)
	{
		putPixel(x1, y1, COLOR_GREEN);
		return;
	}

	// výpočet diferencí souřadnic
	int dx = (x2 - x1), dy = (y2 - y1);

	// Pokud úsečka roste rychleji v ose Y, tak prohodíme X a Y souřadnice.
	bool x_y_swapped = false;
	if (ABS(dy) > ABS(dx))
	{
		x_y_swapped = true;
		SWAP(x1, y1);
		SWAP(x2, y2);
		SWAP(dx, dy);
	}

	// Pokud úsečka není rostoucí od P1 k P2, tak prohodím P1 a P2.
	if (x1 > x2)
	{
		SWAP(x1, x2);
		SWAP(y1, y2);
	}

	int y = y1 << FRAC_BITS; // počáteční posun v ose Y
	const int k = (dy << FRAC_BITS) / dx; // směrnice

	// vykreslování od bodu P1 k bodu P2
	for (int x = x1; x <= x2; x++) // přírůstek na ose X je 1
	{
		// Pokud úsečka roste rychleji v ose Y, tak prohodíme
		// X a Y souřadnice zpátky.
		if (x_y_swapped)
		{
			// vykrselení bodu s prohozenými souřadnicemi
			putPixel(y >> FRAC_BITS, x, COLOR_GREEN);
		}
		else
		{
			// vykrselení bodu
			putPixel(x, y >> FRAC_BITS, COLOR_GREEN);
		}

		y += k; // přírůstek v ose Y o směrnici
	}
}


////////////////////////////////////////////////////////////////////////////////
// Ukol za 1b
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 ******************************************************************************
 Vykreslení všech osmi symetrických bodů kružnice.*/
void put8PixelsOfCircle(int x, int y, int s1, int s2, S_RGBA color)
{
	// vykreslení všech bodů posunutých od středu

	// vykreslení všech bodů [x,y]
	putPixel(x + s1, y + s2, color); // [x,y]
	putPixel(-x + s1, y + s2, color); // [-x,y]
	putPixel(x + s1, -y + s2, color); // [x,-y]
	putPixel(-x + s1, -y + s2, color); // [-x,-y]

	// vykreslení všech bodů [y,x]
	putPixel(y + s1, x + s2, color); // [y,x]
	putPixel(-y + s1, x + s2, color); // [-y,x]
	putPixel(y + s1, -x + s2, color); // [y,-x]
	putPixel(-y + s1, -x + s2, color); // [-y,-x]
}


/******************************************************************************
 ******************************************************************************
 Vykreslení kružnice MidPoint algoritmem.*/
void drawCircle(int s1, int s2, int R)
{
	int x = 0, y = R; // vykreslování od bodu [0,R]
	// nastavení startovací hodnoty preditkoru a dalších pomocných proměnných
	int P = 1 - R, X2 = 3, Y2 = 2 * R - 2;

	// vykreslování, dokud není x = y
	while (x <= y)
	{
		// vykreslení všech symetrických bodů k danému bodu
		put8PixelsOfCircle(x, y, s1, s2, COLOR_RED);

		// rozhodnutí o posunu v ose Y podle prediktoru
		if (P >= 0)
		{
			// modifikace prediktoru a pomocné proměnné
			P += -Y2;
			Y2 -= 2;

			y--; // posun v ose Y
		}

		// modifikace prediktoru a pomocné proměnné
		P += X2;
		X2 += 2;

		x++; // přírůstek na ose X je 1
	}
}


/*****************************************************************************/
/*****************************************************************************/
