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
