/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:40:23 by transfo           #+#    #+#             */
/*   Updated: 2024/03/25 18:11:48 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_programme(t_programme *programme, char **envp)
{
    programme->liste_variable = (t_list **)malloc(sizeof(t_list*));
    programme->liste_env = (t_list **)malloc(sizeof(t_list*));
    *programme->liste_variable = NULL;
    *programme->liste_env = NULL;
    create_lst_envp(envp, programme->liste_env);
}

void create_lst_envp(char **envp, t_list **liste)
{
	int		i;
	t_list	*new_node;

	i = 0;
	while (envp[i])
	{
		new_node = ft_lstnew(envp[i]);
		ft_lstadd_back(liste, new_node);
		i++;
	}
}


void init_data(t_programme *programme)
{
    programme->args = readline("\nprompt > ");
    printf("\n");
    add_history(programme->args);
    programme->split_args = NULL;
    programme->liste_token = (t_token **)malloc(sizeof(t_token*));
    programme->liste_data = (t_data **)malloc(sizeof(t_data*));
    *programme->liste_token = NULL;
    *programme->liste_data = NULL;
}


void free_data(t_programme *programme)
{
    free(programme->args);
    
    if (programme->split_args != NULL)
        free_tab((char **)programme->split_args);
    
    if (*programme->liste_token != NULL)
        free_t_token(*programme->liste_token);
    free(programme->liste_token);
    
    if (*programme->liste_data != NULL)
        free_t_data(*programme->liste_data);
    free(programme->liste_data);
}

void free_programme(t_programme *programme)
{
    if (*programme->liste_variable != NULL)
        free_t_liste(*programme->liste_variable);
    free(programme->liste_variable);

    free_t_liste(*programme->liste_env);
    free(programme->liste_env);
}
