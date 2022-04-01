/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:48:23 by gasselin          #+#    #+#             */
/*   Updated: 2022/04/01 16:03:02 by gasselin         ###   ########.fr       */
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
			allocator_type 		_alloc;
			Compare				_comp;
			BST<value_type>		_bst;

			template <class InputIterator>
				difference_type get_diff(InputIterator first, InputIterator last)
					{
						difference_type diff = 0;
						while (first != last)
						{
							diff++;
							first++;
						}
						return (diff);
					}

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

			map& operator=(const map& x)
				{
					if (*this == x)
						return (*this);
					this->clear();
					this->_bst._begin = NULL;
					this->_bst._end = NULL;
					this->_bst.transfer_map(x._bst);
					return (*this);
				}

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
				{ return (this->_bst.get_size() == 0); }

			size_type size() const
				{ return (this->_bst.get_size()); }

			size_type max_size() const
				{ return (this->_bst.max_size()); }

			// Check if key_type is already present in the map before insertion
			mapped_type& operator[](const key_type& k)
				{ return ((this->insert(ft::make_pair(k,mapped_type())).first)->second); }

			ft::pair<iterator, bool> insert(const value_type& val)
				{
					if (this->find(val.first) != this->end())
						return (ft::make_pair(this->find(val.first), false));
					else
						return (ft::make_pair(this->insert(this->_bst._root, val), true));
				}

			// position: This does not specify the position where the insertion is to be done,
			// it only points to a position from where the searching operation for insertion is
			// to be started to make the process faster. The insertion is done according to the
			// order which is followed by the map container.
			iterator insert(iterator position, const value_type& val)
				{
					(void)position;
				}
			
			template <class InputIterator>
				void insert(InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
					{
						if (!(ft::is_iterator<typename ft::iterator_traits<InputIterator>::iterator_category>::value))
							throw (std::length_error("map::insert"));
						difference_type diff = get_diff(first, last);
						while (diff--)
							this->insert(*(first++));
					}

			void erase(iterator position)
				{ this->erase((*position).first); }

			size_type erase(const key_type& k);

			void erase(iterator first, iterator last)
				{
					while (first != last)
						this->erase((*(first++)).first);
				}

			// Both maps must have the same templates
			void swap(map& x)
				{
					this->_bst.swap(x._bst);
				}

			void clear();
			
			key_compare key_comp() const
				{ return (value_compare(key_compare())); }
			
			value_compare value_comp() const
				{ return (value_compare()); }
			
			iterator find(const key_type& k)
				{
					iterator start = this->begin();

					while (start != this->end())
					{
						if ((*start).first == k)
							return (start);
						start++;
					}
					return (this->end());
				}

			const_iterator find(const key_type& k) const
				{
					const_iterator start = this->begin();

					while (start != this->end())
					{
						if ((*start).first == k)
							return (start);
						start++;
					}
					return (this->end());
				}

			size_type count(const key_type& k) const
				{ return ((this->find(k) == this->end()) ? 0 : 1); }

			iterator lower_bound(const key_type& k)
				{
					iterator	start = this->begin();
					
					while (start != this->end())
					{
						if (_comp((*start).first, k) == false)
							return (start);
						start++;
					}
					return (this->end);
				}
			
			const_iterator lower_bound(const key_type& k) const
				{ return (const_iterator(lower_bound(k))); }

			iterator upper_bound(const key_type& k)
				{
					iterator	start = this->begin();
					
					while (start != this->end())
					{
						if (_comp(k, (*start).first) == true)
							return (start);
						start++;
					}
					return (this->end());
				}

			const_iterator upper_bound(const key_type& k) const
				{ return (const_iterator(this->upper_bound(k))); }

			ft::pair<iterator, iterator> equal_range(const key_type& k)
				{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
				{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
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

	template< class Key, class T, class Compare, class Alloc >
		void swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
			{ lhs.swap(rhs); }
}

#endif
