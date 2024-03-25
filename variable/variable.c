/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:37 by transfo           #+#    #+#             */
/*   Updated: 2024/03/25 18:28:57 by tburtin          ###   ########.fr       */
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


void remplir_liste(char **tab, t_list **liste)
{
    t_list *new;
    char **variable;
    int i = 0;
    
    while(tab[i] != NULL)
    {
	    variable = ft_split(tab[i], '=');
	    if(check_already_exist(variable[0], *liste) == 1)
		    edit_envp(variable[0], tab[i], liste);
	    else
	    {
		    new = ft_lstnew(tab[i]);
		    ft_lstadd_back(liste, new);
	    }
	    free_tab(variable);
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