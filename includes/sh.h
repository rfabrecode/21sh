# ifndef SH_H
# define SH_H

# define BUILTIN "exit echo cd env setenv unsetenv"

# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>


int					ft_pointchar(int c);


typedef	struct		s_edit
{
	struct winsize 	sz;
	int             	cursor_pos;
	// int             	line_number;
	int					max_size;
	char 					*line;
}							t_edit;

void ft_isarrow(char *buf, t_edit *line);
void ft_left_arrow(char *buf, t_edit *line);
void ft_right_arrow(char *buf, t_edit *line);
void ft_homekey(char *buf, t_edit *line);
void ft_endkey(char *buf, t_edit *line);
void ft_delete(char *buf, t_edit *line);
void ft_insert(char *buf, t_edit *line);
void ft_move_it(int i, t_edit *line, char *buf, int check);
void ft_line_reset(t_edit *line);


#endif
