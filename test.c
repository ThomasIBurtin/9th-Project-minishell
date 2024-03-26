/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:27 by transfo           #+#    #+#             */
/*   Updated: 2024/03/26 16:11:47 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test(t_programme *programme)
{
	t_data *temp = *programme->liste_data;
    t_list *temps = *programme->liste_variable;
    int i = 0;
    int j = 0;
    int k = 0;
    int f = 0;
    int m = 0;
    int a = 0;
    

    while(temp != NULL)
    {
        i = 0;
        j = 0;
        k = 0;
        f = 0;
        m = 0;
        printf("commande + arguments : ");
        while(temp->cmd_arg[i] != NULL)
        {
            printf("%s", temp->cmd_arg[i]);
            printf(" ");
            i++;
        }
        printf("\n");
        printf("outfile : ");
        while(temp->outfile[j] != NULL)
        {
            printf("%s", temp->outfile[j]);
            printf(" ");
            j++;
        }
        printf("\n");
        printf("outfile_append : ");
        while(temp->outfile_append[k] != NULL)
        {
            printf("%s", temp->outfile_append[k]);
            printf(" ");
            k++;
        }
        printf("\n");
        printf("infile : ");
        while(temp->infile[f] != NULL)
        {
            printf("%s", temp->infile[f]);
            printf(" ");
            f++;
        }
        printf("\n");
        printf("here_doc : ");
        while(temp->here_doc[m] != NULL)
        {
            printf("%s", temp->here_doc[m]);
            printf(" ");
            m++;
        }
        printf("\n");
        printf("\n");
        temp = temp->next;
    }
    while(temps)
    {
        printf("%s", temps->content);
        printf("\n");
        temps = temps->next;
    }
}