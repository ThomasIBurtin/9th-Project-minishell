/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:39:04 by tburtin           #+#    #+#             */
/*   Updated: 2023/11/04 15:14:18 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	cc;
	unsigned char	*ss;

	i = 0;
	cc = (unsigned char)c;
	ss = (unsigned char *)s;
	while (i < n)
	{
		if (ss[i] == cc)
		{
			return ((void *)&(ss[i]));
		}
	i++;
	}
	return (NULL);
}
