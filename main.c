/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:33 by transfo           #+#    #+#             */
/*   Updated: 2024/03/06 19:06:05 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp) 
{
    t_programme programme;

    while(1)
    {
        init_data(&programme);
        if (parse(&programme) == 1)
        {
            //execution
        }
        free_programme(&programme);
    }
}
