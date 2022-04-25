/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 09:37:00 by gasselin          #+#    #+#             */
/*   Updated: 2022/04/25 16:05:54 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

#include <vector>
#include <iostream>
#include <exception>

#define BRED	"\033[1;31m"
#define BGRN	"\033[1;32m"
#define BLUE	"\033[1;34m"
#define NC		"\033[0m"

#define KO		"\033[1;31mKO\033[0m"
#define PASSED	"\033[1;32mPASSED!\033[0m"

class myexception: public std::exception
{
  virtual const char* what() const throw()
  {
    return "\033[1;31mKO\033[0m";
  }
} ko;

void fill_ft_vector(ft::vector<int>& vec)
{
	for (int i = 0; i < 25; i++)
		vec.push_back(i + 1);
}

void fill_std_vector(std::vector<int>& vec)
{
	for (int i = 0; i < 25; i++)
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

	if (&(*ft_it1) != &(*ft_it2))
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

		// if (stl_vec_alloc.get_allocator() != ft_vec_alloc.get_allocator())
		// 	throw ko;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Constructor - Value count " << NC;
	try {
		std::vector<int> stl_vec(0, 50);
		ft::vector<int> ft_vec(0, 50);

		if (!compare_vectors(stl_vec, ft_vec) || !test_empty_vector_iterators(ft_vec))
			throw ko;

		std::vector<int> stl_vec2(10, 50);
		ft::vector<int> ft_vec2(10, 50);

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

		std::vector<int> stl_vec_range2(stl_vec.begin()+5, stl_vec.begin()+20);
		ft::vector<int> ft_vec_range2(ft_vec.begin()+5, ft_vec.begin()+20);

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

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Max_size " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Resize " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Capacity " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Empty " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Reserve " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

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

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator [] - Const " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "At " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "At - Const " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Front " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Front - Const " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }


	
	std::cout << BLUE << "Back " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Back - Const " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       MODIFIERS       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Front - Value count " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Assign - Range " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Push_back " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Pop_back " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Insert - Single element " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Insert - Value count " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Insert - Range " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Erase - Single element " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Erase - Range " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Swap " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Clear " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

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

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

	

	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|  NON-MEMBER FUNCTIONS |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Operator == " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator != " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator < " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator <= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator > " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Operator >= " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Swap " << NC;
	try {
		std::vector<int> stl_vec;
		ft::vector<int> ft_vec;

		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }

}