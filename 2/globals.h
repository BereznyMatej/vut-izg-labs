/******************************************************************************
 * Laborator 02 - Zaklady pocitacove grafiky - IZG
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

#include <SDL.h>


#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
 * Globalni promenne (definovane v main.c)
 */

/* kreslici buffer knihovny SDL */
extern SDL_Surface *screen;

/* kreslici buffer IZG cvičení */
extern S_RGBA *frame_buffer;

/* pomocna promenna pro ukonceni aplikace */
extern int width;
extern int height;


#ifdef __cplusplus
}
#endif


#endif /* Globals_H */
/*****************************************************************************/
/*****************************************************************************/
