/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:38:17 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/25 21:34:32 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
        free(temp->str);
        free(temp);
    }
}


void free_t_liste(t_list *var)
{
    t_list *temp;
    while (var != NULL)
    {
        temp = var;
        var = var->next;
        free(temp->content);
        free(temp);
    }
}