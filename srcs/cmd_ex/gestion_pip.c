/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_pip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:34:21 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 18:06:53 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_tub_entre_sorti_enfant(t_cmd *cmd)
{
	close(cmd->tub[SORTI]);
	dup2(cmd->tub[ENTRE], 1);
	close(cmd->tub[ENTRE]);
}

void	my_tub_sorti_entre_parent(t_cmd *cmd)
{
	close(cmd->tub[ENTRE]);
	dup2(cmd->tub[SORTI], 0);
	close(cmd->tub[SORTI]);
}

void	my_gestion_pip(t_cmd *cmd)
{
	if (ft_strncmp(cmd->red, "|", 3) == 0)
	{
		if (cmd->pid == 0)
			my_tub_entre_sorti_enfant(cmd);
		else
			my_tub_sorti_entre_parent(cmd);
	}
}

void	my_kill_tub(void)
{
	int	x;

	x = 0;
	while (x < g_term->cmd->info_cmd->nb_maillons)
	{
		close(g_term->cmd->tub[ENTRE]);
		close(g_term->cmd->tub[SORTI]);
		dup2(ENTRE, SORTI);
		g_term->cmd = g_term->cmd->next;
		x++;
	}
}
