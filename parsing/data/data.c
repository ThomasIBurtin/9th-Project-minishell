/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:55:53 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/19 18:09:54 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


t_data *ft_newcmd(t_token *current)
{
	t_data *new = (t_data *)malloc(sizeof(t_data));
	int static position = 0;
	char static  *last_outfile = NULL;
	t_len len;

	new->next = NULL;
	new->prev = NULL;
	
	len_all_tab(current, &len, position);
	allocation_tab(len, new, position, current, last_outfile);
	input_all_tab(current, new);
	last_outfile = find_last_outfile(new->outfile);
	check_position(current, &position);
	return (new);
}


void len_all_tab(t_token *current, t_len *len, int position)
{
	init_compteurs(len);
	
	while(current != NULL && current->type != pip)
	{
		if(current->type == commande || current->type == argument)
			len->compteur_commande++;
		else if(current->type == outfile)
			len->compteur_outfile++;
		else if(current->type == append)
		{
			len->compteur_append++;
			len->compteur_outfile++;
		}
		else if(current->type == infile)
			len->compteur_infile++;
		else if(current->type == here_doc)
		{
			len->compteur_infile++;
			len->compteur_heredoc++;
		}
		current = current->next;
	}
}


void allocation_tab(t_len len, t_data *new, int position, t_token *current, char *last_outfile)
{
	int flag1 = 0;
	int flag2 = 0;
	if(len.compteur_outfile == 0)
	{
		len.compteur_outfile++;
		flag1 = 1;
	}
	if((position == 0 && len.compteur_infile == 0) || (position != 0))
	{
		len.compteur_infile++;
		flag2 = 1;
	}
	
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

	if(flag1 == 1 )
		algo_outfile(current, new);
	if(flag2 == 1)
		algo_infile(new, position, last_outfile);
}


void input_all_tab(t_token *current, t_data *new)
{
	t_len len;
	init_compteurs(&len);

	if((new->infile[0] != NULL) && (new->infile[0][0] >= 'a' && new->infile[0][0] <= 'z'))
		len.compteur_infile++;

	while(current != NULL && current->type != pip)
	{	
		if(current->type == commande || current->type == argument)
			len.compteur_commande = remplir_data(current->str, new->cmd_arg, len.compteur_commande);
		else if(current->type == append)
		{
			len.compteur_append = remplir_data(current->str, new->outfile_append, len.compteur_append);
			len.compteur_outfile = remplir_data(current->str, new->outfile, len.compteur_outfile);
		}
		else if(current->type == outfile)
			len.compteur_outfile = remplir_data(current->str, new->outfile, len.compteur_outfile);
		else if(current->type == here_doc)
		{
			len.compteur_heredoc = remplir_data(current->str, new->here_doc, len.compteur_heredoc);
			len.compteur_infile = remplir_data(current->str, new->infile, len.compteur_infile);
		}
		else if(current->type == infile)
			len.compteur_infile = remplir_data(current->str, new->infile, len.compteur_infile);
		current = current->next;
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