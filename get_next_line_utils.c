/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:54:39 by namoisan          #+#    #+#             */
/*   Updated: 2023/11/22 14:30:10 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	char	*p;

	p = s;
	if (s == NULL)
		return ;
	while (n > 0)
	{
		*p = 0;
		n--;
		p++;
	}
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	result;

	i = 0;
	result = 0;
	if (src == NULL)
		return (0);
	while (src[i] != '\0' && i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	while (src[result] != '\0')
		result++;
	return (result);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d;
	size_t	dst_size;
	size_t	src_size;

	i = 0;
	d = 0;
	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dst == NULL || dstsize == 0)
		return (src_size);
	if (dstsize < dst_size)
		return (src_size + dstsize);
	while (dst[d] != '\0' && d < dstsize)
		d++;
	while (src[i] != '\0' && d + 1 < dstsize)
	{
		dst[d] = src[i];
		i++;
		d++;
	}
	if (dstsize > 0)
		dst[d] = '\0';
	return (dst_size + src_size);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*result;
	int		size;

	result = NULL;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(sizeof(char) * size);
	if (result == NULL)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	ft_bzero(result, size);
	ft_strlcpy(result, s1, ft_strlen(s1) + 1);
	ft_strlcat(result, s2, size);
	if (s1)
		free(s1);
	return (result);
}
