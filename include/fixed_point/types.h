/**
 * @file	types.h
 * @author	Juan I Carrano <juan@carrano.com.ar>
 * @copyright 	Copyright 2013 Juan I Carrano <juan@carrano.com.ar>. All rights
 *		reserved. \n
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
 * @brief Type definitions for fixed point arithmetic types.
 */

#ifndef FIXED_POINT_TYPES_H
#define FIXED_POINT_TYPES_H

/** This header depends only upon the definition of
 * 	- int16_t
 * 	- int32_t
 * 	- INT16_MAX, INT16_MIN
 * 	- INT32_MAX, INT32_MIN
 * If you do not whish to (or cannot) use stdint.h, then you must provide the
 * above definitions
 */
#include <stdint.h>

/** ********************************************************************** *
 * @defgroup fxp_class Fixed point numbers
 * @{
 *
 * Unfortunately in C there is no way to forbid casting between integer types.
 * While this would be inocuous in the case of integers, fractionals are
 * different. For type casting to preserve the numerical value, the decimal
 * point sould be aligned when converting between types.
 * To prevent accidental implicit casts between fractional types we enclose them
 * in structs. The downside of this approach is that it is no longer possible to
 * use the '+' and '-' operators between fractionals, but in most cases you
 * should not do that and use a double-length accumulator instead.
 */

typedef int16_t mfrac_base;	/*!< Base arithmetic type for @ref mfrac.*/
typedef int16_t frac_base;	/*!< Base arithmetic type for @ref frac.*/
typedef int32_t dfrac_base;	/*!< Base arithmetic type for @ref dfrac.*/
typedef int32_t efrac_base;	/*!< Base arithmetic type for @ref efrac.*/

/**
 * 16 bit fractional number in Q8.8 format.
 *
 * Values of this type can represent numbers between -128 and (2**7 - 2**-8), or
 * approximately 127.996 with a precision of 2**-8 (about 0.0039 or 2.4 decimal
 * places).
 */
typedef struct {
	mfrac_base v;
} mfrac;

/**
 * 16 bit fractional number in Q1.15 format.
 *
 * Values of this type can represent numbers between -1 and (1 - 2**-15) with a
 * precision of 2**-15 (about 0.0000305 or 4.5 decimal places).
 */
typedef struct {
	frac_base v;
} frac;

/**
 * 32 bit fractional number in Q2.30 format.
 *
 * Values of this type can represent numbers between -2 and (2 - 2**-30) with a
 * precision of 2**-30 (9.31E-10 or 9 decimal places)
 *
 * A typical use of double fracs is for accumulators that store a multiply-sum
 * of fracs.
 */
typedef struct {
	dfrac_base v;
} dfrac;

/**
 * 32 bit fractional number in Q17.15 format.
 *
 * Values of this type can represent numbers between -65536 and (65536 - 2**-15)
 * with a precision of 2**-15 (about 0.0000305 or 4.5 decimal places).
 *
 * The main reason for defining efracs as Q17.15 is that casting fracs to
 * (int32_t) and adding them naturally results in a 17.15 value.
 */
typedef struct {
	efrac_base v;
} efrac;

/**
 * Make a dfrac from its base value.
 */
static inline frac _frac(frac_base v)
{
	frac r = {v};
	return r;
}

/**
 * Make a dfrac from its base value.
 */
static inline dfrac _dfrac(dfrac_base v)
{
	dfrac r = {v};
	return r;
}

/**
 * Make a efrac from its base value.
 */
static inline efrac _efrac(efrac_base v)
{
	efrac r = {v};
	return r;
}

#define MFRAC_BIT (16)	/*!< Size in bits of a FRAC. */
#define FRAC_BIT (16)	/*!< Size in bits of a FRAC. */
#define DFRAC_BIT (32)	/*!< Size in bits of a DFRAC. */
#define EFRAC_BIT (32)	/*!< Size in bits of an EFRAC. */


/**
 * @addtogroup fxp_width
 * Width based type names.
 *
 * Use these only when strictly necessary.
 * @{
 */

typedef frac frac_s16;	/*!< 16 bit signed fractional */
typedef dfrac frac_s32;	/*!< 32 bit signed fractional */

/** @}
 */

/**
 * @defgroup fxp_limits Limits
 * @{
 */

/**
 * @defgroup mfrac_limits MFRAC Limits
 * @{
 */

/**
 * mfrac representing 1.
 */
#define MFRAC_1_V (-(INT16_MIN >> 8))

/**
 * mfrac representing -1.
 */
#define MFRAC_minus1_V (INT16_MIN >> 8)

/** Maximum (most positive) value for a frac.
 * Represents the value 1**7 - 2**(-8) or "almost 128" */
#define MFRAC_MAX_V INT16_MAX
#define MFRAC_MAX_V INT16_MAX

/** Minimum (most negative) value for a frac.
 * Represents the value -128 */
#define MFRAC_MIN_V INT16_MIN

/** @}
 *
 * @defgroup frac_limits FRAC Limits
 * @{
 */

/**
 * Greatest value for the frac type.
 *
 * @bug	Rename this to "almost1"
 *
 * "Almost 1". Since fracs lie in the range [-1, 1), the number 1 does not have
 * a representation. FRAC_1 is the number closest to one, that is,
 * ```1 - 2**(-15)``` */
#define FRAC_1_V INT16_MAX

/** frac representing 0.5 */
#define FRAC_0_5_V (-(INT16_MIN>>1))

/** frac representing -1.
* This is the smallest value a frac can take*/
#define FRAC_minus1_V INT16_MIN

/** Maximum (most positive) value for a frac.
 * Represents the value 1 - 2**(-15) or "almost 1" */
#define FRAC_MAX_V INT16_MAX

/** Minimum (most negative) value for a frac.
 * Represents the value -1 */
#define FRAC_MIN_V INT16_MIN

/** @}
 *
 * @defgroup dfrac_limits DFRAC Limits
 * @{
 */

/** Unit value for the dfrac type.
 * It represents the value 1.*/
#define DFRAC_1_V (-(INT32_MIN>>1))

/** dfrac representing 0.5 */
#define DFRAC_0_5_V (-(INT32_MIN>>2))

/**
 * dfrac equivalent to FRAC_1
 *
 * This represents the same value as FRAC_1 (1 - 2**(-15)), but expressed as
 * a dfrac */
#define DFRAC_almost1_V (-(INT32_MIN>>1)-1)

/** dfrac for -1. */
#define DFRAC_minus1_V (INT32_MIN>>1)

/** Maximum (most positive) value for a dfrac.
 * Represents 2 - 2**(-31), or "almost 2" */
#define DFRAC_MAX_V INT32_MAX

/** Minimum (most negative) value for a dfrac.
 * Represents the value -2 */
#define DFRAC_MIN_V INT32_MIN


/** @}
 *
 * @defgroup efrac_limits EFRAC Limits.
 * @{
 */

#define EFRAC_minus1_V ((efrac_base)FRAC_minus1_V)
#define EFRAC_1_V (-EFRAC_minus1_V)

#define EFRAC_MAX_V INT32_MAX
#define EFRAC_MIN_V INT32_MIN

/** @}
 */


#ifdef __FRAMAC__

/* By putting the logic definitions in the same conditional compilation block
 * as the dummy function used to assert them we ensure that this block makes
 * it into FRAMA-C or else everything will fail.
 */

/*@
  // There seems to be some weird things going on relating to constants that
  // does not allow us to use them, so we have to hardcode stuff.
  // This is not all that bad, since fractional types have well-defined bit
  // widths, which are part of the API and will not change.

  logic ℝ frac_minus1v = -32768.0;	// 2**15
  logic ℝ dfrac_1v = 1073741824.0;      // 2**30
  logic ℝ efrac_1v = -frac_minus1v;     // 2**8
  logic ℝ mfrac_1v = 128.0;             // 2**15

  logic ℝ frac_minv = frac_minus1v;
  logic ℝ dfrac_minv = -1.0 * (1 << 31);
  logic ℝ efrac_minv = dfrac_minv;
  logic ℝ mfrac_minv = frac_minv;

  logic ℝ frac_maxv =  -frac_minv - 1;
  logic ℝ dfrac_maxv = -dfrac_minv - 1;
  logic ℝ efrac_maxv = -efrac_minv - 1;
  logic ℝ mfrac_maxv = -mfrac_minv - 1;

*/

#define _FXP_FRAMA_EXPOSE3(type, X, Y, Z) type \
	_c##X = X, _c##Y = Y, _c##Z = Z;

/* Check that the constansts are right. This is suboptimal as we could be
 * forgetting one, but it is what it is.
 * We don't need to verify everything, only the stuff we use in the logic
 * specifications, and if logic specifications are well written, we should
 * not use much more than the bounds.
 * */
/*@
  assigns \nothing;
 */
static void _fxp_frama_assertions()
{
   _FXP_FRAMA_EXPOSE3(frac_base, FRAC_MAX_V, FRAC_MIN_V, FRAC_minus1_V)

   _FXP_FRAMA_EXPOSE3(dfrac_base, DFRAC_MAX_V , DFRAC_MIN_V , DFRAC_1_V)

   _FXP_FRAMA_EXPOSE3(mfrac_base, MFRAC_MAX_V , MFRAC_MIN_V, MFRAC_1_V)

   _FXP_FRAMA_EXPOSE3(efrac_base, EFRAC_MAX_V, EFRAC_MIN_V, EFRAC_1_V)

   /*@ assert Fmin: frac_minv    ≡ _cFRAC_MIN_V;      */
   /*@ assert F1:   frac_minus1v ≡ _cFRAC_minus1_V;   */
   /*@ assert FMax: frac_maxv    ≡ _cFRAC_MAX_V;      */

   /*@ assert Dmin: dfrac_minv ≡ _cDFRAC_MIN_V;       */
   /*@ assert D1:   dfrac_1v   ≡ _cDFRAC_1_V;         */
   /*@ assert DMax: dfrac_maxv ≡ _cDFRAC_MAX_V;       */

   /*@ assert Emin: efrac_minv ≡ _cEFRAC_MIN_V;       */
   /*@ assert E1:   efrac_1v   ≡ _cEFRAC_1_V;         */
   /*@ assert EMax: efrac_maxv ≡ _cEFRAC_MAX_V;       */

   /*@ assert Mmin: mfrac_minv ≡ _cMFRAC_MIN_V;       */
   /*@ assert M1:   mfrac_1v   ≡ _cMFRAC_1_V;         */
   /*@ assert MMax: mfrac_maxv ≡ _cMFRAC_MAX_V;	*/
}

#endif /* __FRAMAC__ */

/* Logic declarations to convert fractionals to reals. */
/*@

  // TODO: add assertions to ensure these values are consistent with the
  // defines.
  logic ℝ frac_r(frac x) = x.v / -frac_minus1v;
  logic ℝ frac_r(dfrac x) = x.v / dfrac_1v;
  logic ℝ frac_r(mfrac x) = x.v / mfrac_1v;
  logic ℝ frac_r(efrac x) = x.v / efrac_1v;

 */

/**
 * @defgroup frac_const FRAC Constants
 * @{
 */

static const frac FZero = {0};
static const dfrac DFZero = {0};
static const efrac EFZero = {0};

/** @}
 *  @}
 *
 * @defgroup fxp_conv Conversions to and from double/float
 * @{
 */

/**
 * Convert a @ref frac to a floating point / native format.
 *
 * @param	real_type	The type of the floating point number (eg float
 * 				or double.
 * @param	n		The number to convert. Must be a frac.
 *
 * @return 	The number cast as a real_type.
 */
#define F_TO_REAL(real_type, n) (((real_type)(n.v))/(-(real_type)FRAC_minus1_V))

/**
 * Convert a floating point / native number to @ref frac.
 *
 * @param	f	A floating point number.
 *
 * @return		f represented as a frac.
 *
 * @bug		Does not round before converting.
 */
#define REAL_TO_F(f) (_frac(-f*FRAC_minus1_V))

/**
 * Convert a @ref dfrac to a floating point / native format.
 *
 * @see	F_TO_REAL
 */
#define DF_TO_REAL(real_type, n) (((real_type)(n.v))/((real_type)DFRAC_1_V))

/**
 * Convert a floating point / native number to @ref dfrac.
 *
 * @see	REAL_TO_F
 *
 * @bug		Does not round before converting.
 */
#define REAL_TO_DF(f) (_dfrac(f*DFRAC_1_V))

/**
 * Convert a @ref efrac to a floating point / native format.
 *
 * @see F_TO_REAL
 */
#define EF_TO_REAL(real_type, n) (((real_type)(n.v))/((real_type)EFRAC_1_V))

/**
 * Convert a floating point / native number to @ref efrac.
 *
 * @see	REAL_TO_F
 *
 * @bug		Does not round before converting.
 */
#define REAL_TO_EF(f) (_efrac(f*EFRAC_1_V))

#define F_TO_DOUBLE(n) F_TO_REAL(double, n) /*!< Convert a @ref frac to double.*/
#define DF_TO_DOUBLE(n) DF_TO_REAL(double, n)/*!< Convert a @ref dfrac to double.*/
#define EF_TO_DOUBLE(n) EF_TO_REAL(double, n)/*!< Convert a @ref efrac to double.*/

#define F_TO_FLOAT(n) F_TO_REAL(float, n) /*!< Convert a @ref frac to float.*/
#define DF_TO_FLOAT(n) DF_TO_REAL(float, n)/*!< Convert a @ref dfrac to float.*/
#define EF_TO_FLOAT(n) EF_TO_REAL(float, n)/*!< Convert a @ref efrac to float.*/

/** @}
 */

/** @}
 */

#endif /* FIXED_POINT_TYPES_H */
