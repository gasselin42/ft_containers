/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:00:05 by gasselin          #+#    #+#             */
/*   Updated: 2022/03/15 13:12:36 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
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

	template <class T1, class T2>
		struct pair {
			typedef T1 first_type;
			typedef T2 second_type;

			first_type first;
			second_type second;

			pair();
			
			template<class U, class V>
				pair(const pair<U, V>& pr);

			pair(const first_type& a, const second_type& b);

			pair& operator=(const pair& pr);
		};

	template <class T1, class T2>
		bool operator== (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
			{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template <class T1, class T2>
		bool operator!= (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
			{ return !(lhs == rhs); }

	template <class T1, class T2>
		bool operator<  (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
			{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

	template <class T1, class T2>
		bool operator<= (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
			{ return !(rhs < lhs); }

	template <class T1, class T2>
		bool operator>  (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
			{ return rhs < lhs; }

	template <class T1, class T2>
		bool operator>= (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
			{ return !(lhs < rhs); }

	template <class T1, class T2>
		ft::pair<T1, T2> make_pair(T1 x, T2 y)
			{ return ( ft::pair<T1, T2>(x, y) ); }
}

#endif