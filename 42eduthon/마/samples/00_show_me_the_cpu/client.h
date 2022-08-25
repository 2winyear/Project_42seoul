#ifndef		CLIENT_H
# define	CLIENT_H

# include   <stdio.h>
# include   <stdlib.h>
# include   <string.h>
# include   <unistd.h>

# include   <sys/types.h>
# include   <sys/socket.h>
# include   <netinet/in.h>
# include   <arpa/inet.h>

# define    PORT 		9999

typedef struct cpu_data {
	float user;
	float sys;
	float idle;
} s_cpu_data;

#endif