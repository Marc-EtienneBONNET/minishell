/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_choose_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:15:46 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 13:59:12 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_take_fichier_and_intra_red(char *str, t_cmd *tmp)
{
	int		x;
	int		gu;
	int		red;

	x = -1;
	gu = 0;
	while (str[++x])
	{
		my_check_guil(&gu, str[x]);
		red = my_check_redirection(&(str[x]));
		if (red > 1)
			tmp->intra_red = recup_red(&(str[x]));
		if (red == 3)
			x++;
		if (red > 1 && gu == 0 && !tmp->fichier_1)
			tmp->fichier_1 = recup_element(str, ++x);
		else if (red > 1 && gu == 0 && tmp->fichier_1)
			tmp->fichier_2 = recup_element(str, ++x);
	}
}

int	my_passe_fichier(int x, int red, char *str, int *gu)
{
	x++;
	if (red == 3)
		x++;
	while (ft_whitespace(str[x]) == 1)
		x++;
	while (str[x])
	{
		my_check_guil(gu, str[x]);
		if (*gu == 0 && (ft_whitespace(str[x]) == 1
				|| my_check_redirection(&(str[x])) > 0
				|| !str[x]))
			break ;
		x++;
	}
	return (x);
}

char	**my_choose_var_env_path(void)
{
	int	x;

	x = 0;
	while (g_term.my_env[x].key
		&& ft_strncmp(g_term.my_env[x].key, "PATH=", 5) != 0)
		x++;
	if (!g_term.my_env[x].key)
		return (NULL);
	return (ft_split(g_term.my_env[x].var, ':'));
}

char	*my_choose_path(t_cmd *tmp)
{
	int		x;
	char	**path;
	char	*tmp_2;
	char	*tmp_3;

	x = -1;
	path = my_choose_var_env_path();
	while (path[++x])
	{
		tmp_2 = ft_strjoin(path[x], "/");
		tmp_3 = ft_strjoin(tmp_2, tmp->cmd);
		if (access(tmp_3, F_OK) != 0)
		{
			my_free_tab(tmp_2);
			my_free_tab(tmp_3);
			if (path[x + 1] == NULL)
				return (my_free_double_tab((void **)path, -1));
			continue ;
		}
		my_free_tab(tmp_3);
		break ;
	}
	my_free_double_tab((void **)path, -1);
	return (tmp_2);
}
