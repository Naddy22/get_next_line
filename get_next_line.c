/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:54:26 by namoisan          #+#    #+#             */
/*   Updated: 2023/11/22 15:07:04 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
/*supprime dans le buf la ligne qui vient d'être affiché pour que le
prochain appel de get next line envoie la prochaine ligne*/

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
	{
		res = ft_strdup(&buf[i]);
		free(buf);
		return (res);
	}
	free(buf);
	return (NULL);
}

char	*fill_buffer(char *buf, int fd)
{
	int			read_bytes;
	char		tmp[BUFFER_SIZE + 1];

	read_bytes = 1;
	while ((!ft_strchr(buf, '\n') || !buf) && read_bytes > 0)
	{
		ft_bzero(tmp, BUFFER_SIZE + 1);
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		buf = ft_strjoin(buf, tmp);
		if (buf == NULL)
			return (NULL);
	}
	if (!buf || read_bytes < 0 || buf[0] == 0)
	{
		if (buf != NULL)
			free(buf);
		buf = NULL;
		return (NULL);
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	int			i;
	char		*line;

	buf = fill_buffer(buf, fd);
	if (!buf)
		return (NULL);
	i = 0;
	while (buf[i] != '\0' && (i == 0 || buf[i - 1] != '\n'))
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (line == NULL)
	{
		if (buf)
			free(buf);
		buf = NULL;
		return (NULL);
	}
	ft_strlcpy(line, buf, i);
	buf = delete_buf_line(buf);
	return (line);
}

// int	main(void)
// {
// 	int	fd;
// 	char *result;

// 	fd = 0;
// 	result = "Bouh";
// 	fd = open("1char.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while (result)
// 	{
// 		result = get_next_line(fd);
// 		printf("result :%s\n", result);
// 		if (result)
// 			free (result);
// 	}
// 	return (0);
// }
