/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:27 by transfo           #+#    #+#             */
/*   Updated: 2024/02/22 11:33:09 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	*find_path(char *const *envp, char *const cmd)
{
	char	**path_from_envp;
	char	*part_path;
	char	*path;
	int		i;
	int		j;

	i = 0;
	if (ft_strnstr(cmd, "/", 2) != 0 && access(cmd, F_OK) == 0)
		return ((char *)cmd);
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	path_from_envp = ft_split(envp[i] + 5, ':');
	j = 0;
	while (path_from_envp[j])
	{
		part_path = ft_strjoin(path_from_envp[j], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free((char *)path);
		j++;
	}
	free_tab((char **)path_from_envp);
	return (NULL);
}

void	exec(char *const * av, char *const *envp)
{
	char *const	*cmd;
	const char	*path;
	pid_t		id;
	int stdout_backup_fd;
	int i;

	stdout_backup_fd = -1;
	i = 0;
	while(av[i] != NULL)
	{
	 	if(av[i][0] == '>' && av[i][1] == '>')
		{
	 		stdout_backup_fd = redirection(av[i+1], 0);
			break;
		}
		else if(av[i][0] == '>')
		{
			stdout_backup_fd = redirection(av[i+1], 1);
			break;
		}
	 	i++;
	}

	path = find_path(envp, av[0]);
	if (!path)
	{
		perror("cmd ");
		free_tab((char **)av);
	}
	
	id = fork();
	if (id == -1)
		perror("fork ");
	else if (id == 0)
	{
	 	if (execve(path, av, envp) == -1)
	 		perror("execve ");
	}
	else
	{
        wait(NULL);
        if (stdout_backup_fd != -1)
		{
            dup2(stdout_backup_fd, STDOUT_FILENO);
            close(stdout_backup_fd);
        }
	}
}