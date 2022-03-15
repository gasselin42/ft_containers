/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:30:27 by gasselin          #+#    #+#             */
/*   Updated: 2022/03/15 13:06:41 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef STACK_HPP
#define STACK_HPP

#include <deque>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{
		public:
			typedef	T			value_type;
			typedef	Container	container_type;
			typedef size_t		size_type;

		protected:
			container_type	c;
		
		public:
			explicit stack(const container_type& ctnr = container_type());
			bool empty() const;
			size_type size() const;
			value_type& top();
			const value_type& top() const;
			void push(const value_type& val);
			void pop();

			// template <class T, class Container>
			// 	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

			// template <class T, class Container>
			// 	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

			// template <class T, class Container>
			// 	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

			// template <class T, class Container>
			// 	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

			// template <class T, class Container>
			// 	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

			// template <class T, class Container>
			// 	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
	};

	template <class T, class Container>
		bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
			{ return (lhs.c == rhs.c;); }

	template <class T, class Container>
		bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

	template <class T, class Container>
		bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

	template <class T, class Container>
		bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

	template <class T, class Container>
		bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

	template <class T, class Container>
		bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
}

#endif