/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdamy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:47:35 by sdamy             #+#    #+#             */
/*   Updated: 2022/12/06 20:47:39 by sdamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*ft_cleanstash(char *str)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	i++;
	j = i;
	while (str[j])
		j++;
	temp = malloc(sizeof(char) * ((j - i) + 1));
	j = 0;
	while (str[i])
	{
		temp[j] = str[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

char	*ft_strtrimstash(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i])
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	if (str[i] == '\n')
		line[j] = '\n';
	else 
		line [j] = '\0';
	return (line);
}

int	ft_verif_stash(char *str, int readed)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	if (i == 0 && readed == 0)
		return (2);
	if (readed == 0)
		return (0);
	return (-1);
}

char	*ft_read(int fd, char *temp)
{
	int			readed;
	char		buffer[BUFFER_SIZE + 1];
	static char	*stash;

	readed = read(fd, buffer, BUFFER_SIZE);
	if (readed == 0 && stash == NULL)
		return (NULL);
	if (stash == NULL && readed > 0)
		stash = ft_strdup(buffer);
	else if (readed > 0)
		stash = ft_strjoin(stash, buffer);
	printf("stash = %s, buffer = %s, readed = %d\n", stash, buffer, readed);
	if (ft_verif_stash(stash, readed) == 0)
	{
		temp = ft_strtrimstash(stash);
		stash = ft_cleanstash(stash);
		return (temp);
	}
	if (ft_verif_stash(stash, readed) == 2)
		stash = NULL;
	return (ft_read(fd, temp));
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*temp;

	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = ft_read(fd, temp);
	return (line);
}

int main(void)
{
	int		i;
	int		fd1;
    char    *line;

	fd1 = open("empty.txt", O_RDONLY);
    i = 1;
    // while (i < 5)
	// {
    //     line = get_next_line(fd1);
    //     printf("line : %s", line);
    //     i++;
    // }
	while (6)
	{
		line = get_next_line(fd1);
		printf ("line : %s", line);
		if (line == NULL)
			break ;
		free(line);
	}
    close(fd1);
	return (0);
}
