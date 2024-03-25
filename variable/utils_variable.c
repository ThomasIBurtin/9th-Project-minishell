/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:36:02 by transfo           #+#    #+#             */
/*   Updated: 2024/03/25 17:59:09 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	check_already_exist(char *variable, t_list *list)
{
	while ((list != NULL && list->content != NULL)
		&& (list->content[0] != '\0'))
	{
		if (ft_strncmp(list->content, variable, ft_strlen(variable)) == 0)
			return (1);
		if (list->next == NULL || list->next->content[0] == '\0'
			|| list->next->content == NULL)
			break ;
		list = list->next;
	}
	return (0);
}


void	edit_envp(char *var, char *cmd, t_list **list)
{
	t_list	*current_node;
	t_list	*previous_node;
	t_list	*next_node;
	t_list	*new_node;

	new_node = ft_lstnew(cmd);
	current_node = *list;
	while (ft_strncmp(current_node->content, var, ft_strlen(var)) != 0)
	{
		previous_node = current_node;
		current_node = current_node->next;
		next_node = current_node->next;
	}
	if (current_node == *list)
	{
		new_node->next = current_node->next;
		*list = new_node;
	}
	else
	{
		previous_node->next = new_node;
		new_node->next = next_node;
	}
	free(current_node);
}