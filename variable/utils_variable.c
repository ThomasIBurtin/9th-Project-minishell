/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:36:02 by transfo           #+#    #+#             */
/*   Updated: 2024/03/21 14:27:12 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int check_if_exsite(char *str, t_liste *liste_variable, int len_cle)
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


void replace_value(int index, t_liste *liste_variable, int len_valeur, char *str)
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
        liste_variable->valeur[j++] = str[i++];
    liste_variable->valeur[j] = '\0';
}


void add_back_frontss(t_liste **liste, t_liste *new)
{
    t_liste *current;

    if (*liste == NULL)
	{
    	*liste = new;
		(*liste)->next = NULL;
	}
    else
    {
        current = *liste;
        while (current->next != NULL)
        	current = current->next;
        
        current->next = new;
    }
}


t_liste		*new_variable(char *str, int len_cle, int len_valeur)
{
	int i = 0;
    int j = 0;
	t_liste	*new = (t_liste *)malloc(sizeof(t_liste));
    new->cle = (char *)malloc(sizeof(char) * len_cle + 1);
    new->valeur = (char *)malloc(sizeof(char) * len_valeur + 1);
	
	while(str[i] != '=')
	    new->cle[j++] = str[i++];
    new->cle[j] = '\0';
    i++;
    j = 0;
    while(str[i])
	    new->valeur[j++] = str[i++];
    new->valeur[j] = '\0';
	new->next = NULL;
    
	return(new);
}