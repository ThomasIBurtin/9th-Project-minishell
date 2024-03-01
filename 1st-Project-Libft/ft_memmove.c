/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:39:28 by tburtin           #+#    #+#             */
/*   Updated: 2023/11/04 13:11:41 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	int				i;

	i = len - 1;
	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	if (!(dst) && !(src))
		return (0);
	if (dst < src)
		return (ft_memcpy(dst, src, len));
	while (i >= 0)
	{
		cdst[i] = csrc[i];
		i--;
	}
	return (dst);
}
