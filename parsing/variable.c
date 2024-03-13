/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:37 by transfo           #+#    #+#             */
/*   Updated: 2024/03/13 17:14:06 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


void remplir_var(char **cmd_arg, t_programme *programme)
{
    t_variable *new;
    int i = 0;
    int j = 0;
    int len_cle = 0;
    int len_valeur = 0;
    int index;

    while(cmd_arg[i])
    {
        j = 0;
        len_cle = 0;
        len_valeur = 0;
        while(cmd_arg[i][j] != '=')
        {
            len_cle++;
            j++;
        }
        j++;
        while(cmd_arg[i][j])
        {
            len_valeur++;
            j++;
        }
        index = check_if_exsite(cmd_arg[i], *programme->liste_variable, len_cle);
        if(index != -1)
            replace_value(index, *programme->liste_variable, len_valeur, cmd_arg[i]);
        else
        {
            new = new_variable(cmd_arg[i], len_cle, len_valeur);
            add_back_frontss(programme->liste_variable, new);
        }
        i++;
    }
}


int variable(t_programme *programme)
{
    t_data *liste_data = *programme->liste_data;
    int index;
    
    if(ft_strlen(programme->args) < 1)
        return(0);

    if(ft_strchr(liste_data->cmd_arg[0], '=') == 0)
        return(1);
    
    index = algo_var(liste_data->cmd_arg);
    if(index == -1)
        remplir_var(liste_data->cmd_arg, programme);
    else
        {
            liste_data->cmd_arg = replace_commande(liste_data->cmd_arg, index);
            return(1);
        }
    return(0);   
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