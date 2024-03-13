/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:36:02 by transfo           #+#    #+#             */
/*   Updated: 2024/03/13 17:43:51 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int check_if_exsite(char *str, t_variable *liste_variable, int len_cle)
{
    int i = 0;
    char cle[len_cle];
    
    while(str[i] != '=')
    {
        cle[i] = str[i];
        i++;
    }
    cle[i] = '\0';
    i = 0;
    while(liste_variable)
    {
        if(compare(liste_variable->cle, cle) == 1)
            return(i);
        liste_variable = liste_variable->next;
        i++;
    }
    return(-1);
}


void replace_value(int index, t_variable *liste_variable, int len_valeur, char *str)
{
    int i = 0;
    int j = 0;
    
    while(index != 0)
    {
        liste_variable = liste_variable->next;
        index--;
    }
    free(liste_variable->valeur);
    liste_variable->valeur = (char *)malloc(sizeof(char) * len_valeur + 1);

    while(str[i] != '=')
        i++;
    i++;
    while(str[i])
    {
        liste_variable->valeur[j] = str[i];
        i++;
        j++;
    }
    liste_variable->valeur[j] = '\0';
}


void add_back_frontss(t_variable **liste_variable, t_variable *new)
{
    t_variable *current;

    if (*liste_variable == NULL)
	{
    	*liste_variable = new;
		(*liste_variable)->next = NULL;
	}
    else
    {
        current = *liste_variable;
        while (current->next != NULL)
        	current = current->next;
        
        current->next = new;
    }
}


t_variable		*new_variable(char *str, int len_cle, int len_valeur)
{
	int i = 0;
    int j = 0;
	t_variable	*new = (t_variable *)malloc(sizeof(t_variable));

    new->cle = (char *)malloc(sizeof(char) * len_cle + 1);
    new->valeur = (char *)malloc(sizeof(char) * len_valeur + 1);
	
	while(str[i] != '=')
	{
		new->cle[j] = str[i];
        i++;
        j++;
	}
    
    new->cle[j] = '\0';
    i++;
    j = 0;
    
    while(str[i])
	{
		new->valeur[j] = str[i];
        i++;
        j++;
	}
    new->valeur[j] = '\0';
	new->next = NULL;
    
	return(new);
}