/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:53:15 by transfo           #+#    #+#             */
/*   Updated: 2024/03/14 22:01:12 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


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
			while(temp)
			{
				if(compare(temp->cle, strr) == 1)
					len += ft_strlen(temp->valeur);
				temp = temp->next;
			}
		}
		else	
			break;
	}
	if(wich_quotes(str) != 0)
		len = len - 2;

	new->str = (char *)malloc(sizeof(char) * len + 1 -2);
	remplir_commande(new, str, liste_variable, wich_quotes(str));
}


char *extract(char *str, int *i)
{
	int len = 0;
	int j = *i;
	int k = 0;

	while(str[j])
	{
		if(len != 0)
			break;
		if(str[j] == '$')
		{
			j++;
			while(str[j] && str[j] != ' ' && str[j] != 34 && str[j] != 39)
			{
				j++;
				len++;
			}
		}
		j++;
	}
	char *result = (char *)malloc(sizeof(char) * len + 1);
	while(str[*i])
	{
		if(str[*i] == '$')
		{
			*i+=1;
			while(str[*i] && str[*i] != ' ' && str[*i] != 34 && str[*i] != 39)
			{
				result[k] = str[*i];
				*i+=1;
				k++;
			}
			if(k != 0)
			{
				result[k] = '\0';
				return(result);
			}
		}
		*i+=1;
	}
	return(0);
}


void remplir_commande(t_token *new, char *str, t_variable *liste_variable, int flag)
{
	int i = 0;
	int j = 0;
	t_variable *temp;
	
	while (str[i])
	{
		if(str[i + 1] && str[i + 1] != ' ' && str[i] == '$' && flag != 2)
		{
			char *strr = extract(str, &i);
			temp = liste_variable;
			while (temp)
			{
				if (compare(temp->cle, strr) == 1)
				{
					int k = 0;
					while (temp->valeur[k])
						new->str[j++] = temp->valeur[k++];
				}
				temp = temp->next;
			}
		} 
		else
		{
			if((flag == 1 || flag == 2) && i > 0 && str[i+1] != '\0')
				new->str[j++] = str[i];
			else if(flag != 1 && flag != 2)
    			new->str[j++] = str[i];
			i++;
		}
	}
	new->str[j] = '\0';
}


int wich_quotes(char *str)
{
	if(str[0] == 39 && str[ft_strlen(str) - 1] == 39)
		return(2);
	else if(str[0] == 34 && str[ft_strlen(str) - 1] == 34)
		return(1);
	else
		return(0);
}
