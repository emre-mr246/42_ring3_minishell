/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:58:39 by emgul             #+#    #+#             */
/*   Updated: 2023/12/10 22:55:24 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start_point;
	t_list	*new;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	start_point = NULL;
	while (lst)
	{
		content = f(lst->content);
		new = ft_lstnew(content);
		if (!new || !content)
		{
			if (content)
				del(content);
			else if (new)
				ft_lstdelone(new, del);
			ft_lstclear(&start_point, del);
			return (NULL);
		}
		ft_lstadd_back(&start_point, new);
		lst = lst->next;
	}
	return (start_point);
}
