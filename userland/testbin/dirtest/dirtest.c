WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
/*
 * Copyright (c) 2000, 2001, 2002, 2003, 2004, 2005, 2008, 2009
 *	The President and Fellows of Harvard College.
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
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * dirtest.c
 *
 * 	Tests your hierarchical directory implementation by creating
 * 	and deleting directories.
 *
 *      Works in the current directory.
 *
 *      Intended for the file system assignment. Should run (on SFS)
 *      when that assignment is complete.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <err.h>

#define MAXLEVELS       5

int
main(void)
{
	int i;
	const char *onename = "testdir";
	char dirname[512];

	strcpy(dirname, onename);

	for (i=0; i<MAXLEVELS; i++) {
		printf("Creating directory: %s\n", dirname);

		if (mkdir(dirname, 0755)) {
			err(1, "%s: mkdir", dirname);
		}

		strcat(dirname, "/");
		strcat(dirname, onename);
	}

	printf("Passed directory creation test.\n");

	for (i=0; i<MAXLEVELS; i++) {
		dirname[strlen(dirname) - strlen(onename) - 1] = 0;

		printf("Removing directory: %s\n", dirname);

		if (rmdir(dirname)) {
			err(1, "%s: rmdir", dirname);
		}
	}
	printf("Passed directory removal test.\n");

	return 0;
}

