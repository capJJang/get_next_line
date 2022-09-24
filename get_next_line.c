/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:23:04 by segan             #+#    #+#             */
/*   Updated: 2022/09/25 05:19:47 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*return_only_leftover(char **leftover)
{
	size_t	ret_len;
	size_t	new_left_over_len;
	char	*need_free;
	char	*ret;
	char	*new_left_over;

	need_free = *leftover;
	ret_len = ft_strchr(*leftover, '\n') - *leftover + 1;
	ret = (char *)malloc(ret_len);
	if (ret == NULL)
		return (NULL);
	while (*leftover == ft_strchr(*leftover, '\n'))
		*ret++ = *(*leftover)++;
	*ret = 0;
	new_left_over_len = ft_strlen(*leftover);
	new_left_over = (char *)malloc(new_left_over_len + 1);
	if (new_left_over == NULL)
		return (NULL);
	while (**leftover)
		*new_left_over++ = *(*leftover)++;
	*new_left_over = 0;
	*leftover = new_left_over - new_left_over_len;
	free_arr(&need_free);
	return (ret - ret_len);
}

char	*concat_line(char **ret, char *buff, char **leftover, int read_count)
{
	size_t	ret_len;
	size_t	i;
	char	*new_ret;

	if (ft_strchr(buff, '\n'))
		i = ft_strchr(buff, '\n') - buff + 1;
	else
		i = read_count;
	ret_len = ft_strlen(*ret) + i;
	new_ret = (char *)malloc(ret_len + 1);
	if (new_ret == NULL)
		return (*ret);
	ft_strlcpy(new_ret, *ret, ft_strlen(*ret) + 1);
	free_arr(ret);
	buff[read_count] = 0;
	ft_strlcpy(new_ret + ret_len - i, buff, ret_len + 1);
	if (i < BUFFER_SIZE)
	{
		free(*leftover);
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
	int			read_count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strchr(leftover, '\n'))
		return (return_only_leftover(&leftover));
	buff = (char *)malloc(BUFFER_SIZE + 1);
	ret = (char *)malloc(ft_strlen(leftover) + 1);
	if (buff == NULL || ret == NULL)
		return (NULL);
	ret[ft_strlen(leftover)] = 0;
	ft_strlcpy(ret, leftover, ft_strlen(leftover));
	read_count = read(fd, buff, BUFFER_SIZE);
	if (read_count == 0 || read_count == -1)
		free_arr(&ret);
	while (read_count > 0)
	{
		ret = concat_line(&ret, buff, &leftover, read_count);
		if (ret == NULL)
			return (NULL);
		read_count = read(fd, buff, BUFFER_SIZE);
	}
	free_arr(&buff);
	return (ret);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}
