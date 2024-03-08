/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:16:39 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/06 18:55:14 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_type get_type_arg(t_token *token, char *str)
{
	if (str[0] == '>' && str[1] == '\0')
		return (trunc);
	else if (str[0] == '>' && str[1] == '>' && str[2] == '\0')
		return (append);
	else if (str[0] == '<' && str[1] == '\0')
		return (input);
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


t_token		*ft_newtoken(char *str)
{
	int i = 0;
	t_token	*new = (t_token *)malloc(sizeof(t_token));
	
	while(str[i])
	{
		new->str[i] = str[i];
		i++;
	}
	new->str[i] = '\0';
	new->next = NULL;
	new->prev = NULL;
	return(new);
}