/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:41:29 by tburtin           #+#    #+#             */
/*   Updated: 2023/11/04 14:53:57 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	int		i;
	int		taille;
	char	*tableau;

	i = 0;
	taille = ft_strlen(s);
	tableau = malloc(sizeof(char) * (taille + 1));
	if (!s)
		return (0);
	if (!tableau)
		return (0);
	while (taille > i)
	{
		tableau[i] = (*f)(i, s[i]);
		i++;
	}
	tableau[i] = '\0';
	return (tableau);
}
