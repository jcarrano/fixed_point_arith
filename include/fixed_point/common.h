/**
 * @file
 * @author	Juan I Carrano
 * @author	Juan I. Ubeira
 * @copyright	Copyright 2013 by Juan I Carrano, Andrés Calcabrini, Juan I. Ubeira and
 * 		Nicolás Venturo
 * @license	GNU General Public License, version 3.
 *
 * Common macros.
 */

#ifndef FXP_COMMON_H
#define FXP_COMMON_H

#define FXP_DECLARATION_C99_HEADER(x) _FXP_INLINE_KW x

#define FXP_DECLARATION_C99_BODY(x) _FXP_INLINE_PROTO_KW x; \
_FXP_INLINE_KW x

#endif /* FXP_COMMON_H */
