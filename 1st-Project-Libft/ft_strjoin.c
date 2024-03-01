/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:40:49 by tburtin           #+#    #+#             */
/*   Updated: 2023/11/04 13:26:57 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s3_len;
	char	*s3;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1) + 1;
	s3_len = s1_len + ft_strlen(s2);
	s3 = ft_calloc(s3_len, sizeof(char));
	if (!s3)
		return (0);
	ft_strlcat(s3, s1, s1_len);
	ft_strlcat(s3, s2, s3_len);
	return (s3);
}
