#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = (char *)
		malloc(sizeof(char) * ft_strlen(s1) + sizeof(char) * ft_strlen(s2) + 1);
	if (!str)
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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t ft_strlentrim(char *str)
{
    size_t i;

    i = 0;
    while (str[i] && str[i] != '\n')
    {
        i++;
    }
    return (i);
}

char    *ft_strtrim(char *stash, int len)
{
    char    *str;
    int     i;

    i = 0;
    str = malloc(sizeof(char) * (len + 1));
    while (i <= len)
    {
        str[i] = stash[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

char    *resetstash(char *str)
{
    int     i;
    int     j;
    char    *tmp;

    i = 0;
    j = 0;
    while (str[i] != '\n')
        i++;
    if (str[i] == '\0')
        return (str);  
    else if (str[i] == '\n')
    {    
        i++;
        while (str[i])
        {
            i++;
            j++;
        }
        tmp = malloc(sizeof(char) * (j + 1));
        if (!tmp)
            return (str);
        i -= j;
        j = 0;
        while (str[i])
        {
            tmp[j] = str[i];
            i++;
            j++;
        }
        tmp[j] = '\0';
    }
    return (tmp);
}

char    *get_next_line(int fd)
{
    char        *buff;
    char        *temp;
    static char *stash;
    int         i;
    int         len;
    char        *str;
    int         readed;

    i = 0;
    buff = malloc (sizeof(char) * (BUFFER_SIZE + 1));
    if (!buff)
        return NULL;
    readed = read(fd, buff, BUFFER_SIZE);
    if (stash == NULL)
        temp = buff;
    else 
        temp = ft_strjoin(stash, buff);
    stash = temp;
    while (temp[i])
    {
        if (temp[i] == '\n')
        {
            len = ft_strlentrim(temp);
            str = malloc(sizeof(char) * len + 1);
            str = ft_strtrim(temp, len);
            stash = resetstash(stash);
            printf("Str = %s\n", str);
            return (str);
        }
        else if (readed == 0)
        {
            return stash;
            printf("Str = %s\n", stash);
        }
        i++;
    }
    return get_next_line(fd);
}

int main(void)
{
	int		i;
	int		fd1;
    char    *line;

	fd1 = open("test.txt", O_RDONLY);	
    i = 1;
    while (i < 6)
	{
        line = get_next_line(fd1);
        printf("line : %s\n", line);
        i++;
    }
    close(fd1);
	return (0);
}