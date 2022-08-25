# include	"client.h"

void		ft_color_printf(char* color, char* str)
{
	printf("%s%s%s", color, str, ASCII_RES);
}

void		ft_color_print(int num, char* str)
{
	if (num < 25)
		ft_color_printf(BACKG_WHI, str);
	else if (num < 50)
		ft_color_printf(BACKG_YEL, str);
	else if (num < 75)
		ft_color_printf(BACKG_ORA, str);
	else
		ft_color_printf(BACKG_RED, str);
}

void 		ft_number_print(int num)
{
	if (num == 100)
		printf(" %d", num);
	else if (num > 9)
		printf("  %d", num);
	else
		printf("   %d", num);
}

void		ft_shift_array(int* nums, int new)
{
	for (int i = 1; i < 10; i++)
		*(nums + i) = *(nums + i + 1);
	*(nums + 10) = new;
}
