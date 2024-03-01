/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:40:55 by tburtin           #+#    #+#             */
/*   Updated: 2023/11/08 04:34:35 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsts)
{
	unsigned int	src_len;
	unsigned int	dst_len;
	unsigned int	i;
	unsigned int	dist;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = 0;
	while (i < dsts && dst[i])
		i++;
	dist = i;
	if (dsts < dst_len || dsts == 0)
		return (src_len + dsts);
	if (dst_len < dsts)
	{
		i = 0;
		while ((i < dsts - dst_len - 1) && src[i])
		{
			dst[dst_len + i] = src[i];
			i++;
		}
	}
	if (i > 0)
		dst[dst_len + i] = '\0';
	return (src_len + dist);
}
