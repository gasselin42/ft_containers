/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:20:51 by gasselin          #+#    #+#             */
/*   Updated: 2022/04/27 14:31:47 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "utils.hpp"

namespace ft
{
	// Empty classes to identify the category of an iterator as an iterator:
	class input_iterator_tag {};
	class output_iterator_tag {};
	class forward_iterator_tag {};
	class bidirectional_iterator_tag {};
	class random_access_iterator_tag {};

	template <bool is_integral, typename T>
		struct is_iterator_integral {
			typedef T type;
			static const bool value = is_integral;
		};

	template <bool is_valid, typename T>
		struct is_iterator_valid {
			typedef T type;
			static const bool value = is_valid;
		};

	template <class T>
		struct is_integral_type : public is_iterator_integral<false, bool> {};

	template <>
		struct is_integral_type<bool> : public is_iterator_integral<true, bool> {};

	template <>
		struct is_integral_type<char> : public is_iterator_integral<true, char> {};

	template <>
		struct is_integral_type<signed char> : public is_iterator_integral<true, signed char> {};

	template <>
		struct is_integral_type<unsigned char> : public is_iterator_integral<true, unsigned char> {};

	template <>
		struct is_integral_type<wchar_t> : public is_iterator_integral<true, wchar_t> {};

	template <>
		struct is_integral_type<short> : public is_iterator_integral<true, short> {};

	template <>
		struct is_integral_type<int> : public is_iterator_integral<true, int> {};

	template <>
		struct is_integral_type<long> : public is_iterator_integral<true, long> {};

	template <>
		struct is_integral_type<long long> : public is_iterator_integral<true, long long> {};

	template <>
		struct is_integral_type<unsigned short> : public is_iterator_integral<true, unsigned short> {};

	template <>
		struct is_integral_type<unsigned int> : public is_iterator_integral<true, unsigned int> {};

	template <>
		struct is_integral_type<unsigned long> : public is_iterator_integral<true, unsigned long> {};

	template <>
		struct is_integral_type<unsigned long long> : public is_iterator_integral<true, unsigned long long> {};

	template <typename T>
		struct is_integral : public is_integral_type<T> {};




	template <class T>
		struct is_iterator_tag : public is_iterator_valid<false, T> {};

	template <>
		struct is_iterator_tag<ft::random_access_iterator_tag> : public is_iterator_valid<true, ft::random_access_iterator_tag> {};

	template <>
		struct is_iterator_tag<ft::bidirectional_iterator_tag> : public is_iterator_valid<true, ft::bidirectional_iterator_tag> {};

	template <>
		struct is_iterator_tag<ft::forward_iterator_tag> : public is_iterator_valid<true, ft::forward_iterator_tag> {};

	template <>
		struct is_iterator_tag<ft::output_iterator_tag> : public is_iterator_valid<true, ft::output_iterator_tag> {};
	
	template <>
		struct is_iterator_tag<ft::input_iterator_tag> : public is_iterator_valid<true, ft::input_iterator_tag> {};

	template <typename T>
		struct is_iterator : public is_iterator_tag<T> {};





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
				typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type 	difference_type;
				typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type 		value_type;
				typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
				typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
				typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;

			private:
				pointer _ptr;

			public:
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

				reference operator[](difference_type n) { return (*(operator+(n))); }

				// https://en.cppreference.com/w/cpp/language/cast_operator
				// https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading/4421719#4421719
				operator random_access_iterator<const T> () const
					{ return (random_access_iterator<const T>(this->_ptr)); }
		};

	template <class Iterator>
		class reverse_iterator
		{
			public:
				typedef 			Iterator 											iterator_type;
				typedef typename 	ft::iterator_traits<Iterator>::iterator_category	iterator_category;
				typedef typename 	ft::iterator_traits<Iterator>::value_type			value_type;
				typedef typename 	ft::iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename 	ft::iterator_traits<Iterator>::pointer				pointer;
				typedef typename 	ft::iterator_traits<Iterator>::reference 			reference;

			private:
				iterator_type _it;
				
			public:
				reverse_iterator() : _it() {}
				
				explicit reverse_iterator(iterator_type it) : _it(it) {}

				template <class Iter>
					reverse_iterator(const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) {}

				reverse_iterator& operator=(const reverse_iterator& rhs) { _it = rhs._it; return (*this); }
				
				~reverse_iterator() {}

				reference operator*(void) const { iterator_type temp = _it; return (*(--temp)); }
				pointer operator->(void) const { return &(operator*()); }
				reference operator[](difference_type n) const { return (this->base()[-n - 1]); }

				reverse_iterator& operator++(void) {
					_it--;
					return (*this);
				}

				reverse_iterator operator++(int) {
					reverse_iterator temp = *this;
					++(*this);
					return temp;
				}

				reverse_iterator& operator--(void) {
					_it++;
					return (*this);
				}

				reverse_iterator operator--(int) {
					reverse_iterator temp = *this;
					--(*this);
					return temp;
				}

				reverse_iterator operator+(difference_type n) const { return (reverse_iterator(_it - n)); }
				reverse_iterator operator-(difference_type n) const { return (reverse_iterator(_it + n)); }

				reverse_iterator operator+=(difference_type n) { _it -= n; return (*this); }
				reverse_iterator operator-=(difference_type n) { _it += n; return (*this); }

				iterator_type base() const { return (_it); }
		};

		template <class Iterator>
			reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
				{ return (rev_it + n); }

		template <class Iterator>
			typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
				{ return (lhs.base() - rhs.base()); }
		
		template <class Iterator>
			bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
				{ return (lhs.base() == rhs.base()); }

		template <class Iterator>
			bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
				{ return (lhs.base() != rhs.base()); }

		template <class Iterator>
			bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
				{ return (lhs.base() <= rhs.base()); }

		template <class Iterator>
			bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
				{ return (lhs.base() >= rhs.base()); }

		template <class Iterator>
			bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
				{ return (lhs.base() > rhs.base()); }

		template <class Iterator>
			bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
				{ return (lhs.base() < rhs.base()); }
}
