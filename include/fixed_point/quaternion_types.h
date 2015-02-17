/**
 * @file
 * @author Juan I Carrano
 * @copyright	Copyright 2013 by Juan I Carrano, Andrés Calcabrini, Juan I. Ubeira and
 * 		Nicolás Venturo. All rights reserved. \n
 * 		\n
 *		This program is free software: you can redistribute it and/or modify
 *		it under the terms of the GNU General Public License as published by
 *		the Free Software Foundation, either version 3 of the License, or
 *		(at your option) any later version. \n
 * 		\n
 *		This program is distributed in the hope that it will be useful,
 *		but WITHOUT ANY WARRANTY; without even the implied warranty of
 *		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *		GNU General Public License for more details. \n
 * 		\n
 *		You should have received a copy of the GNU General Public License
 *		along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
