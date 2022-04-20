/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:00:05 by gasselin          #+#    #+#             */
/*   Updated: 2022/04/20 15:56:54 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP

#include "pair.hpp"

namespace ft
{
	template <bool B, class T = void> struct enable_if {};
	template <class T> struct enable_if<true, T> { typedef T type; };
	
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
}

#endif