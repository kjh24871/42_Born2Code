/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukoh <jukoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:20:11 by jukoh             #+#    #+#             */
/*   Updated: 2022/08/27 17:25:19 by jukoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 50
typedef struct	s_list
{
	int				fd;
	char			*chain;
	struct s_list	*next;
	struct s_list	*prec;
}				t_list;

t_list			*ft_new(t_list **list, int fd);
t_list			*ft_list(t_list **list, int fd);
void			ft_read_line(t_list *ptn);
int				ft_strlen(char *s);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_split_gnl(char **buffer, int stop);
char			*ft_strdup(char *src);
void			ft_free(t_list *ptn);
int				get_next_line(int fd, char **line);
int				find_char(char *str);
#endif