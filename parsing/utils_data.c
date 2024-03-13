/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:11:10 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/12 11:32:42 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data *algo_outfile(t_token *current, t_data *new)
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
	return(new);
}


t_data *algo_infile(t_data *new, int position, char *last_outfile)
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
	return(new);
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


t_data *algo_redirection(t_token *current, t_data *new, t_len *len)
{
	init_compteurs(len);

	if((new->infile[0] != NULL) && (new->infile[0][0] >= 'a' && new->infile[0][0] <= 'z'))
		len->compteur_infile++;

	while(current != NULL && current->type != pip)
	{	
		if(current->type == append)
		{
			len->compteur_outfile_append = remplir_data(current->next->str, new->outfile_append, len->compteur_outfile_append);
			len->compteur_outfile = remplir_data(current->next->str, new->outfile, len->compteur_outfile);
		}
		else if(current->type == trunc)
			len->compteur_outfile = remplir_data(current->next->str, new->outfile, len->compteur_outfile);
		else if(current->type == here_doc)
		{
			len->compteur_here_doc = remplir_data(current->next->str, new->here_doc, len->compteur_here_doc);
			len->compteur_infile = remplir_data(current->next->str, new->infile, len->compteur_infile);
		}
		else if(current->type == infile)
			len->compteur_infile = remplir_data(current->next->str, new->infile, len->compteur_infile);
		current = current->next;
	}
	return (new);
}


void init_compteurs(t_len *len)
{
	len->compteur_outfile_append = 0;
	len->compteur_outfile = 0;
	len->compteur_here_doc = 0;
	len->compteur_infile = 0;
}