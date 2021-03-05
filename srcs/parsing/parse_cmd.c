/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 07:16:13 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/04 15:21:47 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"
#include <stdio.h>

static int	size_component(char const *str_cmd, int i, int len)
{
	int		size;

	size = 0;
	if (str_cmd[i] == '"')
	{
		i++;
		size++;
		while (str_cmd[i] != '"' || (str_cmd[i] == '"' &&
			str_cmd[i - 1] == '\\'))
		{
			i++;
			size++;
		}
		i++;
		size++;
	}
	else
	{
		while (str_cmd[i] != ' ' && i < len && str_cmd[i] != '|')
		{
			i++;
			size++;
		}
	}
	return (size);
}

static void fill_exe(t_parse_cmd *p, int i, int size)
{
	int		j;

	p->cmd->exe = malloc(sizeof(char) * (size + 1));
	j = 0;
	while (j < size)
	{
		p->cmd->exe[j] = p->str_cmd[i];
		i++;
		j++;
	}
	p->cmd->exe[j] = '\0';
}

static int	count_arg(char const *str, int i, int len)
{
	int		count;

	count = 0;
	while (i < len)
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '|')
		{
			return (count);
		}
		if (i != len)
			count++;
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' || (str[i] == '"' && str[i - 1] == '\\'))
				i++;
			i++;
		}
		else
		{
			while (str[i] != ' ' && i < len && str[i] != '|')
				i++;
		}
	}
	return (count);
}

char	*trim_d_quote(char *arg, int size)
{
	char	*arg_trimmed;

	if ((arg[0] == '"' && arg[size - 1] == '"')
		|| (arg[0] == '\'' && arg[size - 1] == '\''))
	{
		arg_trimmed = malloc(sizeof(char) * (size - 1));
		ft_strncpy(arg_trimmed, arg + 1, size - 2);
		return (arg_trimmed);
	}
	else
		return (arg);
}

static char		*strncpy_arg(char *dest, const char *src, int n)
{
	int		i;
	int		j;

	(void)n;
	i = 0;
	j = 0;
	while (src[j] != '\0' && j < n)
	{
		if (!((src[j] == '\\' && src[j + 1] == '"')))
		{
			dest[i] = src[j];
			i++;
		}
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int		size_arg(const char *str, int i, int len)
{
	int		size;

	size = 0;
	if (str[i] == '"')
	{
		i++;
		size++;
		while (str[i] != '"' || (str[i] == '"' && str[i - 1] == '\\'))
		{
			if (!(str[i] == '"' && str[i - 1] == '\\'))
				size++;
			i++;
		}
		i++;
		size++;
	}
	else
	{
		while (str[i] != ' ' && i < len)
		{
			i++;
			size++;
		}
	}
	return (size);
}

static char	**fill_args(const char *str_cmd, int *i, int len, int arg_nb)
{
	char	**args;
	int		size;
	int		j;

	args = malloc(sizeof(char *) * (arg_nb + 1));
	args[arg_nb] = NULL;
	if (!args)
		return (0);
	j = 0;
	while (*i < len)
	{
		while (str_cmd[*i] == ' ')
			*i = *i + 1;
		if (str_cmd[*i] == '|' || str_cmd[*i] == '\0')
			return (args);
		size = size_component(str_cmd, *i, len);
		args[j] = malloc(sizeof(char) * (size_arg(str_cmd, *i, len) + 1));
		strncpy_arg(args[j], str_cmd + *i, size);
		args[j] = trim_d_quote(args[j], size_arg(str_cmd, *i, len));
		*i = *i + size;
		j++;
	}
	return (args);
}

static int	set_previous_pipe(t_parse_cmd *p, int *i)
{
	if (p->p_cmd)
	{
		p->p_cmd->pipe = p->cmd;
		printf("there is a previous: %p\n", p->p_cmd);
	}
	else
		printf("there is no previous\n");
	if (p->str_cmd[*i] != '|')
		return (0);
	p->p_cmd = p->cmd;
	*i = *i + 1;
	return (1);
}

char	**parse_arguments(int *i, int size, int len, const char *str_cmd)
{
	int		arg_nb;
	char	**args;

	*i = *i + size;
	arg_nb = count_arg(str_cmd, *i, len);
	args = fill_args(str_cmd, i, len, arg_nb);
	if (!args)
		return (NULL);
	return (args);
}

int	init_cmd_exe(int *i, t_parse_cmd *p, int len, int *size)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd) * (1));
	if (!cmd)
	{
		p->cmd = 0;
		return (0);
	}
	if (*i == 0)
		p->first_cmd = cmd;
	while (p->str_cmd[*i] == ' ')
		*i = *i + 1;
	p->cmd = cmd;
	p->cmd->exe = NULL;
	p->cmd->args = NULL;
	p->cmd->pipe = NULL;
	*size = size_component(p->str_cmd, *i, len);
	fill_exe(p, *i, *size);
	while (p->str_cmd[*i] == ' ')
		*i = *i + 1;
	return (1);
}

int		no_arg(int *i, int len, t_parse_cmd *p, int size)
{
	*i = *i + (size + 1);
	if (*i > len)
		return (0);
	if (!p->p_cmd)
	{
		p->cmd->pipe = NULL;
		return (1);
	}
	p->p_cmd->pipe = p->cmd;
	p->cmd->args = NULL;
	p->p_cmd = p->cmd;
	return (1);
}

void	init_parsing(t_parse_cmd *p, char const *str_cmd)
{
	p->p_cmd = NULL;
	p->first_cmd = NULL;
	p->str_cmd = str_cmd;
}

t_cmd	*parse_cmd(char const *str_cmd, int len)
{
	int		i;
	int		size;
	t_parse_cmd		p;

	i = 0;
	init_parsing(&p, str_cmd);
	while (1)
	{
		if (!init_cmd_exe(&i, &p, len, &size))
			return (NULL);
		if (p.str_cmd[i + size] == '|')
		{
//			printf("%d | %d\n", i, size);
			if (!no_arg(&i, len, &p, size))
				break ;
			printf("exe: %s\n", p.cmd->exe);
			printf("arg = %p", p.args);
		}
		else
		{
//			printf("salut\n");
			p.cmd->args = parse_arguments(&i, size, len, p.str_cmd);
			printf("exe: %s\n", p.cmd->exe);
			int	j;
			j = 0;
			while (p.cmd->args[j] != NULL)
			{
				printf("a: %s\n", p.cmd->args[j]);
				j++;
			}
			if (!p.cmd->args)
				return (NULL);
			if (!set_previous_pipe(&p, &i) || i > len)
				break ;
		}
	}
//	printf("pipe: %s\n", p.first_cmd->pipe->args[0]);
	return (p.first_cmd);
}