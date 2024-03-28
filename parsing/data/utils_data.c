/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:11:10 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/28 10:54:54 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void bonus_len(t_len *len, int position)
{
	if(len->compteur_outfile == 0)
	{
		len->compteur_outfile++;
		len->flag1 = 1;
	}
	if((position == 0 && len->compteur_infile == 0) || (position != 0))
	{
		len->compteur_infile++;
		len->flag2 = 1;
	}
}


void algo_outfile(t_token *liste_token, t_data *new)
{
	while(liste_token)
	{
		if(liste_token->type == pip)
		{
			new->outfile[0] = ft_strdup("fd[1]");
			return;
		}
		liste_token = liste_token->next;
	}
	new->outfile[0] = ft_strdup("stdout");
}


void algo_infile(t_data *new, int position, char *last_outfile)
{
	if(position == 0)
		new->infile[0] = ft_strdup("stdin");
	else
	{
		if(ft_compare(last_outfile, "fd[1]") == 1)
			new->infile[0] = ft_strdup("fd[0]");
		else
			new->infile[0] = ft_strdup("empty");
	}
}


char *find_last_outfile(char **tab)
{
	int i = 0;

	while(tab[i+1] != NULL)
		i++;
	return (ft_strdup(tab[i]));
}


int remplir_data(char *str, char **tab, int compteur)
{
	tab[compteur] = ft_strdup(str);
	return (compteur + 1);
}


void check_position(t_token *liste_token, int *position)
{
	int flag = 0;	
	
	*position+=1;
	while(liste_token != NULL)
	{
		if(liste_token->type == commande)
			flag++;
		liste_token = liste_token->next;
	}
	if(flag < 2)
		*position = 0;
}


void init_compteurs(t_len *len)
{
	len->compteur_commande = 0;
	len->compteur_append = 0;
	len->compteur_outfile = 0;
	len->compteur_heredoc = 0;
	len->compteur_infile = 0;
	len->flag1 = 0;
	len->flag2 = 0;
}