/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:24:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/07 10:58:43 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] > s2[i])
		{
			if (s1[i] == '\0')
			{
				return (-(s1[i] - s2[i]));
			}
			return (s1[i] - s2[i]);
		}
		else if (s1[i] < s2[i])
		{
			if (s2[i] == '\0')
			{
				return (-(s1[i] - s2[i]));
			}
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	long unsigned int	i;
	long unsigned int	j;
	long unsigned int	dlen;
	long unsigned int	slen;

	i = 0;
	j = 0;
	while (dest[j] != '\0' && j < size)
	{
		j++;
	}
	dlen = j;
	slen = ft_strlen(src);
	if (size == 0 || size <= dlen)
		return (slen + size);
	while (src [i] != '\0' && i < size - dlen - 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dlen + slen);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] > s2[i])
		{
			if (s1[i] == '\0')
			{
				return (-(s1[i] - s2[i]));
			}
			return (s1[i] - s2[i]);
		}
		else if (s1[i] < s2[i])
		{
			if (s2[i] == '\0')
			{
				return (-(s1[i] - s2[i]));
			}
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}
