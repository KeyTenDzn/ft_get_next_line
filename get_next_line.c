#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int ft_verifstash(char *str, int readed)
{
    int		i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (0);
        i++;
    }
    if (i > 0 && readed == 0)
        return (0);
    else if (readed == 0)
        return (1);
    return (-1);
}

char    *ft_trimstash(char *str)
{
    int     i;
    int     j;
    char    *temp;

    i = 0;
    j = 0;
    while (str[i] != '\n' && str[i])
        i++;
    if (str[i] == '\n') {
        temp = malloc(sizeof(char) * (i + 2));
    } else {
        temp = malloc(sizeof(char) * (i + 1));
    }
    while (j < i)
    {
        temp[j] = str[j];
        j++;
    }
    temp[j] = str[j];
    if (temp[j] == '\n') {
        temp[j+1] = 0;
    }
    return (temp);
}

char    *ft_cleanstash(char *str)
{
    int     j;
    int     i;
    int     k;
    char    *temp;

    i = 0;
    j = 0;
    while (str[i] != '\n' && str[i])
        i++;
    if (str[i] == '\0')
    {
        temp = (malloc(1));
        temp[0] = '\0';
        return (temp);
    }
    i++;
    j = i;
    while (str[j])
        j++;
    temp = malloc(sizeof(char) * ((j - i) + 1));
    if (!temp)
        return NULL;
    j = i;
    k = 0;
    while (str[j])
    {
        temp[k] = str[j];
        k++;
        j++;
    }
    temp[k] = '\0';
    return (temp);
}

char    *ft_read(int fd)
{
    int			readed;
	char		buffer[BUFFER_SIZE + 1];
    char        *temp;
    char        *temp2; 
	static char	*stash;

    while (1 > 0)
    {
        readed = read(fd, buffer, BUFFER_SIZE);
        buffer[readed] = '\0';
        if (readed < 0 || (stash == NULL && buffer[0] == '\0'))
            break ;
        if (stash == NULL && readed > 0)
		    stash = ft_strdup(buffer);
        else {
            temp = stash;
            stash = ft_strjoin(stash, buffer);
            free(temp);
        }
        if (ft_verifstash(stash, readed) == 0)
        {
            temp = ft_strdup(stash);
            temp2 = stash;
            stash = ft_cleanstash(stash);
            free(temp2);
            temp2 = temp;
            temp = ft_trimstash(temp);
            free(temp2);
            return (temp);
        }
        if (ft_verifstash(stash,readed) == 1)
            break ;
    }
    return (NULL);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = ft_read(fd);
	return (line);
}


// int main(void)
// {
// 	int		i;
// 	int		fd1;
//     char    *line;

// 	fd1 = open("empty.txt", O_RDONLY);
// 	while (6)
// 	{
// 		line = get_next_line(fd1);
// 		if (line == NULL)
// 			break ;
//         printf ("line : %s", line);
// 		free(line);
// 	}
//     close(fd1);
// 	return (0);
// }
