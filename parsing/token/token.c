/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:16:39 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/15 13:45:58 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


t_token	*ft_newtoken(char *str, t_variable *liste_variable)
{
	t_token	*new = (t_token *)malloc(sizeof(t_token));
	create_commande(new, str, liste_variable);
	new->next = NULL;
	new->prev = NULL;
	return(new);
}


void create_commande(t_token *new, char *str, t_variable *liste_variable)
{
	int i = 0;
	t_variable *temp;
	int len = ft_strlen_modife(str);
	char *strr;
	
	while(str[i])
	{
		temp = liste_variable;
		if(ft_strnchr(str, '$', i) == 1)
		{
			strr = extract(str, &i);
			const char *value = getenv(strr);
			if(value != NULL)
				len += ft_strlen(value);
			else
			{
				while(temp)
				{
					if(compare(temp->cle, strr) == 1)
						len += ft_strlen(temp->valeur);
					temp = temp->next;
				}
			}
		}
		else	
			break;
	}
	if(wich_quotes(str) != 0)
		len = len - 2;
	new->str = (char *)malloc(sizeof(char) * len + 1);
	remplir_commande(new, str, liste_variable, wich_quotes(str));
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