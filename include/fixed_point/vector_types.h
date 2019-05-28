/**
 * @file
 * @author Juan I Carrano
 * @copyright	Copyright (c) 2019 Juan I Carrano
 * @copyright	Copyright (c) 2013 Juan I Carrano, Andrés Calcabrini,
 *                                 Juan I. Ubeira and Nicolás Venturo.
 * @copyright	All rights reserved.
 * ```
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of copyright holders nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * ```
 *
 * Type definitions for 3D vectors.
 */

#ifndef FIXED_POINT_VECTOR_T_H
#define FIXED_POINT_VECTOR_T_H

#include "types.h"

/**
 * @defgroup fxp_vec	Vectors
 * @{
 */

/**
 * Mixed integer/fractional 3D vector.
 *
 * Components are represented by values of type @ref mfrac .
 */
typedef struct {
	mfrac x,y,z;
} mvec3;

/**
 * Single precision 3D vector.
 *
 * Components are represented by values of type @ref frac .
 */
typedef struct {
	frac x,y,z;
} vec3;

/**
 * Double precision 3D vector.
 *
 * Components are represented by values of type @ref dfrac .
 */
typedef struct {
	dfrac x,y,z;
} dvec3;

/**
 * Extended precision 3D vector.
 *
 * Components are represented by values of type @ref efrac .
 */
typedef struct {
	efrac x,y,z;
} evec3;

/** Literal for the  Zero vector */
#define VEC0 {{0},{0},{0}}

static const mvec3 mvec3_Zero = VEC0;	/*!< Constant for the zero vector */
static const vec3 vec3_Zero = VEC0;	/*!< Constant for the zero vector */
static const dvec3 dvec3_Zero = VEC0;	/*!< Constant for the zero vector */
static const evec3 evec3_Zero = VEC0;	/*!< Constant for the zero vector */

/**
 * This type is used to indicate the axis.
 */
typedef enum vec_axis {AXIS_X, AXIS_Y, AXIS_Z} vec_axis;

/**
 * @addtogroup fxp_width
 * @{
 */

#if (FRAC_BIT == 16)
/** 3d vector with 16 bit signed components. */
typedef vec3 vec3_s16;
#endif

#if (DFRAC_BIT == 32)
/** 3d vector with 32 bit signed components */
typedef dvec3 vec3_s32;
#endif

/** @}
 */

/** @}
 */

#endif /* FIXED_POINT_VECTOR_T_H */
