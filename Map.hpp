/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:48:23 by gasselin          #+#    #+#             */
/*   Updated: 2022/03/14 15:03:46 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef MAP_HPP
#define MAP_HPP

#include "utils.hpp"
#include "memory"

namespace ft
{
	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
			
	};
}

#endif