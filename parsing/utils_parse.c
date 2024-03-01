/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:11:10 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/01 15:14:13 by tburtin          ###   ########.fr       */
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

t_data *algo_infile(t_token *current, t_data *new, int position, char *last_outfile)
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

int remplir_data(int i, t_programme *programme, char **tab, int compteur)
{
	int j = 0;

	i = i + 1;
	tab[compteur] = (char *)malloc(sizeof(char) * (ft_strlen(programme->split_args[i]) + 1));
	while(programme->split_args[i][j])
	{
		tab[compteur][j] = programme->split_args[i][j];
		j++;
	}
	tab[compteur][j] = '\0';
	return (compteur + 1);
}

t_data *algo_redirection(int i, t_token *current, t_programme *programme, t_data *new)
{
	int compteur1 = 0;
	int compteur2 = 0;
	int compteur3 = 0;

	if((new->infile[0] != NULL) && (new->infile[0][0] >= 'a' && new->infile[0][0] <= 'z'))
		compteur3++;

	while(current != NULL && current->type != pip)
	{	
		if(programme->split_args[i][0] == '>' && programme->split_args[i][1] == '>')
		{
			compteur1 = remplir_data(i, programme, new->outfile_append, compteur1);
			compteur2 = remplir_data(i, programme, new->outfile, compteur2);
		}
		else if(programme->split_args[i][0] == '>')
			compteur2 = remplir_data(i, programme, new->outfile, compteur2);
		else if(programme->split_args[i][0] == '<')
			compteur3 = remplir_data(i, programme, new->infile, compteur3);
		current = current->next;
		i++;
	}
	return (new);
}

int compare(char *str, char *strr)
{
	int i = 0;
	
	if(ft_strlen(str) != ft_strlen(strr))
		return(0);
	while(str[i] && strr[i])
	{
		if(str[i] != strr[i])
			return(0);
		i++;
	}
	return(1);
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