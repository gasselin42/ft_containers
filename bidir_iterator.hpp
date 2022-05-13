/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidir_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:16:38 by gasselin          #+#    #+#             */
/*   Updated: 2022/05/13 11:37:34 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterators.hpp"
#include "utils.hpp"
#include "BST.hpp"

namespace ft
{
	template < class T, class Compare = ft::less<T> >
		class bidir_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
		{
			public:
				typedef typename	T::value_type																	value_type;
				typedef typename	ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
				typedef typename	ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category		iterator_category;
				typedef typename	ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
				typedef typename	ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference				reference;

				T*	_ptr;
				T*	_tri_ptr;
				T*	_exts;
				Compare		_comp;

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
						while (current->left != NULL)
							current = current->left;
						return (current);
					}
				
				T* get_next_ptr()
					{
						T* current;

						if (_ptr == _exts->right)
							return (NULL);

						if (_ptr == _exts->left)
							return (_tri_ptr->left);

						if (_ptr == find_max(_tri_ptr->parent))
							return (_exts->right);

						if (_tri_ptr->parent != _exts->right &&  _tri_ptr->parent->left != NULL && find_max(_tri_ptr->parent->left) == _ptr)
							return (_tri_ptr->parent);
						
						if (_ptr->right != NULL)
							return (find_min(_ptr->right));
						
						if (_ptr->right == NULL)
						{
							if (_ptr->parent->left != NULL && _ptr->parent->left == _ptr)
								return (_ptr->parent);
							else if (_ptr->parent->right != NULL && _ptr->parent->right == _ptr)
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
						
						if (_ptr == _exts->left)
							return (NULL);

						if (_ptr == _exts->right)
							return (_tri_ptr->right);

						if (_ptr == find_min(_tri_ptr->parent))
							return (_exts->left);

						if (_tri_ptr->parent != _exts->right &&  _tri_ptr->parent->right != NULL && find_min(_tri_ptr->parent->right) == _ptr)
							return (_tri_ptr->parent);
						
						if (_ptr->left != NULL)
							return (find_max(_ptr->left));

						if (_ptr->left == NULL)
						{
							if (_ptr->parent->right != NULL && _ptr->parent->right == _ptr)
								return (_ptr->parent);
							else if (_ptr->parent->left != NULL && _ptr->parent->left == _ptr)
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

				bidir_iterator() : _ptr(NULL), _tri_ptr(NULL), _exts(NULL) {}
				bidir_iterator(T* ptr, T* tri_ptr, T* exts) : _ptr(ptr), _tri_ptr(tri_ptr), _exts(exts) {}
				bidir_iterator(const bidir_iterator& rhs) : _ptr(rhs._ptr), _tri_ptr(rhs._tri_ptr), _exts(rhs._exts) {}
				bidir_iterator& operator=(const bidir_iterator& rhs)
					{ _ptr = rhs._ptr; _tri_ptr = rhs._tri_ptr; _exts = rhs._exts; return (*this); }
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

				T* base() const { return (_ptr); }
		};

		template < class T, class Compare>
			bool operator==(const bidir_iterator<T, Compare>& rhs, const bidir_iterator<T, Compare>& lhs)
				{ return (lhs.base() == rhs.base()); }
			
		template < class T, class Compare>
			bool operator!=(const bidir_iterator<T, Compare>& rhs, const bidir_iterator<T, Compare>& lhs)
				{ return (!(lhs.base() == rhs.base())); }

	template < class T, class Compare>
		class const_bidir_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
		{
			public:
				typedef typename T::value_type																	value_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;

				T*	_ptr;
				T*	_tri_ptr;
				T*	_exts;
				Compare	_comp;

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
						while (current->left != NULL)
							current = current->left;
						return (current);
					}
				
				T* get_next_ptr()
					{
						T* current;

						if (_ptr == _exts->right)
							return (NULL);

						if (_ptr == _exts->left)
							return (_tri_ptr->left);

						if (_ptr == find_max(_tri_ptr->parent))
							return (_exts->right);

						if (_tri_ptr->parent != _exts->right &&  _tri_ptr->parent->left != NULL && find_max(_tri_ptr->parent->left) == _ptr)
							return (_tri_ptr->parent);
						
						if (_ptr->right != NULL)
							return (find_min(_ptr->right));
						
						if (_ptr->right == NULL)
						{
							if (_ptr->parent->left != NULL && _ptr->parent->left == _ptr)
								return (_ptr->parent);
							else if (_ptr->parent->right != NULL && _ptr->parent->right == _ptr)
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
						
						if (_ptr == _exts->left)
							return (NULL);

						if (_ptr == _exts->right)
							return (_tri_ptr->right);

						if (_ptr == find_min(_tri_ptr->parent))
							return (_exts->left);

						if (_tri_ptr->parent != _exts->right &&  _tri_ptr->parent->right != NULL && find_min(_tri_ptr->parent->right) == _ptr)
							return (_tri_ptr->parent);
						
						if (_ptr->left != NULL)
							return (find_max(_ptr->left));

						if (_ptr->left == NULL)
						{
							if (_ptr->parent->right != NULL && _ptr->parent->right == _ptr)
								return (_ptr->parent);
							else if (_ptr->parent->left != NULL && _ptr->parent->left == _ptr)
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

				const_bidir_iterator() : _ptr(NULL), _tri_ptr(NULL), _exts(NULL) {}
				const_bidir_iterator(T* ptr, T* tri_ptr, T* exts) : _ptr(ptr), _tri_ptr(tri_ptr), _exts(exts) {}
				const_bidir_iterator(const const_bidir_iterator& rhs) : _ptr(rhs._ptr), _tri_ptr(rhs._tri_ptr), _exts(rhs._exts) {}
				const_bidir_iterator(const bidir_iterator<T, Compare>& rhs) : _ptr(rhs._ptr), _tri_ptr(rhs._tri_ptr) {}
				const_bidir_iterator& operator=(const const_bidir_iterator& rhs)
					{ _ptr = rhs._ptr; _tri_ptr = rhs._tri_ptr; _exts = rhs._exts; return (*this); }
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

				T* base() const { return (_ptr); }
		};
		
		template < class T, class Compare>
			bool operator==(const const_bidir_iterator<T, Compare>& rhs, const const_bidir_iterator<T, Compare>& lhs)
				{ return (lhs.base() == rhs.base()); }
			
		template < class T, class Compare>
			bool operator!=(const const_bidir_iterator<T, Compare>& rhs, const const_bidir_iterator<T, Compare>& lhs)
				{ return (!(lhs.base() == rhs.base())); }
}
