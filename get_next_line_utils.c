/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 23:45:15 by segan             #+#    #+#             */
/*   Updated: 2022/09/23 05:43:50 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int o)
{
	if (o == 0)
		return ((char *)s + ft_strlen(s));
	while (*s)
	{
		if (*s == (char)o)
			return ((char *) s);
		else
			s++;
	}
	return ((void *) 0);
}

char	*return_only_leftover(char **leftover)
{
	char	*ret;
	char	*new_leftover;
	size_t	i;
	size_t	j;
	size_t	new_leftover_size;

	ret = (char *)malloc(ft_strchr(*leftover, '\n') - *leftover + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (1)
	{
		if (ft_strchr(leftover[i++], '\n'))
			break ;
		ret[i++] = *leftover[j++];
	}
	ret[i] = '\n';
	j = i;
	new_leftover_size = 0;
	while (*leftover[i++])
		new_leftover_size++;
	new_leftover = (char *)malloc(new_leftover_size + 1);
	if (new_leftover == NULL)
		return (NULL);
	i = 0;
	while (j < ft_strlen(*leftover))
		new_leftover[i++] = *leftover[j++];
	new_leftover[i] = 0;
	free(*leftover);
	*leftover = new_leftover;
	return (ret);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*ptr;
	size_t	s1_len;
	size_t	s2_len;
	size_t	ptr_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr_len = s1_len + s2_len;
	ptr = (char *)malloc(ptr_len + 1);
	if (ptr == (void *)0)
		return ((void *)0);
	while (s1_len--)
		*ptr++ = *s1++;
	while (s2_len--)
		*ptr++ = *s2++;
	*ptr = 0;
	return (ptr - ptr_len);
}

char	*ft_strjoin2(char **s1, char const *s2)
{
	char	*ptr;
	char	*new_leftover;
	size_t	s1_len;
	size_t	s2_len;
	size_t	ptr_len;

	s1_len = ft_strlen(*s1);
	s2_len = ft_strchr(s2, '\n') - s2;
	ptr_len = s1_len + s2_len;
	ptr = (char *)malloc(ptr_len + 1);
	if (ptr == (void *)0)
		return ((void *)0);
	while (s1_len--)
		*ptr++ = *(*s1)++;
	while (s2_len--)
		*ptr++ = *s2++;
	*ptr = 0;
	new_leftover = (char *)malloc(ft_strlen(*s1) + 1);
	if (new_leftover == NULL)
		return (NULL);
	while (**s1)
		*new_leftover++ = *(*s1)++;
	free(*s1);
	*s1 = new_leftover;
	return (ptr - ptr_len);
}
