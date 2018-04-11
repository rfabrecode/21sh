
#include "../includes/sh.h"

void			ft_init_all_paths(char **paths)
{
	int			i;
	char		*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
}

char				**ft_set_paths(t_env *env)
{
	t_env *tmp;
	char *tmp1;
	char **apaths;

	tmp = env;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strncmp("PATH=", tmp->var, 5))
		{
			tmp1 = ft_strdup(tmp->var + 5);
			apaths = ft_strsplit(tmp1, ':');
			ft_strdel(&tmp1);
			ft_init_all_paths(apaths);
			return (apaths);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
