/******************************************************************************
 * Laborator 04 Krivky - Zaklady pocitacove grafiky - IZG
 * ihulik@fit.vutbr.cz
 *
 * 
 * Popis: Hlavicky funkci pro funkce studentu
 *
 * Opravy a modifikace:
 * - isvoboda@fit.vutbr.cz
 * Dominik Harmim <harmim6@gmail.com>
 */


#include "student.h"
#include "globals.h"

#include <ctime>
#include <cmath>


//Viz hlavicka vector.h
USE_VECTOR_OF(Point2d, point2d_vec)


/* Secte dva body Point2d a vysledek vrati v result (musi byt inicializovan
 * a alokovan) */
void addPoint2d(const Point2d *a, const Point2d *b, Point2d *result)
{
	IZG_ASSERT(result);
	result->x = a->x + b->x;
	result->y = a->y + b->y;
}


/**
 * Inicializace ridicich bodu horni trajektorie ve vykreslovacim okne.
 * Pocatek souradnicove soustavy je v levem hornim rohu okna. Xova souradnice
 * roste smerem doprava, Y smerem dolu.
 *
 * @param points vystup, kam se pridavaji ridici body
 * @param offset_x posun vsech ridicich bodu v horizontalnim smeru
 *       (aby se mohli souradnice zadavat s pocatkem [0,0])
 * @param offset_y posun vsech ridicich bodu ve vertikalnim smeru
 */
void initControlPointsUp(S_Vector **points, int offset_x, int offset_y)
{
	*points = vecCreateEmpty(sizeof(Point2d));
	Point2d p;
	p.x = 0;
	p.y = 0;
	point2d_vecPushBack(*points, p);

	p.x = 40;
	p.y = -250;
	point2d_vecPushBack(*points, p);
	p.x = 160;
	p.y = -250;
	point2d_vecPushBack(*points, p);

	p.x = 200;
	p.y = 0;
	point2d_vecPushBack(*points, p);

	p.x = 210;
	p.y = -180;
	point2d_vecPushBack(*points, p);
	p.x = 350;
	p.y = -180;
	point2d_vecPushBack(*points, p);

	p.x = 360;
	p.y = 0;
	point2d_vecPushBack(*points, p);

	p.x = 390;
	p.y = -120;
	point2d_vecPushBack(*points, p);
	p.x = 430;
	p.y = -120;
	point2d_vecPushBack(*points, p);

	p.x = 460;
	p.y = 0;
	point2d_vecPushBack(*points, p);

	p.x = 470;
	p.y = -70;
	point2d_vecPushBack(*points, p);
	p.x = 525;
	p.y = -70;
	point2d_vecPushBack(*points, p);

	p.x = 535;
	p.y = 0;
	point2d_vecPushBack(*points, p);

	p.x = 545;
	p.y = -40;
	point2d_vecPushBack(*points, p);
	p.x = 575;
	p.y = -40;
	point2d_vecPushBack(*points, p);

	p.x = 585;
	p.y = 0;
	point2d_vecPushBack(*points, p);

	// posun bodů o offset
	Point2d offset = {(double) offset_x, (double) offset_y, 1.0};
	for (int i = 0; i < (*points)->size; i++)
	{
		addPoint2d(
			point2d_vecGetPtr(*points, i),
			&offset,
			point2d_vecGetPtr(*points, i)
		);
	}
}


/**
 * Inicializace ridicich bodu dolni trajektorie ve vykreslovacim okne.
 * Pocatek souradnicove soustavy je v levem hornim rohu okna. Xova souradnice
 * roste smerem doprava, Y smerem dolu.
 *
 * @param points vystup, kam se pridavaji ridici body
 * @param offset_x posun vsech ridicich bodu v horizontalnim smeru
 *       (aby se mohli souradnice zadavat s pocatkem [0,0])
 * @param offset_y posun vsech ridicich bodu ve vertikalnim smeru
 */
void initControlPointsDown(S_Vector **points, int offset_x, int offset_y)
{
	/*
	 * Uloha c.2
	 * Nasledujuci volanni funkce initControlPointsUp(.) zmazte a nahradte
	 * vlastnim kodem, ktery inicializuje ridici body tak, aby byla
	 * trajektorie spojita (C1). Muzete skopirovat kod funkce
	 * initControlPointsUp(.) a upravit primo souradnice bodu v kodu.
	 */

	// zmenšování křivek třeb o 3/4

	*points = vecCreateEmpty(sizeof(Point2d));
	Point2d p;
	p.x = 0;
	p.y = 0;
	point2d_vecPushBack(*points, p);

	p.x = 40;
	p.y = -250;
	point2d_vecPushBack(*points, p);
	p.x = 160;
	p.y = -250;
	point2d_vecPushBack(*points, p);

	p.x = 200;
	p.y = 0;
	point2d_vecPushBack(*points, p);

	p.x = 230; // 200 + (200 - 160) * (3 / 4)
	p.y = 187.5; // 250 * (3 / 4)
	point2d_vecPushBack(*points, p);
	p.x = 337.5; // 360 - (390 - 360) * (3 / 4)
	p.y = 187.5; // 250 * (3 / 4)
	point2d_vecPushBack(*points, p);

	p.x = 360;
	p.y = 0;
	point2d_vecPushBack(*points, p);

	p.x = 382.5; // 360 + (390 - 360) * (3 / 4)
	p.y = -140.626; // -187.5 * (3 / 4)
	point2d_vecPushBack(*points, p);
	p.x = 437.5; // 460 - (460 - 430) * (3 / 4)
	p.y = -140.625; // -187.5 * (3 / 4)
	point2d_vecPushBack(*points, p);

	p.x = 460;
	p.y = 0;
	point2d_vecPushBack(*points, p);

	p.x = 482.5; // 460 + (460 - 430) * (3 / 4)
	p.y = 105.46875; // 140.625 * (3 / 4)
	point2d_vecPushBack(*points, p);
	p.x = 527.5; // 535 - (545 - 535) * (3 / 4)
	p.y = 105.46875; // 140.625 * (3 / 4)
	point2d_vecPushBack(*points, p);

	p.x = 535;
	p.y = 0;
	point2d_vecPushBack(*points, p);

	p.x = 542.5; // 535 + (545 - 535) * (3 / 4)
	p.y = -79.1015625; // -105.46875 * (3 / 4)
	point2d_vecPushBack(*points, p);
	p.x = 577.5; // 585 - (585 - 575) * (3 / 4)
	p.y = -79.1015625; // -105.46875 * (3 / 4)
	point2d_vecPushBack(*points, p);

	p.x = 585;
	p.y = 0;
	point2d_vecPushBack(*points, p);

	// posun bodů o offset
	Point2d offset = {(double) offset_x, (double) offset_y, 1.0};
	for (int i = 0; i < (*points)->size; i++)
	{
		addPoint2d(
			point2d_vecGetPtr(*points, i),
			&offset,
			point2d_vecGetPtr(*points, i)
		);
	}
}


/**
 * Implementace vypoctu Bezierove kubiky.
 *
 * @param P0,P1,P2,P3 ridici body kubiky
 * @param quality pocet bodu na krivke, ktere chceme vypocitat
 * @param trajectory_points vystupni vektor bodu kubiky
 */
void bezierCubic(
	const Point2d *P0, const Point2d *P1, const Point2d *P2, const Point2d *P3,
	const int quality, S_Vector *trajectory_points
)
{
	/*
	 * Soucast Ulohy c.1:
	 * Sem pridejte kod vypoctu Bezierove kubiky.
	 * Body krivky pridavejte do trajectory_points.
	 */

	Point2d Q; // Q(t) bod na křivce daný parameterm t
	// Výpočet 'quantiy' bodů na křivce, parametr t se bude pohybovat
	// v intervalu (0,1).
	double step = 1.0 / (quality - 1), t = step;
	for (int i = 0; i < quality; i++)
	{
		double t1 = 1 - t, t12 = t1 * t1, t2 = t * t,
			B0 = t1 * t12, // B0 = (1 - t)^3
			B1 = 3 * t * t12, // B1 = 3 * t * (1 - t)^2
			B2 = 3 * t2 * t1, // B2 = 3 * t^2 * (1 - t)
			B3 = t * t2; // B3 = t^3

		// Q(t) = P0 * B0 + P1 * B1 + P2 * B2 + P3 * B3
		Q.x = P0->x * B0 + P1->x * B1 + P2->x * B2 + P3->x * B3;
		Q.y = P0->y * B0 + P1->y * B1 + P2->y * B2 + P3->y * B3;

		// přidání vypočítaného bodu do výsledného vektoru
		point2d_vecPushBack(trajectory_points, Q);

		t += step; // zvýšení parametru t o krok daný počtem požadovaných bodů
	}
}


/**
 * Implementace vypoctu trajektorie, ktera se sklada z Bezierovych kubik.
 *
 * @param quality pocet bodu krivky, ktere mame urcit
 * @param control_points ridici body krivky
 * @param trajectory_points vystupni body zakrivene trajektorie
 */
void bezierCubicsTrajectory(
	int quality, const S_Vector *control_points, S_Vector *trajectory_points
)
{
	point2d_vecClean(trajectory_points);

	/*
	 * Uloha c.1
	 * Ziskejte postupne 4 ridici body a pro kazdou ctverici
	 * vypocitejte body Bezierovy kubiky.
	 *
	 * Kostra:
	 *  for(...; ...; ...)
	 *  {
	 *    Point2d *P0 = ...
	 *    Point2d *P1 = ...
	 *    Point2d *P2 = ...
	 *    Point2d *P3 = ...
	 *    bezierCubic(P0, P1, P2, P3, quality, trajectory_points);
	 *  }
	 */

	// musí být alespoň 4 kontrolní body
	if (point2d_vecSize(control_points) < 4)
	{
		return;
	}

	// Průchod přes každé 4 kontrolní body, každý 4. bod se používá dvakrát.
	for (int i = 3; i < point2d_vecSize(control_points); i += 3)
	{
		// výpočet kubiky ze 4 řídících bodů
		bezierCubic(
			point2d_vecGetPtr(control_points, i - 3),
			point2d_vecGetPtr(control_points, i - 2),
			point2d_vecGetPtr(control_points, i - 1),
			point2d_vecGetPtr(control_points, i),
			quality,
			trajectory_points
		);
	}
}
