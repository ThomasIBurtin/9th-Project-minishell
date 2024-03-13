/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:16:39 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/13 17:15:13 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


int variable_value(t_token *new, char *str, t_variable *liste_variable)
{
	int i = 0;
	int j = 1;
	char *strr = (char *)malloc(sizeof(char) * ft_strlen(str) - 1);
	
	while(str[j])
	{
		strr[i] = str[j];
		i++;
		j++;
	}
	strr[j] = '\0';

	while(liste_variable)
	{
		if(compare(liste_variable->cle, strr) == 1)
		{
			new->str = ft_strdup(liste_variable->valeur);
			return(1);
		}
		liste_variable = liste_variable->next;
	}
	perror("variable ");
	return(0);
}


t_token		*ft_newtoken(char *str, t_variable *liste_variable)
{
	t_token	*new = (t_token *)malloc(sizeof(t_token));

	if(str[0] == '$')
	{
		// cherche dans env
		if(variable_value(new, str, liste_variable) == 0)
			return(0);
	}
	else
		new->str = ft_strdup(str);
		
	new->next = NULL;
	new->prev = NULL;
	return(new);
}