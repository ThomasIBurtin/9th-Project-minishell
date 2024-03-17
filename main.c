/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:33 by transfo           #+#    #+#             */
/*   Updated: 2024/03/17 00:25:23 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp) 
{
    t_programme programme;
    programme.liste_variable = (t_variable **)malloc(sizeof(t_variable*));
    *programme.liste_variable = NULL;
    
    while(1)
    {
        init_data(&programme);
        if (parse(&programme) == 1 && variable(&programme) == 1)
        {
            //execution
        }
        test(&programme);
        free_programme(&programme);
    }
    
    if (*programme.liste_variable != NULL)
        free_t_variable(*programme.liste_variable);
    free(programme.liste_variable);
    
}
