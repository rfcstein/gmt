/*--------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 1991-2012 by P. Wessel, W. H. F. Smith, R. Scharroo, and J. Luis
 *	See LICENSE.TXT file for copying and redistribution conditions.
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; version 2 or any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	Contact info: gmt.soest.hawaii.edu
 *--------------------------------------------------------------------*/
/*
 * Machine-dependent macros for generation and testing of NaNs. 
 *
 * These routines use the IEEE definition of Silent NaNs to set NaNs and
 * use the avialable isnan* routines to test NaNs whenever available.
 *
 * Notes:
 * 1) If your system has no IEEE support, add -DNO_IEEE to CFLAGS
 *    We will then use the max double/float values to signify NaNs.
 * 2) For the time being, we kept a seperate setting of NaNs on WIN32 that
 *    is known to work. Likely the general definition will work as well.
 * 3) The bit pattern for NaN is all 1's. This is officially the definition
 *    of a Silent Negative NaN. It is invariant to byte swapping, so should
 *    work on all platforms, even WIN32.
 *
 * Author:	Remko Scharroo
 * Date:	1-JAN-2010
 * Ver:		5 API
 */

#ifndef _GMT_NAN_H
#define _GMT_NAN_H

#if defined(NO_IEEE)
#define GMT_make_fnan(x) (x = FLT_MAX)
#define GMT_make_dnan(x) (x = DBL_MAX)
#elif defined(WIN32)
#define GMT_make_fnan(x) { void *v; unsigned int *i; v = &x; i = (unsigned int *)v; *i = 0x7fffffff;}
#define GMT_make_dnan(x) { void *v; unsigned int *i; v = &x; i = (unsigned int *)v; i[0] = 0xffffffff; i[1] = 0x7fffffff;}
#else
#define GMT_make_fnan(x) { void *v; unsigned int *i; v = &x; i = (unsigned int *)v; *i = 0xffffffff;}
#define GMT_make_dnan(x) { void *v; unsigned int *i; v = &x; i = (unsigned int *)v; i[0] = 0xffffffff; i[1] = 0xffffffff;}
#endif

#if defined(NO_IEEE)
#define GMT_is_fnan(x) ((x) == FLT_MAX)
#elif defined(isnanf)
#define GMT_is_fnan(x) isnanf((x))
#elif defined(isnan)
#define GMT_is_fnan(x) isnan((double)(x))
#elif defined(HAVE_ISNANF)
#define GMT_is_fnan(x) isnanf(x)
extern int isnanf(float x);
#elif defined(HAVE_ISNAN)
#define GMT_is_fnan(x) isnan((double)(x))
#elif defined(HAVE_ISNAND)
#define GMT_is_fnan(x) isnand((double)(x))
#else
#define GMT_is_fnan(x) ((x) != (x))
#endif

#if defined(NO_IEEE)
#define GMT_is_dnan(x) ((x) == DBL_MAX)
#elif defined(isnand)
#define GMT_is_dnan(x) isnand((x))
#elif defined(isnan)
#define GMT_is_dnan(x) isnan((x))
#elif defined(HAVE_ISNAND)
#define GMT_is_dnan(x) isnand(x)
extern int isnand(double x);
#elif defined(HAVE_ISNAN)
#define GMT_is_dnan(x) isnan(x)
extern int isnan(double x);
#else
#define GMT_is_dnan(x) ((x) != (x))
#endif

#endif /* _GMT_NAN_H */
