/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:20:51 by gasselin          #+#    #+#             */
/*   Updated: 2022/08/21 20:20:39 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "utils.hpp"
#include "type_traits.hpp"

#include <iostream>

namespace ft
{
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
		

		


	template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
		struct iterator {
			typedef Category  iterator_category;
			typedef T         value_type;
			typedef Distance  difference_type;
			typedef Pointer   pointer;
			typedef Reference reference;
		};

	template <typename Iterator>
		struct iterator_traits {
			typedef typename Iterator::iterator_category	iterator_category;	
			typedef typename Iterator::value_type 			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer 				pointer;
			typedef typename Iterator::reference 			reference;
		};

	template <typename T>
		struct iterator_traits<T*> {
			typedef std::random_access_iterator_tag	iterator_category;	
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef T*								pointer;
			typedef T&								reference;
		};

	template <typename T>
		struct iterator_traits<const T*> {
			typedef std::random_access_iterator_tag	iterator_category;	
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef const T*						pointer;
			typedef const T&						reference;
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
					random_access_iterator(const random_access_iterator<_Iter, typename enable_if<is_same<_Iter, typename Container::pointer>::value, Container>::_type>& rhs) : _i(rhs.base()) {}
				
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





	template <class Iter>
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
					reverse_iterator(const reverse_iterator<_Iter>& rhs) : _it(rhs.base()) {}

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

		template <class _Iter>
			reverse_iterator<_Iter> operator+(typename reverse_iterator<_Iter>::difference_type n, const reverse_iterator<_Iter>& rev_it)
				{ return (reverse_iterator<_Iter>(rev_it.base() - n)); }

		template <class _Iter>
			typename reverse_iterator<_Iter>::difference_type operator-(const reverse_iterator<_Iter>& lhs, const reverse_iterator<_Iter>& rhs)
				{ return (rhs.base() - lhs.base()); }

		template <class _Iter1, class _Iter2>
			typename reverse_iterator<_Iter1>::difference_type operator-(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs)
				{ return (rhs.base() - lhs.base()); }
		
		template <class _Iter>
			bool operator==(const reverse_iterator<_Iter>& lhs, const reverse_iterator<_Iter>& rhs)
				{ return (lhs.base() == rhs.base()); }

		template <class _Iter1, class _Iter2>
			bool operator==(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs)
				{ return (lhs.base() == rhs.base()); }

		template <class _Iter>
			bool operator!=(const reverse_iterator<_Iter>& lhs, const reverse_iterator<_Iter>& rhs)
				{ return (!(lhs.base() == rhs.base())); }

		template <class _Iter1, class _Iter2>
			bool operator!=(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs)
				{ return (!(lhs.base() == rhs.base())); }

		template <class _Iter>
			bool operator<(const reverse_iterator<_Iter>& lhs, const reverse_iterator<_Iter>& rhs)
				{ return (lhs.base() > rhs.base()); }

		template <class _Iter1, class _Iter2>
			bool operator<(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs)
				{ return (lhs.base() > rhs.base()); }

		template <class _Iter>
			bool operator>(const reverse_iterator<_Iter>& lhs, const reverse_iterator<_Iter>& rhs)
				{ return (lhs.base() < rhs.base()); }

		template <class _Iter1, class _Iter2>
			bool operator>(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs)
				{ return (lhs.base() < rhs.base()); }

		template <class _Iter>
			bool operator>=(const reverse_iterator<_Iter>& lhs, const reverse_iterator<_Iter>& rhs)
				{ return (lhs.base() <= rhs.base()); }

		template <class _Iter1, class _Iter2>
			bool operator>=(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs)
				{ return (lhs.base() <= rhs.base()); }

		template <class _Iter>
			bool operator<=(const reverse_iterator<_Iter>& lhs, const reverse_iterator<_Iter>& rhs)
				{ return (lhs.base() >= rhs.base()); }

		template <class _Iter1, class _Iter2>
			bool operator<=(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter2>& rhs)
				{ return (lhs.base() >= rhs.base()); }

}
