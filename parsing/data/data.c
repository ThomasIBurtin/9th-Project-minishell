/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:55:53 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/14 21:59:08 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


t_data *ft_newcmd(t_token *current)
{
	t_data *new = (t_data *)malloc(sizeof(t_data));
	t_token *temp = current;
	int k = 0;
	int compteur = 0;

	if (new != NULL)
	{
		new->cmd_arg = NULL;
		new->outfile = NULL;
		new->outfile_append = NULL;
		new->infile = NULL;
		new->here_doc = NULL;
		new->next = NULL;
		new->prev = NULL;
	}

	while(temp != NULL && (temp->type == commande || temp->type == argument))
	{
		temp = temp->next;
		compteur++;
	}
	new->cmd_arg = (char **)malloc(sizeof(char *) * (compteur + 1));
	
	while(current != NULL && (current->type == commande || current->type == argument))
	{
		k = remplir_data(current->str, new->cmd_arg, k);
		current = current->next;
	}
	new->cmd_arg[k] = NULL;

	new = parse_redirection(current, new);
	if(new == 0)
		return(0);
	return (new);
}


t_data *parse_redirection(t_token *current, t_data *new)
{
	int static position = 0;
	char static  *last_outfile = NULL;
	int flag1 = 0;
	int flag2 = 0;
	t_len len;

	if(check_redirection(current, &len) == 1)
	{
		perror("no file after redirection ");
		free_tab(new->cmd_arg);
		free(new);
		position = 0;
		return(0);
	}
	if(len.compteur_outfile_append == 0 && len.compteur_outfile == 0)
	{
		flag1 = 1;
		len.compteur_outfile++;
	}
	if((position == 0 && len.compteur_infile == 0) || (position != 0))
	{
		flag2 = 1;
		len.compteur_infile++;
	}
	allocation_tab(len, new);
	if(flag1 == 1)
		new = algo_outfile(current, new);
	if(flag2 == 1)
		new = algo_infile(new, position, last_outfile);
		
	new = algo_redirection(current, new, &len);
	last_outfile = find_last_outfile(new->outfile);
	position++;

	int flag3 = 0;
	if (current == NULL)
		position = 0;	
	while(current != NULL)
	{
		if(current->type == commande)
			flag3 = 1;
		current = current->next;
	}
	if(flag3 == 0)
		position = 0;
	return (new);
}


int check_redirection(t_token *current, t_len *len)
{
	int flag = 0;
	
	init_compteurs(len);
	while(current != NULL && current->type != pip)
	{
		if(current->type == append)
		{
			if(current->next == NULL || current->next->type != argument)
				flag = 1;
			len->compteur_outfile_append++;
		}
		else if(current->type == trunc)
		{
			if(current->next == NULL || current->next->type != argument)
				flag = 1;
			len->compteur_outfile++;
		}
		else if(current->type == here_doc)
		{
			if(current->next == NULL || current->next->type != argument)
				flag = 1;
			len->compteur_here_doc++;
		}
		else if(current->type == infile)
		{
			if(current->next == NULL || current->next->type != argument)
				flag = 1;
			len->compteur_infile++;
		}
		current = current->next;
	}
	return(flag);
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