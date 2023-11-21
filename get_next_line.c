/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadege <nadege@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:54:26 by namoisan          #+#    #+#             */
/*   Updated: 2023/11/20 21:19:42 by nadege           ###   ########.fr       */
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	result;

	i = 0;
	result = 0;
	if (src == NULL)
		return (0);
	while (src[i] != '\0' && i + 1 < dstsize)
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

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*r;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	r = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!r)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	r[len1 + len2] = '\0';
	while (len2--)
		r[len1 + len2] = s2[len2];
	while (len1--)
		r[len1] = s1[len1];
	if (s1)
		free(s1);
	return (r);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == 0)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (0);
}
char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		size;

	if (s1 == NULL)
		return (NULL);
	size = ft_strlen(s1);
	ptr = (char *)malloc((size + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, size + 1);
	return (ptr);
}

//supprime dans le buf la ligne qui vient d'être affiché pour que le prochain appel de get next line envoie la prochaine ligne
char	*delete_buf_line(char *buf)
{
	int		i;
	char	*res;

	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	if (buf[i] == '\n')
		i++;
	if (buf[i] != '\0')
		res = ft_strdup(&buf[i]);
		//protege si c'est la fin du buffer pour pas aller dans une memoire trop loin
	else
		return (NULL);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		tmp[BUFFER_SIZE + 1];
	int			read_bytes;
	int			i;
	char		*line;

	while (!ft_strchr(buf, '\n')) //si j'ai pas de \n avant la fin de mon buffer
	{
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (read_bytes < 1)
			return (NULL);
		tmp[read_bytes] = '\0';
		buf = ft_strjoin(buf, tmp);
	}
	if (read_bytes < 0)
	{
		free(buf);
		buf = NULL;
	}
	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
	{
		line[i] = buf[i];
		i++;
	}
	line[i] = '\0';
	buf = delete_buf_line(buf);
	return (line);
}

// int	main(void)
// {
// 	int	fd;

// 	fd = open("simple.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	return (0);
// }
