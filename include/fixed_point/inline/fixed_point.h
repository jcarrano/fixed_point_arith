/**
 * @file
 * @author	Juan I Carrano
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
 * Fractional number routines.
 *
 * About Fractional multiplication routines:
 * This is the code that you should modify if you want to maximise performance
 * for your particular machine; for example, if you have a hardware multiplier.
 * The rest of the code is generic.
 */

/* Some compilers, such as GCC, support the "extern inline" definition which
 * allows the inlining version of functions to be defined in the header. This
 * leaves to the decision of where to inline to the compiler (or to the user by
 * means of compiler switches). For those with less advanced compilers, they
 * have to  choose: either have the routines in a different module and do
 * zero inlining or include them in ALL source files with the "static" keyword
 * so one may have inlining and optimizations.
 */

#include <stdbool.h>
#include "../fixed_point.h"

/**
 * @addtogroup fxp_class
 * @{
 *
 * @defgroup fxp_cmp	Comparison functions
 * @{
 */

/**
 * Greater-than comparison - single precision.
 *
 * @param	a, b	Operands
 *
 * @return 	True if a > b
 */
FXP_SCMP(f_gt, >)

/**
 * Greater or equal comparison - single precision.
 *
 * @param	a, b	Operands
 *
 * @return 	True if a >= b
 */
FXP_SCMP(f_ge, >=)

/**
 * Less-than comparison - single precision.
 *
 * @param	a, b	Operands
 *
 * @return 	True if a < b
 */
FXP_SCMP(f_lt, <)

/**
 * Less or equal comparison - single precision.
 *
 * @param	a, b	Operands
 *
 * @return 	True if a <= b
 */
FXP_SCMP(f_le, <=)

/**
 * Equality comparison - single precision.
 *
 * @param	a, b	Operands
 *
 * @return 	True if a == b
 */
FXP_SCMP(f_eq, ==)

/**
 * Greater-than comparison - double precision.
 *
 * @param	a, b	Operands
 *
 * @return 	True if a > b
 */
FXP_DCMP(df_gt, >)

/**
 * Greater or equal comparison - double precision.
 *
 * @param	a, b	Operands
 *
 * @return 	True if a >= b
 */
FXP_DCMP(df_ge, >=)

/**
 * Less-than comparison - double precision.
 *
 * @param	a, b	Operands
 *
 * @return 	True if a < b
 */
FXP_DCMP(df_lt, <)

/**
 * Less or equal comparison - double precision.
 *
 * @param	a, b	Operands
 *
 * @return 	True if a <= b
 */
FXP_DCMP(df_le, <=)

/**
 * Equality comparison - double precision.
 *
 * @param	a, b	Operands
 *
 * @return 	True if a == b
 */
FXP_DCMP(df_eq, ==)

/** @}
 *
 * @defgroup fxp_arith	Fixed point arithmetic
 * @{
 */

/** Add two single precision fractional numbers - may overflow. */
FXP_OP3(f_add, frac, +)

/** Substract two single precision fractional numbers - may overflow. */
FXP_OP3(f_sub, frac, -)

/** Add two double precision fractional numbers - may overflow. */
FXP_OP3(df_add, dfrac, +)

/** Substract two double precision fractional numbers - may overflow. */
FXP_OP3(df_sub, dfrac, -)

/** Add two extended precision fractional numbers - may overflow. */
FXP_OP3(ef_add, efrac, +)

/** Substract two extended precision fractional numbers - may overflow. */
FXP_OP3(ef_sub, efrac, -)

/** Add a single precision fractional to an extended precision fractional. */
FXP_DECLARATION(efrac ef_f_add(efrac a, frac b))
{
	a.v += b.v
	return a;
}

/** Negate single precision fractional */
FXP_DECLARATION(frac f_neg(frac a))
{
	frac r = {-a.v};
	return r;
}

/** Negate double precision fractional */
FXP_DECLARATION(dfrac df_neg(dfrac a))
{
	dfrac r = {-a.v};
	return r;
}

/** Negate extended precision fractional */
FXP_DECLARATION(efrac ef_neg(efrac a))
{
	efrac r = {-a.v};
	return r;
}

/**
 * Multiply single precision, yield single precision.
 *
 * 1.15 x 1.15 => 1.15.
 *
 * @param	a,b	Operands
 * @return		a*b
 *
 * @bug		Does not perform convergent rounding.
 */
FXP_DECLARATION(frac f_mul(frac a, frac b))
{
	frac r = {((((dfrac_base)a.v) * b.v) << 1) >> FRAC_BIT};
	return r;
}

/**
 * Multiply single precision, yield double precision
 *
 * 1.15 x 1.15 => 2.30
 *
 * @param	a,b	Operands
 * @return		a*b
 */
FXP_DECLARATION(dfrac f_mul_df(frac a, frac b))
{
	dfrac r = {(((dfrac_base)a.v) * b.v)};
	return r;
}

/**
 * Multiply single precision by mixed fractional, yield extended precision,
 *
 * 1.15 x 8.8 => 17.15
 *
 * @param	a,b	Operands
 * @return		a*b
 */
FXP_DECLARATION(efrac f_mf_mul_ef(frac a, mfrac b))
{
	efrac r = {(((efrac_base)a.v) * b.v)>>8};
	return r;
}

/**
 * Multiply single precision by integer, yield single precision.
 *
 * 1.15 x 16.0 => 1.15.
 *
 * @param	a	Operands, fractional.
 * @param	b	Operand, integer.
 * @return		a*b
 */
FXP_DECLARATION(frac f_imul(frac a, int16_t b))
{
	frac r = { a.v * b };
	return r;
}

/**
 * Multiply single precision by integer, yield extended precision.
 *
 * 1.15 x 16.0 => 17.15.
 *
 * @param	a	Operands, fractional.
 * @param	b	Operand, integer.
 * @return		a*b
 */
FXP_DECLARATION(efrac f_imul_ef(frac a, int16_t b))
{
	efrac r = { ((efrac_base)a.v) * b };
	return r;
}

/**
 * Multiply double precision by integer, yield double precision.
 *
 * 2.30 x 16.0 => 2.30.
 *
 * @param	a	Operands, fractional.
 * @param	b	Operand, integer.
 * @return		a*b
 */
FXP_DECLARATION(dfrac df_imul(dfrac a, int16_t b))
{
	dfrac r = { a.v * b };
	return r;
}

/**
 * Multiply extended precision by integer, yield extended precision.
 *
 * 17.15 x 16.0 => 17.15.
 *
 * @param	a	Operands, fractional.
 * @param	b	Operand, integer.
 * @return		a*b
 */
FXP_DECLARATION(efrac ef_imul(efrac a, int16_t b))
{
	efrac r = { a.v * b };
	return r;
}

/**
 * Divide single precision by integer, yield single precision.
 *
 * 1.15 / 16.0 => 1.15.
 *
 * @param	a	Operands, fractional.
 * @param	b	Operand, integer.
 * @return		a*b
 */
FXP_DECLARATION(frac f_idiv(frac a, int16_t b))
{
	frac r = { a.v / b };
	return r;
}

/**
 * Divide double precision by integer, yield double precision.
 *
 * 2.30 / 16.0 => 2.30.
 *
 * @param	a	Operands, fractional.
 * @param	b	Operand, integer.
 * @return		a/b
 */
FXP_DECLARATION(dfrac df_idiv(dfrac a, int16_t b))
{
	dfrac r = { a.v / b };
	return r;
}

/**
 * Divide extended precision by integer, yield extended precision.
 *
 * 17.15 / 16.0 => 17.15.
 *
 * @param	a	Operands, fractional.
 * @param	b	Operand, integer.
 * @return		a/b
 */
FXP_DECLARATION(efrac ef_idiv(efrac a, int16_t b))
{
	efrac r = { a.v / b };
	return r;
}

/**
 * Arithmetic shift left a double precision fractional.
 *
 *
 * @param	a	Operands, fractional.
 * @param	b	Operand, integer.
 * @return		a << b
 */
FXP_DECLARATION(dfrac df_shiftl(dfrac a, int16_t b))
{
	dfrac r = { a.v << b };
	return r;
}

/**
 * Arithmetic shift right a double precision fractional.
 *
 *
 * @param	a	Operands, fractional.
 * @param	b	Operand, integer.
 * @return		a >> b
 */
FXP_DECLARATION(dfrac df_shiftr(dfrac a, int16_t b))
{
	dfrac r = { a.v >> b };
	return r;
}

/**
 * Truncate to single precision.
 *
 * Removes (truncates) excess fractional bits from a double precision number
 * and saturates the result to fit in tha range of fracs.
 *
 * @param	x	Double precision fractional
 * @return		x as a single precision fractional
 *
 * @bug		Does not perform convergent rounding
 */
FXP_DECLARATION(frac df_to_f(dfrac x))
{ /* 2.30 -> 1.15 */
	frac r;

	if (x.v >= DFRAC_1_V)
		r.v = FRAC_1_V;
	else if ( x.v < DFRAC_minus1_V)
		r.v = FRAC_minus1_V;
	else
		r.v = (x.v << 1) >> FRAC_BIT;

	return r;
}

/**
 * Extend a single precision number to double precision.
 *
 * @param	x	Single precision fractional
 * @return		x as a double precision fractional
 */
FXP_DECLARATION(dfrac f_to_df(frac x))
{ /* 1.15 -> 2.30 */
	dfrac r = { ((dfrac_base)x.v)<<(FRAC_BIT - 1) };
	return r;
}

/**
 * Extend a single precision fractional to an extended-fractional
 */
FXP_DECLARATION(efrac f_to_ef(frac x))
{
	efrac r = {((efrac_base)x.v)};
	return r;
}

/**
 * Divide a frac by an efrac and return an efrac.
 */
FXP_DECLARATION(efrac f_ef_div(frac dividend, efrac divisor))
{
	/* When dividing, the implicit divisors (2**(FRAC_BIT-1)) cancel out,
	 * and we get the ratio as an integer. To get a efrac we must multiply
	 * the divident by 2**(FRAC_BIT-1) BEFORE taking the quotient */
	efrac_base new_dividend = f_to_ef(dividend).v << (FRAC_BIT - 1);
	efrac r = {new_dividend/divisor.v};

	return r;
}

/**
 * Saturate an extended fractional to yield a fractional
 *
 * Note that the precision of efracs and fracs is the same.
 */
FXP_DECLARATION(frac ef_to_f(efrac x))
{
	frac r = { (x.v > FRAC_minus1_V)?
			((x.v < FRAC_1_V)? x.v : FRAC_1_V)
			: FRAC_minus1_V
		};
	return r;
}

/**
 * Clip a number to lie between -limit and limit.
 *
 * @param	x	number to be clipped
 * @param	limit	limit for clipping. Must be positive and strictly less
 * 			than one.
 *
 * @return		min(max(x, -limit), limit)
 */
FXP_DECLARATION(frac f_clip (frac x, frac limit))
{

	frac r = {(x.v > -limit.v)? ((x.v < limit.v)? x.v : limit.v) : -limit.v};

	return r;
}

/**
 * Add with saturation.
 *
 * @return	If the addition would result in an overflow, return DFRAC_MAX
 * 		or DFRAC_MIN. Else, return the sum.
 */
FXP_DECLARATION(dfrac df_addsat(dfrac x1, dfrac x2))
{
	dfrac_base result = x1.v + x2.v;
	dfrac r;

	if (x1.v > 0 && x2.v > 0)
		r.v = ((result < x1.v) ? DFRAC_MAX_V : result);
	else if (x1.v < 0 && x2.v < 0)
		r.v = ((result > x1.v) ? DFRAC_MIN_V : result);
	else
		r.v = result;

	return r;
}

/**
 * Multiply-accumulate with saturation. Use a dfrac as accumulator.
 *
 * Performs z + x*y.
 *
 * @param	x	Factor
 * @param	y	Factor
 * @param	z	Sumand / Accumulator
 *
 * @return		saturateds(z + x*y)
 */
FXP_DECLARATION(dfrac f_macs_df (frac x, frac y, dfrac z))
{
	return df_addsat(z, f_mul_df(x,y));
}

/** @}
 * @}
 */
