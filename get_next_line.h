#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

/* get_next_line.c */
char	*append_and_clear(char *s1, char *s2);
char	*read_until_nl(int fd, char *content);
char	*build_line(char *content);
char	*shrink_buffer(char *content);
char	*get_next_line(int fd);

/* get_next_line_utils.c */
int		ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *str, int c);
int		ft_strlcpy(char *dest, char *src, int size);

#endif