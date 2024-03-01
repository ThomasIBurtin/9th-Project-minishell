/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:05:12 by tburtin           #+#    #+#             */
/*   Updated: 2024/02/28 19:45:52 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_word(const char *str, char c)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	while (*str)
	{
		if(*str == 34 || *str == 39)
		{
			str++;
			while(*str && *str != 39 && *str != 34)
				str++;
		}
		if (*str != c && x == 0)
		{
			x = 1;
			count++;
		}
		else if (*str == c)
			x = 0;
		str++;
	}
	return (count);
}

void	*free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char **ft_fill_tab(const char *s, char **res, char c) 
{
    size_t i = 0;
    size_t j;
	int flag = 0;

    while (*s) 
	{ 
        j = 0;
		flag = 0;
        const char *start = s;

		if(*s != c)
		{
            while (*s && *s != c) 
			{
				if(*s == 34 || *s == 39)
				{
					flag = 1;
					j++;
					s++;
					while(*s && *s != 39 && *s != 34)
					{
						s++;
						j++;
					}
				}
				j++;
				s++;
            }
			if (flag == 1)
				j = j - 2;
            res[i] = ft_substr(start, flag, j);
            if (!res[i]) 
				return (free_tab(res));
            i++;
		}
		else
			s++;
    }
    res[i] = NULL;
    return (res);
}

char	**ft_split(const char *s, char c)
{
	char	**res;

	if (!s)
		return (0);
	res = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!res)
		return (0);
	res = ft_fill_tab(s, res, c);
	return (res);
}
