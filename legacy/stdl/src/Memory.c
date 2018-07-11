/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2017 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU Lesser General Public License version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE included in
** the packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************/

#include <AuroraFW/STDL/LibC/String.h>

void *memcpy(void *dst, const void *src, size_t n)
{
	char *t = dst;
	const char *s = src;

	while (n--)
		*t++ = *s++;
	return dst;
}

void *memmove(void *dst, const void *src, size_t n)
{
	char *t;
	const char *s;

	if (dst <= src) {
		t = dst;
		s = src;
		while (n--)
			*t++ = *s++;
	} else {
		t = dst;
		t += n;
		s = src;
		s += n;
		while (n--)
			*--t = *--s;
	}
	return dst;
}

int memcmp(const void *cs, const void *ct, size_t n)
{
	const unsigned char *su1, *su2;
	int r = 0;

	for (su1 = cs, su2 = ct; 0 < n; ++su1, ++su2, n--)
		if ((r = *su1 - *su2) != 0)
			break;
	return r;
}

void *memset(void *s, const int c, size_t n)
{
	char *xs = s;

	while (n--)
		*xs++ = c;
	return s;
}