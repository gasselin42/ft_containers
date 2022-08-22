/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:49:52 by gasselin          #+#    #+#             */
/*   Updated: 2022/08/21 20:10:16 by gasselin         ###   ########.fr       */
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

// insert_size
// resize ?

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef 			T																value_type;
			typedef 			Alloc															allocator_type;
			typedef typename 	allocator_type::reference										reference;
			typedef typename 	allocator_type::const_reference									const_reference;
			typedef typename	allocator_type::pointer											pointer;
			typedef typename	allocator_type::const_pointer									const_pointer;
			typedef				ft::random_access_iterator<pointer, vector<T, Alloc> >			iterator;
			typedef				ft::random_access_iterator<const_pointer, vector<T, Alloc> >	const_iterator;
			typedef				ft::reverse_iterator<iterator>				reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef				ptrdiff_t														difference_type;
			typedef				size_t															size_type;
			
		private:
			allocator_type 	_alloc;
			pointer			_cont_start;
			pointer			_cont_end;
			size_type		_cont_size;
			size_type		_cont_capacity;

			template <class InputIterator>
				void construct_range(InputIterator first, InputIterator last, std::input_iterator_tag)
					{
						for (; first != last; ++first)
							push_back(*first);
					}

			template <class ForwardIterator>
				void construct_range(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
					{
						difference_type n = std::distance(first, last);
						if (n > 0)
							_cont_start = _alloc.allocate(n);
						_cont_capacity = n;
						_cont_end = _cont_start;
						_cont_size = n;
						for (; first != last; ++first)
						{
							_alloc.construct(_cont_end, *first);
							_cont_end++;
						}
					}

			pointer construct_range(pointer dest, const_pointer end, const_reference value)
				{
					for (; dest != end; ++dest) 
						_alloc.construct(dest, value);  
					return dest;
				}

			template <typename Iter>
				pointer construct_range(pointer dest, Iter start, Iter end)
					{
						for (; start != end; ++dest, ++start) 
							_alloc.construct(dest, *start);  
						return dest;
					}

			template <class InputIterator>
				void assign_range(InputIterator first, InputIterator last, std::input_iterator_tag)
					{
						clear();
						for (; first != last; ++first)
							push_back(*first);
					}

			template <class ForwardIterator>
				void assign_range(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
					{
						size_type new_size = std::distance(first, last);
						if (new_size < size()) 
						{
							iterator it = std::copy(first, last, begin());
							erase(it, end());
						} 
						else 
						{
							if (new_size > capacity())
								reserve(new_size);
							ForwardIterator it = first;
							std::advance(it, size());
							std::copy(first, it, begin());
							insert(end(), it, last);
						}
					}

			template <class InputIterator>
				void insert_range(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag)
					{
						if (position == end())
						{
							for (; first != last; ++first)
								push_back(*first);
						}
						else if (first != last)
						{		
							size_type diff_insert = std::distance(first, last);

							if (size() + diff_insert > capacity())
							{
								size_type diff = std::distance(begin(), position);
								this->reserve(std::max(size() + diff_insert, capacity() * 2));
								position = begin() + diff;
							}

							while (first != last)
							{
								position = insert(position, *first) + 1;
								first++;
							}
						}
					}

			template <class ForwardIterator>
				void insert_range(iterator position, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
					{
						difference_type _n = std::distance(first, last);
						difference_type _dist = std::distance(position.base(), _cont_end);
						if (size() + _n > capacity())
							reserve(((this->_cont_capacity == 0) ? _n : std::max(capacity() * 2, size() + _n)));

						pointer _ptr = _cont_end - _dist;
						pointer _old_end = _cont_end;
						_cont_end += _n;
						_cont_size += _n;

						for (difference_type i = 0; i != _dist; ++i)
						{
							_alloc.construct(_cont_end - i - 1, *(_old_end - 1 - i));
							_alloc.destroy(_old_end - 1 - i);
						}


						for (; first != last; ++first, ++_ptr){
							_alloc.construct(_ptr, *first);
						}
					}

			iterator move_right(iterator pos, size_type n)
				{
					iterator cpy = end() - 1;
					iterator dest = cpy + n;
					if (_cont_size)
					{
						for (; dest != pos && cpy >= pos; --cpy, --dest) {
							if (dest < end())
								*dest = *cpy;
							else
								_alloc.construct(dest.base(), *cpy);
						}
					}
					return ++dest;
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
					_cont_size(0),
					_cont_capacity(0)
				{
					if (n <= 0)
						return ;
					this->_cont_capacity = n;
					_cont_start = _alloc.allocate(this->_cont_capacity);
					_cont_end = _cont_start;
					while (n--)
						this->push_back(val);
				}

			template <class InputIterator>
				vector(InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::_type last, const Alloc& alloc = Alloc())
					: 	_alloc(alloc),
						_cont_start(NULL),
						_cont_end(NULL),
						_cont_size(0),
						_cont_capacity(0)
					{
						typedef typename iterator_traits<InputIterator>::iterator_category category;
						construct_range(first, last, category());
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
					if (!empty())
						this->clear();
					if (this->_cont_capacity)
						this->_alloc.deallocate(this->_cont_start, this->_cont_capacity);
				}

			// Member functions
			allocator_type get_allocator() const
				{ return (this->_alloc); }

			vector& operator=(const vector& x)
				{
					if (*this == x || x.size() == 0)
						return (*this);
					this->reserve(x.size());
					this->assign(x.begin(), x.end());
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
						size_type _old_capacity = this->_cont_capacity;
						
						this->_cont_start = _alloc.allocate(n);
						this->_cont_end = this->_cont_start;
						this->_cont_capacity = n;
						
						while (_old_start != _old_end)
						{
							this->_alloc.construct(this->_cont_end, *_old_start);
							this->_alloc.destroy(_old_start);
							_old_start++;
							this->_cont_end++;
						}
						
						if (_old_capacity)
							_alloc.deallocate(_old_start2, _old_capacity);
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
					if (n > capacity())
						reserve(n);
					this->clear();
					_cont_end = _cont_start;
					_cont_size = n;
					for (size_type i = 0; i != n; i++)
					{
						_alloc.construct(_cont_end, val);
						_cont_end++;
					}
				}

			template <class InputIterator>
				void assign(InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::_type last)
					{
						typedef typename iterator_traits<InputIterator>::iterator_category category;
						assign_range(first, last, category());
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
					if (this->_cont_size == this->max_size())
						throw (std::length_error("vector::insert"));
					
					iterator it = begin();
					difference_type i;
					
					if (it == end() || position == end())
					{
						push_back(val);
						return (end() - 1);
					}
					else
						i = std::distance(begin(), position);
						
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
					if (n <= 0)
						return;
					if (this->_cont_size + n > this->_cont_capacity) {
						size_type new_cap = std::max(size() + n, capacity() * 2);
						pointer new_start = _alloc.allocate(new_cap);
						pointer new_end = construct_range(new_start, begin(), position);
						new_end = construct_range(new_end, new_end + n, val);
						new_end = construct_range(new_end, position, end());
						
						if (_cont_size) {
							for (size_type i = 0; i < _cont_size; i++)
								_alloc.destroy(--_cont_end);
							_alloc.deallocate(_cont_start, _cont_capacity);
						}

						_cont_start = new_start;
						_cont_end = new_end;
						_cont_capacity = new_cap;
					} 
					else 
					{
						iterator cpy_end = move_right(position, n);
						for (; position != cpy_end; ++position) {
							if (position.base() < _cont_end)
								*position = val;
							else
								_alloc.construct(position.base(), val);
						}
						_cont_end += n;
					}
					_cont_size += n;
				}

			// void insert(iterator position, size_type n, const T& val)
			// 	{
			// 		difference_type diff;
					
			// 		if (n <= 0)
			// 			return ;
						
			// 		if ((this->_cont_size + n) > this->max_size())
			// 			throw (std::length_error("vector::insert"));

			// 		if (size() + n > capacity())
			// 		{
			// 			diff = std::distance(begin(), position);
			// 			this->reserve(std::max(size() + n, capacity() * 2));
			// 			position = begin() + diff;
			// 		}

			// 		while (n--)
			// 			position = insert(position, val) + 1;
			// 	}

			template <class InputIterator>
				void insert(iterator position, InputIterator first,  typename enable_if<!is_integral<InputIterator>::value, InputIterator>::_type last)
					{
						typedef typename iterator_traits<InputIterator>::iterator_category category;
						insert_range(position, first, last, category());
					}

			iterator erase(iterator position)
				{
					if (position >= this->end())
						return (this->end());
	
					pointer pos = &(*position);
	
					this->_alloc.destroy(&(*position));
					
					if (position != this->end() - 1)
					{
						difference_type diff = std::distance(position, this->end() - 1);
						for (difference_type j = 0; j < diff; j++) {
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
					if (first != last)
					{
						if (first != end())
							std::move(last, end(), first);

						difference_type diff = std::distance(last, end());
					
						pointer new_end = first.base() + diff;

						for (; new_end != _cont_end; ++new_end) {
							this->_alloc.destroy(new_end);
							_cont_size--;	
						}
						_cont_end = first.base() + diff; 
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
					for (; this->_cont_size > 0; this->_cont_size--)
					{
						this->_cont_end--;
						this->_alloc.destroy(this->_cont_end);
					}
					// this->_cont_size = 0;
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
