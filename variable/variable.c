/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:37 by transfo           #+#    #+#             */
/*   Updated: 2024/03/27 17:18:58 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int variable(t_programme *programme)
{
    t_data *liste_data = *programme->liste_data;
    int index;

    if(liste_data->cmd_arg[0] == NULL || ft_strchr(liste_data->cmd_arg[0], '=') == 0)
        return(1);
    index = check_ifonly_var(liste_data->cmd_arg);
    if(index == -1)
        remplir_liste(liste_data->cmd_arg, programme->liste_variable);
    else
    {
        liste_data->cmd_arg = replace_commande(liste_data->cmd_arg, index);
        return(1);
    }
    return(0);   
}


int check_ifonly_var(char **cmd_arg)
{
    int i = 0;
    while(cmd_arg[i])
    {
        if(ft_strchr(cmd_arg[i], '=') == 0)
            return(i);
        i++;
    }
    return(-1);
}


void remplir_liste(char **tab, t_list **list)
{
    t_list *new;
    char **variable_split;
    int index;
    int i = 0;
    
    while(tab[i] != NULL)
    {
	    variable_split = ft_split(tab[i], '=');
        index = check_already_exist(variable_split[0], *list);
	    if(index != -1)
            replace_var(index, tab[i], list);
	    else
	    {
		    new = ft_lstnew(tab[i]);
		    ft_lstadd_back(list, new);
	    }
        free_tab(variable_split);
        i++;
    }
}


char **replace_commande(char **cmd_arg, int index)
{
    int save = index;
    int compteur = 0;
    int i = 0;
    
    while(cmd_arg[save])
    {
        compteur++;
        save++;
    }
    char **result = (char **)malloc(sizeof(char *) * compteur + 1);
    while(cmd_arg[index])
    {
        result[i] = ft_strdup(cmd_arg[index]);
        i++;
        index++;
    }
    result[i] = NULL;
    free_tab(cmd_arg);
    return(result);
}