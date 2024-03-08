/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:27 by transfo           #+#    #+#             */
/*   Updated: 2024/03/08 11:53:52 by transfo          ###   ########.fr       */
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

void test(t_programme *programme)
{
	    t_data *temp = *programme->liste_data;
    int i = 0;
    int j = 0;
    int k = 0;
    int f = 0;
    int m = 0;

    while(temp != NULL)
    {
        i = 0;
        j = 0;
        k = 0;
        f = 0;
        m = 0;
        printf("commande + arguments : ");
        while(temp->cmd_arg[i] != NULL)
        {
            printf("%s", temp->cmd_arg[i]);
            printf(" ");
            i++;
        }
        printf("\n");
        printf("outfile : ");
        while(temp->outfile[j] != NULL)
        {
            printf("%s", temp->outfile[j]);
            printf(" ");
            j++;
        }
        printf("\n");
        printf("outfile_append : ");
        while(temp->outfile_append[k] != NULL)
        {
            printf("%s", temp->outfile_append[k]);
            printf(" ");
            k++;
        }
        printf("\n");
        printf("infile : ");
        while(temp->infile[f] != NULL)
        {
            printf("%s", temp->infile[f]);
            printf(" ");
            f++;
        }
        printf("\n");
        printf("here_doc : ");
        while(temp->here_doc[m] != NULL)
        {
            printf("%s", temp->here_doc[m]);
            printf(" ");
            m++;
        }
        printf("\n");
        printf("\n");
        printf("\n");
        temp = temp->next;
    }
}