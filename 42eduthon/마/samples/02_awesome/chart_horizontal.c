# include   "client.h"

void		ft_chart_hor(int nums[])
{
	int		width = 50;
	int		height = 10;

	for (int i=0; i<height; i++)
	{
		ft_number_print(nums[i]);
		printf("┃ ");
		for (int j=0; j<nums[i]; j++)
			ft_color_print(nums[i], " ");
		printf("\n");
	}	
	printf("    ┗");
	for (int col = 0; col < 40; col++)
		printf("━━");
	printf("\n");
}

int			ft_chart_horizontal(int *nums, int num)
{
	system("clear");
	ft_shift_array(nums, num);
	ft_chart_hor(nums);
	return (0);
}