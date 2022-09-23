/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:23:04 by segan             #+#    #+#             */
/*   Updated: 2022/09/23 05:46:09 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "limits.h"

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*buff;
	char		*ret;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (ft_strchr(leftover, '\n'))
		return (return_only_leftover(&leftover));
	buff = (char *)malloc(BUFFER_SIZE);
	if (buff == NULL)
		return (NULL);
	while (1)
	{
		if (!read(fd, buff, BUFFER_SIZE))
			return (NULL);
		if (!ft_strchr(buff, '\n'))
			ret = ft_strjoin(leftover, buff);
		else
		{
			ret = ft_strjoin2(&leftover, buff);
		}
	}
	free(buff);
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
