/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:30:27 by gasselin          #+#    #+#             */
/*   Updated: 2022/03/31 10:40:00 by gasselin         ###   ########.fr       */
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
			explicit stack(const container_type& cont = container_type()) : c(cont) {}

			stack(const stack& x)
				{ *this = x; }

			~stack() {}

			stack& operator=(const stack& rhs)
				{ this->c = rhs.c; }

			bool empty() const
				{ return (this->c.empty()); }

			size_type size() const
				{ return (this->c.size()); }

			value_type& top()
				{ return (this->c.back()); }

			const value_type& top() const
				{ return (this->c.back()); }

			void push(const value_type& val)
				{ this->c.push_back(val); }

			void pop()
				{ this->c.pop_back(); }

			template <class TF, class ContainerF>
				friend bool operator==(const ft::stack<TF, ContainerF>& lhs, const ft::stack<TF, ContainerF>& rhs);

			template <class TF, class ContainerF>
				friend bool operator!=(const ft::stack<TF, ContainerF>& lhs, const ft::stack<TF, ContainerF>& rhs);

			template <class TF, class ContainerF>
				friend bool operator<(const ft::stack<TF, ContainerF>& lhs, const ft::stack<TF, ContainerF>& rhs);

			template <class TF, class ContainerF>
				friend bool operator<=(const ft::stack<TF, ContainerF>& lhs, const ft::stack<TF, ContainerF>& rhs);

			template <class TF, class ContainerF>
				friend bool operator>(const ft::stack<TF, ContainerF>& lhs, const ft::stack<TF, ContainerF>& rhs);

			template <class TF, class ContainerF>
				friend bool operator>=(const ft::stack<TF, ContainerF>& lhs, const ft::stack<TF, ContainerF>& rhs);
	};

	template <class T, class Container>
		bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
			{ return (lhs.c == rhs.c); }

	template <class T, class Container>
		bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
			{ return (lhs.c != rhs.c); }

	template <class T, class Container>
		bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
			{ return (lhs.c < rhs.c); }

	template <class T, class Container>
		bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
			{ return (lhs.c <= rhs.c); }

	template <class T, class Container>
		bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
			{ return (lhs.c > rhs.c); }

	template <class T, class Container>
		bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
			{ return (lhs.c >= rhs.c); }
}

#endif