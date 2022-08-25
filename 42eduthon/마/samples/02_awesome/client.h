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

# define    ASCII_RES   "\x1b[1;0m"

# define	CHART_RED	"\x1b[1;31m"
# define	CHART_GRE	"\x1b[1;32m"
# define	CHART_YEL	"\x1b[1;33m"
# define	CHART_BLU	"\x1b[1;34m"
# define	CHART_MAG	"\x1b[1;35m"
# define	CHART_CYA	"\x1b[1;36m"

# define	BACKG_BLA	"\x1b[48;5;0m"
# define	BACKG_WHI	"\x1b[48;5;7m"
# define	BACKG_GRE	"\x1b[48;5;2m"
# define    BACKG_YEL	"\x1b[48;5;226m"
# define    BACKG_BLU	"\x1b[48;5;21m"
# define    BACKG_MAG	"\x1b[48;5;13m"
# define    BACKG_CYA	"\x1b[48;5;14m"
# define    BACKG_RED	"\x1b[48;5;196m"
# define    BACKG_ORA	"\x1b[48;5;208m"

# define    PORT 		9999

typedef struct	cpu_data {
	float	user;
	float	sys;
	float	idle;
}				t_cpu_data;

void		ft_color_print(int num, char* str);
void 		ft_number_print(int num);
void		ft_shift_array(int* nums, int new);

int			ft_chart_vertical(int *nums, int num);
int			ft_chart_horizontal(int *nums, int num);
int			ft_chart_table(struct cpu_data data);

#endif