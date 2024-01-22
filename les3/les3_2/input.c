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

#include "input.h"
#include "macro.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

long long get_number_limit(const char *prompt, long long min, long long max) {
	char *endptr = NULL;
	char buff[128];
	long number;

retry:
	printf("%s", prompt);
	if (!fgets(buff, ARRAY_SIZE(buff), stdin)) {
		fprintf(stderr, "Failed to read from stdin.");
		exit(EXIT_FAILURE);
	}
	errno = 0;
	number = strtoll(buff, &endptr, 10);

	if (errno == ERANGE || errno == EINVAL || buff == endptr || number < min ||
	    number > max) {
		if (errno == ERANGE || number < min || number > max)
			printf("Input too large/small.\n");
		else
			printf("Failed to parse input.\n");
		errno = 0;
		goto retry;
	}
	return number;
}

long long get_number(const char *prompt) {
	return get_number_limit(prompt, LLONG_MIN, LLONG_MAX);
}
