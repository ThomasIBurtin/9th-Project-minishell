/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:41:19 by tburtin           #+#    #+#             */
/*   Updated: 2024/03/14 18:25:13 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_strlen_modife(char *str)
{
	int i = 0;
	int compteur = 0;

	while(str[i])
	{
		if(str[i+1] && str[i+1] != ' ' && str[i] == '$')
		{
			while(str[i] && str[i] != ' ')
				i++;
		}
		compteur++;
		i++;
	}
	return(compteur);
}