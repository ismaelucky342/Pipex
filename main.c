/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:48:09 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/08 22:35:03 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void execute_command(char *cmd, int input_fd, int output_fd) {
    char *argv[10];
    char *token = strtok(cmd, " ");
    int i = 0;

    while (token != NULL) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    dup2(input_fd, STDIN_FILENO);    // Redirigir entrada estándar
    dup2(output_fd, STDOUT_FILENO);   // Redirigir salida estándar
    execvp(argv[0], argv);            // Ejecutar el comando
    perror("execvp failed");          // En caso de error
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <file_in> <cmd1> <cmd2> <file_out>\n", argv[0]);
        return 1;
    }

    int fd_in = open(argv[1], O_RDONLY);
    int fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_in < 0 || fd_out < 0) {
        perror("File open failed");
        return 1;
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    if (fork() == 0) {
        close(pipe_fd[0]);  // Cerrar lectura de la tubería
        execute_command(argv[2], fd_in, pipe_fd[1]);
    }

    if (fork() == 0) {
        close(pipe_fd[1]);  // Cerrar escritura de la tubería
        execute_command(argv[3], pipe_fd[0], fd_out);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(fd_in);
    close(fd_out);

    wait(NULL); // Esperar a los procesos hijos
    wait(NULL);

    return 0;
}
