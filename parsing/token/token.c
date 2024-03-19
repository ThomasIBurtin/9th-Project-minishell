/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:16:39 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/19 13:23:36 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


t_token	*ft_newtoken(char *str, t_variable *liste_variable)
{
	t_token	*new = (t_token *)malloc(sizeof(t_token));
	len_commande(str, liste_variable, new);
	create_commande(new, str, liste_variable);
	new->type = none;
	new->next = NULL;
	new->prev = NULL;
	return(new);
}


void create_commande(t_token *new, char *str, t_variable *liste_variable)
{
	int i = 0;
	int j = 0;
	
	while(str[i])
	{
		if(str[i] == 34)
		{
			i++;
			while(str[i] != 34)
				input_var(new, str, liste_variable, &i, &j);
			i++;
		}
		else if(str[i] == 39)
		{
			i++;
			while(str[i] != 39)
				new->str[j++] = str[i++];
			i++;
		}
		else
			input_var(new, str, liste_variable, &i, &j);
	}
	new->str[j] = '\0';
}


void add_back_front(t_token **liste_token, t_token *new)
{
    t_token *current;

    if (*liste_token == NULL)
	{
    	*liste_token = new;
		(*liste_token)->next = NULL;
	}
    else
    {
        current = *liste_token;
        while (current->next != NULL)
        	current = current->next;
        
        current->next = new;
        new->prev = current;
    }
}


t_type get_type_arg(t_token **liste_token)
{
	t_token *temp = *liste_token;
	int i = 1;

	while(temp)
	{
		if(temp->type == none)
		{
			if(temp->str[0] == '>' && temp->str[1] == '>')
				i = modife_liste(temp, append, liste_token);
			else if(temp->str[0] == '>')
				i = modife_liste(temp, outfile, liste_token);
			else if(temp->str[0] == '<' && temp->str[1] == '<')
				i = modife_liste(temp, here_doc,liste_token);
			else if(temp->str[0] == '<')
				i = modife_liste(temp, infile, liste_token);
			else if (temp->str[0] == '|')
			{
				if(temp->next == NULL || temp->prev == NULL)
					return(0);
				temp->type = pip;
			}
			else if (temp->prev == NULL || temp->prev->type != argument)
				temp->type = commande;
			else
				temp->type = argument;
		}
		if(i == 0)
			return(0);
		temp = temp->next;
	}
	return(1);
}


int modife_liste(t_token *current, t_type type, t_token **liste_token)
{
	t_token *temp = current;
	temp = current;

	if(current->next == NULL || current->next->str[0] == '>' || current->next->str[0] == '<' || current->next->str[0] == '|')
		return(0);
	else if(current->prev == NULL)
	{
		(*liste_token) = (*liste_token)->next;
		(*liste_token)->type = type;
		(*liste_token)->prev = NULL;
	}
	else
	{
		current = current->prev;
		current->next = temp->next;
		temp->next->prev = current;
		temp->next->type = type;
	}
	free(temp);
	return(1);
}