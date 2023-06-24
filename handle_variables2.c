/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:58:54 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/23 18:52:09 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

/* void	up_environ(char *current)
{
	int		i;
	int		flag;
	char	*var;
	char	*name;

	i = 0;
	flag = 0;
	var = take_var(current);
	name = take_var(environ[i]);
	while (environ[i])
	{
		if (ft_strcmp(name, var) != 0)
			i++;
		else
		{	
			flag = 1;
			break ;
		}
	}
	free(var);
	free(name);
	environ[i] = malloc((sizeof(char)) * (ft_strlen(current) + 1));
	ft_strcpy(environ[i], current);
	if (flag == 0)
		environ[i + 1] = NULL;
} */

/* void	up_envp(char *current, char **envp)
{
	int		i;
	int		flag;
	char	*var;
	char	*name;

	i = 0;
	flag = 0;
	var = take_var(current);
	while (envp[i])
	{
		name = take_var(envp[i]);
		if (ft_strcmp(name, var) != 0)
		{	
			i++;
			free(name);
		}
		else
		{	
			printf("1\n");
			flag = 1;
			free(name);
			break ;
		}
	}
	free(var);
	envp[i] = malloc((sizeof(char)) * (ft_strlen(current) + 1));
	ft_strcpy(envp[i], current);
	if (flag == 0)
		envp[i + 1] = NULL;
}
 */

char* ft_sprint(const char* str1, const char* str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    char* result = (char*)malloc((len1 + len2 + 2) * sizeof(char));
    strcpy(result, str1);
    return result;
}

void update_environment(t_cmd* cmd, char* variable, char* value)
{
	char	*name;
    if (cmd == NULL || variable == NULL || value == NULL)
        return;

    int env_size = 0;
    char** env = cmd->cpy_env;

	name = NULL;
    // Count the number of environment variables
    while (env[env_size] != NULL)
        env_size++;

    // Check if the variable already exists in the environment
    for (int i = 0; i < env_size; i++)
	{
		name = take_var(variable);
        if (strncmp(env[i], name, strlen(name)) == 0)
		{
            // Free the previous value
            free(env[i]);

            // Update the existing variable with the new value
			env[i] = ft_sprint(variable, value);
			free(name);
            return;
        }
		free(name);
    }
    // If the variable doesn't exist, create a new entry
    char** new_env = (char**)realloc(env, (env_size + 2) * sizeof(char*));
    if (new_env == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return;
    }

    char* new_variable = (char*)malloc((strlen(variable) + 1)  * sizeof(char));
    ft_strcpy(new_variable, variable);

    new_env[env_size] = new_variable;
    new_env[env_size + 1] = NULL;

    // Update the cmd structure with the new environment array
    cmd->cpy_env = new_env;
}


void	up_envp(char *current, char **envp, t_cmd *cmd)
{
	int		i;
	int		flag;
	char	*var;
	char	*name;
	(void)envp;

	i = 0;
	flag = 0;
	var = take_var(current); 

	while (cmd->cpy_env[i])
	{
		name = take_var(cmd->cpy_env[i]);
		if (ft_strcmp(name, var) != 0)
		{
			i++;
			free(name);
		}
		else
		{
			flag = 1;
			free(cmd->cpy_env[i]);
			free(name);
			break ;
		}
	}
	free(var);
	if (flag == 0)
		realloc_env(cmd, i);
	cmd->cpy_env[i] = malloc(sizeof(char) * (ft_strlen(current) + 1));
	ft_strcpy(cmd->cpy_env[i], current);
	if (flag == 0 && !var)
		cmd->cpy_env[i + 1] = NULL;
}

void	look_var_envp(t_cmd *cmd, char **envp)
{
	int		i;
	int		j;
	char	*value;
	(void)envp;

	i = 0;
	j = 0;
	value = NULL;
	while (cmd->box[i])
	{	
		j = 0;
		while (cmd->box[i][j])
		{	
			if (check_var(cmd->box[i][j]) == 1)
			{	
				value = getcnt(cmd->box[i][j], j, ft_strlen(cmd->box[i][j]));
				update_environment(cmd,cmd->box[i][j], value);
				free(value);
			}
			j++;
		}
		i++;
	}
}

void	look_var(t_cmd *cmd, char **envp)
{
	int	i;
	int	j;
	char *value;
	(void)envp;

	i = 0;
	j = 0;
	value = NULL;
	while (cmd->box[i])
	{	
		j = 0;
		while (cmd->box[i][j])
		{	
			if (check_var(cmd->box[i][j]) == 1)
			{	
				value = getcnt(cmd->box[i][j], j, ft_strlen(cmd->box[i][j]));
				update_environment(cmd,cmd->box[i][j], value);
				free(value);
			}
			j++;
		}
		i++;
	}
}
