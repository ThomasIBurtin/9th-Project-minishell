/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:53:15 by transfo           #+#    #+#             */
/*   Updated: 2024/03/18 20:53:17 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void len_commande(char *str, t_variable *liste_variable, t_token *new)
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
	new->str = (char *)malloc(sizeof(char) * len + 1);
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


int len_var(char *str, int *i, t_variable *liste_variable)
{
	int len = 0;
	char *strr;

	if(str[*i] == '$' && (str[*i+1] == ' ' || str[*i+1] == 34 || str[*i+1] == 39))
	{
		len++;
		*i+=1;
	}
	else if(str[*i] == '$')
	{
		*i+=1;
		strr = extracte_cle(str, i);
		const char *value = getenv(strr);
		if(value != NULL)
			len += ft_strlen(value);
		else
		{
			while(liste_variable)
			{
				if(compare(liste_variable->cle, strr) == 1)
					len += ft_strlen(liste_variable->valeur);
				liste_variable = liste_variable->next;
			}
		}
		//free(strr);
	}
	else
	{
		len++;
		*i+=1;
	}
	return(len);
}


void input_var(t_token *new, char *str, t_variable *liste_variable, int *i, int *j)
{
	char *strr;
	
	if(str[*i] == '$' && (str[*i+1] == ' ' || str[*i+1] == 34 || str[*i+1] == 39 || str[*i+1] == '\0'))
		new->str[(*j)++] = str[(*i)++];
	else if(str[*i] == '$')
	{
		int k = 0;
		*i+=1;
		strr = extracte_cle(str, i);
		const char *value = getenv(strr);
		if(value != NULL)
		{
			while(value[k])
			new->str[(*j)++] = value[k++];
		}
		else
		{
			while(liste_variable)
			{
				if(compare(liste_variable->cle, strr) == 1)
				{
					while(liste_variable->valeur[k])
					new->str[(*j)++] = liste_variable->valeur[k++];	
				}
				liste_variable = liste_variable->next;
			}
		}
		//free(strr);
	}
	else
		new->str[(*j)++] = str[(*i)++];	
}


char *extracte_cle(char *str, int *i)
{
	int compteur = 0;
	int save = *i;
	int j = 0;

	while(str[*i] && str[*i] != ' ' && str[*i] != 34 && str[*i] != 39)
	{
		*i+=1;
		compteur++;
	}
	char *result = (char *)malloc(sizeof(char) * compteur + 1);
	while(str[save] && str[save] != ' ' && str[save] != 34 && str[save] != 39)
		result[j++] = str[save++];
	result[j] = '\0';
	return(result);
}