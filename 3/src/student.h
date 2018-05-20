/**
 * @file        student.h
 * @author      Ladislav Mosner, VUT FIT Brno, imosner@fit.vutbr.cz
 * @author      Petr Kleparnik, VUT FIT Brno, ikleparnik@fit.vutbr.cz
 * @author      Kamil Behun, VUT FIT Brno, ibehun@fit.vutbr.cz
 * @author      Dominik Harmim, VUT FIT Brno, harmim6@gmail.com
 * @date        20.05.2018
 *
 * @brief       Definice funkci studentu.
 */


#ifndef STUDENT_H
#define STUDENT_H


#ifdef __linux__
#include <climits>
#endif


#include <vector>
#include <ctime>
#include <cstdio>

#include "color.h"


void putPixel(int x, int y, RGBA color);

RGBA getPixel(int x, int y);

void pinedaTriangle(
	const Point &v1, const Point &v2, const Point &v3,
	const RGBA &color1, const RGBA &color2,
	bool arrow = false
);

void pinedaPolygon(
	const Point *points, const int size, const RGBA &color1, const RGBA &color2
);


#endif // STUDENT_H
