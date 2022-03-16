/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:48:23 by gasselin          #+#    #+#             */
/*   Updated: 2022/03/16 13:03:02 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef MAP_HPP
#define MAP_HPP

#include "utils.hpp"
#include "memory"

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
			typedef				Key 													key_type;
			typedef				T 														mapped_type;
			typedef				ft::pair<const key_type, mapped_type> 					value_type;
			typedef				Compare 												key_compare;
			typedef				Alloc 													allocator_type;
			typedef typename	allocator_type::reference 								reference;
			typedef typename	allocator_type::const_reference 						const_reference;
			typedef typename	allocator_type::pointer 								pointer;
			typedef typename	allocator_type::const_pointer 							const_pointer;
			typedef				ft::bidir_iterator<value_type> 							iterator;
			typedef				ft::const_bidir_iterator<value_type> 					const_iterator;
			typedef				ft::reverse_iterator<bidir_iterator> 					reverse_iterator;
			typedef				ft::reverse_iterator<const_bidir_iterator> 				const_reverse_iterator;
			typedef typename	ft::iterator_traits<bidir_iterator>::difference_type	difference_type;
			typedef typename	allocator_type::size_type								size_type;
			class value_compare
			{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

					bool operator() (const value_type& x, const value_type& y) const
						{ return comp(x.first, y.first); }
			};

			// Constructors and Destructor
			map();
			
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
			
			template <class InputIterator>
				map(InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type());
			
			map(const map& x);
			~map();

			// Member functions
			map& operator=(const map& x);
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			bool empty() const;
			size_type size() const;
			size_type max_size() const;
			mapped_type& operator[](const key_type& k);
			ft::pair<iterator, bool> insert(const value_type& val);
			iterator insert(iterator position, const value_type& val);
			
			template <class InputIterator>
				void insert(InputIterator first, InputIterator last);

			void erase(iterator position);
			size_type erase(const key_type& k);
			void erase(iterator first, iterator last);
			void swap(map& x);
			void clear();
			key_compare key_comp() const;
			value_compare value_comp() const;
			iterator find(const key_type& k);
			const_iterator find(const key_type& k) const;
			size_type count(const key_type& k) const;
			iterator lower_bound(const key_type& k);
			const_iterator lower_bound(const key_type& k) const;
			iterator upper_bound(const key_type& k);
			const_iterator upper_bound(const key_type& k) const;
			ft::pair<iterator, iterator> equal_range(const key_type& k);
			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
	};
}

#endif
