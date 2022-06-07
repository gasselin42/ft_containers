/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:20:51 by gasselin          #+#    #+#             */
/*   Updated: 2022/06/07 15:22:57 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "utils.hpp"

#include <iostream>

namespace ft
{
	// Empty structs to identify the category of an iterator as an iterator:
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

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

	template <>
		struct is_iterator_tag<std::random_access_iterator_tag> : public is_iterator_valid<true, std::random_access_iterator_tag> {};

	template <>
		struct is_iterator_tag<std::bidirectional_iterator_tag> : public is_iterator_valid<true, std::bidirectional_iterator_tag> {};

	template <>
		struct is_iterator_tag<std::forward_iterator_tag> : public is_iterator_valid<true, std::forward_iterator_tag> {};

	template <>
		struct is_iterator_tag<std::output_iterator_tag> : public is_iterator_valid<true, std::output_iterator_tag> {};
	
	template <>
		struct is_iterator_tag<std::input_iterator_tag> : public is_iterator_valid<true, std::input_iterator_tag> {};

	template <typename T>
		struct is_iterator : public is_iterator_tag<T> {};





	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
		struct iterator {
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

	template <class Iter, class Container>
		class random_access_iterator
		{
			public:
				typedef				Iter													iterator_type;
				typedef typename 	ft::iterator_traits<iterator_type>::iterator_category	iterator_category;
				typedef typename 	ft::iterator_traits<iterator_type>::value_type			value_type;
				typedef typename 	ft::iterator_traits<iterator_type>::difference_type		difference_type;
				typedef typename 	ft::iterator_traits<iterator_type>::pointer				pointer;
				typedef typename 	ft::iterator_traits<iterator_type>::reference 			reference;

			private:
				iterator_type _i;

			public:
				random_access_iterator() : _i(NULL) {}
				random_access_iterator(iterator_type i) : _i(i) {}
				random_access_iterator(const random_access_iterator& rhs) : _i(rhs.base()) {}
				random_access_iterator& operator=(const random_access_iterator& rhs) { _i = rhs.base(); return (*this); }

				template <class _Iter>
					random_access_iterator(const random_access_iterator<_Iter, typename enable_if<is_same<_Iter, typename Container::pointer>::value, Container>::type>& rhs) : _i(rhs.base()) {}
				
				virtual ~random_access_iterator() {}

				reference operator*(void) const { return (*_i); }
				pointer operator->(void) const { return (&(*_i)); }

				random_access_iterator& operator++(void) {
					_i++;
					return (*this);
				}

				random_access_iterator operator++(int) {
					random_access_iterator tmp = *this;
					_i++;
					return (tmp);
				}

				random_access_iterator& operator--(void) {
					_i--;
					return (*this);
				}

				random_access_iterator operator--(int) {
					random_access_iterator tmp = *this;
					_i--;
					return (tmp);
				}

				random_access_iterator operator+(int n) { return (_i + n); }
				random_access_iterator operator-(int n) { return (_i - n); }

				random_access_iterator operator+=(int n) { _i += n; return (*this); }
				random_access_iterator operator-=(int n) { _i -= n; return (*this); }

				reference operator[](difference_type n) { return (*(operator+(n))); }

				iterator_type base() const { return (_i); }
		};

		template <class _Iter, class _Container>
			random_access_iterator<_Iter, _Container> operator+(typename random_access_iterator<_Iter, _Container>::difference_type n, const random_access_iterator<_Iter, _Container>& it)
				{ return (it.base() + n); }

		template <class _Iter, class _Container>
			typename random_access_iterator<_Iter, _Container>::difference_type operator-(const random_access_iterator<_Iter, _Container>& lhs, const random_access_iterator<_Iter, _Container>& rhs)
				{ return (lhs.base() - rhs.base()); }

		template <class _Iter1, class _Iter2, class _Container>
			typename random_access_iterator<_Iter1, _Container>::difference_type operator-(const random_access_iterator<_Iter1, _Container>& lhs, const random_access_iterator<_Iter2, _Container>& rhs)
				{ return (lhs.base() - rhs.base()); }

		template <class _Iter, class _Container>
			bool operator==(const random_access_iterator<_Iter, _Container>& rhs, const random_access_iterator<_Iter, _Container>& lhs)
				{ return (rhs.base() == lhs.base()); }

		template <class _Iter1, class _Iter2, class _Container>
			bool operator==(const random_access_iterator<_Iter1, _Container>& rhs, const random_access_iterator<_Iter2, _Container>& lhs)
				{ return (rhs.base() == lhs.base()); }

		template <class _Iter, class _Container>
			bool operator!=(const random_access_iterator<_Iter, _Container>& rhs, const random_access_iterator<_Iter, _Container>& lhs)
				{ return (!(rhs.base() == lhs.base())); }

		template <class _Iter1, class _Iter2, class _Container>
			bool operator!=(const random_access_iterator<_Iter1, _Container>& rhs, const random_access_iterator<_Iter2, _Container>& lhs)
				{ return (!(rhs.base() == lhs.base())); }

		template <class _Iter, class _Container>
			bool operator<(const random_access_iterator<_Iter, _Container>& rhs, const random_access_iterator<_Iter, _Container>& lhs)
				{ return (rhs.base() < lhs.base()); }

		template <class _Iter1, class _Iter2, class _Container>
			bool operator<(const random_access_iterator<_Iter1, _Container>& rhs, const random_access_iterator<_Iter2, _Container>& lhs)
				{ return (rhs.base() < lhs.base()); }
		
		template <class _Iter, class _Container>
			bool operator>(const random_access_iterator<_Iter, _Container>& rhs, const random_access_iterator<_Iter, _Container>& lhs)
				{ return (rhs.base() > lhs.base()); }

		template <class _Iter1, class _Iter2, class _Container>
			bool operator>(const random_access_iterator<_Iter1, _Container>& rhs, const random_access_iterator<_Iter2, _Container>& lhs)
				{ return (rhs.base() > lhs.base()); }
		
		template <class _Iter, class _Container>
			bool operator>=(const random_access_iterator<_Iter, _Container>& rhs, const random_access_iterator<_Iter, _Container>& lhs)
				{ return (!(rhs.base() < lhs.base())); }

		template <class _Iter1, class _Iter2, class _Container>
			bool operator>=(const random_access_iterator<_Iter1, _Container>& rhs, const random_access_iterator<_Iter2, _Container>& lhs)
				{ return (!(rhs.base() < lhs.base())); }

		template <class _Iter, class _Container>
			bool operator<=(const random_access_iterator<_Iter, _Container>& rhs, const random_access_iterator<_Iter, _Container>& lhs)
				{ return (!(rhs.base() > lhs.base())); }

		template <class _Iter1, class _Iter2, class _Container>
			bool operator<=(const random_access_iterator<_Iter1, _Container>& rhs, const random_access_iterator<_Iter2, _Container>& lhs)
				{ return (!(rhs.base() > lhs.base())); }

	// template <class T>
	// 	class const_random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	// 	{
	// 		public:
	// 			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type 	difference_type;
	// 			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type 		value_type;
	// 			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
	// 			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
	// 			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;

	// 		private:
	// 			pointer _ptr;

	// 		public:
	// 			const_random_access_iterator() : _ptr(NULL) {}
	// 			const_random_access_iterator(pointer ptr) : _ptr(ptr) {}
	// 			const_random_access_iterator(const const_random_access_iterator& rhs) : _ptr(rhs._ptr) {}
	// 			const_random_access_iterator(const random_access_iterator<T>& rhs) : _ptr(rhs._ptr) {}
	// 			const_random_access_iterator& operator=(const const_random_access_iterator& rhs) { _ptr = rhs._ptr; return (*this); }
	// 			virtual ~const_random_access_iterator() {}

	// 			reference operator*(void) const { return (*_ptr); }
	// 			pointer operator->(void) const { return (&(*_ptr)); }

	// 			const_random_access_iterator& operator++(void) {
	// 				_ptr++;
	// 				return (*this);
	// 			}

	// 			const_random_access_iterator operator++(int) {
	// 				const_random_access_iterator tmp = *this;
	// 				_ptr++;
	// 				return (tmp);
	// 			}

	// 			const_random_access_iterator& operator--(void) {
	// 				_ptr--;
	// 				return (*this);
	// 			}

	// 			const_random_access_iterator operator--(int) {
	// 				const_random_access_iterator tmp = *this;
	// 				_ptr--;
	// 				return (tmp);
	// 			}

	// 			const_random_access_iterator operator+(int n) { return (_ptr + n); }
	// 			const_random_access_iterator operator-(int n) { return (_ptr - n); }

	// 			const_random_access_iterator operator+=(int n) { _ptr += n; return (*this); }
	// 			const_random_access_iterator operator-=(int n) { _ptr -= n; return (*this); }

	// 			reference operator[](difference_type n) { return (*(operator+(n))); }

	// 			pointer base() const { return (_ptr); }
	// 	};

	// 	template <class T>
	// 		const_random_access_iterator<T> operator+(typename const_random_access_iterator<T>::difference_type n, const const_random_access_iterator<T>& it)
	// 			{ return (it.base() + n); }

	// 	template <class T>
	// 		typename const_random_access_iterator<T>::difference_type operator-(const const_random_access_iterator<T>& lhs, const const_random_access_iterator<T>& rhs)
	// 			{ return (lhs.base() - rhs.base()); }
		
	// 	template <class T>
	// 		bool operator==(const const_random_access_iterator<T>& rhs, const const_random_access_iterator<T>& lhs)
	// 			{ return (rhs.base() == lhs.base()); }

	// 	template <class T>
	// 		bool operator!=(const const_random_access_iterator<T>& rhs, const const_random_access_iterator<T>& lhs)
	// 			{ return (!(rhs.base() == lhs.base())); }

	// 	template <class T>
	// 		bool operator<(const const_random_access_iterator<T>& rhs, const const_random_access_iterator<T>& lhs)
	// 			{ return (rhs.base() < lhs.base()); }
		
	// 	template <class T>
	// 		bool operator>(const const_random_access_iterator<T>& rhs, const const_random_access_iterator<T>& lhs)
	// 			{ return (rhs.base() > lhs.base()); }
		
	// 	template <class T>
	// 		bool operator>=(const const_random_access_iterator<T>& rhs, const const_random_access_iterator<T>& lhs)
	// 			{ return (!(rhs.base() < lhs.base())); }

	// 	template <class T>
	// 		bool operator<=(const const_random_access_iterator<T>& rhs, const const_random_access_iterator<T>& lhs)
	// 			{ return (!(rhs.base() > lhs.base())); }

	template <class Iter, class Container>
		class reverse_iterator : public ft::iterator<typename Iter::iterator_category, typename Iter::value_type>
		{
			public:
				typedef 			Iter 											iterator_type;
				typedef typename 	ft::iterator_traits<Iter>::iterator_category	iterator_category;
				typedef typename 	ft::iterator_traits<Iter>::value_type			value_type;
				typedef typename 	ft::iterator_traits<Iter>::difference_type		difference_type;
				typedef typename 	ft::iterator_traits<Iter>::pointer				pointer;
				typedef typename 	ft::iterator_traits<Iter>::reference 			reference;

			private:
				iterator_type _it;
				
			public:
				reverse_iterator() : _it() {}
				
				explicit reverse_iterator(iterator_type it) : _it(it) {}

				template <class _Iter>
					reverse_iterator(const reverse_iterator<_Iter, typename enable_if<is_same<_Iter, typename Container::iterator>::value, Container>::type>& rhs) : _it(rhs.base()) {}

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

				reverse_iterator operator+(difference_type n) const { return (reverse_iterator(base() - n)); }
				reverse_iterator operator-(difference_type n) const { return (reverse_iterator(base() + n)); }

				reverse_iterator operator+=(difference_type n) { _it -= n; return (*this); }
				reverse_iterator operator-=(difference_type n) { _it += n; return (*this); }

				iterator_type base() const { return (_it); }
		};

		template <class _Iter, class _Container>
			reverse_iterator<_Iter, _Container> operator+(typename reverse_iterator<_Iter, _Container>::difference_type n, const reverse_iterator<_Iter, _Container>& rev_it)
				{ return (reverse_iterator<_Iter, _Container>(rev_it.base() - n)); }

		template <class _Iter, class _Container>
			typename reverse_iterator<_Iter, _Container>::difference_type operator-(const reverse_iterator<_Iter, _Container>& lhs, const reverse_iterator<_Iter, _Container>& rhs)
				{ return (rhs.base() - lhs.base()); }

		template <class _Iter1, class _Iter2, class _Container>
			typename reverse_iterator<_Iter1, _Container>::difference_type operator-(const reverse_iterator<_Iter1, _Container>& lhs, const reverse_iterator<_Iter2, _Container>& rhs)
				{ return (rhs.base() - lhs.base()); }
		
		template <class _Iter, class _Container>
			bool operator==(const reverse_iterator<_Iter, _Container>& lhs, const reverse_iterator<_Iter, _Container>& rhs)
				{ return (lhs.base() == rhs.base()); }

		template <class _Iter1, class _Iter2, class _Container>
			bool operator==(const reverse_iterator<_Iter1, _Container>& lhs, const reverse_iterator<_Iter2, _Container>& rhs)
				{ return (lhs.base() == rhs.base()); }

		template <class _Iter, class _Container>
			bool operator!=(const reverse_iterator<_Iter, _Container>& lhs, const reverse_iterator<_Iter, _Container>& rhs)
				{ return (!(lhs.base() == rhs.base())); }

		template <class _Iter1, class _Iter2, class _Container>
			bool operator!=(const reverse_iterator<_Iter1, _Container>& lhs, const reverse_iterator<_Iter2, _Container>& rhs)
				{ return (!(lhs.base() == rhs.base())); }

		template <class _Iter, class _Container>
			bool operator<(const reverse_iterator<_Iter, _Container>& lhs, const reverse_iterator<_Iter, _Container>& rhs)
				{ return (lhs.base() > rhs.base()); }

		template <class _Iter1, class _Iter2, class _Container>
			bool operator<(const reverse_iterator<_Iter1, _Container>& lhs, const reverse_iterator<_Iter2, _Container>& rhs)
				{ return (lhs.base() > rhs.base()); }

		template <class _Iter, class _Container>
			bool operator>(const reverse_iterator<_Iter, _Container>& lhs, const reverse_iterator<_Iter, _Container>& rhs)
				{ return (lhs.base() < rhs.base()); }

		template <class _Iter1, class _Iter2, class _Container>
			bool operator>(const reverse_iterator<_Iter1, _Container>& lhs, const reverse_iterator<_Iter2, _Container>& rhs)
				{ return (lhs.base() < rhs.base()); }

		template <class _Iter, class _Container>
			bool operator>=(const reverse_iterator<_Iter, _Container>& lhs, const reverse_iterator<_Iter, _Container>& rhs)
				{ return (lhs.base() <= rhs.base()); }

		template <class _Iter1, class _Iter2, class _Container>
			bool operator>=(const reverse_iterator<_Iter1, _Container>& lhs, const reverse_iterator<_Iter2, _Container>& rhs)
				{ return (lhs.base() <= rhs.base()); }

		template <class _Iter, class _Container>
			bool operator<=(const reverse_iterator<_Iter, _Container>& lhs, const reverse_iterator<_Iter, _Container>& rhs)
				{ return (lhs.base() >= rhs.base()); }

		template <class _Iter1, class _Iter2, class _Container>
			bool operator<=(const reverse_iterator<_Iter1, _Container>& lhs, const reverse_iterator<_Iter2, _Container>& rhs)
				{ return (lhs.base() >= rhs.base()); }

	//'const ft::reverse_iterator<ft::random_access_iterator<int> >::iterator_type' (aka 'const ft::random_access_iterator<int>')
	//'ft::reverse_iterator<ft::random_access_iterator<int> >::difference_type' (aka 'long')

	// template <class Iterator>
	// 	class const_reverse_iterator
	// 	{
	// 		public:
	// 			typedef 			Iterator 											iterator_type;
	// 			typedef typename 	ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	// 			typedef typename 	ft::iterator_traits<Iterator>::value_type			value_type;
	// 			typedef typename 	ft::iterator_traits<Iterator>::difference_type		difference_type;
	// 			typedef typename 	ft::iterator_traits<Iterator>::pointer				pointer;
	// 			typedef typename 	ft::iterator_traits<Iterator>::reference 			reference;

	// 		private:
	// 			iterator_type _it;
				
	// 		public:
	// 			const_reverse_iterator() : _it() {}
				
	// 			explicit const_reverse_iterator(iterator_type it) : _it(it) {}

	// 			// template <class Iter>
	// 			// 	const_reverse_iterator(const const_reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) {}

	// 			template <class Iter>
	// 				const_reverse_iterator(const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) {}

	// 			const_reverse_iterator& operator=(const const_reverse_iterator& rhs) { _it = rhs._it; return (*this); }
				
	// 			~const_reverse_iterator() {}

	// 			reference operator*(void) const { iterator_type temp = _it; return (*(--temp)); }
	// 			pointer operator->(void) const { return &(operator*()); }
	// 			reference operator[](difference_type n) const { return (this->base()[-n - 1]); }

	// 			const_reverse_iterator& operator++(void) {
	// 				_it--;
	// 				return (*this);
	// 			}

	// 			const_reverse_iterator operator++(int) {
	// 				const_reverse_iterator temp = *this;
	// 				++(*this);
	// 				return temp;
	// 			}

	// 			const_reverse_iterator& operator--(void) {
	// 				_it++;
	// 				return (*this);
	// 			}

	// 			const_reverse_iterator operator--(int) {
	// 				const_reverse_iterator temp = *this;
	// 				--(*this);
	// 				return temp;
	// 			}

	// 			const_reverse_iterator operator+(difference_type n) const { return (const_reverse_iterator(base() - n)); }
	// 			const_reverse_iterator operator-(difference_type n) const { return (const_reverse_iterator(base() + n)); }

	// 			const_reverse_iterator operator+=(difference_type n) { _it -= n; return (*this); }
	// 			const_reverse_iterator operator-=(difference_type n) { _it += n; return (*this); }

	// 			iterator_type base() const { return (_it); }
	// 	};

	// 	template <class Iterator>
	// 		const_reverse_iterator<Iterator> operator+(typename const_reverse_iterator<Iterator>::difference_type n, const const_reverse_iterator<Iterator>& rev_it)
	// 			{ return (const_reverse_iterator<Iterator>(rev_it.base() - n)); }

	// 	template <class Iterator>
	// 		typename const_reverse_iterator<Iterator>::difference_type operator-(const const_reverse_iterator<Iterator>& lhs, const const_reverse_iterator<Iterator>& rhs)
	// 			{ return (rhs.base() - lhs.base()); }
		
	// 	template <class Iterator>
	// 		bool operator==(const const_reverse_iterator<Iterator>& lhs, const const_reverse_iterator<Iterator>& rhs)
	// 			{ return (lhs.base() == rhs.base()); }

	// 	template <class Iterator>
	// 		bool operator!=(const const_reverse_iterator<Iterator>& lhs, const const_reverse_iterator<Iterator>& rhs)
	// 			{ return (!(lhs.base() == rhs.base())); }

	// 	template <class Iterator>
	// 		bool operator<(const const_reverse_iterator<Iterator>& lhs, const const_reverse_iterator<Iterator>& rhs)
	// 			{ return (lhs.base() > rhs.base()); }

	// 	template <class Iterator>
	// 		bool operator>(const const_reverse_iterator<Iterator>& lhs, const const_reverse_iterator<Iterator>& rhs)
	// 			{ return (lhs.base() < rhs.base()); }

	// 	template <class Iterator>
	// 		bool operator>=(const const_reverse_iterator<Iterator>& lhs, const const_reverse_iterator<Iterator>& rhs)
	// 			{ return (!(lhs.base() <= rhs.base())); }

	// 	template <class Iterator>
	// 		bool operator<=(const const_reverse_iterator<Iterator>& lhs, const const_reverse_iterator<Iterator>& rhs)
	// 			{ return (!(lhs.base() >= rhs.base())); }
}
