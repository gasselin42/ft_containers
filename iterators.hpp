/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:20:51 by gasselin          #+#    #+#             */
/*   Updated: 2022/03/21 14:26:09 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <stdbool.h>

namespace ft
{
	// Empty classes to identify the category of an iterator as an iterator:
	class input_iterator_tag {};
	class output_iterator_tag {};
	class forward_iterator_tag {};
	class bidirectional_iterator_tag {};
	class random_access_iterator_tag {};
	class bool_tag {};
	class char_tag {};
	class signed_char_tag {};
	class unsigned_char_tag {};
	class wchar_t_tag {};
	class short_tag {};
	class int_tag {};
	class long_tag {};
	class long_long_tag {};
	class unsigned_short_tag {};
	class unsigned_int_tag {};
	class unsigned_long_tag {};
	class unsigned_long_long_tag {};

	template <bool is_integral, typename T>
		struct is_iterator_integral {
			typedef T type;
			static const bool value = is_integral;
		};

	template <class T>
		struct is_integral : public is_iterator_integral<false, bool> {};

	template <>
		struct is_integral<bool> : public is_iterator_integral<true, bool> {};

	template <>
		struct is_integral<char> : public is_iterator_integral<true, char> {};

	template <>
		struct is_integral<signed char> : public is_iterator_integral<true, signed char> {};

	template <>
		struct is_integral<unsigned char> : public is_iterator_integral<true, unsigned char> {};

	template <>
		struct is_integral<wchar_t> : public is_iterator_integral<true, wchar_t> {};

	template <>
		struct is_integral<short> : public is_iterator_integral<true, short> {};

	template <>
		struct is_integral<int> : public is_iterator_integral<true, int> {};

	template <>
		struct is_integral<long> : public is_iterator_integral<true, long> {};

	template <>
		struct is_integral<long long> : public is_iterator_integral<true, long long> {};

	template <>
		struct is_integral<unsigned short> : public is_iterator_integral<true, unsigned short> {};

	template <>
		struct is_integral<unsigned int> : public is_iterator_integral<true, unsigned int> {};

	template <>
		struct is_integral<unsigned long> : public is_iterator_integral<true, unsigned long> {};

	template <>
		struct is_integral<unsigned long long> : public is_iterator_integral<true, unsigned long long> {};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
		class iterator {
			public:
				typedef T         value_type;
				typedef Distance  difference_type;
				typedef Pointer   pointer;
				typedef Reference reference;
				typedef Category  iterator_category;
		};

	template <class Iterator>
		struct iterator_traits {
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type 			value_type;
			typedef typename Iterator::pointer 				pointer;
			typedef typename Iterator::reference 			reference;
			typedef typename Iterator::iterator_category	iterator_category;	
		};

	template <class T>
		struct iterator_traits<T*> {
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef ft::random_access_iterator_tag	iterator_category;	
		};

	template <class T>
		struct iterator_traits<const T*> {
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef ft::random_access_iterator_tag	iterator_category;	
		};

	template <class T>
		class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
		{
			public:
				// typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
				typedef T*	pointer;
				typedef T&	reference;

				random_access_iterator() : _ptr(NULL) {}
				random_access_iterator(pointer ptr) : _ptr(ptr) {}
				random_access_iterator(const random_access_iterator& rhs) : _ptr(rhs._ptr) {}
				random_access_iterator& operator=(const random_access_iterator& rhs) { _ptr = rhs._ptr; return (*this); }
				virtual ~random_access_iterator() {}

				reference operator*(void) const { return (*_ptr); }
				pointer operator->(void) const { return (&(*_ptr)); }

				random_access_iterator& operator++(void) {
					_ptr++;
					return (*this);
				}

				random_access_iterator operator++(int) {
					random_access_iterator tmp = *this;
					_ptr++;
					return (tmp);
				}

				random_access_iterator& operator--(void) {
					_ptr--;
					return (*this);
				}

				random_access_iterator operator--(int) {
					random_access_iterator tmp = *this;
					_ptr--;
					return (tmp);
				}

				random_access_iterator operator+(int n) { return (random_access_iterator(_ptr + n)); }
				random_access_iterator operator-(int n) { return (random_access_iterator(_ptr - n)); }

				random_access_iterator operator+=(int n) { _ptr += n; return (*this); }
				random_access_iterator operator-=(int n) { _ptr -= n; return (*this); }

				bool operator==(const random_access_iterator& rhs) const { return (this->_ptr == rhs._ptr); }
				bool operator!=(const random_access_iterator& rhs) const { return (this->_ptr != rhs._ptr); }
				bool operator>=(const random_access_iterator& rhs) const { return (this->_ptr >= rhs._ptr); }
				bool operator<=(const random_access_iterator& rhs) const { return (this->_ptr <= rhs._ptr); }
				bool operator<(const random_access_iterator& rhs) const { return (this->_ptr < rhs._ptr); }
				bool operator>(const random_access_iterator& rhs) const { return (this->_ptr > rhs._ptr); }

			private:
				pointer _ptr;
		};

		template <class Iterator>
		class reverse_iterator
		{
			
		};
}

#endif