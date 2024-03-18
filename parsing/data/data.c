/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:55:53 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/18 20:57:22 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


t_data *ft_newcmd(t_token *current)
{
	t_data *new = (t_data *)malloc(sizeof(t_data));
	int static position = 0;
	char static  *last_outfile = NULL;
	int flag;
	t_len len;

	new->next = NULL;
	new->prev = NULL;
	
	flag = len_all_tab(current, &len, position);
	allocation_tab(len, new);
	if(flag == 1 || flag == 3)
		algo_outfile(current, new);
	if(flag == 2 || flag == 3)
		algo_infile(new, position, last_outfile);
	input_all_tab(current, new);
	last_outfile = find_last_outfile(new->outfile);
	position++;
	int flag3 = 0;	
	while(current != NULL)
	{
		if(current->type == commande)
			flag3++;
		current = current->next;
	}
	if(flag3 < 2)
		position = 0;
	return (new);
}


int len_all_tab(t_token *current, t_len *len, int position)
{
	int flag = 0;
	init_compteurs(len);
	
	while(current != NULL && current->type != pip)
	{
		if(current->type == commande || current->type == argument)
			len->compteur_commande++;
		else if(current->type == trunc)
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
	if(len->compteur_outfile == 0)
	{
		len->compteur_outfile++;
		flag = 1;
	}
	if((position == 0 && len->compteur_infile == 0) || (position != 0))
	{
		if(flag = 1)
			return (3);
		return(2);
		len->compteur_infile++;
	}
	return(flag);
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
		else if(current->type == trunc)
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