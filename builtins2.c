/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/23 18:36:59 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_env(t_cmd *cmd, char **parsed, char **envp)
{	
	(void)envp;

	if (ft_strcmp(parsed[0], "env") == 0 && (parsed[1] == NULL
			|| cmd->f->re_out == 1))
	{
		print_envp2(cmd->cpy_env);
		g_exitstatus = 0;
	}
	else if (ft_strcmp(parsed[0], "env") == 0 && parsed[1] != NULL)
		g_exitstatus = 130;
}

void	delete_content(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '=')
		i++;
	tmp = malloc((sizeof(char)) * (i + 2));
	i = 0;
	while (str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '=';
	tmp[i + 1] = 0;
	ft_strcpy(str, tmp);
}

void	unset_enviroment(char	*varname, char	**envp)
{
	int	index;
	//int	found;
	int	i;

	index = 0;
	//found = 0;
	while (envp[index] != NULL)
	{
		if (strncmp(envp[index], varname, strlen(varname)) == 0
			&& envp[index][strlen(varname)] == '=')
		{	
			i = index;
			if (envp[i + 1] != NULL)
			{
				//envp[i] = envp[i + 1];
				ft_strcpy(envp[i], envp[i + 1]);
			}
			else
			{	
				free(envp[i]);
				envp[i] = NULL;
			}
			//found = 1;
			break ;
		}
		index++;
	}
}

/* void	unset_environ(char **parsed, int i, int j)
{	
	char	*var;

	while (parsed[j])
	{
		i = 0;
		while (environ[i])
		{	
			var = take_var(environ[i]);
			if (ft_strcmp(parsed[j], var) == 0)
				unset_enviroment(parsed[j], environ);
			free(var);
			i++;
		}
		j++;
	}
} */

void unset_variable(t_cmd* cmd, const char* variable) 
{
	int i;
    int env_size = 0;
    char** env = cmd->cpy_env;
	//int f;

    if (cmd == NULL || cmd->cpy_env == NULL || variable == NULL)
        return;

    // Count the number of environment variables
    while (env[env_size] != NULL)
        env_size++;
    // Create a new environment array without the specified variable
    char** new_env = (char**)malloc((env_size + 1) * sizeof(char*));
    int new_env_index = 0;

    for (int i = 0; i < env_size; i++) {
        if (strncmp(env[i], variable, strlen(variable)) != 0) {
            // Copy variables that don't match the unset variable
            char* var_copy = strdup(env[i]);
            if (var_copy == NULL) {
                fprintf(stderr, "Failed to allocate memory.\n");
                // Cleanup if memory allocation fails
                for (int j = 0; j < new_env_index; j++)
                    free(new_env[j]);
                free(new_env);
                return;
            }
            new_env[new_env_index] = var_copy;
            new_env_index++;
        }
    }
    new_env[new_env_index] = NULL;
	i = 0;
    // Free the original environment array
    while (i < env_size)
	{	
		//if (i != f)
        free(env[i]);
		i++;
	}

    free(env);

    // Update the cmd structure with the new environment array
    cmd->cpy_env = new_env;
}

void	ft_unset(char **parsed, t_cmd *cmd)
{
	int		j;

	j = 1;
	while (parsed[j])
	{
		unset_variable(cmd, parsed[j]);
		j++;
	}
}
