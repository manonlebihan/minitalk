/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:46:26 by mle-biha          #+#    #+#             */
/*   Updated: 2022/06/17 15:39:21 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	new = ft_lstnew((*f)(lst->content));
	if (new == NULL)
	{
		ft_lstclear(&new, del);
		return (NULL);
	}
	tmp = new;
	lst = lst->next;
	while (lst != NULL)
	{
		ft_lstadd_back(&tmp, ft_lstnew(f(lst->content)));
		if (tmp->next == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		tmp = tmp->next;
		lst = lst->next;
	}
	tmp->next = NULL;
	return (new);
}
