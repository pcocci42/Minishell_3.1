/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/02 13:59:37 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include "unistd.h"

void    ft_pwd()
{
    char cwd[1024];
      
    if(getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
        g_exitstatus = 0;
    }
    else
        g_exitstatus = 1;
}

void    ft_exit(char **parsed)
{  
        free(parsed);
        printf("exit\n");
        kill(0,SIGUSR1);
}

int check_cd(char **parsed)
{
    DIR *dir;
    (void)parsed;
    struct dirent *entry;
    dir = opendir(".");
    if (dir == NULL) 
    {
        perror("opendir");
        return 1;
    }
    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }


    // Close the directory
    closedir(dir);

    return 0;
}

int printDirectoryContents(char **parsed)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 2;
    }

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_DIR) {
            printf("Directory: %s\n", entry->d_name);
        } else {
            printf("File: %s\n", entry->d_name);
        }
        if (!ft_strcmp(parsed[1], entry->d_name))
            return (0);
    }
    closedir(dir);
    return (1);
}

void    ft_cd(char **parsed)
{   

    if (parsed[1])
    {
        if (chdir(parsed[1]) == -1)
            perror("chdir");
    }
    else
        chdir("/");
}