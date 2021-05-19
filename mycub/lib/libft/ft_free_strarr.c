/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strarr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:35:11 by jinspark          #+#    #+#             */
/*   Updated: 2021/05/12 16:35:12 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_strarr(char **info)
{
	int	i;

	i = 0;
	while (info[i])
	{
		free(info[i]);
		i++;
	}
	free(info);
	return (NULL);
}
