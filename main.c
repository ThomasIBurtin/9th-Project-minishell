/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:33 by transfo           #+#    #+#             */
/*   Updated: 2024/03/21 14:10:00 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp) 
{
    t_programme programme;
    init_programme(&programme, envp);
    
    while(1)
    {
        init_data(&programme);
        if(parse(&programme) == 1 && variable_env(&programme) == 1)
        {
            //execution
        }
        test(&programme);
        free_data(&programme);
    }
    free_programme(&programme);
}
