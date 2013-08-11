/*
 * arith.c
 *
 * Aritmetica Fraccionaria (punto fijo)
 */

#include "arith.h"

#define TBL_SZ_BITS 4
#define TBL_SZ (1<<TBL_SZ_BITS)
#define TBL_MASK ((u16)(~((0xFFFF) >> (TBL_SZ_BITS+1))))
#define F_TO_TBL(x, tbl) ((tbl)[((x)&TBL_MASK) >> (16 - TBL_SZ_BITS-1)])
#define F_TO_INVTBL(x) F_TO_TBL(x, invtbl)
#define F_TO_STARTTBL(x) F_TO_TBL(x, starttbl)

frac fsqrt(frac b)
{
	const int iters = 2;
	static const int invtbl[TBL_SZ] = {
		32, 11, 6, 5, 4, 3, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1
	};
	static const int starttbl[TBL_SZ] = {
		5792, 10033, 12952, 15325, 17377, 19211, 20885, 22434, 23883,
		25249, 26544, 27780, 28962, 30098, 31193, 32251
	};
	frac x = F_TO_STARTTBL(b);
	int i;

	for (i = 0; i < iters; i++) {
		x = (b - fmul(x,x))*F_TO_INVTBL(x)/2 + x;
	}

	return x;
}
