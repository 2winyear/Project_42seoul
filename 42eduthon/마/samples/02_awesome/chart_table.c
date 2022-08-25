# include   "client.h"

int			ft_chart_table(struct cpu_data data)
{
	system("clear");

	int		user = (int)((data).user / 2 + 1);
	int		sys = (int)((data).sys / 2 + 1);
	int		idle = 50 - user - sys;
	system("clear");

	printf(CHART_CYA);
	printf("user\t\t\t");
	printf(CHART_MAG);
	printf("sys\t\t      ");
	printf(ASCII_RES);
	printf("idle\n");

	printf(BACKG_CYA);
	for (int i=0; i<user; i++)
		printf(" ");
	printf(BACKG_MAG);
	for (int i=0; i<sys; i++)
		printf(" ");
	printf(BACKG_WHI);
	for (int i=0; i<idle; i++)
		printf(" ");
	printf(ASCII_RES);
	printf("\n");
	return (0);
}