/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:40:23 by transfo           #+#    #+#             */
/*   Updated: 2024/03/12 11:33:09 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


void free_t_data(t_data *data)
{
    t_data *temp;
    while (data != NULL)
    {
        temp = data;
        data = data->next;
        free_tab(temp->cmd_arg);
        free_tab(temp->outfile);
        free_tab(temp->outfile_append);
        free_tab(temp->infile);
        free_tab(temp->here_doc);
        free(temp);
    }
}


void free_t_token(t_token *token)
{
    t_token *temp;
    while (token != NULL)
    {
        temp = token;
        token = token->next; 
        free(temp);
    }
}


void free_programme(t_programme *programme)
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
