#include "get_next_line.h"

char	*append_and_clear(char *s1, char *s2)
{
	char	*new;

	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	new = ft_strjoin(s1, s2);
	return (new);
}

char	*read_until_nl(int fd, char *content)
{
	char	*tmp;
	int		bytes;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	bytes = 1;
	while (bytes > 0 && (!content || !ft_strchr(content, '\n')))
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(tmp);
			free(content);
			return (NULL);
		}
		tmp[bytes] = '\0';
		content = append_and_clear(content, tmp);
	}
	free(tmp);
	return (content);
}

char	*build_line(char *content)
{
	int		len;
	char	*line;

	if (!content || !content[0])
		return (NULL);
	len = 0;
	while (content[len] && content[len] != '\n')
		len++;
	if (content[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, content, len + 1);
	return (line);
}

char	*shrink_buffer(char *content)
{
	char	*rest;
	int		i;

	i = 0;
	if (!content)
		return (NULL);
	while (content[i] && content[i] != '\n')
		i++;
	if (!content[i])
	{
		free(content);
		return (NULL);
	}
	rest = ft_strdup(content + i + 1);
	free(content);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*content;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	content = read_until_nl(fd, content);
	if (!content)
		return (NULL);
	line = build_line(content);
	content = shrink_buffer(content);
	return (line);
}
/*
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}*/