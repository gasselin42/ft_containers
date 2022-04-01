/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:49:41 by gasselin          #+#    #+#             */
/*   Updated: 2022/04/01 16:26:04 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef BST_HPP
#define BST_HPP

#include "bidir_iterator.hpp"
#include "utils.hpp"
#include <memory>

namespace ft
{
	template <class T>
		class BST_Node
		{
			public:
				typedef T value_type;

				value_type value;
				BST_Node& parent;
				BST_Node& left;
				BST_Node& right;

				BST_Node() : value(), parent(NULL), left(NULL), right(NULL) {}
				
				BST_Node(const value_type& val, BST_Node& _parent = NULL, BST_Node& _left = NULL, BST_Node& _right = NULL)
					:	value(val),
						parent(_parent),
						left(_left),
						right(_right)
					{}

				BST_Node(const BST_Node& rhs)
					:	value(rhs.value),
						parent(rhs.parent),
						left(rhs.left),
						right(rhs.right)
					{}

				~BST_Node() {}

				BST_Node& operator=(const BST_Node& rhs)
					{
						this->value = rhs.value;
						this->parent = rhs.parent;
						this->left = rhs.left;
						this->right = rhs.right;
						
						return (*this);
					}
		};
	
	template <class T, class Compare = ft::less<T>, class Node = ft::BST_Node<T>, class Node_Alloc = std::allocator<Node> >
		class BST
		{
			public:
				typedef BST self;
				typedef Node * node_ptr;
				typedef Node_Alloc node_alloc;
				typedef	size_t	size_type;
				typedef T value_type;
				typedef ft::bidir_iterator<Node, Compare> iterator;
				
			private:
				node_ptr _begin;
				node_ptr _end;
				node_ptr _root;
				node_alloc _node_alloc;
				size_type _map_size;

			public:
				BST() {};
				~BST() {};

				ft::pair<iterator, bool> insertPair(value_type pr);

				size_type max_size() const
					{ return (this->_node_alloc.max_size()); }

				// https://stackoverflow.com/questions/21143835/can-i-implement-an-autonomous-self-member-type-in-c
				void swap(self& x)
					{
						node_ptr tmp1 = x._root;
						node_ptr tmp2 = x._begin;
						node_ptr tmp3 = x._end;
						
						this->_root = x._root;
						x._root = tmp1;

						this->_begin = x._begin;
						x._begin = tmp2;

						this->_end = x._end;
						x._end = tmp3;
					}

				void transfer_map(self& x)
					{
						size_type _size = x.get_size();

						if (_size-- > 0)
						{
							this->insertPair(*(x._root));
							this->_begin = this->_root;
							this->_end = this->_root;
						}
						while (_size-- > 0)
						{
							
						}
					}

				size_type get_size() const
					{ return (this->_map_size); }

		};
}

#endif