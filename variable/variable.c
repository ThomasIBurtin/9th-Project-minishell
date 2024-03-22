/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:37 by transfo           #+#    #+#             */
/*   Updated: 2024/03/22 12:13:55 by transfo          ###   ########.fr       */
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


void remplir_liste(char **tab, t_liste **liste)
{
    t_liste *new;
    int i = 0;
    int j;
    int len_cle;
    int len_valeur;
    int index;

    while(tab[i])
    {
        j = 0;
        len_cle = 0;
        len_valeur = 0;
        while(tab[i][j++] != '=')
            len_cle++;
        while(tab[i][j++])
            len_valeur++;
        index = check_if_exsite(tab[i], *liste, len_cle);
        if(index != -1)
            replace_value(index, *liste, len_valeur, tab[i]);
        else
        {
            new = new_element(tab[i], len_cle, len_valeur);
            add_back_frontss(liste, new);
        }
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