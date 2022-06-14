/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:49:41 by gasselin          #+#    #+#             */
/*   Updated: 2022/06/13 17:15:12 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "bidir_iterator.hpp"
#include "BST_Node.hpp"
#include "utils.hpp"
#include <memory>
#include <cstring>

namespace ft
{	
	template <class T, class Compare = ft::less<T>, class Node = ft::BST_Node<T>, class Node_Alloc = std::allocator<Node> >
		class BST
		{	
			public:
				typedef BST self;
				typedef Node * node_ptr;
				typedef Node_Alloc node_alloc;
				typedef	size_t	size_type;
				typedef T value_type;
				typedef typename T::first_type Key;
				typedef bidir_iterator<Node, T> iterator;
				typedef const_bidir_iterator<Node, T> const_iterator;

				node_ptr _tri_ptr;
				node_ptr _begin;
				node_ptr _end;
				node_alloc _node_alloc;
				size_type _map_size;
				Compare	_comp;

			private:
				node_ptr find_max(node_ptr ptr)
					{
						while (ptr->right != NULL)
							ptr = ptr->right;
						return (ptr);
					}

				node_ptr find_min(node_ptr ptr)
					{
						while (ptr->left != NULL && ptr->left != _begin)
							ptr = ptr->left;
						return (ptr);
					}

				void rotateLeft(node_ptr node)
				{
					node_ptr right_ptr = node->right;
					
					node->right = right_ptr->left;
					
					if (right_ptr != NULL && right_ptr->left != NULL && right_ptr->left != _begin)
						right_ptr->left->parent = node;

					right_ptr->parent = node->parent;

					if (node->parent == _end)
					{
						_tri_ptr->parent = right_ptr;
						_end->left = right_ptr;
					}
					else if (node == node->parent->left)
						node->parent->left = right_ptr;
					else
						node->parent->right = right_ptr;
						
					right_ptr->left = node;
					node->parent = right_ptr;
				}

				void rotateRight(node_ptr node)
				{
					node_ptr left_ptr = node->left;
					
					node->left = left_ptr->right;
					
					if (left_ptr != _begin && left_ptr->right != NULL)
						node->left->parent = node;

					left_ptr->parent = node->parent;

					if (node->parent == _end)
					{
						_tri_ptr->parent = left_ptr;
						_end->left = left_ptr;
					}
					else if (node == node->parent->left)
						node->parent->left = left_ptr;
					else
						node->parent->right = left_ptr;
						
					left_ptr->right = node;
					node->parent = left_ptr;
				}

				void fix_RBTree(node_ptr new_node)
				{
					node_ptr parent_ptr = NULL;
					node_ptr uncle_ptr = NULL;
					node_ptr gr_parent_ptr = NULL;

					while (new_node != _tri_ptr->parent && new_node->color != BLACK && new_node->parent->color == RED)
					{
						parent_ptr = new_node->parent;
						gr_parent_ptr = new_node->parent->parent;
						
						// Case A : Parent of new_node is left child of grand-parent of new_node
						if (parent_ptr == gr_parent_ptr->left)
						{
							uncle_ptr = gr_parent_ptr->right;
							
							// Case 1 : The uncle of new_node is also red, only recoloring required
							if (uncle_ptr != NULL && uncle_ptr != _begin && uncle_ptr->color == RED)
							{
								gr_parent_ptr->color = RED;
								parent_ptr->color = BLACK;
								uncle_ptr->color = BLACK;
								new_node = gr_parent_ptr;
							}
							else
							{
								// Case 2 : new_node is right child of its parent, left-rotation required
								if (new_node == parent_ptr->right)
								{
									new_node = parent_ptr;
									rotateLeft(new_node);
								}

								// Case 3 : new_node is left child of its parent, right-rotation required
								new_node->parent->color = BLACK;
								new_node->parent->parent->color = RED;
								rotateRight(new_node->parent->parent);
							}
						}
						else
						{ // Case B : Parent of new_node is right child of grand-parent of new_node
							uncle_ptr = gr_parent_ptr->left;

							// Case 1 : The uncle of new_node is also red, only recoloring required
							if (uncle_ptr != NULL && uncle_ptr != _begin && uncle_ptr->color == RED)
							{
								gr_parent_ptr->color = RED;
								parent_ptr->color = BLACK;
								uncle_ptr->color = BLACK;
								new_node = gr_parent_ptr;
							}
							else
							{
								// Case 2 : new_node is left child of its parent, left-rotation required
								if (new_node == parent_ptr->left)
								{
									new_node = parent_ptr;
									rotateRight(new_node);
								}

								// Case 3 : new_node is right child of its parent, right-rotation required
								new_node->parent->color = BLACK;
								new_node->parent->parent->color = RED;
								rotateLeft(new_node->parent->parent);
							}
						}
					}

					_tri_ptr->parent->color = BLACK;
				}

			public:
				BST(const node_alloc& alloc = node_alloc(), const Compare& comp = Compare())
					: 	_node_alloc(alloc),
						_map_size(0),
						_comp(comp)
					{
						_tri_ptr = _node_alloc.allocate(1);
						_node_alloc.construct(_tri_ptr, Node());

						_begin = _node_alloc.allocate(1);
						_node_alloc.construct(_begin, Node());
						
						_end = _node_alloc.allocate(1);
						_node_alloc.construct(_end, Node());
					}
				
				~BST() 
					{
						
						_node_alloc.destroy(_tri_ptr);
						_node_alloc.deallocate(_tri_ptr, 1);
						_tri_ptr = NULL;

						_node_alloc.destroy(_begin);
						_node_alloc.deallocate(_begin, 1);
						_begin = NULL;

						_node_alloc.destroy(_end);
						_node_alloc.deallocate(_end, 1);
						_end = NULL;
					}

				template < typename Key >
				iterator findNode_it(const Key& key)
					{
						node_ptr current = _tri_ptr->parent;

						while (true)
						{
							if (current == NULL || current == _begin)
								break ;
							if (_comp(key, current->value.first) == false &&
								_comp(current->value.first, key) == false)
								return (iterator(current, _tri_ptr));
							if (_comp(key, current->value.first) == true)
								current = current->left;
							else if (_comp(current->value.first, key) == true)
								current = current->right;
						}

						return (iterator(_end, _tri_ptr));
					}

				template < typename Key >
				const_iterator findNode_it(const Key& key) const
					{
						node_ptr current = _tri_ptr->parent;

						while (true)
						{
							if (current == NULL || current == _begin)
								break ;
							if (_comp(key, current->value.first) == false &&
								_comp(current->value.first, key) == false)
								return (const_iterator(current, _tri_ptr));
							if (_comp(key, current->value.first) == true)
								current = current->left;
							else if (_comp(current->value.first, key) == true)
								current = current->right;
						}

						return (const_iterator(_end, _tri_ptr));
					}

				node_ptr findNode(const value_type node_to_find)
					{
						node_ptr current = _tri_ptr->parent;

						while (true)
						{
							if (current == NULL || current == _begin)
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
							_node_alloc.construct(new_node, Node(node_to_add, BLACK, _end, _begin, NULL));
							_begin->parent = new_node;
							_end->left = new_node;
							_tri_ptr->parent = new_node;
							_tri_ptr->left = new_node;
							_tri_ptr->right = new_node;
							return (ft::make_pair(iterator(new_node, _tri_ptr), true));
						}
						else if (findNode(node_to_add) == NULL)
						{
							node_ptr tmp;
							while (current != NULL && current != _begin)
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
							_node_alloc.construct(new_node, Node(node_to_add, RED, tmp, NULL, NULL));

							if (side)
								tmp->right = new_node;
							else
								tmp->left = new_node;
							if (_comp(node_to_add.first, _tri_ptr->left->value.first) == true)
								_tri_ptr->left = new_node;
							else if (_comp(node_to_add.first, _tri_ptr->right->value.first) == false)
								_tri_ptr->right = new_node;

							fix_RBTree(new_node);
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
						if (root == NULL || root == _begin)
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
						node_ptr tmp2;
						node_ptr tmp3;
						size_type tmp_size;
						Compare tmp_comp;
						
						tmp = this->_tri_ptr;
						this->_tri_ptr = x._tri_ptr;
						x._tri_ptr = tmp;

						tmp2 = this->_begin;
						this->_begin = x._begin;
						x._begin = tmp2;

						tmp3 = this->_end;
						this->_end = x._end;
						x._end = tmp3;

						tmp_size = this->_map_size;
						this->_map_size = x._map_size;
						x._map_size = tmp_size;

						tmp_comp = this->_comp;
						this->_comp = x._comp;
						x._comp = tmp_comp;
					}

				void visitNode(node_ptr node, node_ptr x_begin)
					{
						this->insertPair(node->value);
						
						if(node->left != NULL && node->left != x_begin)
							visitNode(node->left, x_begin);
							
						if(node->right != NULL)
							visitNode(node->right, x_begin);
							
						if(node->left == NULL && node->right == NULL)
							return ;
					}

				void transfer_map(const self& x)
					{
						if (x._map_size)
							visitNode(x._tri_ptr->parent, x._begin);
					}

				void fixDeletion(node_ptr ptr, node_ptr node)
					{
						if (ptr->parent == _end)
						{
							_tri_ptr->parent = node;
							_end->left = node;
						}
						else if (ptr == ptr->parent->left)
							ptr->parent->left = node;
						else
							ptr->parent->right = node;
						node->parent = ptr->parent;
					}

				void fixRBTree_deletion(node_ptr node)
					{
						node_ptr sibling;

						while (node != _tri_ptr->parent && node->color == BLACK)
						{
							if (node == node->parent->left)
							{
								sibling = node->parent->right;
								if (sibling->color == RED)
								{
									sibling->color = BLACK;
									node->parent->color = RED;
									rotateLeft(node->parent);
									sibling = node->parent->right;
								}

								if ((sibling->left == NULL || sibling->left->color == BLACK) &&
									(sibling->right == NULL || sibling->right->color == BLACK))
								{
									sibling->color = RED;
									node = node->parent;
								}
								else
								{
									if (sibling->right == NULL || sibling->right->color == BLACK)
									{
										if (sibling->left != NULL)
											sibling->left->color = BLACK;
										sibling->color = RED;
										rotateRight(sibling);
										sibling = node->parent->right;
									}
									
									sibling->color = node->parent->color;
									node->parent->color = BLACK;
									if (sibling->right != NULL)
										sibling->right->color = BLACK;
									rotateLeft(node->parent);
									node = _tri_ptr->parent;
								}
							}
							else // node == node->parent->right
							{
								sibling = node->parent->left;
								if (sibling->color == RED)
								{
									sibling->color = BLACK;
									node->parent->color = RED;
									rotateRight(node->parent);
									sibling = node->parent->left;
								}

								if ((sibling->left == NULL || sibling->left->color == BLACK) &&
									(sibling->right == NULL || sibling->right->color == BLACK))
								{
									sibling->color = RED;
									node = node->parent;
								}
								else
								{
									if (sibling->left == NULL || sibling->left->color == BLACK)
									{
										if (sibling->right != NULL)
											sibling->right->color = BLACK;
										sibling->color = RED;
										rotateLeft(sibling);
										sibling = node->parent->left;
									}
									
									sibling->color = node->parent->color;
									node->parent->color = BLACK;
									if (sibling->left != NULL)
										sibling->left->color = BLACK;
									rotateRight(node->parent);
									node = _tri_ptr->parent;
								}
							}
						}
						node->color = BLACK;
					}

				void deleteNode(iterator it)
					{
						const value_type val = *it;
						node_ptr ptr = findNode(val);
						node_ptr child, x;
						bool ptr_original_color = ptr->color;

						child = _node_alloc.allocate(1);
						_node_alloc.construct(child, Node());
						child->color = BLACK;

						if (ptr->left == NULL || ptr->left == _begin) {
							if (ptr->right != NULL) {
								x = ptr->right;
								fixDeletion(ptr, ptr->right);
							} else {
								x = child;
								child->parent = ptr;
								fixDeletion(ptr, child);
							}
						} else if (ptr->right == NULL) {
							if (ptr->left != NULL && ptr->left != _begin) {
								x = ptr->left;
								fixDeletion(ptr, ptr->left);
							}
							else {
								x = child;
								child->parent = ptr;
								fixDeletion(ptr, child);
							}
						} else {
							node_ptr succ_ptr = find_min(ptr->right);
							ptr_original_color = succ_ptr->color;
							
							if (succ_ptr->right != NULL) {
								x = succ_ptr->right;
								if (succ_ptr->parent == ptr)
									x->parent = succ_ptr;
								else {
									fixDeletion(succ_ptr, succ_ptr->right);
									succ_ptr->right = ptr->right;
									succ_ptr->right->parent = succ_ptr;
								}
							} else {
								x = child;
								if (succ_ptr->parent == ptr)
									child->parent = succ_ptr;
								else {
									child->parent = succ_ptr;
									fixDeletion(succ_ptr, child);
									succ_ptr->right = ptr->right;
									succ_ptr->right->parent = succ_ptr;
								}
							}

							fixDeletion(ptr, succ_ptr);
							succ_ptr->left = ptr->left;
							succ_ptr->left->parent = succ_ptr;
							succ_ptr->color = ptr->color;
						}

						this->_node_alloc.destroy(ptr);
						this->_node_alloc.deallocate(ptr, 1);
						ptr = NULL;
						this->_map_size--;

						if (this->_map_size != 0 && ptr_original_color == BLACK)
							fixRBTree_deletion(x);

						if (child->parent != NULL) {
							if (child->parent->left == child)
								child->parent->left = NULL;
							else
								child->parent->right = NULL;
						}

						_node_alloc.destroy(child);
						_node_alloc.deallocate(child, 1);
						child = NULL;

						if (this->_map_size == 0)
						{
							_tri_ptr->parent = NULL;
							_tri_ptr->left = NULL;
							_tri_ptr->right = NULL;
						}
						else
						{
							_tri_ptr->left = find_min(_tri_ptr->parent);
							_tri_ptr->right = find_max(_tri_ptr->parent);
						}
					}

				size_type get_size() const
					{ return (this->_map_size); }

		};
}
