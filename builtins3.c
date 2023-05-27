/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/05/24 10:11:21 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

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

void    ft_cd(char **parsed, int j)
{   
    char *path = "/nfs/homes/";

    // /printDirectoryContents(parsed);
    // if (ft_strncmp(parsed[0], "cd", 2) == 0)
    {   
        if (parsed[j+1])
        {
            if (chdir(parsed[j+1]) == 0)
                g_exitstatus = 0;
            else
            {   
                printf("Directory does not exist\n");
                g_exitstatus = 1;
            }
        }
        else
        {   
            chdir(path);
            chdir(getenv("USER"));
            g_exitstatus = 0;
        }
       
    }
}