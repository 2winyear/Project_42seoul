#ifndef		SERVER_H
# define	SERVER_H

# include   <stdio.h>
# include   <string.h>
# include   <unistd.h>
# include   <stdlib.h>

# include   <sys/types.h>
# include   <sys/socket.h>
# include   <netinet/in.h>
# include   <arpa/inet.h>
# include   <time.h>

# include	<mach/vm_statistics.h>
# include	<mach/mach_types.h>
# include	<mach/mach_init.h>
# include	<mach/mach_host.h>

# include <signal.h>

# define    PORT 		9999

typedef struct cpu_data {
	float user;
	float sys;
	float idle;
} s_cpu_data;

int		get_cpu_status();

#endif