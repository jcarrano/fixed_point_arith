/**
 * @file
 * @author Juan I Carrano
 * @copyright	Copyright 2013 by Juan I Carrano, Andrés Calcabrini, Juan I. Ubeira and
 * 		Nicolás Venturo
 * @license	GNU General Public License, version 3.
 *
 * Quaternion support.
 */

#ifndef FIXED_POINT_QUATERNION_H
#define FIXED_POINT_QUATERNION_H

#include "common.h"
#include "quaternion_types.h"

#ifdef FXP_C99_INLINE

#ifndef _FXP_INLINE_KW
#define _FXP_INLINE_KW inline
#define _FXP_INLINE_PROTO_KW extern inline
#endif

#ifndef FXP_DECLARATION
#define FXP_DECLARATION FXP_DECLARATION_C99_HEADER
#endif

#include "inline/quaternion.h"

#endif /* FXP_C99_INLINE */

#endif /* FIXED_POINT_QUATERNION_H */
