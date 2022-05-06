/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:49:41 by gasselin          #+#    #+#             */
/*   Updated: 2022/05/06 14:21:29 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "bidir_iterator.hpp"
// #include "iterators.hpp"
#include "utils.hpp"
#include <memory>
#include <cstring>

enum Color {RED, BLACK};

namespace ft
{	
	template <class T>
		class BST_Node
		{
			public:
				typedef T value_type;

				value_type value;
				bool color;
				BST_Node* parent;
				BST_Node* left;
				BST_Node* right;

				BST_Node (bool _color = RED, BST_Node* _parent = NULL, BST_Node* _left = NULL, BST_Node* _right = NULL)
		            :	value(),
						color(_color),
		                parent(_parent),
		                left(_left),
		                right(_right)
		            {}
				
				BST_Node(const value_type& val, bool _color = RED, BST_Node* _parent = NULL, BST_Node* _left = NULL, BST_Node* _right = NULL)
					:	value(val),
						color(_color),
						parent(_parent),
						left(_left),
						right(_right)
					{}

				BST_Node(const BST_Node& rhs)
					:	value(rhs.value),
						color(rhs.color),
						parent(rhs.parent),
						left(rhs.left),
						right(rhs.right)
					{}

				virtual ~BST_Node() {}

				BST_Node& operator=(const BST_Node& rhs)
					{
						this->value = rhs.value;
						this->color = rhs.color;
						this->parent = rhs.parent;
						this->left = rhs.left;
						this->right = rhs.right;
						
						return (*this);
					}
		};

	// An alternative way to insert elements in a map is by using member function map::operator[].
	// Internally, map containers keep all their elements sorted by their key following the criterion
	// specified by its comparison object. The elements are always inserted in its respective position following this ordering.
	
	template <class T, class Compare = ft::less<T>, class Node = BST_Node<T>, class Node_Alloc = std::allocator<Node> >
		class BST
		{	
			public:
				typedef BST self;
				typedef Node * node_ptr;
				typedef Node_Alloc node_alloc;
				typedef	size_t	size_type;
				typedef T value_type;
				typedef bidir_iterator<Node, Compare> iterator;
				typedef const_bidir_iterator<Node, Compare> const_iterator;

				node_ptr _tri_ptr;
				node_ptr _exts;
				node_alloc _node_alloc;
				size_type _map_size;
				Compare	_comp;
				node_ptr TNULL;

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

				void rotateLeft(node_ptr& root, node_ptr& new_node)
				{
					node_ptr right_ptr = new_node->right;
					
					new_node->right = right_ptr->left;
					
					if (new_node->right != NULL)
						new_node->right->parent = new_node;

					right_ptr->parent = new_node->parent;

					if (new_node->parent == NULL)
						root = right_ptr;
					else if (new_node == new_node->parent->left)
						new_node->parent->left = right_ptr;
					else
						new_node->parent->right = right_ptr;
						
					right_ptr->left = new_node;
					new_node->parent = right_ptr;
				}

				void rotateRight(node_ptr& root, node_ptr&new_node)
				{
					node_ptr left_ptr = new_node->left;
					
					new_node->left = left_ptr->right;
					
					if (new_node->left != NULL)
						new_node->left->parent = new_node;

					left_ptr->parent = new_node->parent;

					if (new_node->parent == NULL)
						root = left_ptr;
					else if (new_node == new_node->parent->left)
						new_node->parent->left = left_ptr;
					else
						new_node->parent->right = left_ptr;
						
					left_ptr->right = new_node;
					new_node->parent = left_ptr;
				}

				void fix_RBTree(node_ptr& root, node_ptr& new_node)
				{
					node_ptr parent_ptr = NULL;
					node_ptr uncle_ptr = NULL;
					node_ptr gr_parent_ptr = NULL;

					while (new_node != root && new_node->color != BLACK && new_node->parent->color == RED)
					{
						parent_ptr = new_node->parent;
						gr_parent_ptr = new_node->parent->parent;
						
						// Case A : Parent of new_node is left child of grand-parent of new_node
						if (parent_ptr == gr_parent_ptr->left)
						{
							uncle_ptr = gr_parent_ptr->right;
							
							// Case 1 : The uncle of new_node is also red, only recoloring required
							if (uncle_ptr != NULL && uncle_ptr->color == RED)
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
									rotateLeft(root, parent_ptr);
									new_node = parent_ptr;
									parent_ptr = new_node->parent;
								}

								// Case 3 : new_node is left child of its parent, right-rotation required
								rotateRight(root, gr_parent_ptr);
								std::swap(parent_ptr->color, gr_parent_ptr->color);
								new_node = parent_ptr;
							}
						}
						else
						{ // Case B : Parent of new_node is right child of grand-parent of new_node
							uncle_ptr = gr_parent_ptr->left;

							// Case 1 : The uncle of new_node is also red, only recoloring required
							if (uncle_ptr != NULL && uncle_ptr->color == RED)
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
									rotateRight(root, parent_ptr);
									new_node = parent_ptr;
									parent_ptr = new_node->parent;
								}

								// Case 3 : new_node is right child of its parent, right-rotation required
								rotateLeft(root, gr_parent_ptr);
								std::swap(parent_ptr->color, gr_parent_ptr->color);
								new_node = parent_ptr;
							}
						}
					}

					_tri_ptr->parent->color = BLACK;
				}
			public:
				// void print_tree(node_ptr node)
				// {
				// 	std::cout << node->value.first << "\n";
						
				// 	if(node->left != NULL)
				// 		print_tree(node->left);
						
				// 	if(node->right != NULL)
				// 		print_tree(node->right);
						
				// 	if(node->left == NULL && node->right == NULL)
				// 		return ;
				// }

			public:
				BST(const node_alloc& alloc = node_alloc(), const Compare& comp = Compare())
					: 	_node_alloc(alloc),
						_map_size(0),
						_comp(comp)
					{
						_tri_ptr = _node_alloc.allocate(1);
						_node_alloc.construct(_tri_ptr, Node());

						_exts = _node_alloc.allocate(1);
						_node_alloc.construct(_exts, Node());

						_exts->right = _node_alloc.allocate(1);
						_node_alloc.construct(_exts->right, Node());

						_exts->left = _node_alloc.allocate(1);
						_node_alloc.construct(_exts->left, Node());

						TNULL = _node_alloc.allocate(1);
						_node_alloc.construct(TNULL, Node());

						_tri_ptr->parent = _exts->right;
						_tri_ptr->left = _exts->right;
						_tri_ptr->right = _exts->right;
					}
				
				~BST() 
					{
						
						_node_alloc.destroy(_tri_ptr);
						_node_alloc.deallocate(_tri_ptr, 1);
						_tri_ptr = NULL;

						_node_alloc.destroy(_exts->right);
						_node_alloc.deallocate(_exts->right, 1);
						_exts->right = NULL;

						_node_alloc.destroy(_exts->left);
						_node_alloc.deallocate(_exts->left, 1);
						_exts->left = NULL;
						
						_node_alloc.destroy(_exts);
						_node_alloc.deallocate(_exts, 1);
						_exts = NULL;
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
						
						if (_tri_ptr->parent == _exts->right)
						{
							_map_size++;
							_node_alloc.construct(new_node, Node(node_to_add, BLACK, nullptr, TNULL, TNULL));
							_tri_ptr->parent = new_node;
							_tri_ptr->left = new_node;
							_tri_ptr->right = new_node;
							return (ft::make_pair(iterator(new_node, _tri_ptr, _exts), true));
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
							_node_alloc.construct(new_node, Node(node_to_add, RED, tmp, TNULL, TNULL));

							if (side)
								tmp->right = new_node;
							else
								tmp->left = new_node;
							if (_comp(node_to_add.first, _tri_ptr->left->value.first) == true)
								_tri_ptr->left = new_node;
							else if (_comp(node_to_add.first, _tri_ptr->right->value.first) == false)
								_tri_ptr->right = new_node;

							fix_RBTree(_tri_ptr->parent, new_node);
							return (ft::make_pair(iterator(new_node, _tri_ptr, _exts), true));
						}
						else
						{
							_node_alloc.deallocate(new_node, 1);
							return (ft::make_pair(iterator(findNode(node_to_add), _tri_ptr, _exts), false));
						}
					}

				void deleteBinaryTree(node_ptr root)
					{
						// Base case: empty tree
						if (root == NULL || root == _exts->right || root == _exts->left)
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
						size_type tmp_size;
						
						tmp = this->_tri_ptr;
						this->_tri_ptr = x._tri_ptr;
						x._tri_ptr = tmp;

						tmp2 = this->_exts;
						this->_exts = x._exts;
						x._exts = tmp2;

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

				void fixDeletion(node_ptr ptr, node_ptr node)
					{
						if (ptr->parent == NULL)
							_tri_ptr->parent = node;
						else if (ptr == ptr->parent->left)
							ptr->parent->left = node;
						else
							ptr->parent->right = node;
						if (node != NULL)
							node->parent = ptr->parent;
					}

				void fixRBTree_deletion(node_ptr node)
					{
						// while (node != _tri_ptr->parent && node->color == BLACK)
						// {
							
						// }
					}

				void deleteNode(iterator it)
					{
						const value_type val = *it;
						node_ptr ptr = findNode(val);
						node_ptr child;
						iterator tmp = it;
						// bool double_black = true;
						bool ptr_original_color = ptr->color;

						if (ptr->left == NULL && ptr->right == NULL) {
							fixDeletion(ptr, NULL);
						}
						else if (ptr->left == NULL) {
							child = ptr->right;
							fixDeletion(ptr, child);
						}
						else if (ptr->right == NULL) {
							child = ptr->left;
							fixDeletion(ptr, child);
						}
						else {
							value_type succ_val = *(++tmp);
							node_ptr succ_ptr = findNode(succ_val);
							
							child = succ_ptr->right;
							if (succ_ptr->parent == ptr)
								child->parent = succ_ptr;
							else {
								fixDeletion(succ_ptr, succ_ptr->right);
								succ_ptr->right = ptr->right;
								succ_ptr->right->parent = succ_ptr;
							}

							fixDeletion(ptr, succ_ptr);
							succ_ptr->left = ptr->left;
							succ_ptr->left->parent = succ_ptr;
							succ_ptr->color = ptr_original_color;
						}

						this->_node_alloc.destroy(ptr);
						this->_node_alloc.deallocate(ptr, 1);
						ptr = NULL;
						this->_map_size--;
						
						if (ptr_original_color)
							fixRBTree_deletion(child);

						// if (ptr->left == NULL && ptr->right == NULL)
						// {
						// 	if (ptr->parent != NULL && ptr->parent->right == ptr)
						// 	{
						// 		ptr->parent->right = NULL;
						// 		if (ptr->parent->left != NULL)
						// 			DB_sibling = ptr->parent->left;
						// 	}
						// 	else if (ptr->parent != NULL && ptr->parent->left == ptr)
						// 	{
						// 		ptr->parent->left = NULL;
						// 		if (ptr->parent->right != NULL)
						// 			DB_sibling = ptr->parent->right;
						// 	}

						// 	if (ptr->color == RED)
						// 	{
						// 		double_black = false;
						// 		DB_sibling = NULL;	
						// 	}
							
						// 	if (ptr == _tri_ptr->parent)
						// 	{
						// 		_tri_ptr->parent = _exts->right;
						// 		_tri_ptr->left = _exts->right;
						// 		_tri_ptr->right = _exts->right;
						// 		double_black = false;
						// 	}
						// }
						// else if (ptr->left != NULL && ptr->right != NULL)
						// {
						// 	value_type succ_val = *(--it);
						// 	node_ptr succ_ptr = findNode(succ_val);
							
						// 	if (ptr == _tri_ptr->parent)
						// 		_tri_ptr->parent = succ_ptr;

						// 	if (succ_ptr->right == NULL && succ_ptr->left == NULL)
						// 	{
						// 		if (succ_ptr->parent != NULL && succ_ptr->parent->left == succ_ptr)
						// 			succ_ptr->parent->left = NULL;
						// 		else if (succ_ptr->parent != NULL && succ_ptr->parent->right == succ_ptr)
						// 			succ_ptr->parent->right = NULL;
						// 	}
						// 	else if (succ_ptr->right != NULL)
						// 	{
						// 		succ_ptr->right->parent = succ_ptr->parent;
						// 		if (succ_ptr->parent != NULL && succ_ptr->parent->left == succ_ptr)
						// 			succ_ptr->parent->left = succ_ptr->right;
						// 		else if (succ_ptr->parent != NULL && succ_ptr->parent->right == succ_ptr)
						// 			succ_ptr->parent->right = succ_ptr->right;
						// 	}
						// 	else if (succ_ptr->left != NULL)
						// 	{
						// 		succ_ptr->left->parent = succ_ptr->parent;
						// 		if (succ_ptr->parent != NULL && succ_ptr->parent->left == succ_ptr)
						// 			succ_ptr->parent->left = succ_ptr->left;
						// 		else if (succ_ptr->parent != NULL && succ_ptr->parent->right == succ_ptr)
						// 			succ_ptr->parent->right = succ_ptr->left;
						// 	}

							
						// 	succ_ptr->parent = ptr->parent;
						// 	succ_ptr->left = ptr->left;
						// 	succ_ptr->right = ptr->right;

						// 	if (ptr->left != NULL)
						// 		ptr->left->parent = succ_ptr;
						// 	if (ptr->right != NULL)
						// 		ptr->right->parent = succ_ptr;

						// 	_tri_ptr->parent->parent = NULL;
						// }
						// else
						// {
						// 	bool side;

						// 	if (ptr->left != NULL)
						// 		child = ptr->left;
						// 	else if (ptr->right != NULL)
						// 		child = ptr->right;

						// 	if (ptr->parent != NULL && ptr->parent->left == ptr)
						// 		side = true;
						// 	else if (ptr->parent != NULL && ptr->parent->right == ptr)
						// 		side = false;

						// 	if (ptr == _tri_ptr->parent)
						// 		_tri_ptr->parent = child;
						// 	else 
						// 	{
						// 		if (side)
						// 			ptr->parent->left = child;
						// 		else
						// 			ptr->parent->right = child;
						// 		child->parent = ptr->parent;
						// 	}
						// 	_tri_ptr->parent->parent = NULL;
						// }
						// this->_node_alloc.destroy(ptr);
						// this->_node_alloc.deallocate(ptr, 1);
						// ptr = NULL;
						// this->_map_size--;

						// if (_map_size)
						// {
						// 	_tri_ptr->left = find_min();
						// 	_tri_ptr->right = find_max();
						// }
					}

				size_type get_size() const
					{ return (this->_map_size); }

		};
}
