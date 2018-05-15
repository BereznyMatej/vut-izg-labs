/******************************************************************************
 * Laborator 02 - Zaklady pocitacove grafiky - IZG
 * ihulik@fit.vutbr.cz
 *
 * $Id:$
 *
 * Popis:
 *    soubor obsahuje funkce pro zapis a cteni frame bufferu z/do souboru
 *
 * Opravy a modifikace:
 * Dominik Harmim <harmim6@gmail.com>
 */


#ifndef IO_H
#define IO_H


/*****************************************************************************
 * Includes
 */

#include "color.h"


#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
 * Funkce pro cteni/zapis do/z souboru
 */

/* Nacteni BMP souboru do frame_buffer struktury */
int loadMyBitmap(
	const char *filename, S_RGBA **frame_buffer, int *width, int *height
);

/* Ulozeni BMP souboru z frame_buffer struktury */
int saveMyBitmap(
	const char *filename, S_RGBA **frame_buffer, int width, int height
);

/* Vykresleni usecek ze souboru */
bool drawLinesFromFile(const char *filename);


#ifdef __cplusplus
}
#endif


#endif
/*****************************************************************************/
/*****************************************************************************/
