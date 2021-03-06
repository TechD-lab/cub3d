/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:46:38 by jinspark          #+#    #+#             */
/*   Updated: 2021/05/07 13:46:49 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strarrlen(char **info)
{
	size_t	i;

	i = 0;
	while (info[i])
		i++;
	return (i);
}
