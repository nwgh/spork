/*
 * Copyright (c) 2003
 * Nicholas W. Hurley.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the Nicholas W. Hurley may not be used to endorse or
 *    promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NICHOLAS W. HURLEY ``AS IS'' AND
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
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

extern char **environ;

#define S_EXECL 0
#define S_EXECLP 1

#define S_EXECV 2
#define S_EXECVP 3

pid_t spork(int etype, int num, const char *fp, ...)
{
	va_list ap;
	char **args;
	pid_t rval;
	int i;

	switch(etype) {
	case S_EXECL:
		if(!(args = malloc(num * sizeof(char*)))) {
			rval = -1;
			break;
		}
		
		if((rval = fork()) == 0) {
			va_start(ap, fp);
			for(i = 0; i < num; i++) {
				args[i] = va_arg(ap, char *const);
			}
			va_end(ap);
			execv(fp, args);
			exit(-1);
		}
		break;
	case S_EXECLP:
		if(!(args = malloc(num * sizeof(char*)))) {
			rval = -1;
			break;
		}
		
		if((rval = fork()) == 0) {
			va_start(ap, fp);
			for(i = 0; i < num; i++) {
				args[i] = va_arg(ap, char *const);
			}
			va_end(ap);
			execvp(fp, args);
			exit(-1);
		}
		break;
	case S_EXECV:
		if((rval = fork()) == 0) {
			va_start(ap, fp);
			args = va_arg(ap, char **const);
			va_end(ap);
			execv(fp, args);
			exit(-1);
		}
		break;
	case S_EXECVP:
		if((rval = fork()) == 0) {
			va_start(ap, fp);
			args = va_arg(ap, char **const);
			va_end(ap);
			execvp(fp, args);
			exit(-1);
		}
		break;
	default:
		rval = -1;
	}

	return rval;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
