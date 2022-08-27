/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukoh <jukoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:24:29 by jukoh             #+#    #+#             */
/*   Updated: 2022/08/27 17:39:24 by jukoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_char(char *str)
{
	int	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i] != '\0' && str[i] != 10)
		i++;
	if (str[i] == '\0')
		return (-1);
	return (1);
}

void	ft_read_line(t_list *ptn)
{
	char	buf[BUFFER_SIZE + 1];
	int		i;

	i = read(ptn->fd, buf, BUFFER_SIZE);
	while (i >= 0)
	{
		buf[i] = 0;
		ptn->chain = ft_strjoin(ptn->chain, buf);
		if (i == 0 || find_char(ptn->chain) == 1)
			break ;
		i = read(ptn->fd, buf, BUFFER_SIZE);
	}
}

t_list	*ft_list(t_list **list, int fd)
{
	t_list	*ptn;

	ptn = *list;
	while (ptn)
	{
		if (ptn->fd == fd)
		{
			ft_read_line(ptn);
			return (ptn);
		}
		ptn = ptn->next;
	}
	ptn = (t_list *)malloc(sizeof(t_list));
	if (!ptn)
		return (NULL);
	ptn->fd = fd;
	ptn->chain = NULL;
	ptn->next = *list;
	if (*list != NULL)
		(*list)->prec = ptn;
	ptn->prec = NULL;
	ft_read_line(ptn);
	*list = ptn;
	return (*list);
}

void	ft_free(t_list *ptn)
{
	free(ptn->chain);
	free(ptn);
}

int	get_next_line(int fd, char **line)
{
	char			buf[1];
	static t_list	*list;
	t_list			*ptn;
	int				i;

	ptn = ft_list(&list, fd);
	if (fd < 0 || !line || (read(fd, buf, 0) < 0) || !ptn || BUFFER_SIZE <= 0)
		return (-1);
	i = 0;
	while (ptn->chain[i] != '\0' && ptn->chain[i] != 10)
		i++;
	if (ptn->chain[i] != '\0')
	{
		*line = ft_split_gnl((&ptn->chain), i);
		return (1);
	}
	*line = ft_strdup(ptn->chain);
	if (ptn->prec != NULL)
		ptn->prec->next = ptn->next;
	if (ptn->next != NULL)
		ptn->next->prec = ptn->prec;
	if (list == ptn)
	{
		if (ptn->next == 0)
			list = ptn->prec;
		else
			list = ptn->next;
	}
	ft_free(ptn);
	return (0);
}
