/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:33 by transfo           #+#    #+#             */
/*   Updated: 2024/03/27 17:34:27 by transfo          ###   ########.fr       */
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
        if(parse(&programme) == 1 && variable(&programme) == 1)
        {
            chek_ligne(*programme.liste_token, programme.liste_data, envp);
            //execution
        }
        test(&programme);
        free_data(&programme);
    }
    free_programme(&programme);
}
