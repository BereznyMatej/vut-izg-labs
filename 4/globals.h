/******************************************************************************
 * Laborator 04 - Zaklady pocitacove grafiky - IZG
 * ihulik@fit.vutbr.cz
 *
 * $Id:$
 *
 * Popis: Soubor obsahuje globalni promenne pro toto cviceni
 *
 * Opravy a modifikace:
 * Dominik Harmim <harmim6@gmail.com>
 */


#ifndef Globals_H
#define Globals_H


/*****************************************************************************
 * Includes
 */

#include "vector.h"

#include <SDL.h>


#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
 * Globalni promenne (definovane v main.c)
 */

/* kreslici buffer knihovny SDL */
extern SDL_Surface *screen;

/* kreslici buffer IZG cviceni */
extern S_RGBA *frame_buffer;

/* pomocna promenna pro ukonceni aplikace */
extern int width;
extern int height;

/* Kvalita generovane krivky - pocet segmentu - usecek,
 * ze kterych je vykreslena */
extern int quality;


#ifdef __cplusplus
}
#endif


#endif /* Globals_H */
/*****************************************************************************/
/*****************************************************************************/
