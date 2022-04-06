/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidir_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:16:38 by gasselin          #+#    #+#             */
/*   Updated: 2022/04/06 14:52:53 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef BIDIR_ITERATOR_HPP
#define BIDIR_ITERATOR_HPP

#include "iterators.hpp"

namespace ft
{
	template < class T, class Compare >
		class bidir_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
		{
			public:
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type 	difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type 		value_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;

			private:
				pointer _node;

			public:

				bidir_iterator() {}

				bidir_iterator(T * node)
					: _node(node)
					{}

				virtual ~bidir_iterator() {}
		};
}

/*
iterator(const Compare& comp = Compare())
iterator(T * node_p, T * last_node, const Compare& comp = Compare())
iterator(const iterator& it)
virtual ~iterator()

iterator &operator=(const iterator& it)
bool operator==(const iterator& it)
bool operator!=(const iterator& it)
reference operator*() const
pointer operator->() const

iterator& operator++(void)
iterator operator++(int)
iterator& operator--(void)
iterator operator--(int)

T *			_node;
T *			_last_node;
Compare     _comp;
*/
#endif