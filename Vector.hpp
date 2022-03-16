/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:49:52 by gasselin          #+#    #+#             */
/*   Updated: 2022/03/16 17:03:27 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdbool.h>
#include <cstddef>

#include "iterators.hpp"

namespace ft
{
	template < class T, class Alloc=std::allocator<T> >
	class vector
	{	
		public:
			typedef 			T												value_type;
			typedef 			Alloc											allocator_type;
			typedef typename 	allocator_type::reference						reference;
			typedef typename 	allocator_type::const_reference					const_reference;
			typedef typename	allocator_type::pointer							pointer;
			typedef typename	allocator_type::const_pointer					const_pointer;
			typedef				ft::RandomIterator<value_type>					iterator;
			typedef				ft::ConstRandomIterator<value_type>				const_iterator;
			typedef				ft::ReverseRandomIterator<iterator>				reverse_iterator;
			typedef				ft::ConstReverseRandomIterator<const_iterator>	const_reverse_iterator;
			typedef				ptrdiff_t										difference_type;
			typedef				size_t											size_type;
			
		private:
			allocator_type 	_alloc;
			pointer			_cont_start;
			pointer			_cont_end;
			size_type		_cont_size;

			// Constructors and Destructor
			
			// Note that if a constructor has any arguments that do not
			// have default values, it is not a default constructor.
			explicit vector(const allocator_type& alloc = allocator_type())
				: 	_alloc(alloc),
					_cont_start(NULL),
					_cont_end(NULL),
					_cont_size(0)
				{}

			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type());
				: 	_alloc(alloc),
					_cont_start(NULL),
					_cont_end(NULL),
					_cont_size(n)
				{
					_cont_start = _alloc.allocate(n);
					_cont_end = _cont_start + n;
					assign(n, val);
				}

			template <class InputIterator>
				vector(InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type());
					: 	_alloc(alloc),
						_cont_start(NULL),
						_cont_end(NULL),
						_cont_size(0)
					{
						size_type n;
						// Calculate distance between the 2 iterators
						// Verify if InputIterator is an integral type
						_cont_start = _alloc.allocate(n);
						_cont_end = _cont_start + n;
						assign(first, last);
					}

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

			void assign(size_type n, const value_type& val);
			void push_bask(const value_type& val);
			void pop_back();
			iterator insert(iterator position, const value_type& val);
			void insert(iterator position, size_type n, const value_type& val);
			
			template <class InputIterator>
				void insert(iterator position, InputIterator first, InputIterator last);

			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);

			void swap(vector& x)
			{
				allocator_type 	tmp_alloc = this->_alloc;
				pointer			tmp_cont_start = this->_cont_start;
				pointer			tmp_cont_end = this->_cont_end;
				size_t			tmp_cont_size = this->_cont_size;

				this->_alloc = x._alloc;
				this->_cont_start = x._cont_start;
				this->_cont_end = x._cont_end;
				this->_cont_size = x._cont_size;

				x._alloc = tmp_alloc;
				x._cont_start = tmp_cont_start;
				x._cont_end = tmp_cont_end;
				x._cont_size = tmp_cont_size;
			}

			void clear();
	};

	template <class T, class Alloc>
		bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
			{ return (lhs == rhs); }

	template <class T, class Alloc>
		bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
			{ return (lhs != rhs); }

	template <class T, class Alloc>
		bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
			{ return (lhs < rhs); }

	template <class T, class Alloc>
		bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
			{ return (lhs <= rhs); }

	template <class T, class Alloc>
		bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
			{ return (lhs > rhs); }

	template <class T, class Alloc>
		bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
			{ return (lhs >= rhs); }

	template <class T, class Alloc>
		void swap(ft::vector<T, Alloc>& x,ft:: vector<T, Alloc>& y)
			{ x.swap(y); }
}

#endif