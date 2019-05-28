/**
 * @file
 * @author	Juan I Carrano
 * @author	Juan I. Ubeira
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
