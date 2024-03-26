/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_ligne.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:38:55 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/26 16:41:15 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int chek_ligne(t_token *liste_token, t_data *liste_data, char **envp)
{
	int flag = 0;
	
	while(liste_data)
	{
		while(liste_token)
		{
			if(liste_token->type == infile)
			{
				if(chek_infile(liste_token->str) == 0)
					flag = 1;
			}
			else if(liste_token->type == outfile || liste_token->type == append)
			{
				if(chek_outfile(liste_token) == 0)
					flag = 1;
			}
			liste_token = liste_token->next;
		}
		if((chek_command(liste_data->cmd_arg, envp) == 0) || (flag == 1))
			printf("delete this data");
		liste_data = liste_data->next;
	}
	return(1);
}