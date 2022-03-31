/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:48:23 by gasselin          #+#    #+#             */
/*   Updated: 2022/03/31 16:47:31 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef MAP_HPP
#define MAP_HPP

#include "utils.hpp"
#include "memory"
#include "BST.hpp"

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
			typedef				Key 										key_type;
			typedef				T 											mapped_type;
			typedef				ft::pair<const key_type, mapped_type> 		value_type;
			typedef				Compare 									key_compare;
			typedef				Alloc 										allocator_type;
			typedef typename	allocator_type::reference 					reference;
			typedef typename	allocator_type::const_reference 			const_reference;
			typedef typename	allocator_type::pointer 					pointer;
			typedef typename	allocator_type::const_pointer 				const_pointer;
			typedef				ft::bidir_iterator<value_type, key_compare> iterator;
			typedef				ft::bidir_iterator<const value_type, key_compare>	const_iterator;
			typedef				ft::reverse_iterator<iterator> 				reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator> 		const_reverse_iterator;
			typedef				ptrdiff_t									difference_type;
			typedef				size_t										size_type;

			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, allocator_type>;
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

		private:
			allocator_type 				_alloc;
			size_type					_cont_size;
			size_type					_cont_capacity;
			Compare						_comp;
			BST<value_type, Compare>	_bst;

		public:	
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
			
			template <class InputIterator>
				map(InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type());
			
			map(const map& x)
				{ *this = x; }

			~map();

			// Member functions
			allocator_type get_allocator() const
				{ return (this->_alloc); }

			map& operator=(const map& x);

			iterator begin()
				{ return (this->_bst._begin); }

			const_iterator begin() const
				{ return (this->_bst._begin); }

			iterator end()
				{ return ((this->empty()) ? this->_bst._begin : this->_bst._end); }

			const_iterator end() const
				{ return ((this->empty()) ? this->_bst._begin : this->_bst._end); }

			reverse_iterator rbegin()
				{ return (reverse_iterator(this->end())); }

			const_reverse_iterator rbegin() const
				{ return (const_reverse_iterator(this->end())); }

			reverse_iterator rend()
				{ return (reverse_iterator(this->begin())); }

			const_reverse_iterator rend() const
				{ return (const_reverse_iterator(this->begin())); }

			bool empty() const
				{ return (this->_cont_size == 0); }

			size_type size() const
				{ return (this->_cont_size); }

			size_type max_size() const
				{ return (this->_bst.max_size()); }

			// Check if key_type is already present in the map before insertion
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
			
			key_compare key_comp() const
				{ return (value_compare(key_compare())); }
			
			value_compare value_comp() const
				{ return (value_compare()); }
			
			iterator find(const key_type& k);
			const_iterator find(const key_type& k) const;

			size_type count(const key_type& k) const
				{ return ((this->find(k) == this->end()) ? 0 : 1); }

			iterator lower_bound(const key_type& k);
			const_iterator lower_bound(const key_type& k) const;
			iterator upper_bound(const key_type& k);
			const_iterator upper_bound(const key_type& k) const;
			ft::pair<iterator, iterator> equal_range(const key_type& k);
			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
	};

	template< class Key, class T, class Compare, class Alloc >
		bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
			{ return (lhs == rhs); }

	template< class Key, class T, class Compare, class Alloc >
		bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
			{ return (lhs != rhs); }

	template< class Key, class T, class Compare, class Alloc >
		bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
			{ return (lhs < rhs); }

	template< class Key, class T, class Compare, class Alloc >
		bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
			{ return (lhs <= rhs); }

	template< class Key, class T, class Compare, class Alloc >
		bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
			{ return (lhs > rhs); }

	template< class Key, class T, class Compare, class Alloc >
		bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
			{ return (lhs >= rhs); }
}

#endif
