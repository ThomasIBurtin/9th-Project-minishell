/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:36 by transfo           #+#    #+#             */
/*   Updated: 2024/03/15 12:13:01 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int ft_strchr(char *s, char c)
{
	int	i;

	i = 1;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == c)
		{
			if(s[i+1] == '\0')
				return(0);
			return (1);
		}
		i++;
	}
	return (0);
}

int ft_strnchr(char *s, char c, int start)
{
	if (!s[start])
		return (0);
	while (s[start])
	{
		if (s[start] == c)
			return (1);
		start++;
	}
	return (0);
}