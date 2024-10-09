/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:11:04 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/08 22:11:07 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./Libft/libft.h"
# include <stdio.h>
# include <wait.h>

# define ARGS_ERR_1 "Error: wrong number of arguments.\nStructure must be:\n"
# define ARGS_ERR_2 "./pipex infile command1 command2 outfile\n"

typedef struct s_index
{
	int		i;
	int		total;
	int		n_com;
	int		fd_count;
	int		bonus;
}	t_index;

void	arr_freer(char **arr);
void	forker(int *fds, char **argv, char **env, t_index *index);
int		execution(int *fds, char *argv, char **env, t_index *index);
void	fd_arr_closer(int *fds, int last);

#endif
