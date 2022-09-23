/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:23:04 by segan             #+#    #+#             */
/*   Updated: 2022/09/24 05:26:14 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "limits.h"


char	*concatenate_line(char **ret, char *buff, char **leftover)
{
	size_t	ret_len;
	size_t	i;
	char	*new_ret;

	if (ft_strchr(buff, '\n'))
		i = ft_strchr(buff, '\n') - buff;
	else
		i = BUFFER_SIZE;
	ret_len = ft_strlen(*ret) + i;
	new_ret = (char *)malloc(ret_len + 1);
	if (new_ret == NULL)
		return (*ret);
	ft_strlcpy(new_ret, *ret, ft_strlen(*ret));
	free(*ret);
	//*ret = NULL;
	i = 0;
	while (i < BUFFER_SIZE && buff[i] != '\n')
		*new_ret++ = buff[i++];
	if (i < BUFFER_SIZE)
	{
		free(leftover);
		*leftover = (char *)malloc(BUFFER_SIZE - i + 1);
		*(*leftover)++ = buff[i++];
	}
	return (new_ret);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*buff;
	char		*ret;
	size_t		i;

	i = 0;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strchr(leftover, '\n'))
		return (return_only_leftover(&leftover));
	buff = (char *)malloc(BUFFER_SIZE);
	ret = (char *)malloc(ft_strlen(leftover) + 1);
	if (buff == NULL || ret == NULL)
		return (NULL);
	ft_strlcpy(ret, leftover, ft_strlen(leftover));
	while (1)
	{
		if (!read(fd, buff, BUFFER_SIZE))
			return (ret);
		ret = concatenate_line(&ret, buff, &leftover);
	}
	free(buff);
	buff = NULL;
	return (ret);
}

/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}
*/
