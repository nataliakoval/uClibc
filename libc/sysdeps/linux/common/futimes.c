/* vi: set sw=4 ts=4: */
/*
 * futimes() for uClibc
 *
 * Copyright (C) 2009 Rob Landley <rob@landley.net>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <utime.h>
#include <sys/time.h>

#ifdef __NR_utimensat
libc_hidden_proto(futimes)

int futimes(const int fd, const struct timeval tvp[2])
{
	struct timespec ts[2], *pts = ts;
     
	/* Convert timeval to timespec, for syscall */
   
	if (tvp) {
		TIMEVAL_TO_TIMESPEC(tvp, ts);
		TIMEVAL_TO_TIMESPEC(tvp+1, ts+1);
	} else pts = 0;

	/* Make syscall */

	return INLINE_SYSCALL(utimensat, 4, fd, 0, pts, 0);
}
libc_hidden_def(futimes)
#endif