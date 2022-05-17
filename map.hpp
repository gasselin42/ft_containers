/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:48:23 by gasselin          #+#    #+#             */
/*   Updated: 2022/05/16 09:28:54 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BST.hpp"
#include "utils.hpp"

#include <memory>
#include <stdexcept>

#include <iostream>

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
			typedef				Key 											key_type;
			typedef				T 												mapped_type;
			typedef				ft::pair<const key_type, mapped_type> 			value_type;
			typedef				Compare 										key_compare;
			typedef				Alloc 											allocator_type;
			typedef typename	Alloc::reference 								reference;
			typedef typename	Alloc::const_reference 							const_reference;
			typedef typename	Alloc::pointer 									pointer;
			typedef typename	Alloc::const_pointer 							const_pointer;
			typedef	typename	ft::BST<value_type, Compare>::iterator			iterator;
			typedef	typename	ft::BST<value_type, Compare>::const_iterator	const_iterator;
			typedef				ft::reverse_iterator<iterator> 					reverse_iterator;
			typedef				ft::const_reverse_iterator<const_iterator> 		const_reverse_iterator;
			typedef				ptrdiff_t										difference_type;
			typedef				size_t											size_type;

			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend class map<Key, T, Compare, Alloc>;
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
			BST<value_type, key_compare>	_bst;

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
			void print_map() 
				{
					if (_bst._tri_ptr->parent != _bst._exts->right)
						_bst.print_tree(_bst._tri_ptr->parent, "", true);
				}
		
			map()
				: 	_alloc(),
					_comp(),
					_bst()
				{}
		
			explicit map(const Compare& comp, const Alloc& alloc = Alloc()) 
				: 	_alloc(alloc),
					_comp(comp),
					_bst()
				{}
			
			template <class InputIterator>
				map(InputIterator first, InputIterator last,
					const Compare& comp = Compare(),
					const Alloc& alloc = Alloc(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
					: 	_alloc(alloc),
						_comp(comp),
						_bst()
					{
						if (!(ft::is_iterator<typename ft::iterator_traits<InputIterator>::iterator_category>::value))
							throw (std::length_error("map::constructor"));
						this->insert(first, last);
					}
			
			map(const map& x)
				{ *this = x; }

			~map()
				{ this->_bst.deleteBinaryTree(this->_bst._tri_ptr->parent); }

			// Member functions
			allocator_type get_allocator() const
				{ return (this->_alloc); }

			map& operator=(const map& x)
				{
					if (this == &x)
						return (*this);
					this->_bst.deleteBinaryTree(_bst._tri_ptr->parent);
					this->_bst._tri_ptr->left = this->_bst._exts->right;
					this->_bst._tri_ptr->right = this->_bst._exts->right;
					this->_bst._tri_ptr->parent = this->_bst._exts->right;
					this->_bst.transfer_map(x._bst);
					return (*this);
				}

			iterator begin()
				{ return (iterator(_bst._tri_ptr->left, _bst._tri_ptr, _bst._exts)); }

			const_iterator begin() const
				{ return (const_iterator(_bst._tri_ptr->left, _bst._tri_ptr, _bst._exts)); }

			iterator end()
				{ return (iterator(_bst._exts->right, _bst._tri_ptr, _bst._exts)); }

			const_iterator end() const
				{ return (const_iterator(_bst._exts->right, _bst._tri_ptr, _bst._exts)); }

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
				{
					const size_type num = std::numeric_limits<difference_type>::max();
					const size_type alc = this->_bst.max_size();

					return (std::min(num, alc));
				}

			T& at(const Key& k)
				{
					iterator map_it;

					map_it = this->find(k);
					if (map_it != this->end())
						return ((*map_it).second);
					else
						throw (std::out_of_range("map::at"));
				}

			const T& at(const Key& k) const
				{
					iterator map_it;

					map_it = this->find(k);
					if (map_it != this->end())
						return ((*map_it).second);
					else
						throw (std::out_of_range("map::at"));
				}

			// Check if key_type is already present in the map before insertion
			T& operator[](const Key& k)
				{ return ((this->insert(ft::make_pair(k, T())).first)->second); }

			ft::pair<iterator, bool> insert(const value_type& val)
				{
					if (this->find(val.first) != this->end())
						return (ft::make_pair(this->find(val.first), false));
					else
						return (ft::make_pair((_bst.insertPair(val)).first, true));
				}

			// position: This does not specify the position where the insertion is to be done,
			// it only points to a position from where the searching operation for insertion is
			// to be started to make the process faster. The insertion is done according to the
			// order which is followed by the map container.
			iterator insert(iterator position, const value_type& val)
				{
					(void)position;
					return ((this->insert(val)).first);
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

			size_type erase(const Key& k)
				{
					iterator it = this->find(k);
					if (it == this->end())
						return (0);
					_bst.deleteNode(it);

					return (1);
				}

			void erase(iterator first, iterator last)
				{
					while (first != last)
						this->erase((*(first++)).first);
				}

			// Both maps must have the same templates
			void swap(map& x)
				{ this->_bst.swap(x._bst); }

			void clear()
				{ this->erase(this->begin(), this->end()); }
			
			key_compare key_comp() const
				{ return (key_compare()); }
			
			value_compare value_comp() const
				{ return (value_compare(key_compare())); }
			
			iterator find(const Key& k)
				{ return (_bst.findNode_it(k)); }

			const_iterator find(const Key& k) const
				{ return (_bst.findNode_it_cst(k)); }

			size_type count(const Key& k) const
				{ return ((this->find(k) == this->end()) ? 0 : 1); }

			iterator lower_bound(const Key& k)
				{
					iterator	start = this->begin();
					
					while (start != this->end())
					{
						if (_comp((*start).first, k) == false)
							return (start);
						start++;
					}
					return (this->end());
				}
			
			const_iterator lower_bound(const Key& k) const
				{ 
					const_iterator	start = this->begin();
					
					while (start != this->end())
					{
						if (_comp((*start).first, k) == false)
							return (start);
						start++;
					}
					return (this->end());
				}

			iterator upper_bound(const Key& k)
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

			const_iterator upper_bound(const Key& k) const
				{
					const_iterator	start = this->begin();
					
					while (start != this->end())
					{
						if (_comp(k, (*start).first) == true)
							return (start);
						start++;
					}
					return (this->end());
				}

			ft::pair<iterator, iterator> equal_range(const Key& k)
				{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

			ft::pair<const_iterator, const_iterator> equal_range(const Key& k) const
				{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
	};

	template< class Key, class T, class Compare, class Alloc >
		bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
			{
				if (lhs.size() == rhs.size())
					if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
						return (true);
				return (false);
			}

	template< class Key, class T, class Compare, class Alloc >
		bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
			{ return (!(lhs == rhs)); }

	template< class Key, class T, class Compare, class Alloc >
		bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
			{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template< class Key, class T, class Compare, class Alloc >
		bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
			{ return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }

	template< class Key, class T, class Compare, class Alloc >
		bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
			{ return (!(lhs > rhs)); }

	template< class Key, class T, class Compare, class Alloc >
		bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
			{ return (!(lhs < rhs)); }

	template< class Key, class T, class Compare, class Alloc >
		void swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
			{ lhs.swap(rhs); }
}
