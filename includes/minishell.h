/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:17 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/23 18:40:48 by pcocci           ###   ########.fr       */
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
# include <errno.h>

typedef struct s_var	t_var;
typedef struct s_flags	t_flags;

extern int				g_exitstatus;

typedef struct s_exe {
	int		input_fd;
	int		output_fd;
	int		original_stdout;
	int		num_pipes;
	int		last_command_index;
	pid_t	pid;
}	t_exe;

typedef struct s_index {
	int	i_in;
	int	i_out;
}	t_index;

typedef struct s_int {
	int	i;
	int	j;
}	t_int;

typedef struct s_cmd {
	char	*cmd;
	char	*shell_prompt;
	char	**cpy_env;
	int		fine;
	int		count;
	int		exitstatus;
	char	**parsed;
	char	**var;
	char	**envp;
	char	**envp2;
	int		squote;
	int		dquote;
	int		syntax_err;
	int		nbr_pipe;
	char	***box;
	char	**new_cmd;
	char	*output;
	char	*input;
	int		hd_i;
	int		hd_j;
	int		tmp;
	int		f_echo;
	t_exe	exe;
	t_index	*index;
	t_flags	*f;
	t_int	*ints;
}	t_cmd;

typedef struct s_flags {
	int	re_in;
	int	re_out;
	int	write_in;
	int	append_out;
	int	pipe;
	int	quote;
	int	d_quote;
	int	in;
	int	out;
}	t_flags;

void	exe_basic_cmd(char **parsed, char *command, char **envp);
void	realloc_env(t_cmd *cmd, int i);
void	copy_envp(t_cmd *cmd, char **envp);
void	copy_envp2(t_cmd *cmd, char **envp, int j);
int		check_var_loop(char **parsed);
int		is_valid_command(const char	*string, t_cmd *cmd);
void	variables(t_cmd	*cmd, char	***box);
int		is_there_more_commands(t_cmd *cmd, char **parsed);
void	ft_strstr(t_cmd *cmd, int j, int i, char **parsed);
int		check_redirects_out(t_cmd *cmd, char **parsed, int i, int j);
int		check_exe(char **parsed);
void	exe_cmd_usr(char **parsed, char *command, char **envp);
void	cmd_not_found(char **cmd);
void	free_split(char **args);
char	*path(char *cmd, char **envp);
char	*get_next_line(int fd);
char	*_strjoin(char *str, char *buff);
size_t	_strlen(char *s);
char	*new_txt(char *txt);
char	*_strchr(char *s, int c);
void	loop(t_cmd *cmd, char **envp);
void	handler(int sig_num);
void	custom_commands(t_cmd *cmd, char **parsed, char **envp);
char	*remove_tilde(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		check_dir(char **parsed);
void	handle_var(char **parsed, t_cmd *cmd);
int		check_cmds(char **parsed, int j);
void	ft_export(t_cmd *cmd, char **parsed, char **envp);
void	print_envp(char **envp, char **parsed);
int		check_empty(t_cmd *cmd);
void	parse_input(t_cmd *cmd, char **envp);
void	process_input(t_cmd *cmd, char **parsed);
void	exeargs(t_cmd *cmd);
void	ft_strcpy(char *dst, const char *src);
void	execute_command(t_cmd *cmd, int num_pipe, char **envp);
void	look_var(t_cmd *cmd, char **envp);
void	print_envp2(char **envp);
void	convert(t_cmd *cmd);
void	convert_dquote(t_cmd *cmd);
int		ft_chr(char *cmd, char c, int i);
char	*ft_strdup(const char *s);
void	ft_done(t_cmd *cmd);
void	free_in_out(t_cmd *cmd);
void	new_cmd(t_cmd *cmd, int i);
void	many_cmd(t_cmd *cmd, int i);

// BUILTINS AND REDIRECTIONS

void	ft_env(t_cmd *cmd, char **parsed, char **envp);
void	ft_pwd(void);
void	ft_exit(t_cmd *cmd);
int		check_cd(char **parsed);
int		printDirectoryContents(char **parsed);
void	ft_cd(char **parsed);
void	ft_prova_redirect(t_cmd *cmd, int j);
void	handle_input_redirection(char	*filename);
void	handle_output_redirection(char	*filename);
void	handle_input_heredoc(char	*delimiter);
void	handle_output_append_redirection(char	*filename);
void	ft_unset(char **parsed, t_cmd *cmd);
//EXE

void	close_pipe_fds(int i, int num_pipes, int pipe_fds[][2]);
void	restore_stdout(int original_stdout);
void	expand_var(t_cmd *cmd);

// ENVIRON
int		check_environ_ez(t_cmd *cmd, int j, char **parsed);
int		check_list(t_cmd *cmd, int i, char **parsed);
void	add_lst_ez(t_cmd *cmd, char *parsed);
int		check_environ(t_cmd *cmd, int j, char **parsed);
int		check_environ2(t_cmd *cmd, int j, char **parsed);
int		ft_putenv_ez(char *name, t_cmd *cmd);
int		ft_putenv(char *name, char *value, t_cmd *cmd);
void	look_var_envp(t_cmd *cmd, char **envp);
void	up_environ(char *current);
//void	up_envp(char *current, char **envp);
void	up_envp(char *current, char **envp, t_cmd *cmd);
void 	free_envp(t_cmd *cmd);
void	unset_update(t_cmd *cmd, int i);

// UTILS

size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_putenv(char *nome, char *content, t_cmd *cmd);
void	ft_signal_ctrl_bs(int sig);
void	ft_signal_ctrl_c(int sig);
char	*getcnt(char *parsed, int i, int len);
char	*take_content_ez(char *parsed);
char	*take_var(char *parsed);
int		check_var(char *parsed);
void	export_full(t_cmd *cmd, int i, char **parsed);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	parsing(t_cmd *cmd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_getenv(char *var, t_cmd *cmd);

// PIPE
void	checking_redir(t_cmd *cmd, int i);
void	inter_exe(t_cmd *cmd, char **envp, int i);
void	open_pipes(int i, int num_pipes, int pipe_fds[num_pipes][2]);
void	close_pipes(int i, int pipe_fds[i][2]);
void	expand_var(t_cmd *cmd);
void	redirect_input(t_cmd *cmd, t_exe *exe, int i, int pipe_fds[i][2]);
void	redirect_output(t_cmd *cmd, t_exe *exe, int i, int pipe_fds[i][2]);
void	set_struct(t_exe *exe, int num_pipes);
void	error_fork(pid_t pid);
void	many_redir(t_cmd *cmd, int i);
int		count_redir(t_cmd *cmd, int i);
char	*find_command_path(const char *c, char *path, char *p_e, t_cmd *cmd);

// LISTE VARIABILI
t_var	*ft_lstlast(t_var *lst);
void	ft_lstadd_back(t_var **lst, t_var *new);
t_var	*ft_lst(char *nome, char *content);
int		ft_lstiter(t_var *lst, char *nome, char *content);
t_var	*ft_lst_addcontent(t_var *lst, void *content, void *nome);
int		ft_lstcount(t_var *lst);
void	ft_lstprint(t_var *lst);
int		ft_lstcount(t_var *lst);
void	ft_lstadd_back(t_var **lst, t_var *new);

// GESTIONE FLAG PER CARATTERI SPECIALI
void	flag_init(t_cmd *cmd);
void	flag_checker(t_cmd *cmd);
void	flag_checker2(t_cmd *cmd);
void	print_flags(t_cmd *cmd);

// HEREDOC
void	look_here_doc(t_cmd *cmd, int i, int j);
void	handle_here_doc_input(const char *delimiter, t_cmd *cmd, int j, int i);
void	out_heredoc(t_cmd *cmd);
int		in_fd(t_cmd *cmd, int j, int i);
void	out_heredoc_help(t_cmd *cmd, int i, int j);
void	search(t_cmd *cmd, int i, int j);
void	print_parsed_box(t_cmd *cmd);
void	search_here(t_cmd *cmd);
void	alloc_out(t_cmd *cmd, int i, int j);

// BUILTINS
int		check_echo(char **parsed, int n);
void	echo_no_dollar(char **parsed, int n, int flag);
void	ft_putstr(char *parsed);
void	echo_dollar(char **parsed, int n, t_cmd *cmd, int squote);
char	*ft_putstr_quota(char *parsed);
void	write_line(int input_fd, char *line);

//FREE
void	free_box(t_cmd *cmd);
void	free_altro(t_cmd *cmd);
void	free_dpointer(char **dpoint);
#endif