/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:56:25 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/03 10:58:46 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		deal_key(int key, t_m *params)
{
	if (key == 125 || key == 1)
		params->move.backward = 1;
	else if (key == 126 || key == 13)
		params->move.forward = 1;
	else if (key == 123)
		params->move.rot_left = 1;
	else if (key == 124)
		params->move.rot_right = 1;
	else if (key == 53)
		exit_game(params);
	else if (key == 0)
		params->move.left = 1;
	else if (key == 2)
		params->move.right = 1;
	return (0);
}

int		release_key(int key, t_m *params)
{
	if (key == 125 || key == 1)
		params->move.backward = 0;
	else if (key == 126 || key == 13)
		params->move.forward = 0;
	else if (key == 123)
		params->move.rot_left = 0;
	else if (key == 124)
		params->move.rot_right = 0;
	else if (key == 0)
		params->move.left = 0;
	else if (key == 2)
		params->move.right = 0;
	return (0);
}
