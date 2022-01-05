/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hendler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/05 14:39:36 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_ctr_c(int code)
{
	(void)code;
	bzero(rl_line_buffer, sizeof(char));
	//printf("ici : %s\n",rl_line_buffer);
	//free(rl_line_buffer);
	if (term->str_cmd)
	{
		free(term->str_cmd);
		term->str_cmd = NULL;
	}
	//write(0,"\n\e[1;34mMinishell> \e[0m",ft_strlen("\e[1;34mMinishell> \e[0m") + 1);
	term->str_cmd = readline("\e[1;34mMinishell> \e[0m");
	my_free_liste_chene(term->cmd);
}


