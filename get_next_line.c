/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likiffel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:25:33 by likiffel          #+#    #+#             */
/*   Updated: 2024/03/18 04:12:56 by likiffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char *find_line(int fd, char *buffer, char *line)
{
    int bytes_read;

    bytes_read = 1;
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        buffer[bytes_read] = '\0';
        line = ft_strjoin(line, buffer);
    }
    return (line);
}

char    *get_next_line(int fd)
{
    static char *remainder;
    char        *buffer;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
        return (NULL);
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    if (remainder) 
        line = ft_strdup(remainder);
    else 
        line = ft_strdup("");
    line = find_line(fd, buffer, line);
    free(buffer);
    if (!line || (line[0] == '\0' && !remainder))
        return (NULL);
    remainder = ft_strchr(line, '\n');
    if (remainder) 
    {
        *remainder = '\0';
        remainder++;
    }
    return (line);
}

/*int main()
{
   
    int  fd = open("test.txt", O_RDONLY);

    if (fd == -1) 
    {
        perror("Error");
        return 1;
    }

    char *result = get_next_line(fd);
    printf("first line '%s'\n", result);
    //free(result);
	char *result2 = get_next_line(fd);
	printf("next line '%s' \n", result2);
    //free(result2);
	char *result3 = get_next_line(fd);
	printf("next line '%s'\n", result3);
    //free(result3);
    char *result4 = get_next_line(fd);
    printf("next line '%s'\n" ,result4);
    //free(result4);

    close(fd);
    
    
    return 0;
}*/
