/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:23:04 by segan             #+#    #+#             */
/*   Updated: 2022/09/20 23:51:32 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE];
	int			i;
	int			j;

	char	*ret;
	
	i = ft_strlen(buff);
	if (read(fd, buff + i, BUFFER_SIZE - i) <= 0 || fd < 0)
		return (NULL);
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	ret = ft_substr(buff, 0, i);
	i++;
	while (i < BUFFER_SIZE)
		buff[j++] = buff[i++];
	buff[i] = 0;
	return (ret);
}

/*
#include <fcntl.h>

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}

// a s d f '\n' a s d f
*/