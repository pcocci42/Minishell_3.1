/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:26:08 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/07 10:58:14 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(((finish - start) + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

/*int	main(void)
{
	char s[] = "cscasdcscs";
  	char **split_strings = ft_split(s, 'c');
	for (int i = 0; i < 4; i++)
		printf("%s\n", split_strings[i]);
	printf("***************************\n");
	char s2[] = "Hello there";
  	char **split_strings2 = ft_split(s2, ' ');
	for (int i = 0; i < 2; i++)
		printf("%s\n", split_strings2[i]);
	printf("***************************\n");
	
	char s3[] = ",,, ,,Hello,there,you,,, ,";
  	char **split_strings3 = ft_split(s3, ',');
	for (int i = 0; i < 5; i++)
		printf("%s\n", split_strings3[i]);
	printf("***************************\n");
	char s4[] = "   b  Hello there you   b ";
  	char **split_strings4 = ft_split(s4, ' ');
	for (int i = 0; i < 5; i++)
		printf("%s\n", split_strings4[i]);
	printf("***************************\n");
	return (0);
}*/
