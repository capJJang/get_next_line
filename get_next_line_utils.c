/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 23:45:15 by segan             #+#    #+#             */
/*   Updated: 2022/09/24 05:04:22 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int o)
{
	size_t	i;

	i = 0;
	if (o == 0)
		return ((char *)s + ft_strlen(s));
	if (s == NULL)
		return (NULL);
	while (i < BUFFER_SIZE)
	{
		if (s[i] == (char)o)
			return ((char *)(s + i));
		else
			i++;
	}
	return ((void *) 0);
}

char	*return_only_leftover(char **leftover)
{
	size_t	ret_len;
	size_t	new_left_over_len;
	char	*need_free;
	char	*ret;
	char	*new_left_over;

	need_free = *leftover;
	ret_len = ft_strchr(*leftover, '\n') - *leftover;
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
	free(need_free);
	return (ret - ret_len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	ret;

	ret = ft_strlen(src);
	if (dstsize == 0)
		return (ret);
	while (dstsize-- > 1 && *src)
		*dst++ = *src++;
	*dst = 0;
	return (ret);
}
