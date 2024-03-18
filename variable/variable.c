/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:37 by transfo           #+#    #+#             */
/*   Updated: 2024/03/18 20:49:43 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int variable(t_programme *programme)
{
    t_data *liste_data = *programme->liste_data;
    int index;

    if(ft_strchr(liste_data->cmd_arg[0], '=') == 0)
        return(1);
    
    index = check_ifonly_var(liste_data->cmd_arg);
    if(index == -1)
        remplir_liste_var(liste_data->cmd_arg, programme);
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



void remplir_liste_var(char **cmd_arg, t_programme *programme)
{
    t_variable *new;
    int i = 0;
    int j;
    int len_cle;
    int len_valeur;
    int index;

    while(cmd_arg[i])
    {
        j = 0;
        len_cle = 0;
        len_valeur = 0;
        while(cmd_arg[i][j++] != '=')
            len_cle++;
        j++;
        while(cmd_arg[i][j++])
            len_valeur++;
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


char **replace_commande(char **cmd_arg, int index)
{
    int save = index;
    int i = 0;
    int j = 0;
    
    while(cmd_arg[index])
    {
        i++;
        index++;
    }
    char **result = (char **)malloc(sizeof(char *) * i + 1);
    while(cmd_arg[save])
    {
        result[j] = ft_strdup(cmd_arg[save]);
        j++;
        save++;
    }
    result[j] = NULL;
    free_tab(cmd_arg);
    return(result);
}