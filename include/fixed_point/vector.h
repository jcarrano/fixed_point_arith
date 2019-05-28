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
 * Vector operations.
 */

#ifndef FXP_VECTOR_H
#define FXP_VECTOR_H

#include "common.h"
#include "vector_types.h"

/**
 * @addtogroup fxp_vec
 * @{
 */

/**
 * @defgroup fxp_vec_fmacros Function-generating macros.
 * @{
 */

/**
 * Macro to create functions with element by element operations between vectors.
 *
 * @param	name	Name of the function to be defined.
 * @param	typeR	Type of return value.
 * @param	typeA	Type of first argument.
 * @param	typeB	Type of second argument.
 * @param	f	Name of the function to be applied.
 */
#define MAKE_VEC_VEC_F3(name, typeR, typeA, typeB, f) \
FXP_DECLARATION(_FXP_INLINE_KW typeR name(typeA a, typeB b)) \
{ \
	typeR r; \
	r.x = f(a.x, b.x); \
	r.y = f(a.y, b.y); \
	r.z = f(a.z, b.z); \
	return r; \
}

/**
 * Macro to create functions with element by element operations between vectors.
 *
 * @param	name	Name of the function to be defined.
 * @param	type	Type of arguments and return value.
 * @param	f	Name of the function to be applied.
 */
#define MAKE_VEC_VEC_F(name, type, f) MAKE_VEC_VEC_F3(name, type, type, type, f)

/**
 * Macro to create functions with function-operations between vectors and scalars
 *
 * @param	name	Name of the function.
 * @param	typeR	Return type.
 * @param	typeA	Type of first argument.
 * @param	typeB	Type of second argument.
 * @param	f	Name of the function that will be applied.
 */
#define MAKE_VEC_SCALAR_F2(name, typeR, typeA, typeB, f) \
FXP_DECLARATION(_FXP_INLINE_KW typeR name(typeA a, typeB b)) \
{ \
	typeR r; \
	r.x = f(a.x, b); \
	r.y = f(a.y, b); \
	r.z = f(a.z, b); \
	return r; \
}

/**
 * Macro to create functions with function-operations between vectors and scalars
 *
 * @param	name	Name of the function to be defined.
 * @param	typeA	Type of first argument and return type.
 * @param	typeB	Type of second arguments.
 * @param	f	Name of the function to be applied.
 */
#define MAKE_VEC_SCALAR_F(name, typeA, typeB, f) \
			MAKE_VEC_SCALAR_F2(name, typeA, typeA, typeB, f)

/**
 * Macro to make a function that applies a scalar function to all elements
 * of a vector.
 *
 * @param	name	Name of the function.
 * @param	typeR	Return type.
 * @param	typeA	Type of argument.
 * @param	f	Name of the function that will be applied.
 */
#define MAKE_VEC_ELEM_F(name, typeR, typeA, f) \
FXP_DECLARATION(_FXP_INLINE_KW typeR name(typeA a)) \
{ \
	typeR r; \
	r.x = f(a.x); \
	r.y = f(a.y); \
	r.z = f(a.z); \
	return r; \
}

/** @}
 * @}
 */

#ifdef FXP_C99_INLINE

#ifndef _FXP_INLINE_KW
#define _FXP_INLINE_KW inline
#define _FXP_INLINE_PROTO_KW extern inline
#endif

#ifndef FXP_DECLARATION
#define FXP_DECLARATION FXP_DECLARATION_C99_HEADER
#endif

#include "inline/vector.h"

#endif /* FXP_C99_INLINE */

#endif /* FXP_VECTOR_H */
