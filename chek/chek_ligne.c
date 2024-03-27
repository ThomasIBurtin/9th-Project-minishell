/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_ligne.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:38:55 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/27 17:33:50 by transfo          ###   ########.fr       */
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

	current_data = *liste_data;

	while(current_data)
	{
		printf("%d", current_data->commande_correct);
		current_data = current_data->next;
	}
	return(1);
}