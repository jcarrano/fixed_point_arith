/**
 * @file
 * @author	Juan I Carrano
 * @author	Juan I. Ubeira
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
 * Routines for working with fixed point numbers.
 *
 * If FXP_C99_INLINE is defined, this header will include the definition of the
 * functions to allow inlining.
 *
 * If using link-time optimizations, then do not define FXP_C99_INLINE.
 */

#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#include <stdbool.h>
#include "common.h"
#include "types.h"

/** @defgroup fxp_fmacros	Function-generating macros
 * @{
 */

/**
 * Define a function with an operation between values.
 *
 * The function returns a value of a builtin type.
 *
 * @param	name	Name of the function.
 * @param	typeR	Return type. Must be a builtin.
 * @param	typeAB	type of arguments.
 * @param	op	Operator
 */
#define FXP_VALUE_OP(name, typeR, typeAB, op) \
FXP_DECLARATION(typeR name(typeAB a, typeAB b)) \
{ \
	return a.v op b.v; \
}

/**
 * Define a function with an operation between values.
 *
 * The function returns a value of type frac/dfrac/efrac.
 *
 * @param	name	Name of the function.
 * @param	typeR	Return type.
 * @param	typeA	Type of first argument.
 * @param	typeB 	Type of second argument.
 * @param	op	Operator
 */
#define FXP_OP2(name, typeR, typeA, typeB, op) \
FXP_DECLARATION(typeR name(typeA a, typeB b)) \
{ \
	typeR r = {a.v op b.v}; \
	return r; \
}

/**
 * Define a function with an operation between values.
 *
 * The function returns a value of type frac/dfrac/efrac.
 *
 * @param	name	Name of the function.
 * @param	typeRAB	Type of first and second argument and also return type.
 * @param	op	Operator
 */
#define FXP_OP3(name, typeRAB, op) FXP_OP2(name, typeRAB, typeRAB, typeRAB, op)

/**
 * Define a comparation function (frac).
 *
 * The function takes values of type frac and returns bool.
 *
 * @param	name	Name of the function.
 * @param	op	Operator
 */
#define FXP_SCMP(name, op) FXP_VALUE_OP(name, bool, frac, op)

/**
 * Define a comparation function (dfrac).
 *
 * The function takes values of type dfrac and returns bool.
 *
 * @param	name	Name of the function.
 * @param	op	Operator
 */
#define FXP_DCMP(name, op) FXP_VALUE_OP(name, bool, dfrac, op)

/** @}
 * @defgroup fxp_macros	Macros
 * @{
 */

/**
 * Determine the sign of a number.
 *
 * @param	a	A fixed point number
 *
 * @return		1 if the number is positive or zero, -1 if it is negative
 */
#define F_SIGN(a) (((a).v >= 0)? 1 : -1)

/** @}
 */

#ifdef FXP_C99_INLINE

#ifndef _FXP_INLINE_KW
#define _FXP_INLINE_KW inline
#define _FXP_INLINE_PROTO_KW extern inline
#endif

#ifndef FXP_DECLARATION
#define FXP_DECLARATION FXP_DECLARATION_C99_HEADER
#endif

#include "inline/fixed_point.h"

#endif /* FXP_C99_INLINE */

#endif /* FIXED_POINT_H */
