/**
 * @file        student.cpp
 * @author      Ladislav Mosner, VUT FIT Brno, imosner@fit.vutbr.cz
 * @author      Petr Kleparnik, VUT FIT Brno, ikleparnik@fit.vutbr.cz
 * @author      Kamil Behun, VUT FIT Brno, ibehun@fit.vutbr.cz
 * @author      Dominik Harmim, VUT FIT Brno, harmim6@gmail.com
 * @date        20.05.2018
 *
 * @brief       Deklarace funkci studentu. DOPLNUJI STUDENTI
 */


#include "base.h"
#include "student.h"
#include "globals.h"

#include <cmath>


/**
 * @brief Vraci barvu pixelu z pozice [x, y].
 *
 * @param[in] x X souradnice pixelu
 * @param[in] y Y souradnice pixelu
 *
 * @return Barva pixelu na pozici [x, y] ve formatu RGBA.
 */
RGBA getPixel(int x, int y)
{
	if (x >= width || y >= height || x < 0 || y < 0)
	{
		IZG_ERROR("Pristup do framebufferu mimo hranice okna.\n");
	}
	return framebuffer[y * width + x];
}


/**
 * @brief Nastavi barvu pixelu na pozici [x, y].
 *
 * @param[in] x X souradnice pixelu
 * @param[in] y Y souradnice pixelu
 * @param[in] color barva pixelu ve formatu RGBA
 */
void putPixel(int x, int y, RGBA color)
{
	if (x >= width || y >= height || x < 0 || y < 0)
	{
		IZG_ERROR("Pristup do framebufferu mimo hranice okna.\n");
	}
	framebuffer[y * width + x] = color;
}


/**
 * @brief Vykresli usecku se souradnicemi [x1, y1] a [x2, y2].
 *
 * @param[in] x1 X souradnice 1. bodu usecky
 * @param[in] y1 Y souradnice 1. bodu usecky
 * @param[in] x2 X souradnice 2. bodu usecky
 * @param[in] y2 Y souradnice 2. bodu usecky
 * @param[in] color barva pixelu usecky ve formatu RGBA
 * @param[in] arrow priznak pro vykresleni sipky (orientace hrany)
 */
void drawLine(int x1, int y1, int x2, int y2, RGBA color, bool arrow = false)
{
	if (arrow)
	{
		// Sipka na konci hrany
		double vx1 = x2 - x1;
		double vy1 = y2 - y1;
		double length = sqrt(vx1 * vx1 + vy1 * vy1);
		double vx1N = vx1 / length;
		double vy1N = vy1 / length;
		double vx1NN = -vy1N;
		double vy1NN = vx1N;
		int w = 3;
		int h = 10;
		int xT = (int) (x2 + w * vx1NN - h * vx1N);
		int yT = (int) (y2 + w * vy1NN - h * vy1N);
		int xB = (int) (x2 - w * vx1NN - h * vx1N);
		int yB = (int) (y2 - w * vy1NN - h * vy1N);
		pinedaTriangle(
			Point(x2, y2), Point(xT, yT), Point(xB, yB), color, color, false
		);
	}

	bool steep = abs(y2 - y1) > abs(x2 - x1);

	if (steep)
	{
		SWAP(x1, y1);
		SWAP(x2, y2);
	}

	if (x1 > x2)
	{
		SWAP(x1, x2);
		SWAP(y1, y2);
	}

	const int dx = x2 - x1, dy = abs(y2 - y1);
	const int P1 = 2 * dy, P2 = P1 - 2 * dx;
	int P = 2 * dy - dx;
	int y = y1;
	int ystep = 1;
	if (y1 > y2)
	{
		ystep = -1;
	}

	for (int x = x1; x <= x2; x++)
	{
		if (steep)
		{
			if (y >= 0 && y < width && x >= 0 && x < height)
			{
				putPixel(y, x, color);
			}
		}
		else if (x >= 0 && x < width && y >= 0 && y < height)
		{
			putPixel(x, y, color);
		}

		if (P >= 0)
		{
			P += P2;
			y += ystep;
		}
		else
		{
			P += P1;
		}
	}
}


/**
 * @brief Vyplni a vykresli trojuhelnik.
 *
 * @param[in] v1 prvni bod trojuhelniku
 * @param[in] v2 druhy bod trojuhelniku
 * @param[in] v3 treti bod trojuhelniku
 * @param[in] color1 barva vyplne trojuhelniku
 * @param[in] color2 barva hranice trojuhelniku
 * @param[in] arrow priznak pro vykresleni sipky (orientace hrany)
 *
 * SPOLECNY UKOL. Doplnuji studenti se cvicicim.
 */
void pinedaTriangle(
	const Point &v1, const Point &v2, const Point &v3,
	const RGBA &color1, const RGBA &color2,
	bool arrow
)
{
	// Nalezeni obalky (minX, maxX), (minY, maxY) trojuhleniku.

	// Hledání minima/maxima ze věšech bodů trojúhelníku.
	int minX = MIN(v1.x, MIN(v2.x, v3.x)),
		maxX = MAX(v1.x, MAX(v2.x, v3.x)),
		minY = MIN(v1.y, MIN(v2.y, v3.y)),
		maxY = MAX(v1.y, MAX(v2.y, v3.y));


	// Oriznuti obalky (minX, maxX, minY, maxY) trojuhleniku podle rozmeru okna.

	// Omezení minim a maxim v bodě X/Y na rozsah <0, width - 1/height - 1>.
	minX = MIN(MAX(minX, 0), width - 1);
	maxX = MIN(MAX(maxX, 0), width - 1);
	minY = MIN(MAX(minY, 0), height - 1);
	maxY = MIN(MAX(maxY, 0), height - 1);


	// Spocitani parametru hranove funkce (deltaX, deltaY) pro kazdou hranu.
	// Hodnoty deltaX, deltaY jsou souradnicemi vektoru, ktery ma pocatek
	// v prvnim vrcholu hrany, konec v druhem vrcholu.

	// (deltaX, deltaY) = (x1 - x0, y1 - y0)
	EdgeParams edgeParams(3);
	edgeParams[0] = EdgeParam(v2.x - v1.x, v2.y - v1.y); // [v1, v2]
	edgeParams[1] = EdgeParam(v3.x - v2.x, v3.y - v2.y); // [v2, v3]
	edgeParams[2] = EdgeParam(v1.x - v3.x, v1.y - v3.y); // [v3, v1]


	// Vypocet prvnotni hodnoty hranove funkce.

	// E(x, y) = E(minX, minY) = (minY - y0) * deltaX - (minX - x0) * deltaY
	EdgeFncValues edgeFncValues(3);
	edgeFncValues[0] =
		(minY - v1.y) * edgeParams[0].deltaX
		- (minX - v1.x) * edgeParams[0].deltaY; // v1
	edgeFncValues[1] =
		(minY - v2.y) * edgeParams[1].deltaX
		- (minX - v2.x) * edgeParams[1].deltaY; // v2
	edgeFncValues[2] =
		(minY - v3.y) * edgeParams[2].deltaX
		- (minX - v3.x) * edgeParams[2].deltaY; // v3


	// Vyplnovani: Cyklus pres vsechny body (x, y)
	// v obdelniku (minX, minY), (maxX, maxY).
	// Pro aktualizaci hodnot hranove funkce v bode P (x +/- 1, y) nebo
	// P (x, y +/- 1) vyuzijte hodnoty hranove funkce E (x, y) z bodu P (x, y).
	for (int y = minY; y <= maxY; y++)
	{
		// Uložení hodnoty Ei pro aktuální řádek.
		EdgeFncValues currentEdgeFncValues(edgeFncValues);

		for (int x = minX; x <= maxX; x++)
		{
			// Hodnota pixelu se naství pouze, pokud Ei(x, y) >= 0 pro
			// pro všechny body trojúhelníku.
			if (
				currentEdgeFncValues[0] >= 0
				&& currentEdgeFncValues[1] >= 0
				&& currentEdgeFncValues[2] >= 0
			)
			{
				putPixel(x, y, color1);
			}

			// Aktualizace hodnoty Ei po inkrementaci X.
			// E(x + 1, y) = E(x, y) - deltaY
			currentEdgeFncValues[0] -= edgeParams[0].deltaY; // v1
			currentEdgeFncValues[1] -= edgeParams[1].deltaY; // v2
			currentEdgeFncValues[2] -= edgeParams[2].deltaY; // v3
		}

		// Aktualizace hodnoty Ei po inkrementaci Y.
		// E(x, y + 1) = E(x, y) + deltaX
		edgeFncValues[0] += edgeParams[0].deltaX; // v1
		edgeFncValues[1] += edgeParams[1].deltaX; // v1
		edgeFncValues[2] += edgeParams[2].deltaX; // v3
	}


	// Prekresleni hranic trojuhelniku barvou color2.
	drawLine(v1.x, v1.y, v2.x, v2.y, color2, arrow); // [v1, v2]
	drawLine(v2.x, v2.y, v3.x, v3.y, color2, arrow); // [v2, v3]
	drawLine(v3.x, v3.y, v1.x, v1.y, color2, arrow); // [v3, v1]
}


/**
 * @brief Vyplni a vykresli polygon.
 *
 * @param[in] points pole bodu polygonu
 * @param[in] size pocet bodu polygonu (velikost pole "points")
 * @param[in] color1 barva vyplne polygonu
 * @param[in] color2 barva hranice polygonu
 *
 * SAMOSTATNY BODOVANY UKOL. Doplnuji pouze studenti.
 */
void pinedaPolygon(
	const Point *points, const int size, const RGBA &color1, const RGBA &color2
)
{
	// Pri praci muzete vyuzit pro vas predpripravene datove typy z base.h.,
	// napriklad:
	//
	//      Pro ukladani parametru hranovych funkci muzete vyuzit prichystany
	//      vektor parametru hranovych funkci "EdgeParams":
	//
	//          // Vytvorite vektor (pole) "edgeParams" parametru hranovych
	//          // funkci o velikosti "size".
	//          EdgeParams edgeParams(size)
	//
	//          // Pristup k parametrum (deltaX, deltaY) hranove funkce
	//          // v poli "edgeParams" na indexu "i".
	//          edgeParams[i].deltaX, edgeParams[i].deltaY
	//
	//      Pro ukladani hodnot hranovych funkci muzete vyuzit prichystany
	//      vektor hodnot hranovych funkci "EdgeFncValues":
	//
	//          // Vytvorite vektor (pole) "edgeFncValues" hodnot hranovych
	//          // funkci o velikosti "size".
	//          EdgeFncValues edgeFncValues(size)
	//
	//          // Pristup k hodnote hranove funkce v poli "edgeFncValues"
	//          // na indexu "i".
	//          edgeFncValues[i]
	//

	// Test konvexnosti polygonu.
	for (int i = 0; i < size; i++) // průchod přes všechny vrcholy
	{
		// Výpočet obecné rovnice přímky ax + by + c = 0 pro body i a j = i + 1.
		int j = (i + 1) % size, k = (i + 2) % size;
		int a = points[i].y - points[j].y, // a = yi - yj
			b = points[j].x - points[i].x, // b = xj - xi
			// c = xi * yj - xj * yi
			c = points[i].x * points[j].y - points[j].x * points[i].y;

		// Pokud do obecné rovnice přímky dosadím za bod c následující bod,
		// tj. i + 2 a výsledek rovnice bude < 0 pro kterékoliv 3 body,
		// tak polygon není konvexní.
		if (a * points[k].x + b * points[k].y + c < 0)
		{
			return;
		}
	}


	// Nalezeni obalky (minX, maxX), (minY, maxY) polygonu.

	// Hledání minima/maxima ze věšech bodů polygonu.
	int minX = width - 1, maxX = 0, minY = height - 1, maxY = 0;
	for (int i = 0; i < size; i++) // průchod přes všechny vrcholy
	{
		minX = MIN(minX, points[i].x);
		maxX = MAX(maxX, points[i].x);
		minY = MIN(minY, points[i].y);
		maxY = MAX(maxY, points[i].y);
	}


	// Oriznuti obalky (minX, maxX), (minY, maxY) polygonu podle rozmeru okna

	// Omezení minim a maxim v bodě X/Y na rozsah <0, width - 1/height - 1>.
	minX = MAX(minX, 0);
	maxX = MIN(maxX, width - 1);
	minY = MAX(minY, 0);
	maxY = MIN(maxY, height - 1);


	// Spocitani parametru (deltaX, deltaY) hranove funkce pro kazdou hranu.
	// Hodnoty deltaX, deltaY jsou souradnicemi vektoru, ktery ma pocatek
	// v prvnim vrcholu hrany, konec v druhem vrcholu.

	// (deltaX, deltaY) = (x1 - x0, y1 - y0)
	EdgeParams edgeParams((unsigned long) size);
	for (int i = 0; i < size; i++) // průchod přes všechny vrcholy
	{
		int j = (i + 1) % size;
		Point p1 = points[i], p2 = points[j];
		edgeParams[i] = EdgeParam(p2.x - p1.x, p2.y - p1.y); // [pi, pi + 1]
	}


	// Vypocet prvnotnich hodnot hranovych funkci pro jednotlive hrany.

	// E(x, y) = E(minX, minY) = (minY - y0) * deltaX - (minX - x0) * deltaY
	EdgeFncValues edgeFncValues((unsigned long) size);
	for (int i = 0; i < size; i++) // průchod přes všechny vrcholy
	{
		edgeFncValues[i] =
			(minY - points[i].y) * edgeParams[i].deltaX
			- (minX - points[i].x) * edgeParams[i].deltaY;
	}


	// Vyplnovani: Cyklus pres vsechny body (x, y)
	// v obdelniku (minX, minY), (maxX, maxY).
	// Pro aktualizaci hodnot hranove funkce
	// v bode P (x +/- 1, y) nebo P (x, y +/- 1)
	// vyuzijte hodnoty hranove funkce E (x, y) z bodu P (x, y)
	for (int y = minY; y <= maxY; y++)
	{
		// Uložení hodnoty Ei pro aktuální řádek.
		EdgeFncValues currentEdgeFncValues(edgeFncValues);

		for (int x = minX; x <= maxX; x++)
		{
			// Hodnota pixelu se naství pouze, pokud Ei(x, y) >= 0 pro
			// pro všechny body polygonu.
			bool inside = true;
			for (int i = 0; i < size; i++) // průchod přes všechny vrcholy
			{
				if (currentEdgeFncValues[i] < 0)
				{
					inside = false;
					break;
				}
			}

			// Nastavení hodnoty pixelu, pouze pokud je bod uvnitř polygonu.
			if (inside)
			{
				putPixel(x, y, color1);
			}

			// Aktualizace hodnoty Ei po inkrementaci X.
			for (int i = 0; i < size; i++) // průchod přes všechny vrcholy
			{
				// E(x + 1, y) = E(x, y) - deltaY
				currentEdgeFncValues[i] -= edgeParams[i].deltaY;
			}
		}

		// Aktualizace hodnoty Ei po inkrementaci Y.
		for (int i = 0; i < size; i++) // průchod přes všechny vrcholy
		{
			// E(x, y + 1) = E(x, y) + deltaX
			edgeFncValues[i] += edgeParams[i].deltaX;
		}
	}


	// Prekresleni hranic polygonu barvou color2.
	for (int i = 0; i < size; i++) // průchod přes všechny vrcholy
	{
		int j = (i + 1) % size;
		drawLine( // [vi, vi + 1]
			points[i].x, points[i].y, points[j].x, points[j].y, color2/*, true*/
		);
	}
}
