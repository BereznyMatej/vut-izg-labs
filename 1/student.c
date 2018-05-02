/******************************************************************************
 * Laborator 01 - Zaklady pocitacove grafiky - IZG
 * ihulik@fit.vutbr.cz
 *
 * $Id: $
 * 
 * Popis: Hlavicky funkci pro funkce studentu
 *
 * Opravy a modifikace:
 * - ibobak@fit.vutbr.cz, orderedDithering
 * Dominik Harmim <harmim6@gmail.com>
 */


#include "student.h"
#include "globals.h"

#include <time.h>


const int M[] = {
	0, 204, 51, 255,
	68, 136, 187, 119,
	34, 238, 17, 221,
	170, 102, 153, 85
};

const int M_SIDE = 4;


/******************************************************************************
 ******************************************************************************
 Funkce vraci pixel z pozice x, y. Je nutne hlidat frame_bufferu, pokud 
 je dana souradnice mimo hranice, funkce vraci barvu (0, 0, 0).
 Ukol za 0.25 bodu */
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
 je dana souradnice mimo hranice, funkce neprovadi zadnou zmenu.
 Ukol za 0.25 bodu */
void putPixel(int x, int y, S_RGBA color)
{
	// kontrola souřadnic
	if (x < 0 || x >= width || y < 0 || y >= height) return;

	// nastavení barvy na vypočítaném indexu
	*(frame_buffer + y * width + x) = color;
}


/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na odstiny sedi. Vyuziva funkce GetPixel a PutPixel.
 Ukol za 0.5 bodu */
void grayScale()
{
	// průchod přes všechny pixely
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// načtení aktuální barvy
			S_RGBA color = getPixel(x, y);

			// výpočet intenzity
			unsigned char intensity = ROUND2BYTE(
				0.299 * color.red + 0.287 * color.green + 0.114 * color.blue
			);

			// nastavení všech barevných složek pixelu na hodnotu intenzity
			putPixel(x, y, makeColor(intensity, intensity, intensity));
		}
	}
}


/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na cernobily pomoci algoritmu maticoveho rozptyleni.
 Ukol za 1 bod */

void orderedDithering()
{
	// převod na gracyscale
	grayScale();

	// průchod přes všechny pixely
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// načtení aktuální barvy
			S_RGBA color = getPixel(x, y);

			// porovnání barevné složky s hodnotou rozptylové matice
			// index matice: M[y % řád matice][x % řád matice]
			if (color.red > *(M + y % M_SIDE * M_SIDE + x % M_SIDE))
			{
				putPixel(x, y, COLOR_WHITE);
			}
			else
			{
				putPixel(x, y, COLOR_BLACK);
			}
		}
	}
}


/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na cernobily pomoci algoritmu distribuce chyby.
 Ukol za 1 bod */
void errorDistribution()
{
	// práh pro rozptýlení hodnoty pixelu
	static const unsigned char threshold = 127;

	// převod na gracyscale
	grayScale();

	// průchod přes všechny pixely
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// načtení aktuální barvy
			S_RGBA color = getPixel(x, y);

			// porovnání barevné složky s prahem, nastavení nové barvy
			// a výpočet chyby
			int e;
			if (color.red > threshold)
			{
				putPixel(x, y, COLOR_WHITE);
				e = color.red - 255;
			}
			else
			{
				putPixel(x, y, COLOR_BLACK);
				e = color.red;
			}

			// distribuce chyby
			int pixel_x, pixel_y;
			unsigned char pixel_color;

			// pixel (x + 1, y) += 3 / 8 * e (var / 8 <=> var >> 3)
			pixel_x = x + 1;
			pixel_y = y;
			pixel_color = (unsigned char)
				MAX(MIN(getPixel(pixel_x, pixel_y).red + (3 * e >> 3), 255), 0);
			putPixel(
				pixel_x, pixel_y,
				makeColor(pixel_color, pixel_color, pixel_color)
			);

			// pixel (x, y + 1) += 3 / 8 * e (var / 8 <=> var >> 3)
			pixel_x = x;
			pixel_y = y + 1;
			pixel_color = (unsigned char)
				MAX(MIN(getPixel(pixel_x, pixel_y).red + (3 * e >> 3), 255), 0);
			putPixel(
				pixel_x, pixel_y,
				makeColor(pixel_color, pixel_color, pixel_color)
			);

			// pixel (x + 1, y + 1) += 1 / 4 * e (var / 4 <=> var >> 2)
			pixel_x = x + 1;
			pixel_y = y + 1;
			pixel_color = (unsigned char)
				MAX(MIN(getPixel(pixel_x, pixel_y).red + (e >> 2), 255), 0);
			putPixel(
				pixel_x, pixel_y,
				makeColor(pixel_color, pixel_color, pixel_color)
			);
		}
	}
}


/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na cernobily pomoci metody prahovani.
 Demonstracni funkce */
void thresholding(int Threshold)
{
	/* Prevedeme obrazek na grayscale */
	grayScale();

	/* Projdeme vsechny pixely obrazku */
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			/* Nacteme soucasnou barvu */
			S_RGBA color = getPixel(x, y);

			/* Porovname hodnotu cervene barevne slozky s prahem.
			   Muzeme vyuzit jakoukoli slozku (R, G, B), protoze
			   obrazek je sedotonovy, takze R=G=B */
			if (color.red > Threshold)
			{
				putPixel(x, y, COLOR_WHITE);
			}
			else
			{
				putPixel(x, y, COLOR_BLACK);
			}
		}
	}
}


/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na cernobily pomoci nahodneho rozptyleni. 
 Vyuziva funkce GetPixel, PutPixel a GrayScale.
 Demonstracni funkce. */
void randomDithering()
{
	/* Prevedeme obrazek na grayscale */
	grayScale();

	/* Inicializace generatoru pseudonahodnych cisel */
	srandom((unsigned int) time(NULL));

	/* Projdeme vsechny pixely obrazku */
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			/* Nacteme soucasnou barvu */
			S_RGBA color = getPixel(x, y);

			/* Porovname hodnotu cervene barevne slozky s nahodnym prahem.
			   Muzeme vyuzit jakoukoli slozku (R, G, B), protoze
			   obrazek je sedotonovy, takze R=G=B */
			if (color.red > random() % 255)
			{
				putPixel(x, y, COLOR_WHITE);
			}
			else
			{
				putPixel(x, y, COLOR_BLACK);
			}
		}
	}
}


/*****************************************************************************/
/*****************************************************************************/
