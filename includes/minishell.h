/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:17 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/04 16:53:14 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
#include <errno.h>

//buffer get_next_line
# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 700
# endif

#define clear() printf("\033[H\033[J")

typedef struct s_var t_var;
typedef struct s_flags t_flags;

extern int g_exitstatus;
extern char **environ;

typedef struct s_var {

    char    *nome;
    char    *content;
    t_var   *next;
}   t_var;

typedef struct s_cmd {

    char    *cmd;
    int     var_count;
    char    **parsed;
    char    **var;
    char    **envp; //export
    char    **envp2; //env
    int     squote;
    int     dquote;
    int     syntax_err;
    int     nbr_pipe;
    char    ***box;
    char    **new_cmd;
    char    *output;
    char    *input;
    t_var   *variable;
    t_flags *f;
}   t_cmd;

typedef struct s_flags {
    
	int	re_in;
	int	re_out;
	int	write_in;
	int	append_out;
	int	pipe;
	int	quote;
	int d_quote;
	int	in;
	int	out;;
}   t_flags;

void    exe_basic_cmd(char **parsed, char *command, char **envp);
int		check_var_loop(char **parsed);
int     is_valid_command(const char* string);
void    variables(t_cmd *cmd, char ***box);
int     is_there_more_commands(t_cmd *cmd, char **parsed);
void    ft_strstr(t_cmd *cmd, int j, int i, char **parsed);
void    check_redirects_out(t_cmd *cmd, char **parsed);
int     check_exe(char **parsed);
void    exe_cmd_usr(char **parsed, char *command, char **envp);
void	cmd_not_found(char **cmd);
void	free_split(char **args);
char	*path(char *cmd, char **envp);
char	*get_next_line(int fd);
char	*_strjoin(char *str, char *buff);
size_t	_strlen(char *s);
char	*new_txt(char *txt);
char	*_strchr(char *s, int c);
void    loop();
void    handler(int sig_num);
void    custom_commands(t_cmd *cmd, char **parsed, char **envp);
char    *remove_tilde(char *str);
int     ft_strcmp(const char *s1, const char *s2);
int     check_dir(char **parsed);
void	handle_var(char **parsed, t_cmd *cmd);
int     check_cmds(char **parsed, int j);
void    ft_export(t_cmd *cmd, char **parsed, char **envp);
void    print_envp(char **envp, char **parsed);
int     check_empty(t_cmd *cmd);
void    parse_input(t_cmd *cmd, char **envp);
void    process_input(t_cmd *cmd, char **parsed);
void    exeArgs(t_cmd *cmd, int j, int i);
void	ft_strcpy(char *dst, const char *src);
char    *find_command_path(const char* command);
void    execute_command(char*** commands, t_cmd *cmd, int num_pipe, char **envp);
void	look_var(t_cmd *cmd);
void	print_envp2(char **envp);

// BUILTINS AND REDIRECTIONS

void    ft_env(t_cmd *cmd, char **parsed, char **envp);
void    ft_pwd();
void    ft_exit();
int     check_cd(char **parsed);
int     printDirectoryContents(char **parsed);
void    ft_cd(char **parsed);
void    ft_prova_redirect(t_cmd *cmd, int j);
void    handle_input_redirection(char* filename) ;
void    handle_output_redirection(char* filename);
void    handle_input_heredoc(char* delimiter);
void    handle_output_append_redirection(char* filename);
void    handle_here_doc_input(const char* delimiter);
void	ft_unset(char **parsed, char **envp);
//EXE

void redirect_input(int i, t_cmd* cmd, int pipe_fds[][2]);
void redirect_output(int i, int last_command_index, t_cmd* cmd, int pipe_fds[][2], int original_stdout);
void execute_child_process(int i, char*** commands, t_cmd* cmd, char** environ, char** envp);
void close_pipe_fds(int i, int num_pipes, int pipe_fds[][2]);
void restore_stdout(int original_stdout);
char    *find_command_path(const char* command);
void    expand_var(t_cmd *cmd);
void execute_command2(char*** commands, t_cmd *cmd, int num_pipes, char **envp);

// ENVIRON
int    check_environ_ez(t_cmd *cmd, int j, char **parsed);
int    check_list(t_cmd *cmd, int i, char **parsed);
void    add_lst_ez(t_cmd *cmd, char *parsed);
int    check_environ(t_cmd *cmd, int j, char **parsed);
int    check_environ2(t_cmd *cmd, int j, char **parsed);
int ft_putenv_ez(char *name, t_cmd *cmd);
int ft_putenv(char *name, char *value, t_cmd *cmd);
void	look_var_envp(t_cmd *cmd, char **envp);
void	up_environ(char *current);
void	up_envp(char *current, char **envp);

// UTILS

size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int ft_putenv(char *nome, char *content, t_cmd *cmd);
void	ft_signal_ctrl_bs(int sig);
void	ft_signal_ctrl_c(int sig);
char	*take_content(char *parsed);
char	*take_content_ez(char *parsed);
char	*take_var(char *parsed);
int	check_var(char *parsed);
void    export_full(t_cmd *cmd, int i, char **parsed);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void    parsing(t_cmd   *cmd);
char	*ft_strchr(const char *s, int c);


// LISTE VARIABILI
t_var	*ft_lstlast(t_var *lst);
void	ft_lstadd_back(t_var **lst, t_var *new);
t_var	*ft_lst(char *nome, char *content);
int	ft_lstiter(t_var *lst, char *nome, char *content);
t_var	*ft_lst_addcontent(t_var *lst, void *content, void *nome);
int	    ft_lstcount(t_var *lst);
void	ft_lstprint(t_var *lst);
int	ft_lstcount(t_var *lst);
void	ft_lstadd_back(t_var **lst, t_var *new);

// GESTIONE FLAG PER CARATTERI SPECIALI
void	flag_init(t_cmd *cmd);
void	flag_checker(t_cmd *cmd);
void    flag_checker2(t_cmd *cmd);
void    print_flags(t_cmd *cmd);


#endif