/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chek.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:24:11 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/27 17:40:19 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static char	*free_and_return(char **path_from_envp, char *return_value)
{
	free_tab((char **)path_from_envp);
	return (return_value);
}


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
		part_path = ft_strjoin(path_from_envp[j++], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_and_return(path_from_envp, path));
		free((char *)path);
	}
	free_tab((char **)path_from_envp);
	return (NULL);
}


int chek_infile(char *infile)
{
    errno = 0;
    int fd = open(infile,  O_RDONLY);

    if (fd == -1)
	{
        if (errno == ENOENT)
			printf("no such file or directory\n");
		else if (errno == EACCES)
			printf("permission denied\n");
		return(0);
    }
	else
		close(fd);
    return (1);
}


int chek_outfile(t_token *liste_token)
{
	if(liste_token->type == outfile)
	{
		int fd = open(liste_token->str, O_CREAT | O_RDWR | O_TRUNC, 0644);

		if (fd == -1)
		{
			printf("permission denied\n");
			return(0);
		}
		else
			close(fd);
	}
	else if(liste_token->type == append)
	{
		int fd = open(liste_token->str, O_CREAT | O_RDWR | O_APPEND, 0644);

		if (fd == -1)
		{
			printf("permission denied\n");
			return(0);
		}
		else
			close(fd);
	}
	return(1);
}


int chek_command(char **cmd_arg, char **envp)
{
    char *path = find_path(envp, cmd_arg[0]);
	if (path == NULL)
	{
		printf("command not found\n");
		return (0);
	}
    return (1);
}