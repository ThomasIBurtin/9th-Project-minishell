/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_ligne.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:38:55 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/28 11:49:13 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int chek_ligne(t_token *liste_token, t_data **liste_data, char **envp)
{
	t_data *current_data = *liste_data;
	
	while(current_data)
	{
		while(liste_token && liste_token->type != pip)
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
		if(liste_token != NULL)
			liste_token = liste_token->next;
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
			temp = current_data;
			free_onedata(temp);
			*liste_data = current_data->next;
			modife_infile(current_data);
		}
		else if(current_data->commande_correct == 0 && current_data->next != NULL && current_data->next->commande_correct == 1)
		{
			temp2 = current_data;
			temp = current_data->next;
			if (temp->next != NULL) 
			{
				free_onedata(temp);
				current_data = current_data->next;
			}
			free_onedata(temp2);
			*liste_data = current_data->next;
		}
		current_data = current_data->next;
	}
}


void modife_infile(t_data *current_data)
{
	if(current_data->next && current_data->next->commande_correct == 0)
	{
		current_data = current_data->next;
		if(ft_compare(current_data->infile[0], "fd[0]") == 1)
		{
			free(current_data->infile[0]);
			current_data->infile[0] = ft_strdup("empty");
		}
	}
}