/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_ligne.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:38:55 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/27 21:23:26 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int chek_ligne(t_token *liste_token, t_data **liste_data, char **envp)
{
	t_data *current_data = *liste_data;
	
	while(current_data)
	{
		while(liste_token)
		{
			if(liste_token->type == infile)
			{
				if(chek_infile(liste_token->str) == 0)
					current_data->commande_correct = 1;
			}
			else if(liste_token->type == outfile || liste_token->type == append)
			{
				if(chek_outfile(liste_token) == 0)
					current_data->commande_correct = 1;
			}
			liste_token = liste_token->next;
		}
		if(chek_command(current_data->cmd_arg, envp) == 0)
			current_data->commande_correct = 1;
		current_data = current_data->next;
	}
	delete_wrong_data(liste_data);
	return(1);
}


void delete_wrong_data(t_data **liste_data)
{
	t_data *current_data = *liste_data;
	t_data *temp;
	t_data *temp2;

	while(current_data)
	{
		if(current_data->commande_correct == 1)
		{
			if(current_data->next != NULL)
				(*liste_data)->prev = NULL;
			temp = current_data;
			free_onedata(temp);
			*liste_data = current_data->next;
		}
		else if(current_data->commande_correct == 0 && current_data->next != NULL && current_data->next->commande_correct == 1)
		{
			temp2 = current_data;
			temp = current_data->next;
			if (temp->next != NULL) 
			{
				(*liste_data)->prev = NULL;
				free_onedata(temp);
				current_data = current_data->next;
			}
			free_onedata(temp2);
			*liste_data = current_data->next;
		}
		current_data = current_data->next;
	}
}