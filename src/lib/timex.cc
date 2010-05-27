/*
 * timex.cc
 *
 *  Created on: 2010-05-26
 *      Author: konrad
 */
#include "timex.h"

#if !defined(__QNXNTO__)

uint64_t timespec2nsec(const struct timespec *t)
{
	return t->tv_sec * 1000000 + t->tv_nsec;
}

void nsec2timespec(struct timespec *t, uint64_t nsec)
{
	t->tv_sec = nsec / 1000000;
	t->tv_nsec = nsec % 1000000;
}

#endif
