/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST_Node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:54:08 by gasselin          #+#    #+#             */
/*   Updated: 2022/06/11 17:55:51 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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

				BST_Node ()
		            :	value(),
						color(BLACK),
		                parent(NULL),
		                left(NULL),
		                right(NULL)
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

				~BST_Node() {}

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
}
