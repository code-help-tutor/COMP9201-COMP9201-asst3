WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
/*-
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * From:
 * 	@(#)ashrdi3.c	8.1 (Berkeley) 6/4/93
 *	NetBSD: ashrdi3.c,v 1.1 2005/12/20 19:28:51 christos Exp
 */

#include "longlong.h"

/*
 * Shift a (signed) long long value right (arithmetic shift right).
 */
long long
__ashrdi3(long long a, unsigned int shift)
{
	union uu aa;

	if (shift == 0)
		return(a);
	aa.ll = a;
	if (shift >= INT_BITS) {
		int s;

		/*
		 * Smear bits rightward using the machine's right-shift
		 * method, whether that is sign extension or zero fill,
		 * to get the `sign word' s.  Note that shifting by
		 * INT_BITS is undefined, so we shift (INT_BITS-1),
		 * then 1 more, to get our answer.
		 */
		/* LINTED inherits machine dependency */
		s = (aa.si[H] >> (INT_BITS - 1)) >> 1;
		/* LINTED inherits machine dependency*/
		aa.ui[L] = aa.si[H] >> (shift - INT_BITS);
		aa.ui[H] = s;
	} else {
		aa.ui[L] = (aa.ui[L] >> shift) |
		    (aa.ui[H] << (INT_BITS - shift));
		/* LINTED inherits machine dependency */
		aa.si[H] >>= shift;
	}
	return (aa.ll);
}
