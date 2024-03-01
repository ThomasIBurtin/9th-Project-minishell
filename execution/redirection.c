/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:08:42 by tburtin           #+#    #+#             */
/*   Updated: 2024/02/22 11:29:54 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int redirection(char *file, int i)
{
    int fd;
    
    if(i == 0)
        fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if(i == 1)
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd < 0)
	{
        perror("open");
        return EXIT_FAILURE;
    }

    int stdout_backup_fd = dup(STDOUT_FILENO);
    if (stdout_backup_fd == -1)
        perror("dup");

    if (dup2(fd, STDOUT_FILENO) < 0)
	{
        perror("dup2");
        close(fd);
        return EXIT_FAILURE;
    }
    close(fd);
    return (stdout_backup_fd);
}