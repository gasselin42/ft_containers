/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:49:52 by gasselin          #+#    #+#             */
/*   Updated: 2022/03/18 11:31:19 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdbool.h>
#include <cstddef>
#include <stdexcept>
#include <iostream>

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
			size_type		_cont_capacity;

			size_type	get_next_capacity(const size_type n)
				{
					size_type i = 1;
					while (true)
					{
						if (i >= n)
							break ;
						i *= 2;
					}
					return (i);
				}

			template <class InputIterator>
				difference_type get_diff(InputIterator first, InputIterator last)
					{
						difference_type diff = 0;
						while (first != last)
						{
							diff++;
							first++;
						}
						return (diff);
					}

		public:
			// Constructors and Destructor
			
			// Note that if a constructor has any arguments that do not
			// have default values, it is not a default constructor.
			explicit vector(const allocator_type& alloc = allocator_type())
				: 	_alloc(alloc),
					_cont_start(NULL),
					_cont_end(NULL),
					_cont_size(0),
					_cont_capacity(0)
				{}

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: 	_alloc(alloc),
					_cont_start(NULL),
					_cont_end(NULL),
					_cont_size(n)
				{
					n = get_next_capacity(n);
					this->_cont_capacity = n;
					_cont_start = _alloc.allocate(n);
					_cont_end = _cont_start + n;
					this->assign(n, val);
				}

			template <class InputIterator>
				vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
					: 	_alloc(alloc),
						_cont_start(NULL),
						_cont_end(NULL),
						_cont_size(0),
						_cont_capacity(0)
					{
						// **** Verify if InputIterator is an integral type ****
						// difference_type diff = last - first;
						difference_type diff = get_diff(first, last);
						size_type n = get_next_capacity(diff);
						_cont_start = _alloc.allocate(n);
						_cont_end = _cont_start + n;
						assign(first, last);
					}

			vector(const vector& x)
				{ *this = x; }

			~vector()
				{
					this->clear();
					this->_alloc.deallocate(this->_cont_start, this->_cont_capacity);
				}

			// Member functions
			vector& operator=(const vector& x)
				{
					if (*this == x)
						return (*this);
					if (this->_cont_start != NULL)
						this->clear();
				}

			iterator begin()
				{ return (this->_cont_start); }

			const_iterator begin() const
				{ return (this->_cont_start); }

			iterator end()
				{ return ((this->empty()) ? this->_cont_start : this->_cont_end); }
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;

			size_type size() const
				{ return (this->_cont_size); }

			size_type max_size() const
				{ return (this->_alloc.max_size()); }

			void resize(size_type n, value_type val = value_type());

			size_type capacity() const
				{ return (this->_cont_capacity); }

			bool empty() const
				{ return (this->_cont_size == 0); }

			void reserve(size_type n)
				{
					try {	
						if (this->_cont_size == this->max_size())
							throw (std::length_error("vector::reserve"));
						if (n > this->_cont_capacity)
						{
							n = get_next_capacity(n);
							pointer _old_start = this->_cont_start;
							pointer _old_start2 = this->_cont_start;
							pointer _old_end = this->_cont_end;
							this->_cont_start = _alloc.allocate(n);
							this->_cont_end = this->_cont_start;
							this->_cont_capacity = n;
							while (_old_start != _old_end)
							{
								this->_alloc.construct(this->_cont_end, *_old_start);
								_old_start++;
								this->_cont_end++;
							}
							_alloc.deallocate(_old_start2, this->_cont_size / 2);
						}
					} catch (const std::length_error& e) {
						std::cerr << e.what() << "\n";
					}
				}

			reference operator[](size_type n)
				{ return (*(this->_cont_start + n)); }
			
			const_reference operator[](size_type n) const
				{ return (*(this->_cont_start + n)); }
			
			reference at(size_type n)
				{
					try {	
						if (n >= this->_cont_size)
							throw (std::out_of_range("vector::at"));
						return (*(this->_cont_start + n));
					} catch (const std::out_of_range& e) {
						std::cerr << e.what() << "\n";
					}
				}

			const_reference at(size_type n) const
				{
					try {	
						if (n >= this->_cont_size)
							throw (std::out_of_range("vector::at"));
						return (*(this->_cont_start + n));
					} catch (const std::out_of_range& e) {
						std::cerr << e.what() << "\n";
					}
				}

			reference front()
				{ return (*(this->_cont_start)); }

			const_reference front() const
				{ return (*(this->_cont_start)); }

			reference back()
				{ return (*(this->_cont_end - 1)); }

			const_reference back() const
				{ return (*(this->_cont_end - 1)); }
			
			template <class InputIterator>
				void assign(InputIterator first, InputIterator last);

			void assign(size_type n, const value_type& val);

			void push_back(const value_type& val)
				{
					try {	
						if (this->_cont_size == this->max_size())
							throw (std::length_error("vector::push_back"));
						if (this->_cont_capacity == 0 || this->_cont_size == this->_cont_capacity)
							this->reserve(((this->_cont_capacity == 0) ? 1 : this->_cont_capacity * 2));
						this->_alloc.construct(this->_cont_end, val);
						this->_cont_end++;
						this->_cont_size++;
					} catch (const std::length_error& e) {
						std::cerr << e.what() << "\n";
					}
				}

			void pop_back()
				{
					if (this->_cont_size == 0)
						return ;
					this->_cont_end--;
					this->_alloc.destroy(*(this->_cont_end));
					this->_cont_size--;
				}

			iterator insert(iterator position, const value_type& val)
			{
				
			}

			void insert(iterator position, size_type n, const value_type& val)
			{
				
			}

			template <class InputIterator>
				void insert(iterator position, InputIterator first, InputIterator last)
				 {
					 // Verify if InputIterator is integral
					 
				 }

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

			void clear()
				{
					for (size_type i = 0; i < this->_cont_size; i++)
					{
						this->_cont_end--;
						this->_alloc.destroy(this->_cont_end);
					}
					this->_cont_size = 0;
				}
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
