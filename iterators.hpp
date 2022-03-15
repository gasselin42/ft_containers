/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:20:51 by gasselin          #+#    #+#             */
/*   Updated: 2022/03/15 15:20:08 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef ITERATORS_HPP
#define ITERATORS_HPP

namespace ft
{
	// Empty class to identify the category of an iterator as a random-access iterator:
	class input_iterator_tag {};

	// Empty class to identify the category of an iterator as a random-access iterator:
	class output_iterator_tag {};

	// Empty class to identify the category of an iterator as a random-access iterator:
	class forward_iterator_tag {};

	// Empty class to identify the category of an iterator as a random-access iterator:
	class bidirectional_iterator_tag {};

	// Empty class to identify the category of an iterator as a random-access iterator:
	class random_access_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
		struct iterator {
			typedef T         value_type;
			typedef Distance  difference_type;
			typedef Pointer   pointer;
			typedef Reference reference;
			typedef Category  iterator_category;
		};

	template <class T>
		class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
		{
			
		};
	
	// template <class T>
	// 	class ConstRandomIterator
	// 	{
			
	// 	};

	// template <class T>
	// 	class ReverseRandomIterator
	// 	{
			
	// 	};

	// template <class T>
	// 	class ConstReverseRandomIterator
	// 	{
			
	// 	};
}

#endif