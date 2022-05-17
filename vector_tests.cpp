/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 09:37:00 by gasselin          #+#    #+#             */
/*   Updated: 2022/05/17 11:25:41 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

#include <vector>
#include <iostream>
#include <exception>
#include <cstring>

#define BRED	"\033[1;31m"
#define BGRN	"\033[1;32m"
#define BLUE	"\033[1;34m"
#define NC		"\033[0m"

#define KO		"\033[1;31mKO\033[0m"
#define PASSED	"\033[1;32mPASSED!\033[0m"

static class myexception: public std::exception
{
  virtual const char* what() const throw()
  {
    return "\033[1;31mKO\033[0m";
  }
} ko;

struct Testing {
	std::string first;
	std::string last;	
};

void fill_ft_vector(ft::vector<int>& vec)
{
	for (int i = 0; i < 500; i++)
		vec.push_back(i + 1);
}

void fill_std_vector(std::vector<int>& vec)
{
	for (int i = 0; i < 500; i++)
		vec.push_back(i + 1);
}

void test_deep_copy_ft(ft::vector<int>& vec)
{
	for (int i = 0; i < 10; i++)
		vec.at(10+i) = 50+i;
}

void test_deep_copy_stl(std::vector<int>& vec)
{
	for (int i = 0; i < 10; i++)
		vec.at(10+i) = 50+i;
}

template <class T>
bool iterate_vectors(std::vector<T>& stl_vector, ft::vector<T>& ft_vector)
{
	typename std::vector<T>::iterator stl_it;
	typename ft::vector<T>::iterator ft_it;

	stl_it = stl_vector.begin();
	ft_it = ft_vector.begin();

	while (stl_it != stl_vector.end())
	{
		if (*stl_it != *ft_it)
			return (false);
		stl_it++;
		ft_it++;
	}

	if (ft_it != ft_vector.end())
		return (false);

	return (true);
}

template <class T>
bool compare_vectors(std::vector<T>& stl_vector, ft::vector<T>& ft_vector)
{
	if ((stl_vector.empty() != ft_vector.empty()) ||
		(stl_vector.size() != ft_vector.size()) ||
		(stl_vector.max_size() != ft_vector.max_size()) ||
		(stl_vector.capacity() != ft_vector.capacity()))
		return (false);

	return (true);
}

template <class T>
bool test_empty_vector_iterators(ft::vector<T>& ft_vector)
{
	typename ft::vector<T>::iterator ft_it1;
	typename ft::vector<T>::iterator ft_it2;

	ft_it1 = ft_vector.begin();
	ft_it2 = ft_vector.end();

	if (ft_it1 != ft_it2 || &(*ft_it1) != &(*ft_it2))
		return (false);	

	return (true);
}

void vector_tests(void)
{
	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|      CONSTRUCTORS     |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";


	
	std::cout << BLUE << "Constructor - Default " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		if (!compare_vectors(stl_vec, ft_vec) || !test_empty_vector_iterators(ft_vec))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Constructor - Allocator " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		if (!compare_vectors(stl_vec, ft_vec) || !test_empty_vector_iterators(ft_vec))
			throw ko;

		std::vector<int> stl_vec_alloc(stl_vec.get_allocator());
		ft::vector<int> ft_vec_alloc(ft_vec.get_allocator());

		if (!compare_vectors(stl_vec_alloc, ft_vec_alloc) || !test_empty_vector_iterators(ft_vec_alloc))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Constructor - Value count " << NC;
	try {
		std::vector<int> stl_vec(0, 50);
		ft::vector<int> ft_vec(0, 50);

		if (!compare_vectors(stl_vec, ft_vec) || !test_empty_vector_iterators(ft_vec))
			throw ko;

		std::vector<int> stl_vec2(250, 50);
		ft::vector<int> ft_vec2(250, 50);

		if (!compare_vectors(stl_vec2, ft_vec2) || !iterate_vectors(stl_vec2, ft_vec2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Constructor - Range " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		std::vector<int> stl_vec_range(stl_vec.begin(), stl_vec.end());
		ft::vector<int> ft_vec_range(ft_vec.begin(), ft_vec.end());

		if (!compare_vectors(stl_vec_range, ft_vec_range) || !iterate_vectors(stl_vec_range, ft_vec_range))
			throw ko;

		std::vector<int> stl_vec_range2(stl_vec.begin()+5, stl_vec.begin()+490);
		ft::vector<int> ft_vec_range2(ft_vec.begin()+5, ft_vec.begin()+490);

		if (!compare_vectors(stl_vec_range2, ft_vec_range2) || !iterate_vectors(stl_vec_range2, ft_vec_range2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Constructor - Copy " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		std::vector<int> stl_vec_copy(stl_vec);
		ft::vector<int> ft_vec_copy(ft_vec);

		if (!compare_vectors(stl_vec_copy, ft_vec_copy) || !iterate_vectors(stl_vec_copy, ft_vec_copy))
			throw ko;

		test_deep_copy_stl(stl_vec);
		test_deep_copy_ft(ft_vec);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		if (!compare_vectors(stl_vec_copy, ft_vec_copy) || !iterate_vectors(stl_vec_copy, ft_vec_copy))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator = " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		std::vector<int> stl_vec_copy = stl_vec;
		ft::vector<int> ft_vec_copy = ft_vec;

		if (!compare_vectors(stl_vec_copy, ft_vec_copy) || !iterate_vectors(stl_vec_copy, ft_vec_copy))
			throw ko;

		test_deep_copy_stl(stl_vec);
		test_deep_copy_ft(ft_vec);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		if (!compare_vectors(stl_vec_copy, ft_vec_copy) || !iterate_vectors(stl_vec_copy, ft_vec_copy))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

		

	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       ITERATORS       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Begin " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		if (ft_vec.begin() != ft_vec.end())
			throw ko;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it = stl_vec.begin();
		ft::vector<int>::iterator ft_it = ft_vec.begin();

		while (stl_it != stl_vec.end())
		{
			if (*stl_it != *ft_it)
				throw ko;
			stl_it++;
			ft_it++;
		}

		if (ft_it != ft_vec.end())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Begin - Const " << NC;
	try {
		const ft::vector<int> ft_vec_empty;

		if (ft_vec_empty.begin() != ft_vec_empty.end())
			throw ko;
		
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_begin(stl_vec);
		const ft::vector<int> ft_vec_begin(ft_vec);

		std::vector<int>::const_iterator stl_it = stl_vec_begin.begin();
		ft::vector<int>::const_iterator ft_it = ft_vec_begin.begin();

		while (stl_it != stl_vec_begin.end())
		{
			if (*stl_it != *ft_it)
				throw ko;
			stl_it++;
			ft_it++;
		}

		if (ft_it != ft_vec_begin.end())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "End " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it = stl_vec.end();
		ft::vector<int>::iterator ft_it = ft_vec.end();

		while (stl_it != stl_vec.begin())
		{
			--stl_it;
			--ft_it;
			if (*stl_it != *ft_it)
				throw ko;
		}
			
		if (ft_it != ft_vec.begin())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "End - Const " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_end(stl_vec);
		const ft::vector<int> ft_vec_end(ft_vec);

		std::vector<int>::const_iterator stl_it = stl_vec_end.end();
		ft::vector<int>::const_iterator ft_it = ft_vec_end.end();

		while (stl_it != stl_vec_end.begin())
		{
			--stl_it;
			--ft_it;
			if (*stl_it != *ft_it)
				throw ko;
		}
			
		if (ft_it != ft_vec_end.begin())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Rbegin " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		if (ft_vec.rbegin() != ft_vec.rend())
			throw ko;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it = stl_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it = ft_vec.rbegin();

		while (stl_it != stl_vec.rend())
		{
			if (*stl_it != *ft_it)
				throw ko;
			stl_it++;
			ft_it++;
		}

		if (ft_it != ft_vec.rend())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Rbegin - Const " << NC;
	try {
		const ft::vector<int> ft_vec_empty;

		if (ft_vec_empty.rbegin() != ft_vec_empty.rend())
			throw ko;

		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_rbegin(stl_vec);
		const ft::vector<int> ft_vec_rbegin(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it = stl_vec_rbegin.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it = ft_vec_rbegin.rbegin();

		while (stl_it != stl_vec_rbegin.rend())
		{
			if (*stl_it != *ft_it)
				throw ko;
			stl_it++;
			ft_it++;
		}

		if (ft_it != ft_vec_rbegin.rend())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Rend " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it = stl_vec.rend();
		ft::vector<int>::reverse_iterator ft_it = ft_vec.rend();

		while (stl_it != stl_vec.rbegin())
		{
			--stl_it;
			--ft_it;
			if (*stl_it != *ft_it)
				throw ko;
		}

		if (ft_it != ft_vec.rbegin())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Rend - Const " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_rend(stl_vec);
		const ft::vector<int> ft_vec_rend(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it = stl_vec_rend.rend();
		ft::vector<int>::const_reverse_iterator ft_it = ft_vec_rend.rend();

		while (stl_it != stl_vec_rend.rbegin())
		{
			--stl_it;
			--ft_it;
			if (*stl_it != *ft_it)
				throw ko;
		}

		if (ft_it != ft_vec_rend.rbegin())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

		

	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|        CAPACITY       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Size " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		if (stl_vec.size() != ft_vec.size())
			throw ko;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		if (stl_vec.size() != ft_vec.size())
			throw ko;

		stl_vec.erase(stl_vec.begin()+5, stl_vec.begin()+20);
		ft_vec.erase(ft_vec.begin()+5, ft_vec.begin()+20);

		if (stl_vec.size() != ft_vec.size())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Max_size " << NC;
	try {
		std::vector<int> stl_vec_int;
		ft::vector<int> ft_vec_int;

		if (stl_vec_int.max_size() != ft_vec_int.max_size())
			throw ko;

		std::vector<char> stl_vec_char;
		ft::vector<char> ft_vec_char;

		if (stl_vec_char.max_size() != ft_vec_char.max_size())
			throw ko;

		std::vector<std::string> stl_vec_string;
		ft::vector<std::string> ft_vec_string;

		if (stl_vec_string.max_size() != ft_vec_string.max_size())
			throw ko;

		std::vector<bool> stl_vec_bool;
		ft::vector<bool> ft_vec_bool;

		if (stl_vec_bool.max_size() != ft_vec_bool.max_size())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Resize " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		stl_vec.resize(250);
		ft_vec.resize(250);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		stl_vec.resize(500, 42);
		ft_vec.resize(500, 42);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		stl_vec.resize(0);
		ft_vec.resize(0);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Capacity " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		if (stl_vec.capacity() != ft_vec.capacity())
			throw ko;

		stl_vec.push_back(0);
		stl_vec.push_back(1);
		ft_vec.push_back(0);
		ft_vec.push_back(1);

		if (stl_vec.capacity() != ft_vec.capacity())
			throw ko;

		stl_vec.erase(stl_vec.begin());
		ft_vec.erase(ft_vec.begin());

		if (stl_vec.capacity() != ft_vec.capacity())
			throw ko;

		stl_vec.clear();
		ft_vec.clear();

		if (stl_vec.capacity() != ft_vec.capacity())
			throw ko;

		for (int i = 0; i < 1000; i++)
		{
			stl_vec.push_back(i);
			ft_vec.push_back(i);

			if (stl_vec.capacity() != ft_vec.capacity())
				throw ko;
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Empty " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		if (stl_vec.empty() != ft_vec.empty())
			throw ko;
			
		stl_vec.push_back(1);
		ft_vec.push_back(1);

		if (stl_vec.empty() != ft_vec.empty())
			throw ko;

		stl_vec.pop_back();
		ft_vec.pop_back();

		if (stl_vec.empty() != ft_vec.empty())
			throw ko;

		stl_vec.push_back(1);
		ft_vec.push_back(1);

		stl_vec.erase(stl_vec.begin());
		ft_vec.erase(ft_vec.begin());

		if (stl_vec.empty() != ft_vec.empty())
			throw ko;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		if (stl_vec.empty() != ft_vec.empty())
			throw ko;

		stl_vec.clear();
		ft_vec.clear();

		if (stl_vec.empty() != ft_vec.empty())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Reserve " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		stl_vec.reserve(1000);
		ft_vec.reserve(1000);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		stl_vec.reserve(200);
		ft_vec.reserve(200);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		stl_vec.reserve(500);
		ft_vec.reserve(500);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

		

	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|     ELEMENT ACCESS    |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Operator [] " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		for (size_t i = 0; i < 500; i++)
		{
			if (stl_vec[i] != ft_vec[i])
				throw ko;
		}

		for (size_t i = 0; i < 50; i++)
		{
			stl_vec[i] = 42;
			ft_vec[i] = 42;
		}

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator [] - Const " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		for (size_t i = 0; i < 500; i++)
		{
			if (stl_vec_op[i] != ft_vec_op[i])
				throw ko;
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "At " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		for (size_t i = 0; i < 500; i++)
		{
			if (stl_vec.at(i) != ft_vec.at(i))
				throw ko;
		}

		for (size_t i = 0; i < 50; i++)
		{
			stl_vec.at(i) = 42;
			ft_vec.at(i) = 42;
		}

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "At - Const " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_at(stl_vec);
		const ft::vector<int> ft_vec_at(ft_vec);

		for (size_t i = 0; i < 500; i++)
		{
			if (stl_vec_at.at(i) != ft_vec_at.at(i))
				throw ko;
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Front " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		if (&(ft_vec.front()) != &(*ft_vec.begin()) || &(ft_vec.front()) != &(*ft_vec.end()))
			throw ko;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		if (stl_vec.front() != ft_vec.front())
			throw ko;

		stl_vec.erase(stl_vec.begin());
		ft_vec.erase(ft_vec.begin());

		if (stl_vec.front() != ft_vec.front())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Front - Const " << NC;
	try {
		const std::vector<int> stl_vec_cst;
		const ft::vector<int> ft_vec_cst;

		if (&(ft_vec_cst.front()) != &(*ft_vec_cst.begin()) || &(ft_vec_cst.front()) != &(*ft_vec_cst.end()))
			throw ko;

		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_front(stl_vec);
		const ft::vector<int> ft_vec_front(ft_vec);

		if (stl_vec_front.front() != ft_vec_front.front())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }


	
	std::cout << BLUE << "Back " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		while (!stl_vec.empty())
		{
			if (stl_vec.back() != ft_vec.back())
				throw ko;

			stl_vec.pop_back();
			ft_vec.pop_back();
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Back - Const " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_back(stl_vec);
		const ft::vector<int> ft_vec_back(ft_vec);

		if (stl_vec_back.back() != ft_vec_back.back())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       MODIFIERS       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Assign - Value count " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		stl_vec.assign(0, 42);
		ft_vec.assign(0, 42);

		if (!compare_vectors(stl_vec, ft_vec) || !test_empty_vector_iterators(ft_vec))
			throw ko;

		stl_vec.assign(10, 42);
		ft_vec.assign(10, 42);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		stl_vec.assign(30, 77);
		ft_vec.assign(30, 77);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		stl_vec.assign(50, 111);
		ft_vec.assign(50, 111);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Assign - Range " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		int myints[] = {11,14,22};

		stl_vec.assign(myints, myints);
		ft_vec.assign(myints, myints);

		if (!compare_vectors(stl_vec, ft_vec) || !test_empty_vector_iterators(ft_vec))
			throw ko;

		stl_vec.assign(myints, myints+3);
		ft_vec.assign(myints, myints+3);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		stl_vec.clear();
		ft_vec.clear();

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		stl_vec.assign(stl_vec.begin()+5, stl_vec.begin()+450);
		ft_vec.assign(ft_vec.begin()+5, ft_vec.begin()+450);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Push_back " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		for (int i = 1; i <= 500; i++)
		{
			stl_vec.push_back(i);
			ft_vec.push_back(i);

			if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
				throw ko;
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Pop_back " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		while (!stl_vec.empty())
		{
			stl_vec.pop_back();
			ft_vec.pop_back();

			if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
				throw ko;
		}

		if (!compare_vectors(stl_vec, ft_vec) || !test_empty_vector_iterators(ft_vec))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Insert - Single element " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::vector<int>::iterator stl_it;
		ft::vector<int>::iterator ft_it;

		stl_it = stl_vec.insert(stl_vec.begin(), 42);
		ft_it = ft_vec.insert(ft_vec.begin(), 42);

		if (*stl_it != *ft_it || ft_it != ft_vec.begin())
			throw ko;

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		for (int i = 0; i < 100; i++)
		{
			stl_it = stl_vec.insert(stl_vec.begin()+i, 50+i);
			ft_it = ft_vec.insert(ft_vec.begin()+i, 50+i);

			if (*stl_it != *ft_it || ft_it != ft_vec.begin()+i)
				throw ko;

			if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
				throw ko;
		}

		stl_it = stl_vec.insert(stl_vec.end(), 111);
		ft_it = ft_vec.insert(ft_vec.end(), 111);

		if (*stl_it != *ft_it || ft_it != ft_vec.end()-1)
			throw ko;

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Insert - Value count " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		stl_vec.insert(stl_vec.begin(), 0, 42);
		ft_vec.insert(ft_vec.begin(), 0, 42);

		if (!compare_vectors(stl_vec, ft_vec) || !test_empty_vector_iterators(ft_vec))
			throw ko;

		for (int i = 0; i < 300; i++)
		{
			stl_vec.insert(stl_vec.begin()+i, 2, i);
			ft_vec.insert(ft_vec.begin()+i, 2, i);
			
			if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
				throw ko;
		}

		stl_vec.insert(stl_vec.end(), 200, 111);
		ft_vec.insert(ft_vec.end(), 200, 111);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		stl_vec.insert(stl_vec.end(), 444, 444);
		ft_vec.insert(ft_vec.end(), 444, 444);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Insert - Range " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		int myints[] = {11,14,22};

		stl_vec.insert(stl_vec.begin(), myints, myints);
		ft_vec.insert(ft_vec.begin(), myints, myints);

		if (!compare_vectors(stl_vec, ft_vec) || !test_empty_vector_iterators(ft_vec))
			throw ko;

		stl_vec.insert(stl_vec.begin(), myints, myints+3);
		ft_vec.insert(ft_vec.begin(), myints, myints+3);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		for (int i = 0; i < 50; i++)
		{
			stl_vec.insert(stl_vec.begin()+i, myints, myints+3);
			ft_vec.insert(ft_vec.begin()+i, myints, myints+3);
			
			if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
				throw ko;
		}

		stl_vec.insert(stl_vec.end(), 50, 77);
		ft_vec.insert(ft_vec.end(), 50, 77);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		stl_vec.insert(stl_vec.end(), 200, 111);
		ft_vec.insert(ft_vec.end(), 200, 111);

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Erase - Single element " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::vector<int>::iterator stl_it;
		ft::vector<int>::iterator ft_it;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		stl_it = stl_vec.erase(stl_vec.end()-1);
		ft_it = ft_vec.erase(ft_vec.end()-1);

		if (ft_it != ft_vec.end())
			throw ko;

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		for (int i = 0; i < 300; i++)
		{
			stl_it = stl_vec.erase(stl_vec.begin());
			ft_it = ft_vec.erase(ft_vec.begin());

			if (*stl_it != *ft_it)
				throw ko;

			if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
				throw ko;
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Erase - Range " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::vector<int>::iterator stl_it;
		ft::vector<int>::iterator ft_it;

		stl_vec.insert(stl_vec.begin(), 10, 42);
		ft_vec.insert(ft_vec.begin(), 10, 42);
		
		stl_it = stl_vec.erase(stl_vec.begin()+5, stl_vec.end());
		ft_it = ft_vec.erase(ft_vec.begin()+5, ft_vec.end());

		if (ft_it != ft_vec.end())
			throw ko;

		stl_it = stl_vec.erase(stl_vec.begin(), stl_vec.begin());
		ft_it = ft_vec.erase(ft_vec.begin(), ft_vec.begin());

		if (ft_it != ft_vec.begin())
			throw ko;

		stl_vec.clear();
		ft_vec.clear();

		for (int i = 0; i < 300; i++)
		{
			stl_vec.push_back(i);
			ft_vec.push_back(i);
		}

		if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
			throw ko;

		size_t i = 5;
		while (stl_vec.size() > 60)
		{
			stl_it = stl_vec.erase(stl_vec.begin()+i, stl_vec.begin()+i+5);
			ft_it = ft_vec.erase(ft_vec.begin()+i, ft_vec.begin()+i+5);

			if (*stl_it != *ft_it)
				throw ko;

			if (!compare_vectors(stl_vec, ft_vec) || !iterate_vectors(stl_vec, ft_vec))
				throw ko;
			
			i += 5;
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Swap " << NC;
	try {
		std::vector<int> stl_vec1;
		std::vector<int> stl_vec2;
		ft::vector<int> ft_vec1;
		ft::vector<int> ft_vec2;

		fill_std_vector(stl_vec1);
		fill_ft_vector(ft_vec1);

		stl_vec1.swap(stl_vec2);
		ft_vec1.swap(ft_vec2);

		if (!compare_vectors(stl_vec1, ft_vec1) || !test_empty_vector_iterators(ft_vec1))
			throw ko;

		if (!compare_vectors(stl_vec2, ft_vec2) || !iterate_vectors(stl_vec2, ft_vec2))
			throw ko;

		fill_std_vector(stl_vec1);
		fill_ft_vector(ft_vec1);

		stl_vec2.erase(stl_vec2.begin()+5, stl_vec2.end());
		ft_vec2.erase(ft_vec2.begin()+5, ft_vec2.end());
		
		stl_vec1.swap(stl_vec2);
		ft_vec1.swap(ft_vec2);

		if (!compare_vectors(stl_vec1, ft_vec1) || !iterate_vectors(stl_vec1, ft_vec1))
			throw ko;

		if (!compare_vectors(stl_vec2, ft_vec2) || !iterate_vectors(stl_vec2, ft_vec2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Clear " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;
		
		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		stl_vec.clear();
		ft_vec.clear();

		if (!compare_vectors(stl_vec, ft_vec) || !test_empty_vector_iterators(ft_vec))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       ALLOCATOR       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Get_allocator " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::vector<int> stl_vec_alloc(stl_vec.get_allocator());
		ft::vector<int> ft_vec_alloc(ft_vec.get_allocator());

		if (!compare_vectors(stl_vec_alloc, ft_vec_alloc) || !test_empty_vector_iterators(ft_vec_alloc))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	

	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|  NON-MEMBER FUNCTIONS |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Operator == " << NC;
	try {
		std::vector<int> stl_vec1;
		std::vector<int> stl_vec2;
		ft::vector<int> ft_vec1;
		ft::vector<int> ft_vec2;

		fill_std_vector(stl_vec1);
		fill_std_vector(stl_vec2);

		fill_ft_vector(ft_vec1);
		fill_ft_vector(ft_vec2);

		if ((stl_vec1 == stl_vec2) != (ft_vec1 == ft_vec2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator != " << NC;
	try {
		std::vector<int> stl_vec1;
		std::vector<int> stl_vec2;
		ft::vector<int> ft_vec1;
		ft::vector<int> ft_vec2;

		fill_std_vector(stl_vec1);
		fill_std_vector(stl_vec2);

		fill_ft_vector(ft_vec1);
		fill_ft_vector(ft_vec2);

		stl_vec2.erase(stl_vec2.begin()+5, stl_vec2.begin()+450);
		ft_vec2.erase(ft_vec2.begin()+5, ft_vec2.begin()+450);

		if ((stl_vec1 != stl_vec2) != (ft_vec1 != ft_vec2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator < " << NC;
	try {
		std::vector<int> stl_vec1;
		std::vector<int> stl_vec2;
		ft::vector<int> ft_vec1;
		ft::vector<int> ft_vec2;

		fill_std_vector(stl_vec1);
		fill_std_vector(stl_vec2);

		fill_ft_vector(ft_vec1);
		fill_ft_vector(ft_vec2);

		stl_vec2.erase(stl_vec2.begin()+5, stl_vec2.begin()+20);
		ft_vec2.erase(ft_vec2.begin()+5, ft_vec2.begin()+20);

		if ((stl_vec1 < stl_vec2) != (ft_vec1 < ft_vec2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator > " << NC;
	try {
		std::vector<int> stl_vec1;
		std::vector<int> stl_vec2;
		ft::vector<int> ft_vec1;
		ft::vector<int> ft_vec2;

		fill_std_vector(stl_vec1);
		fill_std_vector(stl_vec2);

		fill_ft_vector(ft_vec1);
		fill_ft_vector(ft_vec2);

		stl_vec2.erase(stl_vec2.begin()+5, stl_vec2.begin()+20);
		ft_vec2.erase(ft_vec2.begin()+5, ft_vec2.begin()+20);

		if ((stl_vec1 > stl_vec2) != (ft_vec1 > ft_vec2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator <= " << NC;
	try {
		std::vector<int> stl_vec1;
		std::vector<int> stl_vec2;
		ft::vector<int> ft_vec1;
		ft::vector<int> ft_vec2;

		fill_std_vector(stl_vec1);
		fill_std_vector(stl_vec2);

		fill_ft_vector(ft_vec1);
		fill_ft_vector(ft_vec2);

		stl_vec2.erase(stl_vec2.begin()+5, stl_vec2.begin()+20);
		ft_vec2.erase(ft_vec2.begin()+5, ft_vec2.begin()+20);

		if ((stl_vec1 <= stl_vec2) != (ft_vec1 <= ft_vec2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator >= " << NC;
	try {
		std::vector<int> stl_vec1;
		std::vector<int> stl_vec2;
		ft::vector<int> ft_vec1;
		ft::vector<int> ft_vec2;

		fill_std_vector(stl_vec1);
		fill_std_vector(stl_vec2);

		fill_ft_vector(ft_vec1);
		fill_ft_vector(ft_vec2);

		stl_vec2.erase(stl_vec2.begin()+5, stl_vec2.begin()+20);
		ft_vec2.erase(ft_vec2.begin()+5, ft_vec2.begin()+20);

		if ((stl_vec1 >= stl_vec2) != (ft_vec1 >= ft_vec2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Swap " << NC;
	try {
		std::vector<int> stl_vec1;
		std::vector<int> stl_vec2;
		ft::vector<int> ft_vec1;
		ft::vector<int> ft_vec2;

		fill_std_vector(stl_vec1);
		fill_ft_vector(ft_vec1);

		swap(stl_vec1, stl_vec2);
		swap(ft_vec1, ft_vec2);

		if (!compare_vectors(stl_vec1, ft_vec1) || !test_empty_vector_iterators(ft_vec1))
			throw ko;

		if (!compare_vectors(stl_vec2, ft_vec2) || !iterate_vectors(stl_vec2, ft_vec2))
			throw ko;

		fill_std_vector(stl_vec1);
		fill_ft_vector(ft_vec1);

		stl_vec2.erase(stl_vec2.begin()+5, stl_vec2.end());
		ft_vec2.erase(ft_vec2.begin()+5, ft_vec2.end());
		
		swap(stl_vec1, stl_vec2);
		swap(ft_vec1, ft_vec2);

		if (!compare_vectors(stl_vec1, ft_vec1) || !iterate_vectors(stl_vec1, ft_vec1))
			throw ko;

		if (!compare_vectors(stl_vec2, ft_vec2) || !iterate_vectors(stl_vec2, ft_vec2))
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	

	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|  ITERATOR OPERATIONS  |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Iterator - Operator + " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it1 = stl_vec.begin();
		std::vector<int>::iterator stl_it2 = stl_vec.begin();
		ft::vector<int>::iterator ft_it1 = ft_vec.begin();
		ft::vector<int>::iterator ft_it2 = ft_vec.begin();

		if ((&(*(ft_it1 + 10)) != &(*(10 + ft_it1))) || 
			(&(*(ft_it1 + 20)) != &(*(20 + ft_it1))) ||
			(&(*(ft_it1 + 30)) != &(*(30 + ft_it1))))
			throw ko;

		stl_it1 = 7 + stl_vec.begin();
		stl_it2 = stl_vec.begin() + 7;
		ft_it1 = 7 + ft_vec.begin();
		ft_it2 = ft_vec.begin() + 7;

		if (*stl_it1 != *ft_it1 || *stl_it2 != *ft_it2 || *ft_it1 != *ft_it2)
			throw ko;

		stl_it1 = 10 + stl_it1;
		stl_it2 = stl_it2 + 10;
		ft_it1 = 10 + ft_it1;
		ft_it2 = ft_it2 + 10;

		if (*stl_it1 != *ft_it1 || *stl_it2 != *ft_it2 || *ft_it1 != *ft_it2)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Iterator - Operator + " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_iterator stl_it1 = stl_vec_op.begin();
		std::vector<int>::const_iterator stl_it2 = stl_vec_op.begin();
		ft::vector<int>::const_iterator ft_it1 = ft_vec_op.begin();
		ft::vector<int>::const_iterator ft_it2 = ft_vec_op.begin();

		if ((&(*(ft_it1 + 10)) != &(*(10 + ft_it1))) || 
			(&(*(ft_it1 + 20)) != &(*(20 + ft_it1))) ||
			(&(*(ft_it1 + 30)) != &(*(30 + ft_it1))))
			throw ko;

		stl_it1 = 7 + stl_vec_op.begin();
		stl_it2 = stl_vec_op.begin() + 7;
		ft_it1 = 7 + ft_vec_op.begin();
		ft_it2 = ft_vec_op.begin() + 7;

		if (*stl_it1 != *ft_it1 || *stl_it2 != *ft_it2 || *ft_it1 != *ft_it2)
			throw ko;

		stl_it1 = 10 + stl_it1;
		stl_it2 = stl_it2 + 10;
		ft_it1 = 10 + ft_it1;
		ft_it2 = ft_it2 + 10;

		if (*stl_it1 != *ft_it1 || *stl_it2 != *ft_it2 || *ft_it1 != *ft_it2)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Reverse Iterator - Operator + " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it1 = stl_vec.rbegin();
		std::vector<int>::reverse_iterator stl_it2 = stl_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it1 = ft_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it2 = ft_vec.rbegin();

		if ((&(*(ft_it1 + 10)) != &(*(10 + ft_it1))) || 
			(&(*(ft_it1 + 20)) != &(*(20 + ft_it1))) ||
			(&(*(ft_it1 + 30)) != &(*(30 + ft_it1))))
			throw ko;

		stl_it1 = 7 + stl_vec.rbegin();
		stl_it2 = stl_vec.rbegin() + 7;
		ft_it1 = 7 + ft_vec.rbegin();
		ft_it2 = ft_vec.rbegin() + 7;

		if (*stl_it1 != *ft_it1 || *stl_it2 != *ft_it2 || *ft_it1 != *ft_it2)
			throw ko;

		stl_it1 = 10 + stl_it1;
		stl_it2 = stl_it2 + 10;
		ft_it1 = 10 + ft_it1;
		ft_it2 = ft_it2 + 10;

		if (*stl_it1 != *ft_it1 || *stl_it2 != *ft_it2 || *ft_it1 != *ft_it2)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Reverse Iterator - Operator + " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it1 = stl_vec_op.rbegin();
		std::vector<int>::const_reverse_iterator stl_it2 = stl_vec_op.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it1 = ft_vec_op.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it2 = ft_vec_op.rbegin();

		if ((&(*(ft_it1 + 10)) != &(*(10 + ft_it1))) || 
			(&(*(ft_it1 + 20)) != &(*(20 + ft_it1))) ||
			(&(*(ft_it1 + 30)) != &(*(30 + ft_it1))))
			throw ko;

		stl_it1 = 7 + stl_vec_op.rbegin();
		stl_it2 = stl_vec_op.rbegin() + 7;
		ft_it1 = 7 + ft_vec_op.rbegin();
		ft_it2 = ft_vec_op.rbegin() + 7;

		if (*stl_it1 != *ft_it1 || *stl_it2 != *ft_it2 || *ft_it1 != *ft_it2)
			throw ko;

		stl_it1 = 10 + stl_it1;
		stl_it2 = stl_it2 + 10;
		ft_it1 = 10 + ft_it1;
		ft_it2 = ft_it2 + 10;

		if (*stl_it1 != *ft_it1 || *stl_it2 != *ft_it2 || *ft_it1 != *ft_it2)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << "\n";

	std::cout << BLUE << "Iterator - Operator - " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it = stl_vec.end();
		ft::vector<int>::iterator ft_it = ft_vec.end();

		stl_it = stl_it - 7;
		ft_it = ft_it - 7;

		if (*stl_it != *ft_it)
			throw ko;

		stl_it = stl_it - 7;
		ft_it = ft_it - 7;

		if (*stl_it != *ft_it)
			throw ko;

		stl_it = stl_it - 7;
		ft_it = ft_it - 7;

		if (*stl_it != *ft_it)
			throw ko;

		if (ft_vec.end() - ft_vec.begin() != ft_vec.size())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Iterator - Operator - " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_iterator stl_it = stl_vec_op.end();
		ft::vector<int>::const_iterator ft_it = ft_vec_op.end();

		stl_it = stl_it - 7;
		ft_it = ft_it - 7;

		if (*stl_it != *ft_it)
			throw ko;

		stl_it = stl_it - 7;
		ft_it = ft_it - 7;

		if (*stl_it != *ft_it)
			throw ko;

		stl_it = stl_it - 7;
		ft_it = ft_it - 7;

		if (*stl_it != *ft_it)
			throw ko;

		if (ft_vec_op.end() - ft_vec_op.begin() != ft_vec_op.size())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Reverse Iterator - Operator - " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it = stl_vec.rend();
		ft::vector<int>::reverse_iterator ft_it = ft_vec.rend();

		stl_it = stl_it - 7;
		ft_it = ft_it - 7;

		if (*stl_it != *ft_it)
			throw ko;

		stl_it = stl_it - 7;
		ft_it = ft_it - 7;

		if (*stl_it != *ft_it)
			throw ko;

		stl_it = stl_it - 7;
		ft_it = ft_it - 7;

		if (*stl_it != *ft_it)
			throw ko;

		if (ft_vec.rend() - ft_vec.rbegin() != ft_vec.size())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Reverse Iterator - Operator - " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it = stl_vec_op.rend();
		ft::vector<int>::const_reverse_iterator ft_it = ft_vec_op.rend();

		stl_it = stl_it - 7;
		ft_it = ft_it - 7;

		if (*stl_it != *ft_it)
			throw ko;

		stl_it = stl_it - 7;
		ft_it = ft_it - 7;

		if (*stl_it != *ft_it)
			throw ko;

		stl_it = stl_it - 7;
		ft_it = ft_it - 7;

		if (*stl_it != *ft_it)
			throw ko;

		if (ft_vec_op.rend() - ft_vec_op.rbegin() != ft_vec_op.size())
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << "\n";

	std::cout << BLUE << "Iterator - Operator += " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it = stl_vec.begin();
		ft::vector<int>::iterator ft_it = ft_vec.begin();

		for (int i = 0; i < 25; i += 2)
		{
			stl_it += 2;
			ft_it += 2;

			if (*stl_it != *ft_it)
				throw ko;
		}

		stl_it = stl_vec.begin();
		ft_it = ft_vec.begin();

		stl_it += (stl_vec.end() - (stl_vec.begin() + 5));
		ft_it += (ft_vec.end() - (ft_vec.begin() + 5));

		if (*stl_it != *ft_it)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Iterator - Operator += " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_iterator stl_it = stl_vec_op.begin();
		ft::vector<int>::const_iterator ft_it = ft_vec_op.begin();

		for (int i = 0; i < 25; i += 2)
		{
			stl_it += 2;
			ft_it += 2;

			if (*stl_it != *ft_it)
				throw ko;
		}

		stl_it = stl_vec_op.begin();
		ft_it = ft_vec_op.begin();

		stl_it += (stl_vec_op.end() - (stl_vec_op.begin() + 5));
		ft_it += (ft_vec_op.end() - (ft_vec_op.begin() + 5));

		if (*stl_it != *ft_it)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Reverse Iterator - Operator += " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it = stl_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it = ft_vec.rbegin();

		for (int i = 0; i < 25; i += 2)
		{
			stl_it += 2;
			ft_it += 2;

			if (*stl_it != *ft_it)
				throw ko;
		}

		stl_it = stl_vec.rbegin();
		ft_it = ft_vec.rbegin();

		stl_it += (stl_vec.rend() - (stl_vec.rbegin() + 5));
		ft_it += (ft_vec.rend() - (ft_vec.rbegin() + 5));

		if (*stl_it != *ft_it)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Reverse Iterator - Operator += " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it = stl_vec_op.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it = ft_vec_op.rbegin();

		for (int i = 0; i < 25; i += 2)
		{
			stl_it += 2;
			ft_it += 2;

			if (*stl_it != *ft_it)
				throw ko;
		}

		stl_it = stl_vec_op.rbegin();
		ft_it = ft_vec_op.rbegin();

		stl_it += (stl_vec_op.rend() - (stl_vec_op.rbegin() + 5));
		ft_it += (ft_vec_op.rend() - (ft_vec_op.rbegin() + 5));

		if (*stl_it != *ft_it)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << "\n";

	std::cout << BLUE << "Iterator - Operator -= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it = stl_vec.end();
		ft::vector<int>::iterator ft_it = ft_vec.end();

		for (int i = 0; i < 25; i += 2)
		{
			stl_it -= 2;
			ft_it -= 2;

			if (*stl_it != *ft_it)
				throw ko;
		}

		stl_it = stl_vec.end();
		ft_it = ft_vec.end();

		stl_it -= (stl_vec.end() - (stl_vec.begin() + 5));
		ft_it -= (ft_vec.end() - (ft_vec.begin() + 5));

		if (*stl_it != *ft_it)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Iterator - Operator -= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_iterator stl_it = stl_vec_op.end();
		ft::vector<int>::const_iterator ft_it = ft_vec_op.end();

		for (int i = 0; i < 25; i += 2)
		{
			stl_it -= 2;
			ft_it -= 2;

			if (*stl_it != *ft_it)
				throw ko;
		}

		stl_it = stl_vec_op.end();
		ft_it = ft_vec_op.end();

		stl_it -= (stl_vec_op.end() - (stl_vec_op.begin() + 5));
		ft_it -= (ft_vec_op.end() - (ft_vec_op.begin() + 5));

		if (*stl_it != *ft_it)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Reverse Iterator - Operator -= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it = stl_vec.rend();
		ft::vector<int>::reverse_iterator ft_it = ft_vec.rend();

		for (int i = 0; i < 25; i += 2)
		{
			stl_it -= 2;
			ft_it -= 2;

			if (*stl_it != *ft_it)
				throw ko;
		}

		stl_it = stl_vec.rend();
		ft_it = ft_vec.rend();

		stl_it -= (stl_vec.rend() - (stl_vec.rbegin() + 5));
		ft_it -= (ft_vec.rend() - (ft_vec.rbegin() + 5));

		if (*stl_it != *ft_it)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Reverse Iterator - Operator -= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it = stl_vec_op.rend();
		ft::vector<int>::const_reverse_iterator ft_it = ft_vec_op.rend();

		for (int i = 0; i < 25; i += 2)
		{
			stl_it -= 2;
			ft_it -= 2;

			if (*stl_it != *ft_it)
				throw ko;
		}

		stl_it = stl_vec_op.rend();
		ft_it = ft_vec_op.rend();

		stl_it -= (stl_vec_op.rend() - (stl_vec_op.rbegin() + 5));
		ft_it -= (ft_vec_op.rend() - (ft_vec_op.rbegin() + 5));

		if (*stl_it != *ft_it)
			throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << "\n";

	std::cout << BLUE << "Iterator - Operator [] " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it = stl_vec.begin();
		ft::vector<int>::iterator ft_it = ft_vec.begin();

		for (int i = 0; i < 500; i++)
		{
			if (stl_it[i] != ft_it[i])
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Iterator - Operator [] " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_iterator stl_it = stl_vec_op.begin();
		ft::vector<int>::const_iterator ft_it = ft_vec_op.begin();

		for (int i = 0; i < 500; i++)
		{
			if (stl_it[i] != ft_it[i])
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Reverse Iterator - Operator [] " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it = stl_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it = ft_vec.rbegin();

		for (int i = 0; i < 500; i++)
		{
			if (stl_it[i] != ft_it[i])
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Reverse Iterator - Operator [] " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it = stl_vec_op.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it = ft_vec_op.rbegin();

		for (int i = 0; i < 500; i++)
		{
			if (stl_it[i] != ft_it[i])
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << "\n";

	std::cout << BLUE << "Iterator - Base " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it = stl_vec.begin();
		ft::vector<int>::iterator ft_it = ft_vec.begin();

		for (; stl_it != stl_vec.end(); stl_it++, ft_it++)
		{
			if (*stl_it.base() != *ft_it.base())
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Iterator - Base " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_iterator stl_it = stl_vec_op.begin();
		ft::vector<int>::const_iterator ft_it = ft_vec_op.begin();

		for (; stl_it != stl_vec_op.end(); stl_it++, ft_it++)
		{
			if (*stl_it.base() != *ft_it.base())
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Reverse Iterator - Base " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it = stl_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it = ft_vec.rbegin();

		for (; stl_it != stl_vec.rend(); stl_it++, ft_it++)
		{
			if (*stl_it.base() != *ft_it.base())
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Reverse Iterator - Base " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it = stl_vec_op.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it = ft_vec_op.rbegin();

		for (; stl_it != stl_vec_op.rend(); stl_it++, ft_it++)
		{
			if (*stl_it.base() != *ft_it.base())
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << "\n";

	std::cout << BLUE << "Iterator - Operator == " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it = stl_vec.begin();
		std::vector<int>::iterator stl_it2 = stl_vec.begin();
		ft::vector<int>::iterator ft_it = ft_vec.begin();
		ft::vector<int>::iterator ft_it2 = ft_vec.begin();

		for (; stl_it != stl_vec.end(); stl_it++, stl_it2++, ft_it++, ft_it2++)
		{
			if ((stl_it == stl_it2) != (ft_it == ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Iterator - Operator == " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_iterator stl_it = stl_vec_op.begin();
		std::vector<int>::const_iterator stl_it2 = stl_vec_op.begin();
		ft::vector<int>::const_iterator ft_it = ft_vec_op.begin();
		ft::vector<int>::const_iterator ft_it2 = ft_vec_op.begin();

		for (; stl_it != stl_vec_op.end(); stl_it++, stl_it2++, ft_it++, ft_it2++)
		{
			if ((stl_it == stl_it2) != (ft_it == ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Reverse Iterator - Operator == " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;
		
		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it = stl_vec.rbegin();
		std::vector<int>::reverse_iterator stl_it2 = stl_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it = ft_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it2 = ft_vec.rbegin();

		for (; stl_it != stl_vec.rend(); stl_it++, stl_it2++, ft_it++, ft_it2++)
		{
			if ((stl_it == stl_it2) != (ft_it == ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Reverse Iterator - Operator == " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it = stl_vec_op.rbegin();
		std::vector<int>::const_reverse_iterator stl_it2 = stl_vec_op.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it = ft_vec_op.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it2 = ft_vec_op.rbegin();

		for (; stl_it != stl_vec.rend(); stl_it++, stl_it2++, ft_it++, ft_it2++)
		{
			if ((stl_it == stl_it2) != (ft_it == ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << "\n";

	std::cout << BLUE << "Iterator - Operator != " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it = stl_vec.begin();
		std::vector<int>::iterator stl_it2 = stl_vec.begin();
		ft::vector<int>::iterator ft_it = ft_vec.begin();
		ft::vector<int>::iterator ft_it2 = ft_vec.begin();

		for (; stl_it != stl_vec.end(); stl_it++, stl_it2++, ft_it++, ft_it2++)
		{
			if ((stl_it != stl_it2) != (ft_it != ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Iterator - Operator != " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_iterator stl_it = stl_vec_op.begin();
		std::vector<int>::const_iterator stl_it2 = stl_vec_op.begin();
		ft::vector<int>::const_iterator ft_it = ft_vec_op.begin();
		ft::vector<int>::const_iterator ft_it2 = ft_vec_op.begin();

		for (; stl_it != stl_vec_op.end(); stl_it++, stl_it2++, ft_it++, ft_it2++)
		{
			if ((stl_it != stl_it2) != (ft_it != ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Reverse Iterator - Operator != " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it = stl_vec.rbegin();
		std::vector<int>::reverse_iterator stl_it2 = stl_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it = ft_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it2 = ft_vec.rbegin();

		for (; stl_it != stl_vec.rend(); stl_it++, stl_it2++, ft_it++, ft_it2++)
		{
			if ((stl_it != stl_it2) != (ft_it != ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Reverse Iterator - Operator != " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it = stl_vec_op.rbegin();
		std::vector<int>::const_reverse_iterator stl_it2 = stl_vec_op.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it = ft_vec_op.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it2 = ft_vec_op.rbegin();

		for (; stl_it != stl_vec_op.rend(); stl_it++, stl_it2++, ft_it++, ft_it2++)
		{
			if ((stl_it != stl_it2) != (ft_it != ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << "\n";

	std::cout << BLUE << "Iterator - Operator < " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it = stl_vec.begin() + 125;
		std::vector<int>::iterator stl_it2 = stl_vec.begin();
		ft::vector<int>::iterator ft_it = ft_vec.begin() + 125;
		ft::vector<int>::iterator ft_it2 = ft_vec.begin();

		for (; stl_it2 != stl_vec.end(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it < stl_it2) != (ft_it < ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Iterator - Operator < " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_iterator stl_it = stl_vec_op.begin() + 125;
		std::vector<int>::const_iterator stl_it2 = stl_vec_op.begin();
		ft::vector<int>::const_iterator ft_it = ft_vec_op.begin() + 125;
		ft::vector<int>::const_iterator ft_it2 = ft_vec_op.begin();

		for (; stl_it2 != stl_vec_op.end(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it < stl_it2) != (ft_it < ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Reverse Iterator - Operator < " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it = stl_vec.rbegin() + 125;
		std::vector<int>::reverse_iterator stl_it2 = stl_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it = ft_vec.rbegin() + 125;
		ft::vector<int>::reverse_iterator ft_it2 = ft_vec.rbegin();

		for (; stl_it2 != stl_vec.rend(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it < stl_it2) != (ft_it < ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Reverse Iterator - Operator < " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it = stl_vec_op.rbegin() + 125;
		std::vector<int>::const_reverse_iterator stl_it2 = stl_vec_op.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it = ft_vec_op.rbegin() + 125;
		ft::vector<int>::const_reverse_iterator ft_it2 = ft_vec_op.rbegin();

		for (; stl_it2 != stl_vec.rend(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it < stl_it2) != (ft_it < ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << "\n";

	std::cout << BLUE << "Iterator - Operator > " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it = stl_vec.begin() + 125;
		std::vector<int>::iterator stl_it2 = stl_vec.begin();
		ft::vector<int>::iterator ft_it = ft_vec.begin() + 125;
		ft::vector<int>::iterator ft_it2 = ft_vec.begin();

		for (; stl_it2 != stl_vec.end(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it > stl_it2) != (ft_it > ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Iterator - Operator > " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_iterator stl_it = stl_vec_op.begin() + 125;
		std::vector<int>::const_iterator stl_it2 = stl_vec_op.begin();
		ft::vector<int>::const_iterator ft_it = ft_vec_op.begin() + 125;
		ft::vector<int>::const_iterator ft_it2 = ft_vec_op.begin();

		for (; stl_it2 != stl_vec_op.end(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it > stl_it2) != (ft_it > ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Reverse Iterator - Operator > " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it = stl_vec.rbegin() + 125;
		std::vector<int>::reverse_iterator stl_it2 = stl_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it = ft_vec.rbegin() + 125;
		ft::vector<int>::reverse_iterator ft_it2 = ft_vec.rbegin();

		for (; stl_it2 != stl_vec.rend(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it > stl_it2) != (ft_it > ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Reverse Iterator - Operator > " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it = stl_vec_op.rbegin() + 125;
		std::vector<int>::const_reverse_iterator stl_it2 = stl_vec_op.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it = ft_vec_op.rbegin() + 125;
		ft::vector<int>::const_reverse_iterator ft_it2 = ft_vec_op.rbegin();

		for (; stl_it2 != stl_vec.rend(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it > stl_it2) != (ft_it > ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << "\n";

	std::cout << BLUE << "Iterator - Operator <= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it = stl_vec.begin() + 125;
		std::vector<int>::iterator stl_it2 = stl_vec.begin();
		ft::vector<int>::iterator ft_it = ft_vec.begin() + 125;
		ft::vector<int>::iterator ft_it2 = ft_vec.begin();

		for (; stl_it2 != stl_vec.end(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it <= stl_it2) != (ft_it <= ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Iterator - Operator <= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_iterator stl_it = stl_vec_op.begin() + 125;
		std::vector<int>::const_iterator stl_it2 = stl_vec_op.begin();
		ft::vector<int>::const_iterator ft_it = ft_vec_op.begin() + 125;
		ft::vector<int>::const_iterator ft_it2 = ft_vec_op.begin();

		for (; stl_it2 != stl_vec_op.end(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it <= stl_it2) != (ft_it <= ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Reverse Iterator - Operator <= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it = stl_vec.rbegin() + 125;
		std::vector<int>::reverse_iterator stl_it2 = stl_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it = ft_vec.rbegin() + 125;
		ft::vector<int>::reverse_iterator ft_it2 = ft_vec.rbegin();

		for (; stl_it2 != stl_vec.rend(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it <= stl_it2) != (ft_it <= ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Reverse Iterator - Operator <= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it = stl_vec_op.rbegin() + 125;
		std::vector<int>::const_reverse_iterator stl_it2 = stl_vec_op.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it = ft_vec_op.rbegin() + 125;
		ft::vector<int>::const_reverse_iterator ft_it2 = ft_vec_op.rbegin();

		for (; stl_it2 != stl_vec.rend(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it <= stl_it2) != (ft_it <= ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << "\n";

	std::cout << BLUE << "Iterator - Operator >= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::iterator stl_it = stl_vec.begin() + 125;
		std::vector<int>::iterator stl_it2 = stl_vec.begin();
		ft::vector<int>::iterator ft_it = ft_vec.begin() + 125;
		ft::vector<int>::iterator ft_it2 = ft_vec.begin();

		for (; stl_it2 != stl_vec.end(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it >= stl_it2) != (ft_it >= ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Iterator - Operator >= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_iterator stl_it = stl_vec_op.begin() + 125;
		std::vector<int>::const_iterator stl_it2 = stl_vec_op.begin();
		ft::vector<int>::const_iterator ft_it = ft_vec_op.begin() + 125;
		ft::vector<int>::const_iterator ft_it2 = ft_vec_op.begin();

		for (; stl_it2 != stl_vec_op.end(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it >= stl_it2) != (ft_it >= ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Reverse Iterator - Operator >= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		std::vector<int>::reverse_iterator stl_it = stl_vec.rbegin() + 125;
		std::vector<int>::reverse_iterator stl_it2 = stl_vec.rbegin();
		ft::vector<int>::reverse_iterator ft_it = ft_vec.rbegin() + 125;
		ft::vector<int>::reverse_iterator ft_it2 = ft_vec.rbegin();

		for (; stl_it2 != stl_vec.rend(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it >= stl_it2) != (ft_it >= ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	std::cout << BLUE << "Const Reverse Iterator - Operator >= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		fill_std_vector(stl_vec);
		fill_ft_vector(ft_vec);

		const std::vector<int> stl_vec_op(stl_vec);
		const ft::vector<int> ft_vec_op(ft_vec);

		std::vector<int>::const_reverse_iterator stl_it = stl_vec_op.rbegin() + 125;
		std::vector<int>::const_reverse_iterator stl_it2 = stl_vec_op.rbegin();
		ft::vector<int>::const_reverse_iterator ft_it = ft_vec_op.rbegin() + 125;
		ft::vector<int>::const_reverse_iterator ft_it2 = ft_vec_op.rbegin();

		for (; stl_it2 != stl_vec.rend(); stl_it++, stl_it2 += 2, ft_it++, ft_it2 += 2)
		{
			if ((stl_it >= stl_it2) != (ft_it >= ft_it2))
				throw ko;	
		}

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	// std::cout << "\n";

	// std::cout << BLUE << "Iterator - Operator -> " << NC;
	// try {
	// 	std::vector<Testing> stl_vec;
	// 	ft::vector<Testing> ft_vec;

	// 	fill_std_vector(stl_vec);
	// 	fill_ft_vector(ft_vec);

	// 	std::vector<Testing>::iterator stl_it;
	// 	ft::vector<Testing>::iterator ft_it;

	// 	std::cout << PASSED << "\n";
	// } catch(std::exception& e)
	// 	{ std::cout << e.what() << "\n"; }

	// std::cout << BLUE << "Const Iterator - Operator -> " << NC;
	// try {
	// 	std::vector<int> stl_vec;
	// 	ft::vector<int> ft_vec;

	// 	fill_std_vector(stl_vec);
	// 	fill_ft_vector(ft_vec);

	// 	const std::vector<int> stl_vec_op(stl_vec);
	// 	const ft::vector<int> ft_vec_op(ft_vec);

	// 	std::vector<int>::const_iterator stl_it;
	// 	ft::vector<int>::const_iterator ft_it;

	// 	std::cout << PASSED << "\n";
	// } catch(std::exception& e)
	// 	{ std::cout << e.what() << "\n"; }

	// std::cout << BLUE << "Reverse Iterator - Operator -> " << NC;
	// try {
	// 	std::vector<int> stl_vec;
	// 	ft::vector<int> ft_vec;

	// 	fill_std_vector(stl_vec);
	// 	fill_ft_vector(ft_vec);

	// 	std::vector<int>::reverse_iterator stl_it;
	// 	ft::vector<int>::reverse_iterator ft_it;

	// 	std::cout << PASSED << "\n";
	// } catch(std::exception& e)
	// 	{ std::cout << e.what() << "\n"; }

	// std::cout << BLUE << "Const Reverse Iterator - Operator -> " << NC;
	// try {
	// 	std::vector<int> stl_vec;
	// 	ft::vector<int> ft_vec;

	// 	fill_std_vector(stl_vec);
	// 	fill_ft_vector(ft_vec);

	// 	const std::vector<int> stl_vec_op(stl_vec);
	// 	const ft::vector<int> ft_vec_op(ft_vec);

	// 	std::vector<int>::const_reverse_iterator stl_it;
	// 	ft::vector<int>::const_reverse_iterator ft_it;

	// 	std::cout << PASSED << "\n";
	// } catch(std::exception& e)
	// 	{ std::cout << e.what() << "\n"; }

}
