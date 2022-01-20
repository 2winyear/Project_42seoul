/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 00:10:32 by seungyel          #+#    #+#             */
/*   Updated: 2021/07/07 17:01:42 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include "get_next_line.h"
# include "mlx.h"
# include "mlx_screen.h"

# define R 0
# define G 1
# define B 2
# define ERROR_MSG "Error\n"
# define CHECKED_ROAD 10
# define MAX_WIDTH 1920
# define MAX_HEIGHT 1080
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define TEX_WIDTH 512
# define TEX_HEIGHT 512
# define NUM_SPRITES 4
# define TEX_GHOST 4
# define K_A 0
# define K_B 11
# define K_C 8
# define K_D 2
# define K_E 14
# define K_F 3
# define K_G 5
# define K_H 4
# define K_I 34
# define K_J 38
# define K_K 40
# define K_L 37
# define K_M 46
# define K_N 45
# define K_O 31
# define K_P 35
# define K_Q 12
# define K_R 15
# define K_S 1
# define K_T 17
# define K_U 32
# define K_V 9
# define K_W 13
# define K_X 7
# define K_Y 16
# define K_Z 6
# define K_AR_L 123
# define K_AR_R 124
# define K_AR_U 126
# define K_AR_D 125
# define K_NP_DIV 75
# define K_NP_MUL 67
# define K_NP_MIN 78
# define K_NP_PLU 69
# define K_NP_1 83
# define K_NP_2 84
# define K_NP_3 85
# define K_NP_4 86
# define K_NP_5 87
# define K_NP_6 88
# define K_NP_7 89
# define K_NP_8 91
# define K_NP_9 92
# define K_SP 49
# define K_ESC 53
# define K_TAB 48
# define M_CLK_L 1
# define M_CLK_R 3
# define M_CLK_M 2
# define M_SCR_U 4
# define M_SCR_D 5
# define OP_R 0
# define OP_NO 1
# define OP_SO 2
# define OP_WE 3
# define OP_EA 4
# define OP_S 5
# define OP_F 6
# define OP_C 7
# define UDIV 1
# define VDIV 1
# define VMOVE 0.0
# define GUMBA_WIDTH 512
# define GUMBA_HEIGHT 512
# define MINI_SCALE 0.1
# define TILE_SIZE 120


int								g_gumba_texture[512 * 512];
char							**g_world_map;

typedef struct					s_press
{
	int							k_w;
	int							k_s;
	int							k_d;
	int							k_a;
	int							k_ar_r;
	int							k_ar_l;
}								t_press;

typedef struct					s_info
{
	double						p_x;
	double						p_y;
	double						dir_x;
	double						dir_y;
	double						plane_x;
	double						plane_y;
	void						*mlx;
	void						*win;
	void						*img1;
	void						*img2;
	int							*data1;
	int							*data2;
	double						z_buf[MAX_WIDTH];
	int							texture[8][TEX_HEIGHT * TEX_WIDTH];
	double						m_speed;
	double						r_sp;
	t_press						press;
}								t_info;



typedef struct s_node			t_node;
struct							s_node
{
	char						*value;
	t_node						*next;
};

typedef struct s_calc_wall		t_calc_wall;
struct							s_calc_wall
{
	int							y;
	int							hit;
	int							side;
	int							tex_x;
	int							tex_y;
	int							map_x;
	int							map_y;
	int							step_x;
	int							step_y;
	int							color;
	int							tex_num;
	int							l_h;
	int							draw_s;
	int							draw_e;
	double						step;
	double						tex_pos;
	double						wall_x;
	double						cam_x;
	double						r_dir_x;
	double						r_dir_y;
	double						d_x;
	double						d_y;
	double						s_dist_x;
	double						s_dist_y;
	double						p_w_dist;
};

typedef struct s_calc_sprite	t_calc_sprite;
struct							s_calc_sprite
{
	int							d;
	int							y;
	int							idx;
	int							tex_x;
	int							tex_y;
	int							color;
	int							st;
	int							draw_e_x;
	int							draw_e_y;
	int							draw_s_x;
	int							draw_s_y;
	int							v_m_s;
	int							sp_w;
	int							sp_h;
	int							sp_s_x;
	double						inv_d;
	double						sp_x;
	double						sp_y;
	double						tr_x;
	double						tr_y;
};

typedef struct s_calc			t_calc;
struct							s_calc
{
	int							y;
	int							hit;
	int							side;
	int							tex_x;
	int							tex_y;
	int							map_x;
	int							map_y;
	int							step_x;
	int							step_y;
	int							color;
	int							tex_num;
	int							line_height;
	int							draw_start;
	int							draw_end;
	double						step;
	double						texpos;
	double						wall_x;
	double						camera_x;
	double						raydir_x;
	double						raydir_y;
	double						d_x;
	double						d_y;
	double						s_x;
	double						sidedist_y;
	double						perpwalldist;
};

typedef struct s_sprite			t_sprite;
struct							s_sprite
{
	double						pos_x;
	double						pos_y;
	double						dist;
	int							texture_id;
};

typedef struct s_node_sprite	t_node_sprite;
struct							s_node_sprite
{
	t_sprite					value;
	t_node_sprite				*next;
};

//보너스
typedef struct		s_bonus_img
{
	void		*img2;
    int         *data2;
    int         bpp;
    int         line_size;
    int         endian;
}	t_bonus_img;

typedef struct s_model			t_model;
struct							s_model
{
	char						*no_path;
	char						*so_path;
	char						*we_path;
	char						*ea_path;
	char						*s_path;
	char						**real_map;
	int							width;
	int							height;
	int							row;
	int							col;
	int							bpp;
	int							player_flag;
	int							player_location_x;
	int							player_location_y;
	int							player_direction;
	char						*sprite_x;
	char						*sprite_y;
	int							op_flags[8];
	unsigned int				f_color[3];
	unsigned int				c_color[3];
	int							**texture;
	double						move_speed;
	double						rot_speed;
	t_node						*map;
	t_node_sprite				*sprites;
	t_info						info;
	t_bonus_img					*map2;
};

t_model							g_model;


typedef struct     s_data {
    void        *img;
    char        *addr;
    int            bits_per_pixel;
    int            line_length;
    int            endian;
}                t_data;
//

typedef struct					s_img
{
	void						*img;
	int							*data;
	int							size_l;
	int							bpp;
	int							endian;
	int							img_width;
	int							img_height;
}								t_img;

void							init(void);
int								main_loop(t_info *info);
void							parse_cub(char *filename);
void							ft_exit(int no, int error);
int								ft_isdigit(char c);
int								ft_isalpha(char c);
int								ft_strcmp(char *dst, char *src);
int								ft_isupper(char symbol);
int								ft_isspace(char symbol);
int								save_bmp(t_info *info);
void							check_file(char *filename, int flag);
void							option_color
								(char *line, int i, unsigned int *color);
void							option_r(char *line, int i);
void							option_path(char *line, int start, char **path);
int								read_option(char *line, char *op_str);
void							input_option_from_line
								(int op_symbol, char *line, int i);
int								is_option_symbol(char *str);
int								is_map_symbol(char c);
int								allocate_map();
void							input_map_from_row(char *row);
void							input_map_from_line(char *line);
void							check_map(int r, int c);
void							check_cub(void);
void							rewind_map(void);
void							input_player_location
								(int i, int j, int direction);
void							*ft_memset(void *ptr, int value, size_t num);
void							*ft_memmove(void *dest, void *src, size_t n);
void							calc_wall(t_info *info);
void							sort_sprites(void);
void							calc_sprite(t_info *info);
int								key_press(int key, t_info *info);
int								key_release(int key, t_info *info);
void							info_press(t_info *info, int sign);
void							init_cub3d(t_info *info);
void							load_texture(t_info *info);
void							input_node_sprite(int i, int j);
void							parse_map(void);
int								process_line(char *op_str,
								char **line, int i, int map_flag);
void							calc_dist(t_info *info);
int								ft_memexit(void);
void							free_node(void);
void							free_map(void);
void							free_sprite(void);
#endif
