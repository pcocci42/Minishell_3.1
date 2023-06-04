/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:33:41 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/04 17:45:29 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int   ft_chr(char *cmd, char c, int i)
{
    while (cmd[i])
    {
        if (cmd[i] == c)
            return (0);
        i++;
    }
    return (1);
}

void    convert_dquote(t_cmd *cmd)
{
    int i;
    int j;

    j = 0;
    i = 0;
    {
        while (cmd->cmd[i])
        {
            if (cmd->cmd[i] == '"' && cmd->squote == 0)
            {   
                if (cmd->cmd[i - 1] != '=')
                    cmd->cmd[i] = ' ';
                else
                    cmd->cmd[i] = 19;
                j = i -1;
                i++;
                cmd->squote = 0;
                if (ft_chr(cmd->cmd, '"', i) == 0)
                    cmd->dquote = 1;
                while (cmd->cmd[i] != '"' && cmd->dquote == 1)
                {
                    if (cmd->cmd[i] == ' ')
                        cmd->cmd[i] = 17;
                    if (cmd->cmd[i] == '|')
                        cmd->cmd[i] = 18;
                    i++;
                }
                if (cmd->cmd[j] != '=')
                    cmd->cmd[i] = ' ';
                else
                    cmd->cmd[i] = 19;
                cmd->dquote = 0;
            }
            else if (cmd->cmd[i] == '\'' && cmd->dquote == 0)
            {
                if (cmd->cmd[i - 1] != '=')
                    cmd->cmd[i] = ' ';
                else
                    cmd->cmd[i] = 19;
                j = i -1;
                i++;
                cmd->dquote = 0;
                if (ft_chr(cmd->cmd, '\'', i) == 0)
                    cmd->squote = 1;
                while (cmd->cmd[i] != '\'' && cmd->squote == 1)
                {
                    if (cmd->cmd[i] == ' ')
                        cmd->cmd[i] = 17;
                    if (cmd->cmd[i] == '|')
                        cmd->cmd[i] = 18;
                    if  (cmd->cmd[i] == '$')
                        cmd->cmd[i] = 20;
                    i++;
                }
                if (cmd->cmd[j] != '=')
                    cmd->cmd[i] = ' ';
                else
                    cmd->cmd[i] = 19;
                cmd->squote = 0;
            }
            i++;
        }
    }
}

void    print_parsed_quotes(t_cmd *cmd)
{   
    int i;

    i = 0;
    while (cmd->parsed[i])
    {
        printf("%s\n", cmd->parsed[i]);
        i++;
    }
}

void    print_parsed_box(t_cmd *cmd)
{   
    int i;
    i = 0;
    int j = 0;
    //printf("%d\n", cmd->nbr_pipe);
    printf("ciao");
    while (cmd->box[i])
    {   
        j = 0;
        while (cmd->box[i][j])
        {
            printf("%s\n", cmd->box[i][j]);
            j++;
        } 
        i++;
    }
}

void    convert(t_cmd *cmd)
{
    cmd->squote = 0;
    cmd->dquote = 0;
    convert_dquote(cmd);
    cmd->squote = 0;
    cmd->dquote = 0;
}

void    count_pipes(t_cmd *cmd)
{   
    int i;

    i = 0;
    cmd->nbr_pipe = 0;
    while (cmd->cmd[i])
    {
        if (cmd->cmd[i] == '|')
            cmd->nbr_pipe++;
        i++;
    }
}

void    split_pipes(t_cmd *cmd)
{   
    int i;
    char **split_pipes;
    i = 0;
    split_pipes = ft_split(cmd->cmd, '|');
    cmd->box = malloc((sizeof(char **)) * (cmd->nbr_pipe + 2));
    while (split_pipes[i])
    {
        cmd->box[i] = ft_split(split_pipes[i], ' ');
        i++;
    }
    /* printf("%d\n", i); */
    cmd->box[i] = NULL;
    //printf("%s\n", cmd->box[i][0]);
    i = 0;
    while (split_pipes[i])
    {
        free(split_pipes[i]);
        i++;
    }
    free(split_pipes);
}

void    add_spaces(t_cmd *cmd)
{   
    int i = 0;
    int j = 0;
    int x = 0;

    while (cmd->box[i])
    {   
        j = 0;
        while (cmd->box[i][j])
        {   
            x = 0;
            while (cmd->box[i][j][x])
            {
                if (cmd->box[i][j][x] == 17)
                    cmd->box[i][j][x] = ' '; 
                if (cmd->box[i][j][x] == 18)
                    cmd->box[i][j][x] = '|';
                x++;
            }
            j++;
        }
        i++;
    }
}

void    parse_input(t_cmd *cmd, char **envp)
{   
    convert(cmd);
    count_pipes(cmd);
    split_pipes(cmd);
    if (cmd->box[0][0] == NULL)
        return ;
    cmd->output = NULL;
    cmd->input = NULL;
    add_spaces(cmd);
    look_var(cmd);
    if (ft_strcmp(cmd->box[0][0], "<<") == 0)
    {
        handle_here_doc_input(cmd->box[0][1]);
        cmd->input = "heredoc_tmp.txt";
    }
    if (ft_strcmp(cmd->box[0][0], "export") == 0)
        look_var_envp(cmd, envp);
    if (ft_strncmp(cmd->box[0][0], "unset", 5) == 0)
        ft_unset(cmd->box[0], envp);
    flag_init(cmd);
    if (ft_strcmp(cmd->box[0][0], "cd") == 0)
    {
        ft_cd(cmd->box[0]);
        if (cmd->box[1] != NULL)
            cmd->box++;
    }
    execute_command(cmd->box, cmd, cmd->nbr_pipe, envp);
    unlink("heredoc_tmp.txt");
    cmd->output = NULL;
    cmd->input = NULL;
    flag_init(cmd);
}