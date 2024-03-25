/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:28:56 by transfo           #+#    #+#             */
/*   Updated: 2024/03/25 19:54:14 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_compare(char *str, char *strr)
{
	int i = 0;
	
	if(ft_strlen(str) != ft_strlen(strr))
		return(0);
	while(str[i] && strr[i])
	{
		if(str[i] != strr[i])
			return(0);
		i++;
	}
	return(1);
}