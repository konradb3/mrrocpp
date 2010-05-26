/*
 * timex.h
 *
 *  Created on: 2010-05-26
 *      Author: konrad
 */
#include <inttypes.h>
#include <sys/time.h>

#ifndef TIMEX_H_
#define TIMEX_H_

uint64_t timespec2nsec(const timespec& ts);

timespec nsec2timespec(uint64_t ns);

#endif /* TIMEX_H_ */
