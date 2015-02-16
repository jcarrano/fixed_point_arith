/**
 * @file
 * @author Juan I Carrano
 * @copyright	Copyright 2013 by Juan I Carrano, Andrés Calcabrini, Juan I. Ubeira and
 * 		Nicolás Venturo
 * @license	GNU General Public License, version 3.
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
