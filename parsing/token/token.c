/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:16:39 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/17 03:34:39 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


t_token	*ft_newtoken(char *str, t_variable *liste_variable)
{
	t_token	*new = (t_token *)malloc(sizeof(t_token));
	int len = len_commande(str, liste_variable);
	new->str = (char *)malloc(sizeof(char) * len + 1);
	create_commande(new, str, liste_variable, len);
	new->next = NULL;
	new->prev = NULL;
	return(new);
}


int len_commande(char *str, t_variable *liste_variable)
{
	int i = 0;
	int len = 0;
	
	while(str[i])
	{
		if(str[i] == 34)
		{
			i++;
			while(str[i] != 34)
				len += len_var(str, &i, liste_variable);
			i++;
		}
		else if(str[i] == 39)
		{
			i++;
			while(str[i] != 39)
			{
				i++;
				len++;
			}
			i++;
		}
		else
			len += len_var(str, &i, liste_variable);
	}
	return(len);
}


void create_commande(t_token *new, char *str, t_variable *liste_variable, int len)
{
	int i = 0;
	int j = 0;
	t_variable *temp;
	
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


t_type get_type_arg(t_token *token, char *str)
{
	if (str[0] == '>' && str[1] == '>' && str[2] == '\0')
		return (append);
	else if (str[0] == '>' && str[1] == '\0')
		return (trunc);
	else if (str[0] == '<' && str[1] == '<' && str[2] == '\0')
		return (here_doc);
	else if (str[0] == '<' && str[1] == '\0')
		return (infile);
	else if (str[0] == '|' && str[1] == '\0')
		return (pip);
	else if (token->prev == NULL || token->prev->type == pip)
		return (commande);
	else
		return (argument);
}