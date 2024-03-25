/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:36:02 by transfo           #+#    #+#             */
/*   Updated: 2024/03/25 22:25:50 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	check_already_exist(char *variable_split, t_list *list)
{
	char **var;
	int i = 0;

	while (list)
	{
		var = ft_split(list->content, '=');
		if(ft_compare(var[0], variable_split) == 1)
			return (i);
		free_tab(var);
		list = list->next;
		i++;
	}
	return (-1);
}


void edit_envp(int index, char *var, t_list **list)
{
    t_list *current_node = *list;
    t_list *previous_node = NULL;

    t_list *new_node = ft_lstnew(var);

    while (index > 0)
    {
        previous_node = current_node;
        current_node = current_node->next;
        index--;
    }

    if (previous_node == NULL)
    {
        new_node->next = current_node->next;
        *list = new_node;
    }
    else
    {
        previous_node->next = new_node;
        new_node->next = current_node->next;
    }

    free(current_node->content);
    free(current_node);
}