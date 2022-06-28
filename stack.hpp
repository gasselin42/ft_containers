/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:30:27 by gasselin          #+#    #+#             */
/*   Updated: 2022/06/28 12:54:17 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef STACK_HPP
#define STACK_HPP

#include <deque>
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef				Container					container_type;
			typedef typename 	Container::value_type 		value_type;
			typedef typename 	Container::size_type 		size_type;
			typedef typename 	Container::reference 		reference;
			typedef typename 	Container::const_reference 	const_reference;

		protected:
			Container	c;
		
		public:
			explicit stack(const Container& cont = Container()) : c(cont) {}

			stack(const stack& x) : c(x.c)
				{ if (x.size() > 0)
					*this = x; }

			~stack() {}

			stack& operator=(const stack& rhs)
				{ this->c = rhs.c; return (*this); }

			reference top()
				{ return (this->c.back()); }

			const_reference top() const
				{ return (this->c.back()); }

			bool empty() const
				{ return (this->c.empty()); }

			size_type size() const
				{ return (this->c.size()); }

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
			{ return (!(lhs.c == rhs.c)); }

	template <class T, class Container>
		bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
			{ return (lhs.c < rhs.c); }

	template <class T, class Container>
		bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
			{ return (lhs.c > rhs.c); }

	template <class T, class Container>
		bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
			{ return (!(lhs.c > rhs.c)); }

	template <class T, class Container>
		bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
			{ return (!(lhs.c < rhs.c)); }
}

#endif