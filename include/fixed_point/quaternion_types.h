/**
 * @file
 * @author Juan I Carrano
 * @copyright	Copyright 2013 by Juan I Carrano, Andrés Calcabrini, Juan I. Ubeira and
 * 		Nicolás Venturo
 * @license	GNU General Public License, version 3.
 *
 * Type definitions for quaternions.
 */

#ifndef FIXED_POINT_QUATERNION_T_H
#define FIXED_POINT_QUATERNION_T_H

#include "types.h"
#include "vector_types.h"

/**
 * @defgroup fxp_quat	Quaternions
 * @{
 */

/** Single precision quaternion.
 *
 * Components are represented by value of @ref frac type
 */
typedef struct {
	frac r;		/*!< Scalar part*/
	vec3 v;		/*!< Vector part*/
} quat;

/** Double precision quaternion.
 *
 * Components are represented by value of @ref dfrac type.
 */
typedef struct {
	dfrac r;	/*!< Scalar part*/
	dvec3 v;	/*!< Vector part*/
} dquat;

/* there is no equat */

/** Literal for Unit quaternion */
#define UNIT_QUAT {{FRAC_1_V}, VEC0}
/** Literal for double precision Unit quaternion */
#define UNIT_DQUAT {{DFRAC_1_V}, VEC0}

/** This declaration is provided for the cases when a literal cannot be used */
static const quat quat_Unit = UNIT_QUAT;
/** This declaration is provided for the cases when a literal cannot be used */
static const dquat dquat_Unit = UNIT_DQUAT;

/** @}
 */

#endif /* FIXED_POINT_QUATERNION_T_H */
