/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:49:52 by gasselin          #+#    #+#             */
/*   Updated: 2022/03/14 14:44:47 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdbool.h>

namespace ft
{
	template < class T, class Alloc=std::allocator<T> >
	class vector
	{
		public:
			typedef 			T value_type;
			typedef 			Alloc allocator_type;
			typedef typename 	allocator_type::reference reference;
			typedef typename 	allocator_type::const_reference const_reference;
			typedef typename	allocator_type::pointer pointer;
			typedef typename	allocator_type::const_pointer const_pointer;
			typedef				ft::iterator<value_type> iterator;
			typedef				ft::const_iterator<value_type> const_iterator;
			typedef				ft::reverse_iterator<iterator> reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename	ft::iterator_traits<iterator>::difference_type difference_type;
			typedef typename	allocator_type::size_type size_type;

			// Constructors and Destructor
			explicit vector(const allocator_type& alloc = allocator_type());

			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type());

			template <class InputIterator>
				vector(InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type());

			vector(const vector& x);

			~vector();

			// Member functions
			vector& operator=(const vector& x);
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			size_type size() const;
			size_type max_size() const;
			void resize(size_type n, value_type val = value_type());
			size_type capacity() const;
			bool empty() const;
			void reserve(size_type n);
			reference operator[](size_type n);
			const_reference operator[](size_type n) const;
			reference at(size_type n);
			const_reference at(size_type n) const;
			reference front(size_type n);
			const_reference front(size_type n) const;
			reference back(size_type n);
			const_reference back(size_type n) const;
			
			template <class InputIterator>
				void assign(InputIterator first, InputIterator last);

			void assign(size_type n, const value_type& val)
			void push_bask(const value_type& val);
			void pop_back();
			iterator insert(iterator position, const value_type& val);
			void insert(iterator position, size_type n, const value_type& val);
			
			template <class InputIterator>
				void insert(iterator position, InputIterator first, InputIterator last);

			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);
			void swap(vector& x);
			void clear();
	};

	template <class T, class Alloc>
		bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
}

#endif