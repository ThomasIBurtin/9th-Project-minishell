/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:18:00 by transfo           #+#    #+#             */
/*   Updated: 2024/03/01 15:15:24 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int check_quotes(char *str)
{
    int i;
    int flag_1;
    int flag_2;

    i = 0;
    flag_1 = 0;
    flag_2 = 0;
    while(str[i])
    {
        if(str[i] == 34)
            flag_1++;
        if(str[i] == 39)
            flag_2++;
        i++;
    }
    if(flag_1 % 2 != 0 || flag_2 % 2 != 0)
    {
        perror("quotes ");
        return(0);
    }
    return(1);   
}

char *add_space_redirection(char *str)
{
    int i = 0;
    int j = 0;
    int count = ft_strlen(str);
    
    while (str[i]) 
    {
        if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')) 
        {
            count += 2;
            i += 2;
        } 
        else if (str[i] == '<' || str[i] == '>')
        {
            count += 2;
            i++;
        } 
        else
            i++;
    }
    char *result = malloc(sizeof(char) * (count + 1));
    i = 0;
    while (str[i]) 
    {
        if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
        {
            result[j++] = ' ';
            result[j++] = str[i++];
            result[j++] = str[i];
            result[j++] = ' ';
        }
        else if (str[i] == '<' || str[i] == '>')
        {
            result[j++] = ' ';
            result[j++] = str[i];
            result[j++] = ' ';
        }
        else
            result[j++] = str[i];
        i++;
    }
    result[j] = '\0';
    free(str);
    return result;
}

void get_tokens(t_token **liste_token, char **args)
{
	int i;
	t_token *new;
	i = 0;

	while(args[i] != NULL)
	{
		new = ft_newtoken(args[i]);
		add_back_front(liste_token, new);
		new->type = get_type_arg(new, args[i]);
		i++;
	}
}

int add_data(t_programme *programme)
{
    t_data *new;
    t_token *current = *programme->liste_token;
    int i = 0;

    while(current != NULL)
    {
        if(current->type == commande)
        {
            new = ft_newcmd(programme, i);
            if(new == 0)
                return(0);
            add_back_fronts(programme->liste_data, new);
        }
        current = current->next;
        i++;
    }
    return(1);
}


int parse(t_programme *programme)
{
    if(check_quotes(programme->args) == 0)
        return(0);

    programme->args = add_space_redirection(programme->args);
    programme->split_args = (char *const *)ft_split(programme->args, ' ');
    get_tokens(programme->liste_token, (char **)programme->split_args);
    
    if (add_data(programme) == 0)
        return(0);
    
    t_data *temp = *programme->liste_data;
    int i = 0;
    int j = 0;
    int k = 0;
    int f = 0;

    while(temp != NULL)
    {
        i = 0;
        j = 0;
        k = 0;
        f = 0;
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
        printf("\n");
        printf("\n");
        temp = temp->next;
    }
    
    return(1);
}