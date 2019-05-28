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
