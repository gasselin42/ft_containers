/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:49:41 by gasselin          #+#    #+#             */
/*   Updated: 2022/04/06 14:53:24 by gasselin         ###   ########.fr       */
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
				BST_Node* parent;
				BST_Node* left;
				BST_Node* right;

				BST_Node() : value(), parent(NULL), left(NULL), right(NULL) {}
				
				BST_Node(const value_type& val, BST_Node* _parent = NULL, BST_Node* _left = NULL, BST_Node* _right = NULL)
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

	// An alternative way to insert elements in a map is by using member function map::operator[].
	// Internally, map containers keep all their elements sorted by their key following the criterion
	// specified by its comparison object. The elements are always inserted in its respective position following this ordering.
	
	template <class T, class Compare = ft::less<T>, class Node = ft::BST_Node<T>, class Node_Alloc = std::allocator<Node> >
		class BST
		{
			public:
				typedef BST self;
				typedef Node * node_ptr;
				typedef Node_Alloc node_alloc;
				typedef	size_t	size_type;
				typedef T value_type;
				typedef Compare comp;
				typedef ft::bidir_iterator<Node, Compare> iterator;

			private:
				node_ptr _begin;
				node_ptr _end;
				node_ptr _root;
				node_alloc _node_alloc;
				size_type _map_size;
				Compare	_comp;

			public:
				BST(const node_alloc& alloc = node_alloc(), const comp& comparisor = comp())
					: 	_begin(NULL),
						_end(NULL),
						_root(NULL),
						_node_alloc(alloc),
						_map_size(0),
						_comp(comparisor)
					{}
				
				~BST() {}

				node_ptr getRoot()
					{ return (this->_root); }

				node_ptr findNode(const value_type node_to_find)
					{
						node_ptr current = _root;

						while (true)
						{
							if (current == NULL)
								break ;
							if (current->value.first == node_to_find.first)
								return (current);
							if (node_to_find.first < current->value.first)
								current = current->left;
							else
								current = current->right;
						}

						return (NULL);
					}

				ft::pair<iterator, bool> insertPair(const value_type node_to_add)
					{
						node_ptr new_node = _node_alloc.allocate(1);
						node_ptr current = _root;
						bool side = false;
						
						if (_root == NULL)
						{
							_map_size++;
							_node_alloc.construct(new_node, Node(node_to_add, NULL, NULL, NULL));
							_root = new_node;
							_begin = new_node;
							_end = new_node->right;
							return (ft::make_pair(iterator(new_node), true));
						}
						else if (findNode(node_to_add) == NULL)
						{
							// add new_node
							while (current != NULL)
							{
								if (_comp(node_to_add.first, current->value.first))
								{
									current = current->left;
									side = false;
								}
								else
								{
									current = current->right;
									side = true;
								}
							}
							_map_size++;
							_node_alloc.construct(new_node, Node(node_to_add, current->parent, NULL, NULL));
							if (side)
								current->parent->right = new_node;
							else
								current->parent->left = new_node;
							return (ft::make_pair(iterator(new_node), true));
						}
						else
						{
							_node_alloc.deallocate(new_node, 1);
							return (ft::make_pair(iterator(findNode(node_to_add)), false));
						}
					}

				void destroyBST(node_ptr node)
					{
						if(node->left != NULL)
							visitNode(node->left);
							
						if(node->right != NULL)
							visitNode(node->right);
							
						if(node->left == NULL && node->right == NULL)
						{
							this->_node_alloc.destroy(node);
							this->_node_alloc.deallocate(node, 1);
						}
					}

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

				void visitNode(node_ptr node)
					{
						insertPair(node->value);
						
						if(node->left != NULL)
							visitNode(node->left);
							
						if(node->right != NULL)
							visitNode(node->right);
							
						if(node->left == NULL && node->right == NULL)
							return ;
					}

				void transfer_map(self& x)
					{
						size_type _size = x.get_size();

						// if (_size-- > 0)
						// {
						// 	this->insertPair(*(x._root));
						// 	this->_begin = this->_root;
						// 	this->_end = this->_root;
						// }
						if (_size)
							visitNode(x._root);
					}

				size_type get_size() const
					{ return (this->_map_size); }

		};
}

#endif