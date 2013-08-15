/*
 * fixed_point_inline.h
 *
 * Copyright 2013 Juan I Carrano <juan@superfreak.com.ar>
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
 */

 /* Some compilers, such as GCC, support the "extern inline" definition which
  * allows the inlining version of functions to be defined in the header. This
  * leaves to the decision of where to inline to the compiler (or to the user by
  * means of compiler switches). For those less advances compilers has to
  * choose: either have the rouutines in a different module and do zero inlining
  * or include them in ALL source files with the "static" keyword so one may have
  * inlinig and optimizations.
  */

#ifndef FIXED_POINT_INLINE_H
#define FIXED_POINT_INLINE_H

/* Each function in fixed_point_arith.c has _FTA_KW in front of it. We define it
 * to be the keyword "static" and then copy over the code with an include */

#define _FTA_KW static
#include "fixed_point_arith.c"

#endif /* FIXED_POINT_INLINE_H */
