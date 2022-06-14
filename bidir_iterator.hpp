/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidir_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:16:38 by gasselin          #+#    #+#             */
/*   Updated: 2022/06/13 17:15:14 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterators.hpp"
#include "utils.hpp"

namespace ft
{
	template < class T, class V >
		class const_bidir_iterator;

	template < class T, class V >
		class bidir_iterator
		{
			public:
				typedef 			V									value_type;
				typedef 			std::bidirectional_iterator_tag		iterator_category;
				typedef 			ptrdiff_t							difference_type;
				typedef 			value_type*							pointer;
				typedef				value_type&							reference;
				typedef 			bidir_iterator<T, V>				iterator;
				typedef 			const_bidir_iterator<T, V>			const_iterator;

				T*	_ptr;
				T*	_tri_ptr;

			private:
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
						while (current->left != NULL && current->left != _tri_ptr->left->left)
							current = current->left;
						return (current);
					}

				T* get_next_ptr()
					{
						if (_ptr == _tri_ptr->right)
							return (_tri_ptr->parent->parent);
						if (_ptr->right)
						{
							_ptr = _ptr->right;
							while (_ptr->left)
								_ptr = _ptr->left;
						}
						else
						{
							T* tmp = _ptr;
							_ptr = _ptr->parent;
							while (_ptr->right == tmp)
							{
								tmp = _ptr;
								_ptr = _ptr->parent;
							}
						}
						return (_ptr);
					}

				T* get_prev_ptr()
					{
						if (_ptr->left)
						{
							_ptr = _ptr->left;
							while (_ptr->right)
								_ptr = _ptr->right;
						}
						else
						{
							T* tmp = _ptr;
							_ptr = _ptr->parent;
							while (_ptr->left == tmp)
							{
								tmp = _ptr;
								_ptr = _ptr->parent;
							}
						}
						return (_ptr);
					}

			public:
				
				bidir_iterator() : _ptr(NULL), _tri_ptr(NULL) {}
				bidir_iterator(T* ptr, T* tri_ptr) : _ptr(ptr), _tri_ptr(tri_ptr) {}
				bidir_iterator(const bidir_iterator& rhs) : _ptr(rhs._ptr), _tri_ptr(rhs._tri_ptr) {}
				bidir_iterator& operator=(const bidir_iterator& rhs)
					{ _ptr = rhs._ptr; _tri_ptr = rhs._tri_ptr; return (*this); }
				virtual ~bidir_iterator() {}

				reference operator*(void) const { return (_ptr->value); }
				pointer operator->(void) const { return (&_ptr->value); }

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

				T* base() { return (_ptr); }
				const T* base() const { return (_ptr); }
		};

		template < class T, class V >
			bool operator==(const bidir_iterator<T,V>& rhs, const bidir_iterator<T,V>& lhs)
				{ return (lhs.base() == rhs.base()); }
			
		template < class T, class V >
			bool operator!=(const bidir_iterator<T,V>& rhs, const bidir_iterator<T,V>& lhs)
				{ return (!(lhs.base() == rhs.base())); }

	template < class T, class V >
		class const_bidir_iterator
		{
			public:
				typedef 			V									value_type;
				typedef 			std::bidirectional_iterator_tag		iterator_category;
				typedef 			ptrdiff_t							difference_type;
				typedef const		value_type*							pointer;
				typedef const		value_type&							reference;
				typedef 			bidir_iterator<T, V>				iterator;
				typedef 			const_bidir_iterator<T, V>			const_iterator;

				T*	_ptr;
				T*	_tri_ptr;

			private:
				T* find_max(T* ptr) const
					{
						T* current;

						current = ptr;
						while (current->right != NULL)
							current = current->right;
						return (current);
					}

				T* find_min(T* ptr) const
					{
						T* current;

						current = ptr;
						while (current->left != NULL && current->left != _tri_ptr->left->left)
							current = current->left;
						return (current);
					}

				T* get_next_ptr()
					{
						if (_ptr == _tri_ptr->right)
							return (_tri_ptr->parent->parent);
						if (_ptr->right)
						{
							_ptr = _ptr->right;
							while (_ptr->left)
								_ptr = _ptr->left;
						}
						else
						{
							T* tmp = _ptr;
							_ptr = _ptr->parent;
							while (_ptr->right == tmp)
							{
								tmp = _ptr;
								_ptr = _ptr->parent;
							}
						}
						return (_ptr);
					}

				T* get_prev_ptr()
					{
						if (_ptr->left)
						{
							_ptr = _ptr->left;
							while (_ptr->right)
								_ptr = _ptr->right;
						}
						else
						{
							T* tmp = _ptr;
							_ptr = _ptr->parent;
							while (_ptr->left == tmp)
							{
								tmp = _ptr;
								_ptr = _ptr->parent;
							}
						}
						return (_ptr);
					}

			public:
				const_bidir_iterator() : _ptr(NULL), _tri_ptr(NULL) {}
				const_bidir_iterator(T* ptr, T* tri_ptr) : _ptr(ptr), _tri_ptr(tri_ptr) {}
				const_bidir_iterator(const const_bidir_iterator& rhs) : _ptr(rhs._ptr), _tri_ptr(rhs._tri_ptr) {}				
				const_bidir_iterator(const bidir_iterator<T,V>& rhs) : _ptr(rhs._ptr), _tri_ptr(rhs._tri_ptr) {}
				const_bidir_iterator& operator=(const const_bidir_iterator& rhs)
					{ _ptr = rhs._ptr; _tri_ptr = rhs._tri_ptr; return (*this); }
				virtual ~const_bidir_iterator() {}

				reference operator*(void) const { return (_ptr->value); }
				pointer operator->(void) const { return (&_ptr->value); }

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

				T* base() { return (_ptr); }
				const T* base() const { return (_ptr); }
		};
		
		template < class T, class V >
			bool operator==(const const_bidir_iterator<T,V>& rhs, const const_bidir_iterator<T,V>& lhs)
				{ return (lhs.base() == rhs.base()); }
			
		template < class T, class V >
			bool operator!=(const const_bidir_iterator<T,V>& rhs, const const_bidir_iterator<T,V>& lhs)
				{ return (!(lhs.base() == rhs.base())); }

		template < class T, class V >
			bool operator==(const bidir_iterator<T,V>& rhs, const const_bidir_iterator<T,V>& lhs)
				{ return (lhs.base() == rhs.base()); }
			
		template < class T, class V >
			bool operator!=(const bidir_iterator<T,V>& rhs, const const_bidir_iterator<T,V>& lhs)
				{ return (!(lhs.base() == rhs.base())); }

		template < class T, class V >
			bool operator==(const const_bidir_iterator<T,V>& rhs, const bidir_iterator<T,V>& lhs)
				{ return (lhs.base() == rhs.base()); }

		template < class T, class V >
			bool operator!=(const const_bidir_iterator<T,V>& rhs, const bidir_iterator<T,V>& lhs)
				{ return (!(lhs.base() == rhs.base())); }

}
