/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:58:54 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/04 17:44:54 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_var(char *parsed)
{
	int i;

	i = 0;
	while (parsed[i])
	{
		if (parsed[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*take_var(char *parsed)
{
	char	*var;

	int i;
	i = 0;
	while (parsed[i] != '=' && parsed[i] != '\0') 
		i++;
	var = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (parsed[i] != '=' && parsed[i] != '\0')
	{
		var[i] = parsed[i];
		i++;
	}
	var[i++] = '\0';
	return (var);
}

char	*take_content(char *parsed)
{
	char *content;
	int i;
	int len;
	int	start;

	i = 0;
	len = 0;
	while (parsed[i] != '=')
		i++;
	i++;
	start = i;
	while (parsed[i] != '\0')
	{
		len++;
		i++;
	}
	i = 0;
	content = malloc(sizeof(char) * (len + 1));
	while (parsed[start] != '\0')
	{
		content[i] = parsed[start];
		i++;
		start++;
	}
	content[i] = '\0';
	return (content);
}

int is_valid_command(const char* string) 
{
    // Check if the string contains the '=' character
    if (strchr(string, '=') != NULL) {
        return 0; // Contains '=', it's a variable
    }

    // Check if the string is a valid command or executable
    if (access(string, X_OK) == 0) {
        return 0; // Valid command or executable
    }

    // Check if the string is a command available in PATH
    char* path_env = getenv("PATH");
    if (path_env != NULL) {
        char* path = strdup(path_env);
        if (path != NULL) {
            char* dir = strtok(path, ":");
            while (dir != NULL) {
                char* full_path = (char*)malloc(strlen(dir) + strlen(string) + 2);
                if (full_path != NULL) {
                    sprintf(full_path, "%s/%s", dir, string);

                    if (access(full_path, X_OK) == 0) {
                        free(path);
                        free(full_path);
                        return 0; // Valid command in PATH
                    }
                    free(full_path);
                }
                dir = strtok(NULL, ":");
            }
            free(path);
        }
    }
    return 1; // Not a command or executable
}


int		check_var_loop(char **parsed)
{
	int i;

	i = 0;
	while (parsed[i])
	{
		if (check_var(parsed[i]) == 1)
			return (1);
		i++;
	}
	return (0);

}

void	print_envp2(char **envp)
{
	int i;

	i = 0;

	while(envp[i])
	{
		printf("%s\n", envp[i++]);
	}
}

void	ft_realloc(char **env)
{
	int i;
	int j;
	char **copy;
	i = 0;
	j = 0;
	while (env[i])
		i++;
	copy = malloc((sizeof(char *)) * (i + 1));
	j = i + 1;
	i = 0;
	while (env[i])
	{
		copy[i] = env[i];
		i++;
	}
	copy[j] = NULL;
}

void	up_environ(char *current)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (environ[i])
	{
		if (ft_strcmp(take_var(environ[i]), take_var(current)) != 0)
		{
			i++;
		}
		else
		{	
			flag = 1;
			break ;
		}
	}
	environ[i] = malloc((sizeof(char)) * (ft_strlen(current) + 1));
	ft_strcpy(environ[i], current);
	if (flag == 0)
		environ[i + 1] = NULL;
}

void	up_envp(char *current, char **envp)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (envp[i])
	{
		if (ft_strcmp(take_var(envp[i]), take_var(current)) != 0)
		{
			i++;
		}
		else
		{	
			flag = 1;
			break ;
		}
	}
	envp[i] = malloc((sizeof(char)) * (ft_strlen(current) + 1));
	ft_strcpy(envp[i], current);
	if (flag == 0)
		envp[i + 1] = NULL;
}

void	look_var_envp(t_cmd *cmd, char **envp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cmd->box[i])
	{	
		j = 0;
		while (cmd->box[i][j])
		{	
			if (check_var(cmd->box[i][j]) == 1)
			{
				up_envp(cmd->box[i][j], envp);
			}
			j++;
		}
		i++;
	}
}

void	look_var(t_cmd *cmd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cmd->box[i])
	{	
		j = 0;
		while (cmd->box[i][j])
		{	
			if (check_var(cmd->box[i][j]) == 1)
			{
				up_environ(cmd->box[i][j]);
			}
			j++;
		}
		i++;
	}
}