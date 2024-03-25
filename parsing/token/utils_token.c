/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:53:15 by transfo           #+#    #+#             */
/*   Updated: 2024/03/25 21:20:18 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int len_commande(char *str, t_programme *programme)
{
	int i = 0;
	int len = 0;
	
	while(str[i])
	{
		if(str[i] == 34)
		{
			i++;
			while(str[i] != 34)
				len += len_var(str, &i, programme);
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
			len += len_var(str, &i, programme);
	}
	return(len);
}


int len_var(char *str, int *i, t_programme *programme)
{
	int len = 0;

	if(str[*i] == '$' && (str[*i+1] == ' ' || str[*i+1] == 34 || str[*i+1] == 39))
	{
		len++;
		*i+=1;
	}
	else if(str[*i] == '$')
	{
		*i+=1;
		char *cle = extracte_cle(str, i);
		char *env_value = find_value(*programme->liste_env, cle);
		char *variable_value = find_value(*programme->liste_variable, cle);
		if(env_value != NULL)
			len += ft_strlen(env_value);
		else if(variable_value != NULL)
			len+=ft_strlen(variable_value);
		free(cle);
	}
	else
	{
		len++;
		*i+=1;
	}
	return(len);
}


void input_var(t_token *new, char *str, t_programme *programme, int *i, int *j)
{
	if(str[*i] == '$' && (str[*i+1] == ' ' || str[*i+1] == 34 || str[*i+1] == 39 || str[*i+1] == '\0'))
		new->str[(*j)++] = str[(*i)++];
	else if(str[*i] == '$')
	{
		int k = 0;
		*i+=1;
		char *cle = extracte_cle(str, i);
		char *env_value = find_value(*programme->liste_env, cle);
		char *variable_value = find_value(*programme->liste_variable, cle);
		if(env_value != NULL)
		{
			while(env_value[k])
				new->str[(*j)++] = env_value[k++];
		}
		else if(variable_value != NULL)
		{
			while(variable_value[k])
				new->str[(*j)++] = variable_value[k++];
		}
		free(cle);
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


char *find_value(t_list *list, char *cle)
{
	char **tab_key_value;
	
	while(list)
	{
		tab_key_value = ft_split(list->content, '=');
		if(ft_compare(tab_key_value[0], cle) == 1)
			return(tab_key_value[1]);
		free_tab(tab_key_value);
		list = list->next;
	}
	return(NULL);
}
