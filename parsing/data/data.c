/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:55:53 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/25 18:23:46 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


t_data *ft_newcmd(t_token *liste_token)
{
	t_data *new = (t_data *)malloc(sizeof(t_data));
	int static position = 0;
	char static  *last_outfile = NULL;
	t_len len;

	len_all_tab(liste_token, &len, position);
	allocation_tab(len, new);
	
	if(len.flag1 == 1 )
		algo_outfile(liste_token, new);
	if(len.flag2 == 1)
		algo_infile(new, position, last_outfile);
		
	input_all_tab(liste_token, new);
	last_outfile = find_last_outfile(new->outfile);
	check_position(liste_token, &position);
	return (new);
}


void len_all_tab(t_token *liste_token, t_len *len, int position)
{
	init_compteurs(len);
	
	while(liste_token != NULL && liste_token->type != pip)
	{
		if(liste_token->type == commande || liste_token->type == argument)
			len->compteur_commande++;
		else if(liste_token->type == outfile)
			len->compteur_outfile++;
		else if(liste_token->type == append)
		{
			len->compteur_append++;
			len->compteur_outfile++;
		}
		else if(liste_token->type == infile)
			len->compteur_infile++;
		else if(liste_token->type == here_doc)
		{
			len->compteur_infile++;
			len->compteur_heredoc++;
		}
		liste_token = liste_token->next;
	}
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


void allocation_tab(t_len len, t_data *new)
{
	new->cmd_arg = ft_calloc(sizeof(char **), len.compteur_commande + 1);;
	new->outfile =  ft_calloc(sizeof(char **), len.compteur_append + len.compteur_outfile + 1);
	new->outfile_append = ft_calloc(sizeof(char **), len.compteur_append + 1);
	new->infile = ft_calloc(sizeof(char **), len.compteur_heredoc + len.compteur_infile + 1);
	new->here_doc = ft_calloc(sizeof(char **), len.compteur_heredoc + 1);

	new->cmd_arg[len.compteur_commande] = NULL;
	new->outfile[len.compteur_append + len.compteur_outfile] = NULL;
	new->outfile_append[len.compteur_append] = NULL;
	new->infile[len.compteur_heredoc + len.compteur_infile] = NULL;
	new->here_doc[len.compteur_heredoc] = NULL;
}


void input_all_tab(t_token *liste_token, t_data *new)
{
	t_len len;		
	init_compteurs(&len);

	if((new->infile[0] != NULL) && (new->infile[0][0] >= 'a' && new->infile[0][0] <= 'z'))
		len.compteur_infile++;

	while(liste_token != NULL && liste_token->type != pip)
	{	
		if(liste_token->type == commande || liste_token->type == argument)
			len.compteur_commande = remplir_data(liste_token->str, new->cmd_arg, len.compteur_commande);
		else if(liste_token->type == append)
		{
			len.compteur_append = remplir_data(liste_token->str, new->outfile_append, len.compteur_append);
			len.compteur_outfile = remplir_data(liste_token->str, new->outfile, len.compteur_outfile);
		}
		else if(liste_token->type == outfile)
			len.compteur_outfile = remplir_data(liste_token->str, new->outfile, len.compteur_outfile);
		else if(liste_token->type == here_doc)
		{
			len.compteur_heredoc = remplir_data(liste_token->str, new->here_doc, len.compteur_heredoc);
			len.compteur_infile = remplir_data(liste_token->str, new->infile, len.compteur_infile);
		}
		else if(liste_token->type == infile)
			len.compteur_infile = remplir_data(liste_token->str, new->infile, len.compteur_infile);
		liste_token = liste_token->next;
	}
}


void add_back_fronts(t_data **liste_data, t_data *new)
{
    t_data *current;

    if (*liste_data == NULL)
	{
    	*liste_data = new;
		(*liste_data)->next = NULL;
	}
    else
    {
        current = *liste_data;
        while (current->next != NULL)
        	current = current->next;
        current->next = new;
        new->prev = current;
    }
}