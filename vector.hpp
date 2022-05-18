/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:49:52 by gasselin          #+#    #+#             */
/*   Updated: 2022/05/18 14:46:46 by gasselin         ###   ########.fr       */
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
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef 			T												value_type;
			typedef 			Alloc											allocator_type;
			typedef typename 	allocator_type::reference						reference;
			typedef typename 	allocator_type::const_reference					const_reference;
			typedef typename	allocator_type::pointer							pointer;
			typedef typename	allocator_type::const_pointer					const_pointer;
			typedef				ft::random_access_iterator<pointer, vector<T, Alloc> >				iterator;
			typedef				ft::random_access_iterator<const_pointer, vector<T, Alloc> >		const_iterator;
			typedef				ft::reverse_iterator<iterator>					reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator>			const_reverse_iterator;
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
			vector()
				: 	_alloc(),
					_cont_start(NULL),
					_cont_end(NULL),
					_cont_size(0),
					_cont_capacity(0)
				{}
			
			explicit vector(const Alloc& alloc)
				: 	_alloc(alloc),
					_cont_start(NULL),
					_cont_end(NULL),
					_cont_size(0),
					_cont_capacity(0)
				{}

			explicit vector(size_type n, const T& val = T(), const Alloc& alloc = Alloc())
				: 	_alloc(alloc),
					_cont_start(NULL),
					_cont_end(NULL),
					_cont_size(n),
					_cont_capacity(0)
				{
					if (n <= 0)
						return ;
					this->_cont_capacity = n;
					_cont_start = _alloc.allocate(this->_cont_capacity);
					_cont_end = _cont_start + n;
					this->assign(n, val);
				}

			// vector(_ForwardIterator __first, _ForwardIterator __last, const allocator_type& __a,
            //    typename enable_if<__is_cpp17_forward_iterator<_ForwardIterator>::value &&
            //                      is_constructible<
            //                         value_type,
            //                         typename iterator_traits<_ForwardIterator>::reference>::value>::type* = 0);


			template <class InputIterator>
				vector(InputIterator first, InputIterator last, const Alloc& alloc = Alloc(),
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
					: 	_alloc(alloc),
						_cont_start(NULL),
						_cont_end(NULL),
						_cont_size(0),
						_cont_capacity(0)
					{
						// Verify if InputIterator is integral
						if (!(ft::is_iterator<typename ft::iterator_traits<InputIterator>::iterator_category>::value))
							throw (std::length_error("vector::constructor"));
						
						difference_type diff = this->get_diff(first, last);
						if (diff == 0)
							return ;
							
						this->_cont_capacity = diff;
						_cont_start = _alloc.allocate(this->_cont_capacity);
						_cont_end = _cont_start;
						
						while (first != last)
							this->push_back(*(first++));
					}

			vector(const vector& x)
				: 	_alloc(),
					_cont_start(NULL),
					_cont_end(NULL),
					_cont_size(0),
					_cont_capacity(0)
					{
						*this = x;
					}

			~vector()
				{
					this->clear();
					this->_alloc.deallocate(this->_cont_start, this->_cont_capacity);
				}

			// Member functions
			allocator_type get_allocator() const
				{ return (this->_alloc); }

			vector& operator=(const vector& x)
				{
					if (*this == x)
						return (*this);
					if (this->_cont_start == NULL)
					{
						this->_cont_start = this->_alloc.allocate(x._cont_size);
						this->_cont_capacity = x._cont_size;	
					}
					else if (this->_cont_size < x._cont_size)
					{
						this->reserve(x._cont_size);
						this->_cont_capacity = x._cont_size;
					}
					this->clear();
					this->_cont_end = this->_cont_start;
					this->insert(this->begin(), x.begin(), x.end());
					return (*this);
				}

			iterator begin()
				{ return (iterator(this->_cont_start)); }

			const_iterator begin() const
				{ return (const_iterator(this->_cont_start)); }

			iterator end()
				{ return (iterator((this->empty()) ? this->_cont_start : this->_cont_end)); }

			const_iterator end() const
				{ return (const_iterator((this->empty()) ? this->_cont_start : this->_cont_end)); }

			reverse_iterator rbegin()
				{ return (reverse_iterator(this->end())); }

			const_reverse_iterator rbegin() const
				{ return (const_reverse_iterator(this->end())); }

			reverse_iterator rend()
				{ return (reverse_iterator(this->begin())); }

			const_reverse_iterator rend() const
				{ return (const_reverse_iterator(this->begin())); }

			size_type size() const
				{ return (this->_cont_size); }

			size_type max_size() const
				{
					const size_type num = std::numeric_limits<difference_type>::max();
					const size_type alc = _alloc.max_size();

					return (std::min(num, alc));
				}

			void resize(size_type n, T val = T())
				{
					if (n > this->max_size())
						throw (std::length_error("vector::reserve"));
					else if (n < this->_cont_size)
					{
						while (this->_cont_size > n)
							this->pop_back();
					}
					else if (n > this->_cont_size)
					{
						if (n > this->_cont_capacity)
							this->reserve(this->_cont_capacity*2);
						while (this->_cont_size < n)
							this->push_back(val);
					}
				}

			size_type capacity() const
				{ return (this->_cont_capacity); }

			bool empty() const
				{ return (this->_cont_size == 0); }

			void reserve(size_type n)
				{
					if (this->_cont_size == this->max_size())
						throw (std::length_error("vector::reserve"));
					else if (n > this->_cont_capacity)
					{						
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
						_alloc.deallocate(_old_start2, this->_cont_size);
					}
				}

			reference operator[](size_type n)
				{ return (*(this->_cont_start + n)); }
			
			const_reference operator[](size_type n) const
				{ return (*(this->_cont_start + n)); }
			
			reference at(size_type n)
				{	
					if (n >= this->_cont_size)
						throw (std::out_of_range("vector::at"));
					else
						return (*(this->_cont_start + n));
				}

			const_reference at(size_type n) const
				{
					if (n >= this->_cont_size)
						throw (std::out_of_range("vector::at"));
					else
						return (*(this->_cont_start + n));
				}

			reference front()
				{ return (*(this->_cont_start)); }

			const_reference front() const
				{ return (*(this->_cont_start)); }

			reference back()
				{ return (*(this->_cont_end - 1)); }

			const_reference back() const
				{ return (*(this->_cont_end - 1)); }
			
			void assign(size_type n, const T& val)
				{
					if (n > this->max_size())
						throw (std::length_error("vector::assign"));
					else
					{
						this->clear();
						if (n > this->_cont_capacity)
							this->reserve(n);
						while (n--)
							this->push_back(val);
					}
				}

			template <class InputIterator>
				void assign(InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
					{
						// Verify if InputIterator is integral
						if (!(ft::is_iterator<typename ft::iterator_traits<InputIterator>::iterator_category>::value))
							throw (std::length_error("vector::assign"));
							
						size_type diff = get_diff(first, last);
						
						if (diff > this->max_size())
							throw (std::length_error("vector::assign"));
						else if (first != last)
						{
							this->clear();
							if (diff > this->_cont_capacity)
								this->reserve(diff);
							while (first != last)
							{
								this->push_back(*first);
								first++;
							}
							
						}
					}

			void push_back(const T& val)
				{	
					if (this->_cont_size == this->max_size())
						throw (std::length_error("vector::push_back"));
					else {
						if (this->_cont_capacity == 0 || this->_cont_size == this->_cont_capacity)
							this->reserve(((this->_cont_capacity == 0) ? 1 : this->_cont_capacity * 2));
						this->_alloc.construct(this->_cont_end, val);
						this->_cont_end++;
						this->_cont_size++;
					}
				}

			void pop_back()
				{
					if (this->_cont_size == 0)
						return ;
					this->_cont_end--;
					this->_alloc.destroy(this->_cont_end);
					this->_cont_size--;
				}

			iterator insert(iterator position, const T& val)
				{
					try {	
						if (this->_cont_size == this->max_size())
							throw (std::length_error("vector::insert"));
					} catch (const std::length_error& e) {
						std::cerr << e.what() << "\n";
						return (this->_cont_start);
					}
					
					iterator it = begin();
					size_type i;
					
					if (it == end())
						i = 0;
					else
						i = get_diff(begin(), position);
						
					if (this->_cont_size == this->_cont_capacity)
						this->reserve(((this->_cont_capacity == 0) ? 1 : this->_cont_capacity * 2));
					
					size_type j = 0;
					while (j < this->_cont_size - i) {
						this->_alloc.construct(this->_cont_end - j, *(this->_cont_end - 1 - j));
						this->_alloc.destroy(this->_cont_end - 1 - j);
						j++;
					}
					
					this->_cont_end++;
					this->_cont_size++;
					this->_alloc.construct(this->_cont_start + i, val);
					
					return (this->_cont_start + i);
				}

			void insert(iterator position, size_type n, const T& val)
				{
					if (n == 0)
						return ;
						
					try {	
						if ((this->_cont_size + n) > this->max_size())
							throw (std::length_error("vector::insert"));
					} catch (const std::length_error& e) {
						std::cerr << e.what() << "\n";
						return ;
					}

					if (size() + n > capacity())
					{
						difference_type diff = get_diff(begin(), position);
						this->reserve(std::max(size() + n, capacity() * 2));
						position = begin() + diff;
					}
					
					while (n--)
						position = insert(position, val) + 1;
				}

			template <class InputIterator>
				void insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
					{
						// Verify if InputIterator is integral
						if (!(ft::is_iterator<typename ft::iterator_traits<InputIterator>::iterator_category>::value))
							throw (std::length_error("vector::insert"));
							
						if (first == last)
							return ;
							
						size_type diff_insert = get_diff(first, last);
						try {	
							if ((this->_cont_size + diff_insert) > this->max_size())
								throw (std::length_error("vector::insert"));
						} catch (const std::length_error& e) {
							std::cerr << e.what() << "\n";
							return ;
						}

						if (size() + diff_insert > capacity())
						{
							difference_type diff = get_diff(begin(), position);
							this->reserve(std::max(size() + diff_insert, capacity() * 2));
							position = begin() + diff;
						}
						
						while (first != last)
						{
							position = insert(position, *first) + 1;
							first++;
						}
					}

			iterator erase(iterator position)
				{
					if (position >= this->end())
						return (this->end());
	
					pointer pos = &(*position);
	
					this->_alloc.destroy(&(*position));
					
					if (position != this->end() - 1)
					{
						size_type diff = get_diff(position, this->end() - 1);
						for (size_type j = 0; j < diff; j++) {
							this->_alloc.construct(&(*position) + j, *(position + j + 1));
							this->_alloc.destroy(&(*position) + j + 1);
						}
					}

					this->_cont_end--;
					this->_cont_size--;
					
					return (iterator(pos));
				}

			iterator erase(iterator first, iterator last)
				{
					difference_type diff = get_diff(first, last);

					if (diff == 0)
						return (last);
					
					if (first >= this->end())
						return (this->end());

					while (diff--) {
						first = erase(first);
						if (first >= this->end())
							break ;
					}
					
					return (first);
				}

			void swap(vector& x)
				{
					allocator_type 	tmp_alloc = this->_alloc;
					pointer			tmp_cont_start = this->_cont_start;
					pointer			tmp_cont_end = this->_cont_end;
					size_t			tmp_cont_size = this->_cont_size;
					size_t			tmp_cont_capacity = this->_cont_capacity;

					this->_alloc = x._alloc;
					this->_cont_start = x._cont_start;
					this->_cont_end = x._cont_end;
					this->_cont_size = x._cont_size;
					this->_cont_capacity = x._cont_capacity;

					x._alloc = tmp_alloc;
					x._cont_start = tmp_cont_start;
					x._cont_end = tmp_cont_end;
					x._cont_size = tmp_cont_size;
					x._cont_capacity = tmp_cont_capacity;
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

			T* data()
				{ return (this->_cont_start); }

			const T* data() const
				{ return (this->_cont_start); }
	};

	template <class T, class Alloc>
		bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
			{ 
				if (lhs.size() == rhs.size())
					if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
						return (true);
				return (false);
			}

	template <class T, class Alloc>
		bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
			{ return (!(lhs == rhs)); }

	template <class T, class Alloc>
		bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
			{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template <class T, class Alloc>
		bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
			{ return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }

	template <class T, class Alloc>
		bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
			{ return (!(lhs > rhs)); }

	template <class T, class Alloc>
		bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
			{ return (!(lhs < rhs)); }

	template <class T, class Alloc>
		void swap(ft::vector<T, Alloc>& x, ft::vector<T, Alloc>& y)
			{ x.swap(y); }
}

#endif
