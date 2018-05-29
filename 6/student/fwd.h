/**
 * @file 
 * @brief This file contains forward declarations and constants.
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 * @author Dominik Harmim <harmim6@gmail.com>
 */


#pragma once


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>


/**
 * @brief pi constant
 */
#define MY_PI 3.14159265359f


struct Vec2; //forward declaration
struct Vec3; //forward declaration
struct Vec4; //forward declaration
struct Mat4; //forward declaration


typedef struct Vec2 Vec2; ///< shortcut
typedef struct Vec3 Vec3; ///< shortcut
typedef struct Vec4 Vec4; ///< shortcut
typedef struct Mat4 Mat4; ///< shortcut


/**
 * @brief Instance of this type contains index to vertex.
 */
typedef uint32_t VertexIndex;


#ifdef __cplusplus
}
#endif
