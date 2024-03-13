/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:36:02 by transfo           #+#    #+#             */
/*   Updated: 2024/03/13 17:26:56 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int algo_var(char **cmd_arg)
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