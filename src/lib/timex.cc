/*
 * timex.cc
 *
 *  Created on: 2010-05-26
 *      Author: konrad
 */
#include "timex.h"

#if !defined(_QNXNTO_)
uint64_t timespec2nsec(const timespec& ts)
{
	return (ts.tv_sec * 1000000 + ts.tv_nsec);
}

timespec nsec2timespec(uint64_t ns)
{
	timespec ts;
	ts.tv_sec = ns/1000000;
	ts.tv_nsec = ns%1000000;

	return ts;
}
#endif
