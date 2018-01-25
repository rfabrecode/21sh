/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 02:16:33 by rfabre            #+#    #+#             */
/*   Updated: 2018/01/25 03:53:33 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static void swap_norme(t_edit *line)
{
    int swap;

    swap = line->end_select;
    line->end_select = line->start_select;
    line->start_select = swap + 1;
}

void ft_highlight(t_edit *line, char *buf)
{
	int i;
	char *tmp;
	char *tmp2;

	i = 0;
	tmp = ft_strndup(line->line, line->start_select);
	ft_putstr(tmp);
	ft_putstr(tgetstr("mr", NULL));
  if (line->start_select > line->end_select)
      swap_norme(line);
	tmp2 = ft_strsub(line->line, line->start_select , (line->end_select - line->start_select));
	ft_putstr(tmp2);
	free(tmp);
	ft_putstr(tgetstr("me", NULL));
	tmp = ft_strsub(line->line, line->end_select , (line->max_size - 3));
	ft_putstr(tmp);
	line->cursor_pos = line->max_size;
	while ((size_t)++i <= ft_strlen(tmp))
	{
		buf[2] = 68;
		ft_left_arrow(buf, line);
	}
	free(tmp);
	free(line->is_highlight);
	line->is_highlight = tmp2;
}

void ft_go_start(t_edit *line, char *buf)
{
	int i;

	i = 0;
	while (i < line->max_size)
	{
		buf[2] = 68;
		ft_left_arrow(buf, line);
		i++;
	}
	tputs(tgetstr("ce", NULL), 1, ft_pointchar);
}

void ft_cut(t_edit *line, char *buf)
{
	int i;

	char *tmp;
  char *tmp2;

	i = 0;
	tmp = ft_strndup(line->line, line->start_select);
	ft_putstr(tmp);
	tmp2 = ft_strsub(line->line, line->end_select , (line->max_size - 3));
	ft_putstr(tmp2);
  buf[2] = 68;
  free(line->line);
  line->max_size -= ft_strlen(line->is_highlight);
  line->line = ft_freejoinstr(tmp, tmp2);
  free(tmp2);
  line->cursor_pos = (ft_strlen(line->line) + 2);
}

void select_copy_cut(t_edit *line, char *buf)
{
	if (!line->select_mode && buf[0] == 11)
	{
		line->select_mode = 1;
		line->start_select = ((line->cursor_pos) - 2);
	}
	else if ((line->select_mode) && ((buf[0] == 11) || buf[0] == 9))
	{
		line->select_mode = 0;
    ft_go_start(line, buf);
    ft_putstr(line->line);
	}
	else if (buf[0] == 21)
  {
    line->select_mode = 0;
    ft_go_start(line, buf);
    // ft_putchar('\n');
    // ft_putchar('\n');
    // ft_putstr("---");
    // ft_putnbr(line->cursor_pos);
    // ft_putchar('\n');
    // ft_putchar('\n');
    // ft_putstr("---");
    // ft_putnbr(line->max_size);
    ft_cut(line, buf);
  }
}