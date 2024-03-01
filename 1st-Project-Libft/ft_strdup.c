/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:40:32 by tburtin           #+#    #+#             */
/*   Updated: 2023/11/04 14:55:06 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		place;
	char	*tableau_copie;
	int		i;

	place = ft_strlen(s);
	tableau_copie = malloc(sizeof(char) * (place + 1));
	if (!tableau_copie)
		return (0);
	i = 0;
	while (s[i])
	{
		tableau_copie[i] = s[i];
		i++;
	}
	tableau_copie[i] = '\0';
	return (tableau_copie);
}
