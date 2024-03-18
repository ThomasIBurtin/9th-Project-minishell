/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:11:10 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/18 20:16:55 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void allocation_tab(t_len len, t_data *new)
{
	new->cmd_arg = ft_calloc(sizeof(char **), len.compteur_commande + 1);;
	new->outfile =  ft_calloc(sizeof(char **), len.compteur_append + len.compteur_outfile + 1);
	new->outfile_append = ft_calloc(sizeof(char **), len.compteur_append + 1);
	new->infile = ft_calloc(sizeof(char **), len.compteur_heredoc + len.compteur_infile + 1);
	new->here_doc = ft_calloc(sizeof(char **), len.compteur_heredoc + 1);

	new->here_doc[len.compteur_append] = NULL;
	new->outfile[len.compteur_append + len.compteur_outfile] = NULL;
	new->outfile_append[len.compteur_append] = NULL;
	new->infile[len.compteur_heredoc + len.compteur_infile] = NULL;
	new->here_doc[len.compteur_heredoc] = NULL;
}


void algo_outfile(t_token *current, t_data *new)
{
	int flag = 0;

	while(current != NULL)
	{
		if(current->type == pip)
		{
			flag = 1;
			new->outfile[0] = ft_strdup("fd[1]");
			break;
		}
		current = current->next;
	}
	if(flag == 0)
		new->outfile[0] = ft_strdup("stdout");
}


void algo_infile(t_data *new, int position, char *last_outfile)
{
	if(position == 0)
		new->infile[0] = ft_strdup("stdin");
	else
	{
		if(compare(last_outfile, "fd[1]") == 1)
			new->infile[0] = ft_strdup("fd[0]");
		else
			new->infile[0] = ft_strdup(last_outfile);
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


void init_compteurs(t_len *len)
{
	len->compteur_commande = 0;
	len->compteur_append = 0;
	len->compteur_outfile = 0;
	len->compteur_heredoc = 0;
	len->compteur_infile = 0;
}