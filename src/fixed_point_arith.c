/*
 * fixed_point_arith.c
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

#include "fixed_point_types.h"

#define SIGN(a) (((a) >= 0)? 1 : -1)

/* ********************************************************************** *
 * Fractional numbers
 * ********************************************************************** */

/* Fractional multiplication routines
 * This is the code that you should modify if you want to maximise performance
 * for your particular machine; for example, if you have a hardware multiplier.
 * The rest of the code is generic.
 */

/* 1.15 x 1.15 => 1.15 */
static frac fmul(frac a, frac b)
{
	return ((((dfrac)a) * b) << 1) >> FRAC_BIT;
}

/* 1.15 x 1.15 => 2.30 */
static dfrac fmul2(frac a, frac b)
{
	return (((dfrac)a) * b);
}

static frac dtrunc(dfrac x)
{ /* 2.30 -> 1.15 */
	if (x >= DFRAC_1)
		return FRAC_1;
	else if ( x < DFRAC_minus1)
		return FRAC_minus1;
	else
		return (x << 1) >> FRAC_BIT;
}

static dfrac fexpand(frac x)
{ /* 1.15 -> 2.30 */
	return ((dfrac)x)<<(FRAC_BIT - 1);
}

#define f_to_extended(x) ((efrac)(x))

static efrac efdiv(frac dividend, efrac divisor)
{
	efrac result = f_to_extended(dividend);
	result << (FRAC_BIT - 1);

	return result/divisor;

}

static frac efclip(efrac x)
{
	return (x > FRAC_minus1)? ((x < FRAC_1)? x : FRAC_1) : FRAC_minus1;
}

static frac frac_sat (frac x, frac sat)
{

	return  (x > -sat)? ((x < sat)? x : sat) : -sat;
}


/* **** Vectors in R^3 ****/

typedef struct {
	frac x,y,z;
} vec3;

typedef struct {
	dfrac x,y,z;
} dvec3;

typedef dvec3 evec3;

#if (FRAC_BIT == 16)
typedef vec3 s16Vec3;
#endif

#if (DFRAC_BIT == 32)
typedef dvec3 s32Vec3;
#endif

#define VEC0 {0,0,0}

enum {AXIS_X, AXIS_Y, AXIS_Z};

static void vec_AddInPlace(s16Vec3* This, s16Vec3* b)
{
	This->x += b->x;
	This->y += b->y;
	This->z += b->z;

	return;
}

static void vec_SubInPlace(s16Vec3* This, s16Vec3* b)
{
	This->x -= b->x;
	This->y -= b->y;
	This->z -= b->z;

	return;
}


static void dVec_dAddInPlace(s32Vec3* This, s32Vec3* b)
{
	This->x += b->x;
	This->y += b->y;
	This->z += b->z;

	return;
}

static void dVec_dSubInPlace(s32Vec3* This, s32Vec3* b)
{
	This->x -= b->x;
	This->y -= b->y;
	This->z -= b->z;

	return;
}

static void dVec_AddInPlace(s32Vec3* This, s16Vec3* b)
{
	This->x += b->x;
	This->y += b->y;
	This->z += b->z;

	return;
}

static void vec_MulInPlace(s16Vec3* This, s16 b)
{
	This->x *= b;
	This->y *= b;
	This->z *= b;

	return;
}


static void dVec_MulInPlace(s32Vec3* This, s16 b)
{
	This->x *= b;
	This->y *= b;
	This->z *= b;

	return;
}


static void vec_DivInPlace(s16Vec3* This, s16 b)
{
	This->x /= b;
	This->y /= b;
	This->z /= b;

	return;
}


static void dVec_DivInPlace(s32Vec3* This, s16 b)
{
	This->x /= b;
	This->y /= b;
	This->z /= b;

	return;
}

static dvec3 dvec_Add(dvec3 a, dvec3 b)
{
	dvec3 c = a;

	dVec_dAddInPlace(&c, &b);

	return c;
}

static dvec3 dvec_Sub(dvec3 a, dvec3 b)
{
	dvec3 c = a;

	dVec_dSubInPlace(&c, &b);

	return c;
}

static dvec3 dvec_Div(dvec3 a, s16 b)
{
	dvec3 c = a;

	dVec_DivInPlace(&c, b);

	return c;
}

static vec3 vec_Add(vec3 a, vec3 b)
{
	vec3 c = a;

	vec_AddInPlace(&c, &b);

	return c;
}

static vec3 vec_Sub(vec3 a, vec3 b)
{
	vec3 c = a;

	vec_SubInPlace(&c, &b);

	return c;
}

static vec3 vec_Div(vec3 a, int f)
{
	vec3 c = a;

	vec_DivInPlace(&c,f);

	return c;
}

static vec3 vec_Mul(vec3 a, int f)
{
	vec3 c = a;

	vec_MulInPlace(&c, f);

	return c;
}

static evec3 vefdiv(vec3 a, efrac divisor)
{
	evec3 r;

	r.x = efdiv(a.x, divisor);
	r.y = efdiv(a.y, divisor);
	r.z = efdiv(a.x, divisor);

	return r;
}

static vec3 vfmul(vec3 a, frac f)
{
	vec3 r;

	r.x = fmul(a.x, f);
	r.y = fmul(a.y, f);
	r.z = fmul(a.z, f);

	return r;
}

static dvec3 vfmul2(vec3 a, frac f)
{
	dvec3 r;

	r.x = fmul2(a.x, f);
	r.y = fmul2(a.y, f);
	r.z = fmul2(a.z, f);

	return r;
}

static dvec3 dvec_lShift(dvec3 a, u8 shift)
{
	a.x <<= shift;
	a.y <<= shift;
	a.z <<= shift;

	return a;
}


static dvec3 dvec_rShift(dvec3 a, u8 shift)
{
	a.x >>= shift;
	a.y >>= shift;
	a.z >>= shift;

	return a;
}

static evec3 vimul2(vec3 v, int a)
{
	evec3 r;

	r.x = v.x*a;
	r.y = v.y*a;
	r.z = v.z*a;

	return r;
}

static evec3 evimul(evec3 v, int a)
{
	evec3 r;

	r.x = v.x*a;
	r.y = v.y*a;
	r.z = v.z*a;

	return r;
}

static vec3 evclip(evec3 v)
{
	vec3 r;

	r.x = efclip(v.x);
	r.y = efclip(v.y);
	r.z = efclip(v.z);

	return r;
}

static evec3 v_to_extended(vec3 v)
{
	evec3 r;

	r.x = v.x;
	r.y = v.y;
	r.z = v.z;

	return r;
}

static dvec3 vexpand(vec3 a)
{
	dvec3 r;

	r.x=fexpand(a.x);
	r.y=fexpand(a.y);
	r.z=fexpand(a.z);

	return r;
}


static dfrac dfrac_SumSat2(dfrac x1, dfrac x2)
{
	dfrac result = x1+x2;
	if (x1 > 0 && x2 > 0)
		return ((result < x1) ? DFRAC_MAX : result);
	else if (x1 < 0 && x2 < 0)
		return ((result > x1) ? DFRAC_MIN : result);
	else
		return result;
}


static dvec3 dvsumsat(dvec3 a, dvec3 b)
{
	a.x = dfrac_SumSat2(a.x, b.x);
	a.y = dfrac_SumSat2(a.y, b.y);
	a.z = dfrac_SumSat2(a.z, b.z);

	return a;
}



static vec3 vsat (vec3 a, frac sat)
{
	a.x = frac_sat (a.x, sat);
	a.y = frac_sat (a.y, sat);
	a.z = frac_sat (a.z, sat);

	return a;
}

static vec3 vec_clip_d(dvec3 a)
{
	vec3 r;
#define _DFRAC_CLIP(k) (((k) >= DFRAC_minus1)? (((k) < DFRAC_1)? dtrunc(k): FRAC_1) : FRAC_minus1)
	r.x = _DFRAC_CLIP(a.x);
	r.y = _DFRAC_CLIP(a.y);
	r.z = _DFRAC_CLIP(a.z);

	return r;
}

#define vdiv vec_Div
#define vsum vec_Add
#define vsub vec_Sub
#define vmul vec_Mul
#define dvsum dvec_Add
#define dvsub dvec_Sub
#define dvdiv dvec_Div

/* **** Quaternions ****/

typedef struct {
	frac r;
	vec3 v;
} quat;

typedef struct {
	dfrac r;
	dvec3 v;
} dquat;

#define UNIT_Q {FRAC_1, {0, 0, 0}}
#define UNIT_DQ {DFRAC_1, {0, 0, 0}}

static  quat qtrunc(dquat q)
{
	quat s;
#define _QTR(e) s.e = dtrunc(q.e)

	_QTR(r);
	_QTR(v.x);
	_QTR(v.y);
	_QTR(v.z);

	return s;
}

static  frac q_normerror(quat q)
{ /* Pseudo-error de la norma:
   *	calcula una aproximación a (1 - norm(q))
   *	La aproxiimación está en decir que sqrt(x) = 0.5(x + 1)
   */
	return FRAC_0_5 - dtrunc((fmul2(q.r, q.r) + fmul2(q.v.x, q.v.x) +
			fmul2(q.v.y, q.v.y) + fmul2(q.v.z, q.v.z))/2);
}

static  dquat qscale2(quat q, frac f)
{
	dquat s;

	s.r = fmul2(q.r, f);
	s.v.x = fmul2(q.v.x, f);
	s.v.y = fmul2(q.v.y, f);
	s.v.z = fmul2(q.v.z, f);

	return s;
}

static  quat qscale(quat q, frac f)
{
	quat s;

	s.r = fmul(q.r, f);
	s.v.x = fmul(q.v.x, f);
	s.v.y = fmul(q.v.y, f);
	s.v.z = fmul(q.v.z, f);

	return s;
}

static quat qconj(quat q)
{
	quat p;

	p.r = q.r;
	p.v.x = -q.v.x;
	p.v.y = -q.v.y;
	p.v.z = -q.v.z;

	return p;
}

static  quat qmul(quat q, quat p)
{
	quat s;

	s.r = (fmul(q.r,p.r)-fmul(q.v.x,p.v.x)-fmul(q.v.y,p.v.y)-fmul(q.v.z,p.v.z));
	s.v.x = (fmul(p.r,q.v.x)+fmul(p.v.x,q.r)-fmul(p.v.y,q.v.z)+fmul(p.v.z,q.v.y));
	s.v.y = (fmul(p.r,q.v.y)+fmul(p.v.x,q.v.z)+fmul(p.v.y,q.r)-fmul(p.v.z,q.v.x));
	s.v.z = (fmul(p.r,q.v.z)-fmul(p.v.x,q.v.y)+fmul(p.v.y,q.v.x)+fmul(p.v.z,q.r));

	return s;
}

static  dquat qmul2(quat q, quat p, int f)
{
	dquat s;

	s.r = (fmul2(q.r,p.r)-fmul2(q.v.x,p.v.x)-fmul2(q.v.y,p.v.y)-fmul2(q.v.z,p.v.z))/f;
	s.v.x = (fmul2(p.r,q.v.x)+fmul2(p.v.x,q.r)-fmul2(p.v.y,q.v.z)+fmul2(p.v.z,q.v.y))/f;
	s.v.y = (fmul2(p.r,q.v.y)+fmul2(p.v.x,q.v.z)+fmul2(p.v.y,q.r)-fmul2(p.v.z,q.v.x))/f;
	s.v.z = (fmul2(p.r,q.v.z)-fmul2(p.v.x,q.v.y)+fmul2(p.v.y,q.v.x)+fmul2(p.v.z,q.r))/f;

	return s;
}

#define _QSUM(e) s.e = q.e + p.e
static  dquat dqsum(dquat q, dquat p)
{
	dquat s;

	_QSUM(r);
	_QSUM(v.x);
	_QSUM(v.y);
	_QSUM(v.z);

	return s;
}

static  quat qsum(quat q, quat p)
{
	quat s;

	_QSUM(r);
	_QSUM(v.x);
	_QSUM(v.y);
	_QSUM(v.z);

	return s;
}

static vec3 qrot(quat q, vec3 v)
{
	quat _v;

	_v.r = 0;
	_v.v = v;

	return qmul(q, qmul(_v, qconj(q))).v;
}

static quat qrenorm(quat q)
{
	frac err;
	quat correction;

	err = q_normerror(q);
	correction = qscale(q, err);
	return qsum(q, correction);
}

static dquat dqrenorm(dquat q)
{
	frac err;
	dquat correction;
	quat qh = qtrunc(q);

	err = q_normerror(qh);
	correction = qscale2(qh, err);
	return dqsum(q, correction);
}

static quat qdecompose(quat q, u8 axis)
{
	frac norm_err;
	frac the_axis;
	quat ret = {0, {0,0,0}};

	switch (axis) {
	case AXIS_X:
		the_axis = q.v.x;
		break;
	case AXIS_Y:
		the_axis = q.v.y;
		break;
	case AXIS_Z:
		the_axis = q.v.z;
		break;
	}

	norm_err = FRAC_0_5 - dtrunc(fmul2(q.r, q.r) +
						fmul2(the_axis,the_axis))/2;
	ret.r = q.r + fmul(norm_err, q.r);
	the_axis = the_axis + fmul(norm_err, the_axis);

	switch (axis) {
	case AXIS_X:
		ret.v.x = the_axis;
		break;
	case AXIS_Y:
		ret.v.y = the_axis;
		break;
	case AXIS_Z:
		ret.v.z = the_axis;
		break;
	}

	return ret;
}

/* Estas funciones dan el giro que hay que realizar para ir de
 * 'pos' hacia 'setp', en el marco de referencia de 'pos'
 */

static vec3 qerror(quat setp, quat pos)
{
	quat c = qmul(qconj(pos), setp);

	return vfmul(c.v, c.r);
}

static vec3 qerror2(quat setp, quat pos)
{
	quat c = qmul(qconj(pos), setp);

	return vmul(c.v, SIGN(c.r));
}

#endif /* _ARITH_H_ */
