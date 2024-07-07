/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_delone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:16:33 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/07 19:39:05 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void  *del(void *content)
{
	free(content);
	return (NULL);
}

void	dlist_delone(t_dlinked_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->data);
	free(lst);
}
