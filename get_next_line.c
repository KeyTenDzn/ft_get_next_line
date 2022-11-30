#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = (char *)
		malloc(sizeof(char) * ft_strlen(s1) + sizeof(char) * ft_strlen(s2) + 1);
	if (!str || !s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		str[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	verified_stash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*trim_stash(char *str)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\0')
		{
			j = i;
			i = 0;
			line = malloc(sizeof(char) * (j + 1));
			if (!line)
				return (NULL);
			while (i < j)
			{
				line[i] = str[i];
				i++;
			}
			line[i] = '\n';
			return (line);
		}
		i++;
	}
	return (str);
}

char	*clean_stash(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		temp;

	i = 0;
	j = 0;
	while (str[i] != '\n')
		i++;
	i++;
	temp = i;
	while (str[i++])
		j++;
	new_str = malloc(sizeof(char) * (j + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[temp])
	{
		new_str[i] = str[temp];
		temp++;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buff;
	char		*temp;
	int			readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readed = read(fd, buff, BUFFER_SIZE);
	if (stash == NULL && readed == 0)
	{	
		free (buff);
		return (NULL);
	}
	if (stash == NULL)
		stash = buff;
	else
		stash = ft_strjoin(stash, buff);
	if (readed == 0)
	{
		free (buff);
		free (stash);
		return (NULL);
	}
	if (verified_stash(stash) == 1)
	{
		temp = trim_stash(stash);
		stash = clean_stash(stash);
		free (buff);
		return (temp);
	}
	return (get_next_line(fd));
}

int main(void)
{
 	int		i;
 	int		fd1;
     char    *line;

 	fd1 = open("empty.txt", O_RDONLY);	
     i = 0;
     while (i < 1)
 	{
         line = get_next_line(fd1);
         printf("line : %s", line);
         i++;
     }
     close(fd1);
 	return (0);
}
