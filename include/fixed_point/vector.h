/**
 * @author	Juan I Carrano
 * @author	Juan I. Ubeira
 * @copyright	Copyright 2014 by Juan I Carrano, Andrés Calcabrini, Juan I. Ubeira and
 * 		Nicolás Venturo
 * @license	GNU General Public License, version 3.
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
 * @param	type	Type of arguments and return value.
 * @param	f	Name of the function to be applied.
 */
#define MAKE_VEC_VEC_F(name, type, f) \
FXP_DECLARATION(_FXP_INLINE_KW type name(type a, type b)) \
{ \
	type r; \
	r.x = f(a.x, b.x); \
	r.y = f(a.y, b.y); \
	r.z = f(a.z, b.z); \
	return r; \
}

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
