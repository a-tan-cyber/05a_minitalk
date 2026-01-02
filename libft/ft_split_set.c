/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 22:16:48 by amtan             #+#    #+#             */
/*   Updated: 2026/01/02 21:34:51 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

static size_t	count_words(char const *s, char const *d);
static char		**fill_arr(char const *s, char const *d, char **arr,
					size_t arr_index);
static char		*malloc_word(char **arr, size_t arr_index, size_t word_len);
static void		free_arr(char **arr, size_t arr_index);

char	**ft_split_set(char const *s, char const *d)
{
	char	**arr;
	size_t	arr_index;
	size_t	word_count;

	word_count = count_words(s, d);
	arr = malloc((word_count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr_index = 0;
	arr = fill_arr(s, d, arr, arr_index);
	if (!arr)
		return (NULL);
	arr[word_count] = NULL;
	return (arr);
}

static size_t	count_words(char const *s, char const *d)
{
	size_t	i;
	size_t	word_count;

	i = 0;
	word_count = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && ft_strchr(d, s[i]))
			i++;
		if (s[i] == '\0')
			break ;
		word_count++;
		while (s[i] != '\0' && !ft_strchr(d, s[i]))
			i++;
	}
	return (word_count);
}

static char	**fill_arr(char const *s, char const *d, char **arr,
		size_t arr_index)
{
	size_t	s_index;
	size_t	word_start;
	size_t	word_len;
	char	*arr_word;

	s_index = 0;
	while (s[s_index] != '\0')
	{
		while (s[s_index] != '\0' && ft_strchr(d, s[s_index]))
			s_index++;
		if (s[s_index] != '\0')
		{
			word_start = s_index;
			while (s[s_index] != '\0' && !ft_strchr(d, s[s_index]))
				s_index++;
			word_len = s_index - word_start;
			arr_word = malloc_word(arr, arr_index, word_len);
			if (!arr_word)
				return (NULL);
			ft_memcpy(arr_word, s + word_start, word_len);
			arr_word[word_len] = '\0';
			arr_index++;
		}
	}
	return (arr);
}

static char	*malloc_word(char **arr, size_t arr_index, size_t word_len)
{
	arr[arr_index] = malloc(word_len + 1);
	if (!arr[arr_index])
	{
		free_arr(arr, arr_index);
		return (NULL);
	}
	return (arr[arr_index]);
}

static void	free_arr(char **arr, size_t arr_index)
{
	size_t	i;

	i = 0;
	while (i < arr_index)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
