/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:03:33 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:44:19 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*actual;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	res = ft_lstnew(f(lst->content));
	if (res == NULL)
		return (NULL);
	actual = res;
	lst = lst->next;
	while (lst)
	{
		actual->next = ft_lstnew(f(lst->content));
		if (actual->next == NULL)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		actual = actual->next;
		lst = lst->next;
	}
	return (res);
}
