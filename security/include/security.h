#ifndef SECURITY_H
# define SECURITY_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <time.h>
# include <errno.h>
# include <math.h>
//# include "../libft/libft.h"

typedef enum s_severity
{
	LOW,
	MID,
	HIGH,
	CRITICAL,
}		t_severity;

typedef struct s_vulnerabilities
{
	t_severity	grade;

	char	*id;
	char	*pkg_name;
	char	*install_version;
	char	*fixed_version;
	char	*title;
	char	*description;
	char	**references;
}			t_vulnerabilities;

typedef struct s_results
{
	struct s_vulnerabilities	*vuln_list;

	char	*target;
	char	*pc_class; // TODO arranjar nome melhor
	char	*type;
}			t_results;

/*
//Utils - Error Handling
void	error_exit(char *msg, t_game *g);
void	error_map(char *msg, t_game *g, bool fd_error);
//Utils - Destroying
void	destroy_map(t_game *g);
int		destroy_game(t_game *game);
//Utils - Loading
void	load_map(t_game *g, char *file);
void	load_graphics(t_game *g);
int		count_ws(char *line, int start);
//Utils - Rendering
int		game_frame_loop(t_game *game);
void	draw_wall(t_game *game, int h_pixel, int l_pixel, int x);
void	draw_ceiling(t_game *game, int x, int ray_count, int h_pixel);
void	draw_floor(t_game *game, int x, int ray_count, int l_pixel);
int		get_texture_color(t_game *game, int tex_y);
//Utils - Moving
int		key_handler(const int key, t_game *game);
void	look_direction(t_game *game, const bool is_left);
//Utils - Validation
void	validate_map(t_game *g);
int		flood_fill_cub3d(char **tab, t_game *g, t_point begin);
*/
#endif
