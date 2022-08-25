# include   "client.h"

void		ft_chart_ver(int nums[])
{
	int		grid = 5;
	int		level = 20;

	for (int col = 0; col < 20; col++)
	{
		ft_number_print(level * 5);
		printf("┃ ");
		for (int row = 1; row < 11; row++)
		{
			if (((nums[row] + nums[row - 1]) / 10) >= level)
				ft_color_print(nums[row], " ");
			else
				printf(" ");

			if ((nums[row] / 5) >= level)
				ft_color_print(nums[row], "  ");
			else
				printf("  ");
			
			if (row != 10 && ((nums[row] + nums[row + 1]) / 10) >= level)
				ft_color_print(nums[row], " ");
			else
				printf(" ");
		}
		printf("\n");
		--level;
	}
	printf("    ┗");
	for (int col = 0; col < 20; col++)
		printf("━━");
	printf("\n    ");
	for (int i = 1; i < 11; i++)
		ft_number_print(nums[i]);
	printf("\n");
}


int			ft_chart_vertical(int *nums, int num)
{
	system("clear");
	ft_shift_array(nums, num);
	ft_chart_ver(nums);
	return (0);
}