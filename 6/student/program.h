/**
 * @file 
 * @brief This file contains function declarations for compiling
 * and linking shader programs.
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 * @author Dominik Harmim <harmim6@gmail.com>
 */


#pragma once


#ifdef __cplusplus
extern "C" {
#endif


#include <opengl/opengl.h>
#include <student/fwd.h>


/**
 * @brief This function creates shader.
 *
 * @param type a type of shader
 * @param source a source code of shader
 *
 * @return It returns compiled shader id.
 */
GLuint compileShader(GLenum type, const char *source);

/**
 * @brief This function creates shader program.
 *
 * @param shader0 an id of compiled shader
 * @param shader1 an id of compiled shader
 *
 * @return It returns linked shader program id.
 */
GLuint linkProgram(GLuint shader0, GLuint shader1);


#ifdef __cplusplus
}
#endif
