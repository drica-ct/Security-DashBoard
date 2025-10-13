#ifndef SECURITY_H
# define SECURITY_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <time.h>
# include <errno.h>
# include <math.h>
# include <pthread.h>

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


//Utils - Libft
size_t	ft_strlen(const char *str);
bool	ft_isdelim(int c);
char	*trim_whitespace(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(const char *str, unsigned int start, size_t len);
//Utils - Parsing
void	parse_json(t_results *result, const char *file);
int		destroy_game(t_game *game);
//Utils - Destroying
//void	destroy_map(t_game *g);
//int		destroy_game(t_game *game);

#endif
