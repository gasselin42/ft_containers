/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:26:45 by gasselin          #+#    #+#             */
/*   Updated: 2022/08/21 20:52:19 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{

	template< class T > struct remove_const          { typedef T type; };
	template< class T > struct remove_const<const T> { typedef T type; };

	template< class T > struct remove_volatile          { typedef T type; };
	template< class T > struct remove_volatile<volatile T> { typedef T type; };

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


	template <bool B, class T = void> struct enable_if {};
	template <class T> struct enable_if<true, T> { typedef T _type; };



	template < typename >
		struct is_integral_type : public false_type {};

	template <>
		struct is_integral_type<bool> : public true_type {};

	template <>
		struct is_integral_type<char> : public true_type {};

	template <>
		struct is_integral_type<signed char> : public true_type {};

	template <>
		struct is_integral_type<unsigned char> : public true_type {};

	template <>
		struct is_integral_type<wchar_t> : public true_type {};

	template <>
		struct is_integral_type<short> : public true_type {};

	template <>
		struct is_integral_type<int> : public true_type {};

	template <>
		struct is_integral_type<long> : public true_type {};

	template <>
		struct is_integral_type<long long> : public true_type {};

	template <>
		struct is_integral_type<unsigned short> : public true_type {};

	template <>
		struct is_integral_type<unsigned int> : public true_type {};

	template <>
		struct is_integral_type<unsigned long> : public true_type {};

	template <>
		struct is_integral_type<unsigned long long> : public true_type {};

	template <typename T>
		struct is_integral : public is_integral_type< typename ft::remove_const< typename ft::remove_volatile<T>::type >::type > {};

}