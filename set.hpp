/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:52:47 by gasselin          #+#    #+#             */
/*   Updated: 2022/08/17 20:11:04 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BST_set.hpp"
#include "utils.hpp"

#include <memory>
#include <stdexcept>

#include <iostream>

namespace ft
{
	template < class Key, class Compare = ft::less<Key>, class Alloc = std::allocator<Key> >
	class set
	{
		public:
			typedef				Key 										key_type;
			typedef				Key 										value_type;
			typedef				size_t										size_type;
			typedef				ptrdiff_t									difference_type;
			typedef				Compare 									key_compare;
			typedef				Compare 									value_compare;
			typedef				Alloc										allocator_type;
			typedef 			value_type&		 							reference;
			typedef 			const value_type&							const_reference;
			typedef typename	Alloc::pointer 								pointer;
			typedef typename	Alloc::const_pointer 						const_pointer;
			typedef	typename	ft::BST_set<Key, Compare>::iterator			iterator;
			typedef	typename	ft::BST_set<Key, Compare>::const_iterator	const_iterator;
			typedef				ft::reverse_iterator<iterator> 		reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator> const_reverse_iterator;

		private:
			Alloc					_alloc;
			Compare					_comp;
			BST_set<Key, Compare>	_bst;

		public:
			set()
				: 	_alloc(),
					_comp(),
					_bst()
				{}
		
			explicit set(const Compare& comp, const Alloc& alloc = Alloc()) 
				: 	_alloc(alloc),
					_comp(comp),
					_bst()
				{}
			
			template <class InputIterator>
				set(InputIterator first, InputIterator last,
					const Compare& comp = Compare(),
					const Alloc& alloc = Alloc())
					: 	_alloc(alloc),
						_comp(comp),
						_bst()
					{
						this->insert(first, last);
					}
			
			set(const set& x)
				{ *this = x; }

			~set()
				{ this->_bst.deleteBinaryTree(this->_bst._tri_ptr->parent); }

			// Member functions
			allocator_type get_allocator() const
				{ return (this->_alloc); }

			set& operator=(const set& x)
				{
					if (this == &x)
						return (*this);
					this->_bst.deleteBinaryTree(_bst._tri_ptr->parent);
					this->_bst._tri_ptr->left = NULL;
					this->_bst._tri_ptr->right = NULL;
					this->_bst._tri_ptr->parent = NULL;
					this->_bst.transfer_map(x._bst);
					return (*this);
				}

			iterator begin()
				{
					if (empty())
						return (this->end());
					return (iterator(_bst._tri_ptr->left, _bst._tri_ptr));
				}

			const_iterator begin() const
				{
					if (empty())
						return (this->end());
					return (const_iterator(_bst._tri_ptr->left, _bst._tri_ptr));
				}

			iterator end()
				{ return (iterator(_bst._end, _bst._tri_ptr)); }

			const_iterator end() const
				{ return (const_iterator(_bst._end, _bst._tri_ptr)); }

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

			ft::pair<iterator, bool> insert(const value_type& val)
				{
					if (this->find(val) != this->end())
						return (ft::make_pair(this->find(val), false));
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
				void insert(InputIterator first, InputIterator last)
					{
						difference_type diff = std::distance(first, last);
						while (diff--)
							this->insert(*(first++));
					}

			void erase(iterator position)
				{ this->erase(*position); }

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
						this->erase(*(first++));
				}

			// Both maps must have the same templates
			void swap(set& x)
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
				{ return (_bst.findNode_it(k)); }

			size_type count(const Key& k) const
				{ return ((this->find(k) == this->end()) ? 0 : 1); }

			iterator lower_bound(const Key& k)
				{ return (_bst.lower_bound(k)); }
			
			const_iterator lower_bound(const Key& k) const
				{ return (_bst.lower_bound(k)); }

			iterator upper_bound(const Key& k)
				{ return (_bst.upper_bound(k)); }

			const_iterator upper_bound(const Key& k) const
				{ return (_bst.upper_bound(k)); }

			ft::pair<iterator, iterator> equal_range(const Key& k)
				{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

			ft::pair<const_iterator, const_iterator> equal_range(const Key& k) const
				{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
	};

	template< class Key, class Compare, class Alloc >
		bool operator==(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
			{
				if (lhs.size() == rhs.size())
					if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
						return (true);
				return (false);
			}

	template< class Key, class Compare, class Alloc >
		bool operator!=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
			{ return (!(lhs == rhs)); }

	template< class Key, class Compare, class Alloc >
		bool operator<(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
			{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template< class Key, class Compare, class Alloc >
		bool operator>(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
			{ return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }

	template< class Key, class Compare, class Alloc >
		bool operator<=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
			{ return (!(lhs > rhs)); }

	template< class Key, class Compare, class Alloc >
		bool operator>=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
			{ return (!(lhs < rhs)); }

	template< class Key, class Compare, class Alloc >
		void swap(ft::set<Key,Compare,Alloc>& lhs, ft::set<Key,Compare,Alloc>& rhs)
			{ lhs.swap(rhs); }
}
