/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidir_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:16:38 by gasselin          #+#    #+#             */
/*   Updated: 2022/04/12 13:38:57 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef BIDIR_ITERATOR_HPP
#define BIDIR_ITERATOR_HPP

#include "iterators.hpp"

namespace ft
{
	template < class T, class Compare >
		class bidir_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
		{
			public:
				typedef typename T::value_type																	value_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;


			private:
				T*	_ptr;
				T*	_tri_ptr;
				Compare	_comp;

				T* find_max(T* ptr)
					{
						T* current;

						current = ptr;
						while (current->right != NULL)
							current = current->right;
						return (current);
					}

				T* find_min(T* ptr)
					{
						T* current;

						current = ptr;
						while (current->left != NULL)
							current = current->left;
						return (current);
					}
				
				T* get_next_ptr()
					{
						T* current;

						if (_tri_ptr->right != NULL && _tri_ptr->right->value == _ptr->value)
							return (_ptr->right);

						if (_tri_ptr->parent != NULL &&  _tri_ptr->parent->left != NULL && find_max(_tri_ptr->parent->left)->value == _ptr->value)
							return (_tri_ptr->parent);
						
						if (_tri_ptr->parent != NULL && _ptr->value == _tri_ptr->parent->value)
						{
							if (_ptr->right == NULL || _ptr->right->left == NULL)
								return (_ptr->right);
							else
								return (find_min(_ptr->right));
						}
						
						if (_ptr->right != NULL)
							return (find_min(_ptr->right));
						
						if (_ptr->right == NULL)
						{
							if (_ptr->parent->left != NULL && _ptr->parent->left->value == _ptr->value)
								return (_ptr->parent);
							else if (_ptr->parent->right != NULL && _ptr->parent->right->value == _ptr->value)
							{
								current = _ptr->parent;
								while (_comp(current->value.first, _ptr->value.first) == true)
									current = current->parent;
								return (current);
							}
						}

						return (_ptr);
					}

				T* get_prev_ptr()
					{
						T* current;
						
						if (_tri_ptr->left != NULL && _tri_ptr->left->value == _ptr->value)
							return (_ptr->left);

						if (_tri_ptr->parent != NULL &&  _tri_ptr->parent->right != NULL && find_min(_tri_ptr->parent->right)->value == _ptr->value)
							return (_tri_ptr->parent);
						
						if (_tri_ptr->parent != NULL && _ptr->value == _tri_ptr->parent->value)
						{
							if (_ptr->left == NULL || _ptr->left->right == NULL)
								return (_ptr->left);
							else
								return (find_max(_ptr->left));
						}
						
						if (_ptr->left != NULL)
							return (find_max(_ptr->left));

						if (_ptr->left == NULL)
						{
							if (_ptr->parent->right != NULL && _ptr->parent->right->value == _ptr->value)
								return (_ptr->parent);
							else if (_ptr->parent->left != NULL && _ptr->parent->left->value == _ptr->value)
							{
								current = _ptr->parent;
								while (_comp(current->value.first, _ptr->value.first) == false)
									current = current->parent;
								return (current);
							}
						}

						return (_ptr);
					}

			public:

				bidir_iterator() : _ptr(NULL), _tri_ptr(NULL) {}
				bidir_iterator(T* ptr, T* tri_ptr) : _ptr(ptr), _tri_ptr(tri_ptr) {}
				bidir_iterator(const bidir_iterator& rhs) : _ptr(rhs._ptr), _tri_ptr(rhs._tri_ptr) {}
				bidir_iterator& operator=(const bidir_iterator& rhs) { _ptr = rhs._ptr; _tri_ptr = rhs._tri_ptr; return (*this); }
				virtual ~bidir_iterator() {}

				reference operator*(void) const { return (this->_ptr->value); }
				pointer operator->(void) const { return (&this->_ptr->value); }

				bidir_iterator& operator++(void) {
					_ptr = get_next_ptr();
					return (*this);
				}

				bidir_iterator operator++(int) {
					bidir_iterator tmp = *this;
					_ptr = get_next_ptr();
					return (tmp);
				}

				bidir_iterator& operator--(void) {
					_ptr = get_prev_ptr();
					return (*this);
				}

				bidir_iterator operator--(int) {
					bidir_iterator tmp = *this;
					_ptr = get_prev_ptr();
					return (tmp);
				}

				bool operator==(const bidir_iterator& rhs) const { return (this->_ptr == rhs._ptr); }
				bool operator!=(const bidir_iterator& rhs) const { return (this->_ptr != rhs._ptr); }
		};



	template < class T, class Compare >
		class const_bidir_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
		{
			public:
				typedef typename T::value_type 																	value_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;


			private:
				T*	_ptr;
				T*	_tri_ptr;
				Compare	_comp;
				
				T* get_next_ptr()
					{
						T* current;
						
						if ((_tri_ptr->right != NULL && _ptr->value == _tri_ptr->right->value) ||
							(_tri_ptr->parent != NULL && _ptr->value == _tri_ptr->parent->value) ||
							 _ptr->right != NULL)
							return (_ptr->right);
						
						if (_ptr->right == NULL)
						{
							if (_ptr->parent->left->value == _ptr->value)
								return (_ptr->parent);
							else if (_ptr->parent->right->value == _ptr->value)
							{
								current = _ptr->parent;
								while (_comp(current->value.first, _ptr->value.first) == true)
									current = current->parent;
								return (current);
							}
						}

						return (_ptr);
					}

				T* get_prev_ptr()
					{
						T* current;
						
						if ((_tri_ptr->left != NULL && _ptr->value == _tri_ptr->left->value) || 
							(_tri_ptr->parent != NULL && _ptr->value == _tri_ptr->parent->value) ||
							 _ptr->left != NULL)
							return (_ptr->left);

						if (_ptr->left == NULL)
						{
							if (_ptr->parent->right != NULL && _ptr->parent->right->value == _ptr->value)
								return (_ptr->parent);
							else if (_ptr->parent->left != NULL && _ptr->parent->left->value == _ptr->value)
							{
								current = _ptr->parent;
								while (_comp(current->value.first, _ptr->value.first) == false)
									current = current->parent;
								return (current);
							}
						}

						return (_ptr);
					}

			public:

				const_bidir_iterator() : _ptr(NULL), _tri_ptr(NULL) {}
				const_bidir_iterator(T* ptr, T* tri_ptr) : _ptr(ptr), _tri_ptr(tri_ptr) {}
				const_bidir_iterator(const const_bidir_iterator& rhs) : _ptr(rhs._ptr), _tri_ptr(rhs._tri_ptr) {}
				const_bidir_iterator& operator=(const const_bidir_iterator& rhs) { _ptr = rhs._ptr; _tri_ptr = rhs._tri_ptr; return (*this); }
				virtual ~const_bidir_iterator() {}

				reference operator*(void) const { return (this->_ptr->value); }
				pointer operator->(void) const { return (&this->_ptr->value); }

				const_bidir_iterator& operator++(void) {
					_ptr = get_next_ptr();
					return (*this);
				}

				const_bidir_iterator operator++(int) {
					const_bidir_iterator tmp = *this;
					_ptr = get_next_ptr();
					return (tmp);
				}

				const_bidir_iterator& operator--(void) {
					_ptr = get_prev_ptr();
					return (*this);
				}

				const_bidir_iterator operator--(int) {
					const_bidir_iterator tmp = *this;
					_ptr = get_prev_ptr();
					return (tmp);
				}

				bool operator==(const const_bidir_iterator& rhs) const { return (this->_ptr == rhs._ptr); }
				bool operator!=(const const_bidir_iterator& rhs) const { return (this->_ptr != rhs._ptr); }
		};
}

#endif