/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:52:31 by mbyrne            #+#    #+#             */
/*   Updated: 2025/02/05 09:58:05 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Duplicates up to `len` characters from the given string.
** Allocates memory for the new string and ensures it is null-terminated.
**
** @param src: The source string.
** @param len: The number of characters to duplicate.
** @return:    A newly allocated string containing the substring, 
** or NULL on failure.
*/
static char	*ft_strndup(const char *src, size_t len)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len && src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*
** Skips leading spaces in the given input string by advancing the pointer.
**
** @param input: A pointer to the input string that will be modified.
*/
static void	skip_spaces(const char **input)
{
	while (**input == ' ')
	{
		(*input)++;
	}
}

/*
** Counts the number of arguments in the input string, 
** considering quoted arguments.
**
** @param input: The input command string.
** @return:      The number of arguments found in the input.
*/
static int	count_args(const char *input)
{
	int		count;
	char	quote;

	count = 0;
	while (*input)
	{
		skip_spaces(&input);
		if (!*input)
			break ;
		count++;
		if (*input == '\'' || *input == '"')
		{
			quote = *input++;
			while (*input && *input != quote)
				input++;
			if (*input)
				input++;
		}
		else
			while (*input && *input != ' ')
				input++;
	}
	return (count);
}

/*
** Extracts the next argument from the input string, handling quotes if present.
** Allocates memory for the extracted argument.
**
** @param input: A pointer to the input string that will be modified.
** @return:      A newly allocated string containing the extracted argument.
*/
static char	*get_arg(const char **input)
{
	const char	*start;
	char		quote;

	quote = **input;
	start = *input;
	if (quote == '\'' || quote == '"')
	{
		(*input)++;
		start = *input;
		while (**input && **input != quote)
			(*input)++;
	}
	else
	{
		while (**input && **input != ' ')
			(*input)++;
	}
	return (ft_strndup(start, *input - start));
}

/*
** Splits an input string into an array of arguments, 
** considering spaces and quotes.
** Allocates memory for the argument array and each individual argument.
**
** @param input: The input string containing the command and its arguments.
** @return:      A NULL-terminated array of strings (arguments), 
** or NULL on failure.
*/
char	**ft_pipex_split_args(const char *input)
{
	int		arg_count;
	int		i;
	char	**args;

	if (!input)
		return (NULL);
	arg_count = count_args(input);
	args = (char **)malloc((arg_count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (i < arg_count)
	{
		skip_spaces(&input);
		args[i] = get_arg(&input);
		i++;
	}
	args[arg_count] = NULL;
	return (args);
}