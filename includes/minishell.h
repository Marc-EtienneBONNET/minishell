/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:44 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/14 17:38:15 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_info_cmd
{
	int		nb_maillons;
}	t_info_cmd;

typedef struct s_cmd
{
	char			*cmd;
	char			*path;
	char			*fichier_1;
	char			*fichier_2;
	char			*intra_red;
	char			**arg;
	char			*red;
	t_info_cmd		*info_cmd;
	pid_t			pid;
	int				tub[2];
	struct s_cmd	*next;
	struct s_cmd	*previous;

}	t_cmd;

typedef struct str_env
{
	char	*key;
	char	*var;
}	t_env;

typedef struct s_term
{
	char	**exp;
	char	**envp;
	char	*str_cmd;
	t_cmd	*cmd;
	t_env	*my_env;
	int		dernier_ret;
}	t_term;

t_term *term;

#define ENTRE 1
#define SORTI 0

//hendler
	//hendler.c
void	handler_ctr_c(int code);
void	handler_ctr_c_2(int code);
void	handler_ctr_backslash(int code);

//parsing
	//protocole parsing
t_cmd	*my_parsing(char *cmd_tmp);
	//gestion_var_env
char	*my_take_key_env(char *cmd_tmp, int x);
void	my_inclus_res_var_env_2(char **tmp, int x, char **res, char *str_env);
char	*my_inclus_res_var_env(char **tmp, char *key_env, int x);
char	*my_gestion_var_env(char *cmd_tmp);
int		my_unset(char **argv);
	//tab_cmd
		//init_tab_cmd
char	**my_malloc_chaine(char *cmd_tmp);
int		my_strlen_space(char *str, int *index);
void	my_strlen_space_2(char *str, int *index, int *conteur);
int		my_compte_nb_chaine(char *cmd_tmp);
int		my_avance_chaine(char *cmd_tmp, int *i);
		//rempli tab cmd 
void	my_rempli_cmd(char **tab_cmd, char *cmd_tmp, int *i, int *y);
void	my_rempli_tab_cmd(char **tab_cmd, char *cmd_tmp);
	//4struct_chene_cmd
		//1chenage.c
t_cmd	*my_init_struct_cmd(char **tab_cmd);;
t_cmd	*my_ajoute_maillon(t_cmd *cmd, t_cmd *tmp);
t_cmd	*my_ajoute_maillon_2(t_cmd *cmd, t_cmd *tmp);
		//2create_new_maillon.c
t_cmd	*new_maillons(char **tab_cmd, int *x);
t_cmd	*bzero_tmp(void);
char	**init_cmd_arg(char **tab_cmd, int *x, int *y);
		//#mouv_struct_for_red.c
t_cmd	*my_mouv_struct_for_red(t_cmd **cmd);
	//pars_env
		//my_pars_env
int		my_init_struct_env(void);
	//utile
		//gestion des free
void	*my_free_tab(void *a_free);
void	*my_free_double_tab(void **tab_str, int nb_str);
void	*my_free_liste_chene(t_cmd *cmd);
void	*my_free_maillon(t_cmd *tmp);
		//checker_et_ft_utile.c
int		my_check_redirection(char *str);
char	*my_little_printf_char(char *str);
		//fonction_tmp
int		my_print_list_chene(t_cmd *cmd);
char	*my_modifi_for_export(char *cmd_tmp);

//cmd_ex
	//lancement_ex_cmd.c
int		my_lancement_ex(void);
	//ex_cmd.c
int		my_ex_building(t_cmd *cmd);
int		my_exe_cmd(t_term *term, t_cmd *cmd);
	//gestion_pip
void	my_gestion_pip(t_cmd *cmd);
void	my_tub_entre_sorti_enfant(t_cmd *cmd);
void	my_tub_sorti_entre_parent(t_cmd *cmd);
void	my_kill_tub(void);
	//gestion_red.c
char	*my_choose_fichier(t_cmd *cmd);
pid_t	my_gestion_red(void);
	//heredoc.c
void	my_heredoc(pid_t pid);

//building
	//my_building
int		my_echo(char **argv);
int		my_pwd(t_cmd *cmd);
void	my_env(t_cmd *cmd);
	//my_building_2
int		my_cd(char **argv);
	//my_building_4
int		sort_exp(void);
int		aj_export(char *str);
void	creat_export(void);
int		ft_strcmp(char *str1, char *str2);
int		verif(char *str);
	//my_building_5
int		check_arg(char *str);
int		mess_err2(char *str);
int		check2(char *argv);
int		check_dbl(char *key);
int		change_var(char *key, char *var);
	//my_building_6
int		aj_env_to_exp(char *key, char *var);
	//my_building_7
int		my_export(char **argv);
char	*remp_key(char *dst, char *src);
char	*remp_var(char *dst, char *src);
int		add_elem(char *key, char *var);
int		add_var(t_env *tmp);

#endif
