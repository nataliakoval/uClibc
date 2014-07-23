#include <fcntl.h>
#include <stdlib.h>

#ifdef __USE_BSD

/* Put the 1 minute, 5 minute and 15 minute load averages into the first
   NELEM elements of LOADAVG.  Return the number written (never more than
   three, but may be less than NELEM), or -1 if an error occurred.  */
int getloadavg (double __loadavg[], int __nelem)
{
	int fd;
    
	fd = open ("/proc/loadavg", O_RDONLY);
	if (fd < 0)
		return -1;
	else
	{
		char buf[65], *p;
		ssize_t nread;
		int i;
    
		nread = read (fd, buf, sizeof buf - 1);
		close (fd);
		if (nread <= 0)
			return -1;
		buf[nread - 1] = '\0';
   
		if (__nelem > 3)
			__nelem = 3;
		p = buf;
		for (i = 0; i < __nelem; ++i)
		{
			char *endp;
			__loadavg[i] = strtod (p, &endp);
			if (endp == p)
 				return -1;
			p = endp;
		}
    
		return i;
	}
}

#endif