/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:56:45 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/10 15:27:48 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *list;
	t_list *first;

	if (!lst)
		return (0);
	if (!(list = ft_lstnew(f(lst->content))))
		return (0);
	first = list;
	while (lst)
	{
		if (lst->next)
		{
			if (!(list->next = ft_lstnew(f(lst->next->content))))
			{
				ft_lstclear(&first, del);
				return (0);
			}
			list = list->next;
		}
		lst = lst->next;
	}
	list->next = 0;
	return (first);
}
