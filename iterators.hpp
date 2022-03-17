/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:20:51 by gasselin          #+#    #+#             */
/*   Updated: 2022/03/17 16:20:48 by gasselin         ###   ########.fr       */
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
		struct iterator {
			typedef T         value_type;
			typedef Distance  difference_type;
			typedef Pointer   pointer;
			typedef Reference reference;
			typedef Category  iterator_category;
		};

	template <class T>
		class RandomIterator : ft::iterator<ft::random_access_iterator_tag, T>
		{
			
		};
	
	template <class T>
		class ConstRandomIterator : ft::iterator<ft::random_access_iterator_tag, T>
		{
			
		};

	template <class T>
		class ReverseRandomIterator : ft::iterator<ft::random_access_iterator_tag, T>
		{
			
		};

	template <class T>
		class ConstReverseRandomIterator : ft::iterator<ft::random_access_iterator_tag, T>
		{
			
		};
}

#endif