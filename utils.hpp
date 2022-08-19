/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:00:05 by gasselin          #+#    #+#             */
/*   Updated: 2022/08/17 19:09:52 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"

namespace ft
{

	template <bool B, class T = void> struct enable_if {};
	template <class T> struct enable_if<true, T> { typedef T _type; };
	
	template <class Arg1, class Arg2, class Result>
		struct binary_function {
			typedef Arg1 first_argument_type;
			typedef Arg2 second_argument_type;
			typedef Result result_type;
		};

	template <class T>
		struct less : binary_function<T, T, bool> {
			bool operator() (const T& x, const T& y) const
				{ return x < y; }
		};

	template < typename T, T Val >
	struct integral_constant {
		typedef integral_constant   type;
		typedef T                   value_type;
		static const bool           value = Val;
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template<typename _T1, typename _T2>
		struct is_same : public false_type { };

	template<typename _Tp>
		struct is_same<_Tp, _Tp> : public true_type { };

	template <class InputIt1, class InputIt2>
		bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
									 InputIt2 first2, InputIt2 last2)
			{
				while (first1 != last1)
				{
					if (first2 == last2 || *first2 < *first1)
						return false;
					else if (*first1 < *first2)
						return true;
					++first1;
					++first2;
				}
				return (first2 != last2);
			}

	template <class InputIt1, class InputIt2, class Compare>
		bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
									 InputIt2 first2, InputIt2 last2,
									 Compare comp)
			{
				while (first1 != last1)
				{
					if (comp(*first2, *first1))
						return false;
					else if (comp(*first1, *first2))
						return true;
					++first1;
					++first2;
				}
				return (first2 != last2);
			}

	template <class InputIt1, class InputIt2>
		bool equal (InputIt1 first1, InputIt1 last1, InputIt2 first2)
			{
				while (first1 != last1) {
					if (!(*first1 == *first2))
						return false;
					++first1;
					++first2;
				}
				return true;
			}

	template <class InputIt1, class InputIt2, class BinaryPredicate>
		bool equal (InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate pred)
			{
				while (first1 != last1) {
					if (!pred(*first1, *first2))
						return false;
					++first1;
					++first2;
				}
				return true;
			}

}
