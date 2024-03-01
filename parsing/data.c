/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:55:53 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/01 15:13:36 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void allocation_tab(t_len len, t_data *new)
{
	new->outfile =  ft_calloc(sizeof(char **), len.compteur1 + len.compteur1 + 1);
	new->outfile_append = ft_calloc(sizeof(char **), len.compteur1 + 1);;
	new->infile = ft_calloc(sizeof(char **), len.compteur3 + 1);

	new->outfile[len.compteur1 + len.compteur2] = NULL;
	new->outfile_append[len.compteur1] = NULL;
	new->infile[len.compteur3] = NULL;
}

int check_redirection(t_token *current, t_programme *programme, int i, t_len *len)
{
	int flag = 0;
	len->compteur1 = 0;
	len->compteur2 = 0;
	len->compteur3 = 0;
	
	while(current != NULL && current->type != pip)
	{
		if(programme->split_args[i][0] == '>' && programme->split_args[i][1] == '>')
		{
			if(current->next == NULL || current->next->type != argument)
				flag = 1;
			len->compteur1++;
		}
		else if(programme->split_args[i][0] == '>')
		{
			if(current->next == NULL || current->next->type != argument)
				flag = 1;
			len->compteur2++;
		}
		else if(programme->split_args[i][0] == '<')
		{
			if(current->next == NULL || current->next->type != argument)
				flag = 1;
			len->compteur3++;
		}
		i++;
		current = current->next;
	}
	return(flag);
}



t_data *parse_redirection(int i, t_token *current, t_programme *programme, t_data *new)
{
	int static position = 0;
	char static  *last_outfile = NULL;
	int flag1 = 0;
	int flag2 = 0;
	t_len len;

	if(check_redirection(current, programme, i, &len) == 1)
	{
		perror("no file after redirection ");
		free_tab(new->cmd_arg);
		free(new);
		position = 0;
		return(0);
	}
	
	if(len.compteur1 == 0 && len.compteur2 == 0)
	{
		flag1 = 1;
		len.compteur2++;
	}

	if((position == 0 && len.compteur3 == 0) || (position != 0))
	{
		flag2 = 1;
		len.compteur3++;
	}

	allocation_tab(len, new);
	
	if(flag1 == 1)
		new = algo_outfile(current, new);
	
	if(flag2 == 1)
		new = algo_infile(current, new, position, last_outfile);
	
	new = algo_redirection(i, current, programme, new);
	
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

t_data *ft_newcmd(t_programme *programme, int i)
{
	t_data *new;
	new = (t_data *)malloc(sizeof(t_data));

	if (new != NULL)
	{
		new->cmd_arg = NULL;
		new->outfile = NULL;
		new->outfile_append = NULL;
		new->infile = NULL;
		new->next = NULL;
	}
	
	t_token *current = *programme->liste_token;
	t_token *current2 = *programme->liste_token;
	int j = 0;
	int sav = i;
	int k = 0;
	int compteur = 0;

	while(sav > 0)
	{
		current = current->next;
		current2 = current2->next;
		sav--;
	}

	while(current2 != NULL && (current2->type == commande || current2->type == argument))
	{
		current2 = current2->next;
		compteur++;
	}
	
	new->cmd_arg = (char **)malloc(sizeof(char *) * (compteur + 1));
	
	while(current != NULL && (current->type == commande || current->type == argument))
	{
		k = remplir_data(i-1, programme, new->cmd_arg, k);
		current = current->next;
		i++;
	}
	new->cmd_arg[k] = NULL;

	new = parse_redirection(i, current, programme, new);
	
	if(new == 0)
		return(0);
		
	return (new);
}