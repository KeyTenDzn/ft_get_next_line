#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strdup(char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_concat(char	*s1, char *s2);
size_t	ft_strlen(const char *str);

# ifndef BUFFER_SIZE
#   define  BUFFER_SIZE 10
# endif
#endif
