/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:48:04 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/08 22:37:42 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**path_array_b(char **env)
{
	int		i;
	char	*path;
	char	**path_split;

	i = 0;
	while (env[i] != NULL)
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		if (path != NULL)
		{
			path_split = ft_split(path, ':');
			if (!path_split)
				return (NULL);
			path = path_split[0];
			path_split[0] = ft_strdup(&path[5]);
			free(path);
			return (path_split);
		}
		i++;
	}
	return (NULL);
}

static char	*where_is_comm_b(char *command, char **env)
{
	char	*path_program;
	char	**path_arr;
	int		i;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	else
	{
		command = ft_strjoin("/", command);
		if (!command)
			return (NULL);
		path_arr = path_array_b(env);
		if (!path_arr)
			return (command);
		i = 0;
		while (path_arr[i] != NULL)
		{
			path_program = ft_strjoin(path_arr[i ++], command);
			if (access(path_program, X_OK) != -1)
				return (arr_freer(path_arr), free(command), path_program);
			free(path_program);
		}
		return (arr_freer(path_arr), command);
	}
}

static int	first_pipe(int *fds, t_index *index)
{
	if (index->i != 0 || fds[0] == -1)
		return (1);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (dup2(fds[0], STDIN_FILENO) == -1)
		return (1);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

static int	last_pipe(int *fds, t_index *index)
{
	int		*pipe;

	if (index->i == 0)
		return (1);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	pipe = &fds[(index->i * 2) - 1];
	if (pipe[2] == -1)
		return (1);
	if (dup2(pipe[1], STDIN_FILENO) == -1)
		return (1);
	if (dup2(pipe[2], STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

int	execution(int *fds, char *arg, char **env, t_index *index)
{
	char	*path_program;
	char	*command;
	char	**arguments;

	arguments = ft_split(arg, ' ');
	if (!arguments)
		exit(EXIT_FAILURE);
	command = arguments[0];
	path_program = where_is_comm_b(command, env);
	if (first_pipe(fds, index) && last_pipe(fds, index))
	fd_arr_closer(fds, (index->n_com * 2) - 1);
	if (index->bonus)
		free(fds);
	execve(path_program, arguments, env);
	perror(arguments[0]);
	free(path_program);
	arr_freer(arguments);
	exit(EXIT_FAILURE);
}
