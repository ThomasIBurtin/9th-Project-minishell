/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:18:00 by transfo           #+#    #+#             */
/*   Updated: 2024/03/17 03:45:08 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_quotes(char *str)
{
    int i = 0;
    int flag_1 = 0;
    int flag_2 = 0;

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
            i++;
        } 
        else if (str[i] == '<' || str[i] == '>')
            count += 2;
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


int get_tokens(t_token **liste_token, char **args, t_variable *liste_variable)
{
	int i = 0;
	t_token *new;

	while(args[i] != NULL)
	{
		new = ft_newtoken(args[i], liste_variable);
		add_back_front(liste_token, new);
		new->type = get_type_arg(new, args[i]);
		i++;
	}
    t_token *current = *liste_token;
    while(current)
    {
        if((current->prev == NULL || current->prev->type == pip) && current->type != commande)
            return(0);
        current = current->next;
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
            new = ft_newcmd(current);
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
    if(ft_strlen(programme->args) < 1)
        return(0);
    if(check_quotes(programme->args) == 0)
        return(0);
    programme->args = add_space_redirection(programme->args);
    programme->split_args = (char *const *)ft_split(programme->args, ' ');
    if(get_tokens(programme->liste_token, (char **)programme->split_args, *programme->liste_variable) == 0)
        return(0);
    if(add_data(programme) == 0)
        return(0);
    return(1);
}