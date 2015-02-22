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
 * Vector inline definitions
 */

#include "../vector.h"
#include "../fixed_point.h"

/**
 * @addtogroup fxp_vec
 * @{
 */

/**
 * Add two single precision vectors.
 */
MAKE_VEC_VEC_F(v_add, vec3, f_add)

/**
 * Substract two single precision vectors.
 */
MAKE_VEC_VEC_F(v_sub, vec3, f_sub)

/**
 * Add two double precision vectors.
 */
MAKE_VEC_VEC_F(dv_add, dvec3, df_add)

/**
 * Sum two double precision vectors with saturation. Yield double precision.
 */
MAKE_VEC_VEC_F(dv_addsat, dvec3, df_addsat)

/**
 * Substract two double precision vectors.
 */
MAKE_VEC_VEC_F(dv_sub, dvec3, df_sub)

/**
 * Element-by-element mutiplication of a single precision vector by mixed
 * precision, yieding extended precision.
 */
MAKE_VEC_VEC_F3(v_mvmul_ev, evec3, vec3, mvec3, f_mf_mul_ef)

/**
 * Multiply vector by integer having the same width as frac.
 */
MAKE_VEC_SCALAR_F(v_imul, vec3, int16_t, f_imul)

/**
 * Multiply double precision vector by integer having the same width as frac.
 */
MAKE_VEC_SCALAR_F(dv_imul, dvec3, int16_t, df_imul)

/**
 * Multiply extended precision vector by integer.
 */
MAKE_VEC_SCALAR_F(ev_imul, evec3, int, ef_imul)

/**
 * Divide vector by integer having the same width as frac.
 */
MAKE_VEC_SCALAR_F(v_idiv, vec3, int16_t, f_idiv)

/**
 * Divide double precision vector by integer having the same width as frac.
 */
MAKE_VEC_SCALAR_F(dv_idiv, dvec3, int16_t, df_idiv)

/**
 * Arithmetic shift components left.
 */
MAKE_VEC_SCALAR_F(dv_shiftl, dvec3, int8_t, df_shiftl)

/**
 * Arithmetic shift components right.
 */
MAKE_VEC_SCALAR_F(dv_shiftr, dvec3, int8_t, df_shiftr)

/**
 * Clip components between -b and b.
 */
MAKE_VEC_SCALAR_F(v_clip, vec3, frac, f_clip)

/**
 * Multiply single precicion vector by integer, yield extended precision vector.
 */
MAKE_VEC_SCALAR_F2(v_imul_ev, evec3, vec3, int, f_imul_ef)

/**
 * Divide a vector by an extended frac, yield an extended vector.
 */
MAKE_VEC_SCALAR_F2(v_efdiv_ev, evec3, vec3, efrac, f_ef_div)

/**
 * Multiply a single precision vector by a fractional, yield single precision.
 */
MAKE_VEC_SCALAR_F2(v_fmul, vec3, vec3, frac, f_mul)

/**
 * Multiply a single precision vector by a fractional, yield double precision.
 */
MAKE_VEC_SCALAR_F2(v_fmul_dv, dvec3, vec3, frac, f_mul_df)

/**
 * Multiply a single precision vector by a mixed fractional, yield extended precision.
 */
MAKE_VEC_SCALAR_F2(v_mfmul_ev, evec3, vec3, mfrac, f_mf_mul_ef)

/**
 * Clip an extended precision vector to the range of a single precision.
 */
MAKE_VEC_ELEM_F(ev_to_v, vec3, evec3, ef_to_f)

/**
 * Extend a single precision vector.
 */
MAKE_VEC_ELEM_F(v_to_ev, evec3, vec3, f_to_ef)

/**
 * Convert single precision vector to double precision.
 */
MAKE_VEC_ELEM_F(v_to_dv, dvec3, vec3, f_to_df)

/**
 * Convert double precision vector to single precision, by clipping and
 * truncating.
 *
 * @bug		Does not perform convergent rounding.
 */
MAKE_VEC_ELEM_F(dv_to_v, vec3, dvec3, df_to_f)

/** @}
 */
