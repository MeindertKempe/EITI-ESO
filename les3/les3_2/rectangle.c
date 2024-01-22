/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2024 Meindert Kempe
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *     3. Neither the name of the copyright holder nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "rectangle.h"
#include "macro.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef __has_builtin
#	if __has_builtin(__builtin_smul_overflow)
#		define smul_overflow(a, b, r) __builtin_smul_overflow(a, b, r)
#	endif
#endif
#ifndef smul_overflow
#	define smul_overflow(a, b, r) smul_overflow_div(a, b, r)
#endif

UNUSED static bool smul_overflow_div(int a, int b, int *res) {
	*res = a * b;
	if (a != 0 && *res / a != b) return true;
	return false;
}

int surface(struct rectangle rect) {
	int surface;
	if (smul_overflow(rect.length, rect.width, &surface)) {
		// fprintf(stderr, "Overflow on surface calculation.\n");
		return INT_MAX;
	}
	return surface;
}

void print_rects(const struct rectangle *rects, size_t count) {
	for (size_t i = 0; i < count; ++i) {
		printf("rectangle %zu, length: %d, width: %d, surface: %d\n", i,
		       rects[i].length, rects[i].width, surface(rects[i]));
	}
}

int comp_rect(const void *rect1, const void *rect2) {
	int surf1 = surface(*(const struct rectangle *)rect1);
	int surf2 = surface(*(const struct rectangle *)rect2);
	if (surf1 > surf2) return 1;
	if (surf1 < surf2) return -1;
	return 0;
}
