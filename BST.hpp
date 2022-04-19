/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:49:41 by gasselin          #+#    #+#             */
/*   Updated: 2022/04/19 16:02:30 by gasselin         ###   ########.fr       */
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

				BST_Node (BST_Node* _parent = NULL, BST_Node* _left = NULL, BST_Node* _right = NULL)
		            :	value(),
		                parent(_parent),
		                left(_left),
		                right(_right)
		            {}
				
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

				virtual ~BST_Node() {}

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
				typedef ft::bidir_iterator<Node, Compare> iterator;
				typedef ft::const_bidir_iterator<Node, Compare> const_iterator;

				node_ptr _tri_ptr;
				node_alloc _node_alloc;
				size_type _map_size;
				Compare	_comp;

				void test(void)
				{
					node_ptr _tmp_ptr;
					_tmp_ptr = _node_alloc.allocate(1);
					_node_alloc.construct(_tmp_ptr, Node());

					_tri_ptr->left = _tmp_ptr;
					_tri_ptr->right = _tmp_ptr;

					std::cout << &(_tri_ptr->left) << "\n";
					std::cout << &(_tri_ptr->right) << "\n";

					std::cout << &(*_tri_ptr->left) << "\n";
					std::cout << &(*_tri_ptr->right) << "\n";

					this->_node_alloc.destroy(_tmp_ptr);
					this->_node_alloc.deallocate(_tmp_ptr, 1);
				}

			private:
				node_ptr find_max()
					{
						node_ptr current;

						current = _tri_ptr->parent;
						while (current->right != NULL)
							current = current->right;
						return (current);
					}

				node_ptr find_min()
					{
						node_ptr current;

						current = _tri_ptr->parent;
						while (current->left != NULL)
							current = current->left;
						return (current);
					}

			public:
				BST(const node_alloc& alloc = node_alloc(), const Compare& comp = Compare())
					: 	_tri_ptr(NULL),
						_node_alloc(alloc),
						_map_size(0),
						_comp(comp)
					{
						_tri_ptr = _node_alloc.allocate(1);
						_node_alloc.construct(_tri_ptr, Node());
					}
				
				~BST() 
					{
						_node_alloc.destroy(_tri_ptr);
						_node_alloc.deallocate(_tri_ptr, 1);
						_tri_ptr = NULL;
					}

				node_ptr findNode(const value_type node_to_find)
					{
						node_ptr current = _tri_ptr->parent;

						while (true)
						{
							if (current == NULL)
								break ;
							if (_comp(node_to_find.first, current->value.first) == false &&
								_comp(current->value.first, node_to_find.first) == false)
								return (current);
							if (_comp(node_to_find.first, current->value.first) == true)
								current = current->left;
							else if (_comp(current->value.first, node_to_find.first) == true)
								current = current->right;
						}

						return (NULL);
					}

				ft::pair<iterator, bool> insertPair(const value_type node_to_add)
					{
						node_ptr new_node = _node_alloc.allocate(1);
						node_ptr current = _tri_ptr->parent;
						bool side = false;
						
						if (_tri_ptr->parent == NULL)
						{
							_map_size++;
							_node_alloc.construct(new_node, Node(node_to_add, NULL, NULL, NULL));
							_tri_ptr->parent = new_node;
							_tri_ptr->left = new_node;
							_tri_ptr->right = new_node;
							return (ft::make_pair(iterator(new_node, _tri_ptr), true));
						}
						else if (findNode(node_to_add) == NULL)
						{
							node_ptr tmp;
							while (current != NULL)
							{
								tmp = current;
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
							_node_alloc.construct(new_node, Node(node_to_add, tmp, NULL, NULL));

							if (side)
								tmp->right = new_node;
							else
								tmp->left = new_node;
							if (_comp(node_to_add.first, _tri_ptr->left->value.first) == true)
								_tri_ptr->left = new_node;
							else if (_comp(node_to_add.first, _tri_ptr->right->value.first) == false)
								_tri_ptr->right = new_node;

							return (ft::make_pair(iterator(new_node, _tri_ptr), true));
						}
						else
						{
							_node_alloc.deallocate(new_node, 1);
							return (ft::make_pair(iterator(findNode(node_to_add), _tri_ptr), false));
						}
					}

				void deleteBinaryTree(node_ptr root)
					{
						// Base case: empty tree
						if (root == NULL)
							return ;
					
						// delete left and right subtree first (Postorder)
						deleteBinaryTree(root->left);
						deleteBinaryTree(root->right);
					
						// delete the current node after deleting its left and right subtree
						this->_node_alloc.destroy(root);
						this->_node_alloc.deallocate(root, 1);
						this->_map_size--;
					
						// set root as null before returning
						root = NULL;
					}

				size_type max_size() const
					{ return (this->_node_alloc.max_size()); }

				// https://stackoverflow.com/questions/21143835/can-i-implement-an-autonomous-self-member-type-in-c
				void swap(self& x)
					{
						node_ptr tmp;
						size_type tmp_size;
						
						tmp = this->_tri_ptr;
						this->_tri_ptr = x._tri_ptr;
						x._tri_ptr = tmp;

						tmp_size = this->_map_size;
						this->_map_size = x._map_size;
						x._map_size = tmp_size;
					}

				void visitNode(node_ptr node)
					{
						this->insertPair(node->value);
						
						if(node->left != NULL)
							visitNode(node->left);
							
						if(node->right != NULL)
							visitNode(node->right);
							
						if(node->left == NULL && node->right == NULL)
							return ;
					}

				void transfer_map(const self& x)
					{
						if (x._map_size)
							visitNode(x._tri_ptr->parent);
					}

				void deleteNode(iterator it)
					{
						const value_type val = *it;
						node_ptr ptr = findNode(val);

						if (ptr->left == NULL && ptr->right == NULL)
						{
							if (ptr->parent != NULL && ptr->parent->right == ptr)
								ptr->parent->right = NULL;
							else if (ptr->parent != NULL && ptr->parent->left == ptr)
								ptr->parent->left = NULL;
							
							if (ptr == _tri_ptr->parent)
							{
								_tri_ptr->parent = NULL;
								_tri_ptr->left = NULL;
								_tri_ptr->right = NULL;
							}
							this->_node_alloc.destroy(ptr);
							this->_node_alloc.deallocate(ptr, 1);
							ptr = NULL;
							this->_map_size--;
						}
						else if (ptr->left != NULL && ptr->right != NULL)
						{
							value_type succ_val = *(++it);
							deleteNode(it);
							node_ptr new_node = _node_alloc.allocate(1);
							_node_alloc.construct(new_node, Node(succ_val, ptr->parent, ptr->left, ptr->right));
							if (ptr->left)
								ptr->left->parent = new_node;
							if (ptr->right)
								ptr->right->parent = new_node;
							if (ptr->parent)
							{
								if (ptr->parent->left == ptr)
									ptr->parent->left = new_node;
								else if (ptr->parent->right == ptr)
									ptr->parent->right = new_node;
							}
							if (ptr == _tri_ptr->parent)
								_tri_ptr->parent = new_node;
							this->_node_alloc.destroy(ptr);
							this->_node_alloc.deallocate(ptr, 1);
						}
						else
						{
							node_ptr child;
							bool side;

							if (ptr->left != NULL)
								child = ptr->left;
							else if (ptr->right != NULL)
								child = ptr->right;

							if (ptr->parent != NULL && ptr->parent->left == ptr)
								side = true;
							else if (ptr->parent != NULL && ptr->parent->right == ptr)
								side = false;

							if (side)
								ptr->parent->left = child;
							else
								ptr->parent->right = child;
							child->parent = ptr->parent;

							this->_node_alloc.destroy(ptr);
							this->_node_alloc.deallocate(ptr, 1);
							this->_map_size--;
						}
						
						if (_map_size)
						{
							_tri_ptr->left = find_min();
							_tri_ptr->right = find_max();
						}
					}

				size_type get_size() const
					{ return (this->_map_size); }

		};
}

#endif