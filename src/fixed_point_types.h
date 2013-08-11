/*
 * fixed_point_types.h
 *
 * Copyright 2013 Juan I Carrano <juan@carrano.com.ar>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 * Type definitios for fixed point numbers, vectors and quaternions
 */

#ifndef FIXED_POINT_TYPES_H
#define FIXED_POINT_TYPES_H

/* This header depends only upon the definition of
 * 	- int16_t
 * 	- int32_t
 * 	- INT16_MAX, INT16_MIN
 * 	- INT32_MAX, INT32_MIN
 * If you do not whish to (or cannot) use stdint.h, then you must provide the
 * above definitions
 */
#include <stdint.h>

/* ********************************************************************** *
 *  Fixed point formats
 * ********************************************************************** */

/* Q1.15 : frac */
typedef int16_t frac;

/* Q2.30 : double-frac */
typedef int32_t dfrac;

/* Q17.15 : extended-frac
 * The extended-frac (efrac) is defined as Q17.15. The reason for this is that
 * casting fracs to (int32_t) and adding them naturally results in a 17.15 value.
 */
typedef dfrac efrac;

/* Bit lengths */
#define FRAC_BIT (16)
#define DFRAC_BIT (32)
#define EFRAC_BIT (32)

/* Limits */

/* for the frac type */
#define FRAC_1 INT16_MAX
	/* "Almost 1". Since fracs lie in the range [-1, 1), the number 1 does
	 * not have a representation. FRAC_1 is the number closest to one, that
	 * is, ```1 - 2**(-15)```
	 */

#define FRAC_0_5 (-(INT16_MIN>>1)) /* 0.5 */
#define FRAC_minus1 INT16_MIN
	/* -1 . This is the smallest value a frac can assume
	 */

/* for the dfrac type */
#define DFRAC_1 (-(INT32_MIN>>1))
	/* 1. This is *really* the value 1.
	 */

#define DFRAC_0_5 (-(INT32_MIN>>2))  /* 0.5 */
#define DFRAC_almost1 (-(INT32_MIN>>1)-1)
	/* This has the same value as FRAC_1 (1 - 2**(-15)), but expressed as
	 * a dfrac
	 */

#define DFRAC_minus1 (INT32_MIN>>1) /* -1 */

#define DFRAC_MAX INT32_MAX /* 2 - 2^(-31), or "almost 2" */
#define DFRAC_MIN INT32_MIN /* -2 */

/* Conversions: frac <--> double */

#define FRAC2DBL(n) (((double)(n))/(-(double)FRAC_minus1))
#define F_TO_FRAC(f) ((frac)(-f*FRAC_minus1))

/* ************************************************************************ *
 * 3D Vector Support
 * ************************************************************************ */

/* vec3 is made out of fracs */
typedef struct {
	frac x,y,z;
} vec3;

/* dvec3 is made out of dfracs */
typedef struct {
	dfrac x,y,z;
} dvec3;

/* evec3 is made out of efracs, but since efracs and dfracs are both defined as
 * s32, evec3 has the same definition (but is not the same as) dvec3.
 */
typedef dvec3 evec3;

/* Zero vector */
#define VEC0 {0,0,0}

enum {AXIS_X, AXIS_Y, AXIS_Z};

/* ************************************************************************ *
 * Quaternion support
 * ************************************************************************ */

/* quat is made out of fracs */
typedef struct {
	frac r;
	vec3 v;
} quat;

/* dquat is made out of dfracs */
typedef struct {
	dfrac r;
	dvec3 v;
} dquat;

/* there is no equat */

/* Unit quaternion */
#define UNIT_QUAT {FRAC_1, {0, 0, 0}}
#define UNIT_DQUAT {DFRAC_1, {0, 0, 0}}

#endif /* FIXED_POINT_TYPES_H */
