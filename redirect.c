/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:23:42 by lmasetti          #+#    #+#             */
/*   Updated: 2023/05/24 09:59:51 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void handle_input_redirection(char* filename) // handles the < redirection operator
{
    int file = open(filename, O_RDONLY);
    if (file == -1) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    dup2(file, STDIN_FILENO);
    close(file);
}

void handle_output_redirection(char* filename) // handles the > redirection operator. 
{
    int file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }
    dup2(file, STDOUT_FILENO);
    close(file);
}

void handle_input_heredoc(char* delimiter) // handles the << redirection operator. 
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) // dovrebbe essere gnl.
    {
        if (strcmp(line, delimiter) == 0)
            break;
    }

    free(line);
}

void handle_output_append_redirection(char* filename) // handles the >> redirection operator.
{
    int file = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (file == -1) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }
    dup2(file, STDOUT_FILENO);
    close(file);
}