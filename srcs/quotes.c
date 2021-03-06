/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:38:24 by rfabre            #+#    #+#             */
/*   Updated: 2018/05/03 15:17:17 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		reset_line_mode(t_sh *sh)
{
	sh->line->cur_mod_pos = 6;
	sh->line->max_mod_size = 6;
}

void		del_after_quote(t_sh *sh, char quote)
{
	int		i;
	char	*tmp;

	i = 0;
	while (sh->line->q_str[i])
		i++;
	i--;
	while (sh->line->q_str[i] && (sh->line->q_str[i] != quote))
		i--;
	tmp = ft_strsub(sh->line->q_str, 0, (i));
	ft_strdel(&sh->line->q_str);
	sh->line->q_str = ft_strdup(tmp);
	ft_strdel(&tmp);
}

void		simple_quote_work(t_sh *sh, int *ret_stop, char quote)
{
	char *tmp;

	if (sh->line->q_str && ft_strchr(sh->line->q_str, quote))
	{
		*ret_stop = 1;
		sh->line->prompt_mode = 0;
		set_term_back();
		del_after_quote(sh, quote);
		ft_putchar('\n');
	}
	else if (sh->buf == 10)
	{
		reset_line_mode(sh);
		tmp = ft_strdup(sh->line->q_str);
		if (tmp)
			ft_strdel(&sh->line->q_str);
		sh->line->q_str = ft_freejoinstr(tmp, "\n");
		sh->buf = 0;
		ft_putchar('\n');
	}
}

void		del_quote(t_sh *sh, char quote)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (sh->line->q_str)
		ft_strdel(&sh->line->q_str);
	sh->line->q_str = ft_strnew(0);
	while (sh->line->line[i])
		i++;
	i--;
	while (sh->line->line[i] && (sh->line->line[i] != quote))
		i--;
	if (sh->line->line[i] && sh->line->line[i] == quote)
	{
		i++;
		sh->line->q_str = ft_freejoinstr(sh->line->q_str, &sh->line->line[i]);
	}
	sh->line->q_str = ft_freejoinstr(sh->line->q_str, "\n");
}
