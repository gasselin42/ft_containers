/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 09:37:00 by gasselin          #+#    #+#             */
/*   Updated: 2022/06/16 11:03:26 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector.hpp"

#include <vector>
#include <iostream>
#include <exception>
#include <cstring>

#define T1 int

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

struct Testing {
	std::string first;
	std::string last;	
};

template <class T>
void fill_vector(NAMESPACE::vector<T>& vec)
{
	for (int i = 0; i < 100; i++)
		vec.push_back(i + 1);
}

template <class T>
void test_deep_copy(NAMESPACE::vector<T>& vec)
{
	for (int i = 0; i < 10; i++)
		vec.at(10+i) = 50+i;
}

template <class T>
void reverse_iterate_vector(const NAMESPACE::vector<T>& vec)
{
	typename NAMESPACE::vector<T>::const_reverse_iterator it;

	it = vec.rbegin();

	if (it != vec.rend())
	{
		std::cout << "Iteration : ";
		for (int i = 0; it != vec.rend(); it++, i++)
			std::cout << "[" << i << "] = " << *it << "; ";
	}
	else
		std::cout << "Empty vector";
	std::cout << "\n";
}

template <class T>
void reverse_iterate_vector(NAMESPACE::vector<T>& vec)
{
	typename NAMESPACE::vector<T>::reverse_iterator it;

	it = vec.rbegin();

	if (it != vec.rend())
	{
		std::cout << "Iteration : ";
		for (int i = 0; it != vec.rend(); it++, i++)
			std::cout << "[" << i << "] = " << *it << "; ";
	}
	else
		std::cout << "Empty vector";
	std::cout << "\n";
}

template <class T>
void iterate_vector(NAMESPACE::vector<T>& vec)
{
	typename NAMESPACE::vector<T>::iterator it;

	it = vec.begin();

	if (it != vec.end())
	{
		std::cout << "Iteration : ";
		for (int i = 0; it != vec.end(); it++, i++)
			std::cout << "[" << i << "] = " << *it << "; ";
	}
	else
		std::cout << "Empty vector";
	std::cout << "\n";
}

template <class T>
void iterate_vector(const NAMESPACE::vector<T>& vec)
{
	typename NAMESPACE::vector<T>::const_iterator it;

	it = vec.begin();

	if (it != vec.end())
	{
		std::cout << "Iteration : ";
		for (int i = 0; it != vec.end(); it++, i++)
			std::cout << "[" << i << "] = " << *it << "; ";
	}
	else
		std::cout << "Empty vector";
	std::cout << "\n";
}

template <class T>
void compare_vectors(NAMESPACE::vector<T>& vec)
{
	std::cout << "Size : " << vec.size() << " ";
	std::cout << "Max size : " << vec.max_size() << " ";
	std::cout << "Capacity : " << vec.capacity() << "\n";
}

int main(void)
{
	std::cout << "-------------------------" << "\n";
	std::cout << "|      CONSTRUCTORS     |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Constructor - Default \n";
	{
		NAMESPACE::vector<T1> vec;
		compare_vectors(vec);
	}

	std::cout << "\n";

	std::cout << "Constructor - Allocator \n";
	{
		NAMESPACE::vector<T1> vec;

		compare_vectors(vec);

		NAMESPACE::vector<T1> vec_alloc(vec.get_allocator());

		compare_vectors(vec_alloc);
	}

	std::cout << "\n";

	std::cout << "Constructor - Value count \n";
	{
		NAMESPACE::vector<T1> vec(0, 50);

		compare_vectors(vec);

		NAMESPACE::vector<T1> vec2(250, 50);

		compare_vectors(vec2);
	}

	std::cout << "\n";

	std::cout << "Constructor - Range \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		compare_vectors(vec);
		iterate_vector(vec);

		NAMESPACE::vector<T1> vec_range(vec.begin(), vec.end());

		compare_vectors(vec_range);
		iterate_vector(vec_range);

		NAMESPACE::vector<T1> vec_range2(vec.begin()+5, vec.begin()+90);

		compare_vectors(vec_range2);
		iterate_vector(vec_range2);
	}

	std::cout << "\n";

	std::cout << "Constructor - Copy \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		compare_vectors(vec);
		iterate_vector(vec);

		NAMESPACE::vector<T1> vec_copy(vec);

		compare_vectors(vec_copy);
		iterate_vector(vec_copy);

		test_deep_copy(vec);

		compare_vectors(vec);
		iterate_vector(vec);

		compare_vectors(vec_copy);
		iterate_vector(vec_copy);
	}

	std::cout << "\n";

	std::cout << "Operator = \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		compare_vectors(vec);
		iterate_vector(vec);

		NAMESPACE::vector<T1> vec_copy = vec;

		compare_vectors(vec_copy);
		iterate_vector(vec_copy);
		
		test_deep_copy(vec);

		compare_vectors(vec);
		iterate_vector(vec);

		compare_vectors(vec_copy);
		iterate_vector(vec_copy);
	}

		

	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|       ITERATORS       |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Begin \n";
	{
		NAMESPACE::vector<T1> vec;

		if (vec.begin() != vec.end())
			std::cout << "KO\n";

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it = vec.begin();

		std::cout << "Begin = " << *it << "\n";

		iterate_vector(vec);
	}

	std::cout << "\n";

	std::cout << "Begin - Const \n";
	{
		const NAMESPACE::vector<T1> vec_empty;

		if (vec_empty.begin() != vec_empty.end())
			std::cout << "KO\n";
		
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_begin(vec);

		NAMESPACE::vector<T1>::const_iterator it = vec_begin.begin();

		std::cout << "Begin = " << *it << "\n";

		iterate_vector(vec_begin);
	}

	std::cout << "\n";

	std::cout << "End \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it = vec.end();

		for (size_t i = 0; it != vec.begin(); i++)
			std::cout << "[" << i << "] = " << *(--it) << "; ";
		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "End - Const \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_end(vec);

		NAMESPACE::vector<T1>::const_iterator it = vec_end.end();

		for (size_t i = 0; it != vec_end.begin(); i++)
			std::cout << "[" << i << "] = " << *(--it) << "; ";
		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "Rbegin \n";
	{
		NAMESPACE::vector<T1> vec;

		if (vec.rbegin() != vec.rend())
			std::cout << "KO\n";

		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it = vec.rbegin();

		std::cout << "Rbegin = " << *it << "\n";

		reverse_iterate_vector(vec);
	}

	std::cout << "\n";

	std::cout << "Rbegin - Const \n";
	{
		const NAMESPACE::vector<T1> vec_empty;

		if (vec_empty.rbegin() != vec_empty.rend())
			std::cout << "KO\n";

		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_rbegin(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it = vec_rbegin.rbegin();

		std::cout << "Rbegin = " << *it << "\n";

		reverse_iterate_vector(vec_rbegin);
	}

	std::cout << "\n";

	std::cout << "Rend \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it = vec.rend();

		for (size_t i = 0; it != vec.rbegin(); i++)
			std::cout << "[" << i << "] = " << *(--it) << "; ";
		std::cout << "\n";
	}

	std::cout << "\n";

	std::cout << "Rend - Const \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_rend(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it = vec_rend.rend();

		for (size_t i = 0; it != vec_rend.rbegin(); it--, i++)
			std::cout << "[" << i << "] = " << *(it) << "; ";
		std::cout << "\n";
	}

		

	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|        CAPACITY       |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Size \n";
	{
		NAMESPACE::vector<T1> vec;

		std::cout << "Size : " << vec.size() << "\n";

		fill_vector(vec);

		std::cout << "Size : " << vec.size() << "\n";

		vec.erase(vec.begin()+5, vec.begin()+20);

		std::cout << "Size : " << vec.size() << "\n";
	}

	std::cout << "\n";

	std::cout << "Max_size \n";
	{
		NAMESPACE::vector<T1> vec_int;

		std::cout << "Max size (int) : " << vec_int.max_size() << "\n";

		NAMESPACE::vector<char> vec_char;

		std::cout << "Max size (char) : " << vec_char.max_size() << "\n";

		NAMESPACE::vector<std::string> vec_string;

		std::cout << "Max size (string) : " << vec_string.max_size() << "\n";

		NAMESPACE::vector<bool> vec_bool;

		std::cout << "Max size (bool) : " << vec_char.max_size() << "\n";
	}

	std::cout << "\n";

	std::cout << "Resize \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		vec.resize(250);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.resize(500, 42);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.resize(0);

		compare_vectors(vec);
		iterate_vector(vec);
	}

	std::cout << "\n";

	std::cout << "Capacity \n";
	{
		NAMESPACE::vector<T1> vec;

		std::cout << "Capacity : " << vec.capacity() << "\n";

		vec.push_back(0);
		vec.push_back(1);

		std::cout << "Capacity : " << vec.capacity() << "\n";

		vec.erase(vec.begin());

		std::cout << "Capacity : " << vec.capacity() << "\n";

		vec.clear();

		std::cout << "Capacity : " << vec.capacity() << "\n";

		fill_vector(vec);
		
		std::cout << "Capacity : " << vec.capacity() << "\n";
	}

	std::cout << "\n";

	std::cout << "Empty \n";
	{
		NAMESPACE::vector<T1> vec;

		std::cout << (vec.empty() ? "True" : "False") << "\n";
			
		vec.push_back(1);

		std::cout << (vec.empty() ? "True" : "False") << "\n";

		vec.pop_back();

		std::cout << (vec.empty() ? "True" : "False") << "\n";

		vec.push_back(1);

		vec.erase(vec.begin());

		std::cout << (vec.empty() ? "True" : "False") << "\n";

		fill_vector(vec);

		std::cout << (vec.empty() ? "True" : "False") << "\n";

		vec.clear();

		std::cout << (vec.empty() ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Reserve \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		vec.reserve(1000);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.reserve(200);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.reserve(500);

		compare_vectors(vec);
		iterate_vector(vec);
	}

		

	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|     ELEMENT ACCESS    |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Operator [] \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		for (size_t i = 0; i < vec.size(); i += 10)
			std::cout << "[" << i << "] = " << vec[i] << "\n";

		for (size_t i = 0; i < 50; i++)
			vec[i] = 42;

		compare_vectors(vec);
		iterate_vector(vec);
	}

	std::cout << "\n";

	std::cout << "Operator [] - Const \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		for (size_t i = 0; i < vec.size(); i += 10)
			std::cout << "[" << i << "] = " << vec[i] << "\n";
	}

	std::cout << "\n";

	std::cout << "At \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		for (size_t i = 0; i < vec.size(); i += 10)
			std::cout << "At " << i << " = " << vec.at(i) << "\n";

		for (size_t i = 0; i < 50; i++)
			vec.at(i) = 42;

		compare_vectors(vec);
		iterate_vector(vec);
	}

	std::cout << "\n";

	std::cout << "At - Const \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_at(vec);

		for (size_t i = 0; i < vec.size(); i += 10)
			std::cout << "At " << i << " = " << vec.at(i) << "\n";
	}

	std::cout << "\n";

	std::cout << "Front \n";
	{
		NAMESPACE::vector<T1> vec;

		if (&(vec.front()) != &(*vec.begin()) || &(vec.front()) != &(*vec.end()))
			std::cout << "Front != Begin OR End\n";
		else
			std::cout << "Front == Begin AND End\n";

		fill_vector(vec);

		std::cout << "Front : " << vec.front() << "\n";

		vec.erase(vec.begin());

		std::cout << "Front : " << vec.front() << "\n";
	}

	std::cout << "\n";

	std::cout << "Front - Const \n";
	{
		const NAMESPACE::vector<T1> vec_cst;

		if (&(vec_cst.front()) != &(*vec_cst.begin()) || &(vec_cst.front()) != &(*vec_cst.end()))
			std::cout << "Front != Begin OR End\n";
		else
			std::cout << "Front == Begin AND End\n";

		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_front(vec);

		std::cout << "Front : " << vec_front.front() << "\n";
	}

	std::cout << "\n";
	
	std::cout << "Back \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		while (!vec.empty())
		{
			if (vec.size() % 10 == 0)
				std::cout << "Back : " << vec.back() << "\n";
			vec.pop_back();
		}
	}

	std::cout << "\n";

	std::cout << "Back - Const \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_back(vec);

		std::cout << "Back : " << vec.back() << "\n";
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|       MODIFIERS       |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Assign - Value count \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		vec.assign(0, 42);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.assign(10, 42);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.assign(30, 77);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.assign(50, 111);

		compare_vectors(vec);
		iterate_vector(vec);
	}

	std::cout << "\n";

	std::cout << "Assign - Range \n";
	{
		NAMESPACE::vector<T1> vec;

		int myints[] = {11,14,22};

		vec.assign(myints, myints);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.assign(myints, myints+3);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.clear();
		fill_vector(vec);

		vec.assign(vec.begin()+5, vec.begin()+80);

		compare_vectors(vec);
		iterate_vector(vec);
	}

	std::cout << "\n";

	std::cout << "Push_back \n";
	{
		NAMESPACE::vector<T1> vec;

		for (int i = 1; i <= 100; i++)
		{
			vec.push_back(i);
			compare_vectors(vec);
			iterate_vector(vec);
		}
	}

	std::cout << "\n";

	std::cout << "Pop_back \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		while (!vec.empty())
		{
			vec.pop_back();
			compare_vectors(vec);
			iterate_vector(vec);
		}
	}

	std::cout << "\n";

	std::cout << "Insert - Single element \n";
	{
		NAMESPACE::vector<T1> vec;

		NAMESPACE::vector<T1>::iterator it;

		it = vec.insert(vec.begin(), 42);

		compare_vectors(vec);

		std::cout << "*it = " << *it << "\n";
		std::cout << "Begin? = " << ((it == vec.begin()) ? "True" : "False") << "\n";

		for (int i = 0; i < 100; i++)
		{
			it = vec.insert(vec.begin()+i, 50+i);

			std::cout << "*it = " << *it << " ";
			std::cout << "it == begin() + i ? = " << ((it == vec.begin() + i) ? "True" : "False") << "\n";
		}

		compare_vectors(vec);
		iterate_vector(vec);

		it = vec.insert(vec.end(), 111);

		std::cout << "*it = " << *it << "\n";
		std::cout << "End? = " << ((it == vec.end() - 1) ? "True" : "False") << "\n";

		compare_vectors(vec);
		iterate_vector(vec);
	}

	std::cout << "\n";

	std::cout << "Insert - Value count \n";
	{
		NAMESPACE::vector<T1> vec;

		vec.insert(vec.begin(), 0, 42);

		compare_vectors(vec);
		iterate_vector(vec);

		for (int i = 0; i < 300; i++)
			vec.insert(vec.begin()+i, 2, i);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.insert(vec.end(), 20, 111);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.insert(vec.end(), 44, 444);

		compare_vectors(vec);
		iterate_vector(vec);
	}

	std::cout << "\n";

	std::cout << "Insert - Range \n";
	{
		NAMESPACE::vector<T1> vec;

		int myints[] = {11,14,22};

		vec.insert(vec.begin(), myints, myints);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.insert(vec.begin(), myints, myints+3);

		compare_vectors(vec);
		iterate_vector(vec);

		for (int i = 0; i < 50; i++)
			vec.insert(vec.begin()+i, myints, myints+3);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.insert(vec.end(), 20, 77);

		compare_vectors(vec);
		iterate_vector(vec);

		vec.insert(vec.end(), 50, 111);

		compare_vectors(vec);
		iterate_vector(vec);
	}

	std::cout << "\n";

	std::cout << "Erase - Single element \n";
	{
		NAMESPACE::vector<T1> vec;

		NAMESPACE::vector<T1>::iterator it;

		fill_vector(vec);

		it = vec.erase(vec.end()-1);

		std::cout << "End? = " << ((it == vec.end()) ? "True" : "False") << "\n";

		compare_vectors(vec);
		iterate_vector(vec);

		for (int i = 0; i < 50; i++)
		{
			it = vec.erase(vec.begin());
			std::cout << "*it (" << i << ") = " << *it << "; ";
		}
		std::cout << "\n";
		
		compare_vectors(vec);
		iterate_vector(vec);
	}

	std::cout << "\n";

	std::cout << "Erase - Range \n";
	{
		NAMESPACE::vector<T1> vec;

		NAMESPACE::vector<T1>::iterator it;

		vec.insert(vec.begin(), 10, 42);
		
		it = vec.erase(vec.begin()+5, vec.end());

		std::cout << "End? = " << ((it == vec.end()) ? "True" : "False") << "\n";

		it = vec.erase(vec.begin(), vec.begin());

		std::cout << "Begin? = " << ((it == vec.begin()) ? "True" : "False") << "\n";

		vec.clear();

		for (int i = 0; i < 500; i++)
			vec.push_back(i);

		vec.erase(vec.begin()+10, vec.begin()+490);

		compare_vectors(vec);
		iterate_vector(vec);
	}

	std::cout << "\n";

	std::cout << "Swap \n";
	{
		NAMESPACE::vector<T1> vec1;
		NAMESPACE::vector<T1> vec2;

		fill_vector(vec1);

		vec1.swap(vec2);

		compare_vectors(vec1);
		iterate_vector(vec1);

		compare_vectors(vec2);
		iterate_vector(vec2);

		fill_vector(vec1);

		vec2.erase(vec2.begin()+5, vec2.end());
		vec1.swap(vec2);

		compare_vectors(vec1);
		iterate_vector(vec1);

		compare_vectors(vec2);
		iterate_vector(vec2);
	}

	std::cout << "\n";

	std::cout << "Clear \n";
	{
		NAMESPACE::vector<T1> vec;
		
		fill_vector(vec);

		vec.clear();

		compare_vectors(vec);
		iterate_vector(vec);
	}



	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|       ALLOCATOR       |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Get_allocator \n";
	{
		NAMESPACE::vector<T1> vec;
		NAMESPACE::vector<T1> vec_alloc(vec.get_allocator());

		compare_vectors(vec);
		iterate_vector(vec);
	}

	

	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|  NON-MEMBER FUNCTIONS |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Operator == \n";
	{
		NAMESPACE::vector<T1> vec1;
		NAMESPACE::vector<T1> vec2;

		fill_vector(vec1);
		fill_vector(vec2);

		std::cout << "vec1 == vec2 " << ((vec1 == vec2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator != \n";
	{
		NAMESPACE::vector<T1> vec1;
		NAMESPACE::vector<T1> vec2;

		fill_vector(vec1);
		fill_vector(vec2);

		vec2.erase(vec2.begin()+5, vec2.begin()+90);

		std::cout << "vec1 != vec2 \n" << ((vec1 != vec2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator < \n";
	{
		NAMESPACE::vector<T1> vec1;
		NAMESPACE::vector<T1> vec2;

		fill_vector(vec1);
		fill_vector(vec2);

		vec2.erase(vec2.begin()+5, vec2.begin()+20);

		std::cout << "vec1 < vec2 " << ((vec1 < vec2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator > \n";
	{
		NAMESPACE::vector<T1> vec1;
		NAMESPACE::vector<T1> vec2;

		fill_vector(vec1);
		fill_vector(vec2);

		vec2.erase(vec2.begin()+5, vec2.begin()+20);

		std::cout << "vec1 > vec2 " << ((vec1 > vec2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator <= \n";
	{
		NAMESPACE::vector<T1> vec1;
		NAMESPACE::vector<T1> vec2;

		fill_vector(vec1);
		fill_vector(vec2);

		vec2.erase(vec2.begin()+5, vec2.begin()+20);

		std::cout << "vec1 <= vec2 " << ((vec1 <= vec2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Operator >= \n";
	{
		NAMESPACE::vector<T1> vec1;
		NAMESPACE::vector<T1> vec2;

		fill_vector(vec1);
		fill_vector(vec2);

		vec2.erase(vec2.begin()+5, vec2.begin()+20);

		std::cout << "vec1 >= vec2 " << ((vec1 >= vec2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Swap \n";
	{
		NAMESPACE::vector<T1> vec1;
		NAMESPACE::vector<T1> vec2;

		fill_vector(vec1);
		swap(vec1, vec2);

		compare_vectors(vec1);
		iterate_vector(vec1);

		compare_vectors(vec2);
		iterate_vector(vec2);

		fill_vector(vec1);

		vec2.erase(vec2.begin()+5, vec2.end());
		
		swap(vec1, vec2);

		compare_vectors(vec1);
		iterate_vector(vec1);

		compare_vectors(vec2);
		iterate_vector(vec2);
	}

	

	std::cout << "\n";

	std::cout << "-------------------------" << "\n";
	std::cout << "|  ITERATOR OPERATIONS  |" << "\n";
	std::cout << "-------------------------" << "\n\n";



	std::cout << "Iterator - Operator + \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it1 = vec.begin();
		NAMESPACE::vector<T1>::iterator it2 = vec.begin();

		if ((&(*(it1 + 10)) != &(*(10 + it1))) || 
			(&(*(it1 + 20)) != &(*(20 + it1))) ||
			(&(*(it1 + 30)) != &(*(30 + it1))))
			std::cout << "KO\n";

		it1 = 7 + vec.begin();
		it2 = vec.begin() + 7;

		std::cout << "*it1 = " << *it1 << "; *it2 = " << *it2 << "\n";

		it1 = 10 + it1;
		it2 = it2 + 10;

		std::cout << "*it1 = " << *it1 << "; *it2 = " << *it2 << "\n";
	}

	std::cout << "Const Iterator - Operator + \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_iterator it1 = vec_op.begin();
		NAMESPACE::vector<T1>::const_iterator it2 = vec_op.begin();

		if ((&(*(it1 + 10)) != &(*(10 + it1))) || 
			(&(*(it1 + 20)) != &(*(20 + it1))) ||
			(&(*(it1 + 30)) != &(*(30 + it1))))
			std::cout << "KO\n";

		it1 = 7 + vec_op.begin();
		it2 = vec_op.begin() + 7;

		std::cout << "*it1 = " << *it1 << "; *it2 = " << *it2 << "\n";

		it1 = 10 + it1;
		it2 = it2 + 10;

		std::cout << "*it1 = " << *it1 << "; *it2 = " << *it2 << "\n";
	}

	std::cout << "Reverse Iterator - Operator + \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it1 = vec.rbegin();
		NAMESPACE::vector<T1>::reverse_iterator it2 = vec.rbegin();

		if ((&(*(it1 + 10)) != &(*(10 + it1))) || 
			(&(*(it1 + 20)) != &(*(20 + it1))) ||
			(&(*(it1 + 30)) != &(*(30 + it1))))
			std::cout << "KO\n";

		it1 = 7 + vec.rbegin();
		it2 = vec.rbegin() + 7;

		std::cout << "*it1 = " << *it1 << "; *it2 = " << *it2 << "\n";

		it1 = 10 + it1;
		it2 = it2 + 10;

		std::cout << "*it1 = " << *it1 << "; *it2 = " << *it2 << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator + \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it1 = vec_op.rbegin();
		NAMESPACE::vector<T1>::const_reverse_iterator it2 = vec_op.rbegin();

		if ((&(*(it1 + 10)) != &(*(10 + it1))) || 
			(&(*(it1 + 20)) != &(*(20 + it1))) ||
			(&(*(it1 + 30)) != &(*(30 + it1))))
			std::cout << "KO\n";

		it1 = 7 + vec_op.rbegin();
		it2 = vec_op.rbegin() + 7;

		std::cout << "*it1 = " << *it1 << "; *it2 = " << *it2 << "\n";

		it1 = 10 + it1;
		it2 = it2 + 10;

		std::cout << "*it1 = " << *it1 << "; *it2 = " << *it2 << "\n";
	}

	std::cout << "\n";

	std::cout << "Iterator - Operator - \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it = vec.end();

		it = it - 7;

		std::cout << "*it = " << *it << "\n";

		it = it - 7;

		std::cout << "*it = " << *it << "\n";

		it = it - 7;

		std::cout << "*it = " << *it << "\n";

		if (vec.end() - vec.begin() != (ptrdiff_t)vec.size())
			std::cout << "KO\n";
	}

	std::cout << "Const Iterator - Operator - \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_iterator it = vec_op.end();

		it = it - 7;

		std::cout << "*it = " << *it << "\n";

		it = it - 7;

		std::cout << "*it = " << *it << "\n";

		it = it - 7;

		std::cout << "*it = " << *it << "\n";

		if (vec.end() - vec.begin() != (ptrdiff_t)vec.size())
			std::cout << "KO\n";
	}

	std::cout << "Reverse Iterator - Operator - \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it = vec.rend();

		it = it - 7;

		std::cout << "*it = " << *it << "\n";

		it = it - 7;

		std::cout << "*it = " << *it << "\n";

		it = it - 7;

		std::cout << "*it = " << *it << "\n";

		if (vec.rend() - vec.rbegin() != (ptrdiff_t)vec.size())
			std::cout << "KO\n";
	}

	std::cout << "Const Reverse Iterator - Operator - \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it = vec_op.rend();

		it = it - 7;

		std::cout << "*it = " << *it << "\n";

		it = it - 7;

		std::cout << "*it = " << *it << "\n";

		it = it - 7;

		std::cout << "*it = " << *it << "\n";

		if (vec.rend() - vec.rbegin() != (ptrdiff_t)vec.size())
			std::cout << "KO\n";
	}

	std::cout << "\n";

	std::cout << "Iterator - Operator += \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it = vec.begin();

		for (int i = 0; i < 25; i += 5)
		{
			it += 5;
			std::cout << "*it = " << *it << "\n";
		}

		it = vec.begin();
		it += (vec.end() - (vec.begin() + 5));

		std::cout << "*it = " << *it << "\n";
	}

	std::cout << "Const Iterator - Operator += \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_iterator it = vec_op.begin();

		for (int i = 0; i < 25; i += 5)
		{
			it += 5;
			std::cout << "*it = " << *it << "\n";
		}

		it = vec_op.begin();
		it += (vec_op.end() - (vec_op.begin() + 5));

		std::cout << "*it = " << *it << "\n";
	}

	std::cout << "Reverse Iterator - Operator += \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it = vec.rbegin();

		for (int i = 0; i < 25; i += 5)
		{
			it += 5;
			std::cout << "*it = " << *it << "\n";
		}

		it = vec.rbegin();
		it += (vec.rend() - (vec.rbegin() + 5));

		std::cout << "*it = " << *it << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator += \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it = vec_op.rbegin();

		for (int i = 0; i < 25; i += 5)
		{
			it += 5;
			std::cout << "*it = " << *it << "\n";
		}

		it = vec_op.rbegin();
		it += (vec_op.rend() - (vec_op.rbegin() + 5));

		std::cout << "*it = " << *it << "\n";
	}

	std::cout << "\n";

	std::cout << "Iterator - Operator -= \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it = vec.end();

		for (int i = 0; i < 25; i += 5)
		{
			it -= 5;
			std::cout << "*it = " << *it << "\n";
		}

		it = vec.end();
		it -= (vec.end() - (vec.begin() + 5));

		std::cout << "*it = " << *it << "\n";
	}

	std::cout << "Const Iterator - Operator -= \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_iterator it = vec_op.end();

		for (int i = 0; i < 25; i += 5)
		{
			it -= 5;
			std::cout << "*it = " << *it << "\n";
		}

		it = vec_op.end();
		it -= (vec_op.end() - (vec_op.begin() + 5));

		std::cout << "*it = " << *it << "\n";
	}

	std::cout << "Reverse Iterator - Operator -= \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it = vec.rend();

		for (int i = 0; i < 25; i += 5)
		{
			it -= 5;
			std::cout << "*it = " << *it << "\n";
		}

		it = vec.rend();
		it -= (vec.rend() - (vec.rbegin() + 5));

		std::cout << "*it = " << *it << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator -= \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it = vec_op.rend();

		for (int i = 0; i < 25; i += 5)
		{
			it -= 5;
			std::cout << "*it = " << *it << "\n";
		}

		it = vec_op.rend();
		it -= (vec_op.rend() - (vec_op.rbegin() + 5));

		std::cout << "*it = " << *it << "\n";
	}

	std::cout << "\n";

	std::cout << "Iterator - Operator [] \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it = vec.begin();

		for (int i = 0; i < 100; i += 10)
			std::cout << "it[" << i << "] = " << it[i] << "\n";
	}

	std::cout << "Const Iterator - Operator [] \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_iterator it = vec_op.begin();

		for (int i = 0; i < 100; i += 10)
			std::cout << "it[" << i << "] = " << it[i] << "\n";
	}

	std::cout << "Reverse Iterator - Operator [] \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it = vec.rbegin();

		for (int i = 0; i < 100; i += 10)
			std::cout << "it[" << i << "] = " << it[i] << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator [] \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it = vec_op.rbegin();

		for (int i = 0; i < 100; i += 10)
			std::cout << "it[" << i << "] = " << it[i] << "\n";
	}

	std::cout << "\n";

	std::cout << "Iterator - Base \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it = vec.begin();

		for (; it != vec.end(); it += 10)
			std::cout << "*it.base() = " << *it.base() << "\n";
	}

	std::cout << "Const Iterator - Base \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_iterator it = vec_op.begin();

		for (; it != vec_op.end(); it += 10)
			std::cout << "*it.base() = " << *it.base() << "\n";
	}

	std::cout << "Reverse Iterator - Base \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it = vec.rbegin();

		it++;
		for (int i = 0; i < 100; it += 10, i += 10)
			std::cout << "*it.base() = " << *it.base() << "\n";
	}

	std::cout << "Const Reverse Iterator - Base \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it = vec_op.rbegin();

		it++;
		for (int i = 0; i < 100; it += 10, i += 10)
			std::cout << "*it.base() = " << *it.base() << "\n";
	}

	std::cout << "\n";

	std::cout << "Iterator - Operator == \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it = vec.begin();
		NAMESPACE::vector<T1>::iterator it2 = vec.begin();

		for (; it != vec.end(); it += 10, it2 += 10)
			std::cout << "it == it2 " << ((it == it2) ? "True" : "False") << "\n";
	}

	std::cout << "Const Iterator - Operator == \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_iterator it = vec_op.begin();
		NAMESPACE::vector<T1>::const_iterator it2 = vec_op.begin();

		for (; it != vec_op.end(); it += 10, it2 += 10)
			std::cout << "it == it2 " << ((it == it2) ? "True" : "False") << "\n";
	}

	std::cout << "Reverse Iterator - Operator == \n";
	{
		NAMESPACE::vector<T1> vec;
		
		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it = vec.rbegin();
		NAMESPACE::vector<T1>::reverse_iterator it2 = vec.rbegin();

		for (; it != vec.rend(); it += 10, it2 += 10)
			std::cout << "it == it2 " << ((it == it2) ? "True" : "False") << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator == \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it = vec_op.rbegin();
		NAMESPACE::vector<T1>::const_reverse_iterator it2 = vec_op.rbegin();

		for (; it != vec_op.rend(); it += 10, it2 += 10)
			std::cout << "it == it2 " << ((it == it2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Iterator - Operator != \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it = vec.begin();
		NAMESPACE::vector<T1>::iterator it2 = vec.begin();

		for (; it != vec.end(); it += 10, it2 += 10)
			std::cout << "it != it2 " << ((it != it2) ? "True" : "False") << "\n";
	}

	std::cout << "Const Iterator - Operator != \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_iterator it = vec_op.begin();
		NAMESPACE::vector<T1>::const_iterator it2 = vec_op.begin();

		for (; it != vec_op.end(); it += 10, it2 += 10)
			std::cout << "it != it2 " << ((it != it2) ? "True" : "False") << "\n";
	}

	std::cout << "Reverse Iterator - Operator != \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it = vec.rbegin();
		NAMESPACE::vector<T1>::reverse_iterator it2 = vec.rbegin();

		for (; it != vec.rend(); it += 10, it2 += 10)
			std::cout << "it != it2 " << ((it != it2) ? "True" : "False") << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator != \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it = vec_op.rbegin();
		NAMESPACE::vector<T1>::const_reverse_iterator it2 = vec_op.rbegin();

		for (; it != vec_op.rend(); it += 10, it2 += 10)
			std::cout << "it != it2 " << ((it != it2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Iterator - Operator < \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it = vec.begin() + 50;
		NAMESPACE::vector<T1>::iterator it2 = vec.begin();

		for (; it != vec.end(); it += 10, it2 += 10)
			std::cout << "it < it2 " << ((it < it2) ? "True" : "False") << "\n";
	}

	std::cout << "Const Iterator - Operator < \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_iterator it = vec_op.begin() + 50;
		NAMESPACE::vector<T1>::const_iterator it2 = vec_op.begin();

		for (; it != vec_op.end(); it += 10, it2 += 10)
			std::cout << "it < it2 " << ((it < it2) ? "True" : "False") << "\n";
	}

	std::cout << "Reverse Iterator - Operator < \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it = vec.rbegin() + 50;
		NAMESPACE::vector<T1>::reverse_iterator it2 = vec.rbegin();

		for (; it != vec.rend(); it += 10, it2 += 10)
			std::cout << "it < it2 " << ((it < it2) ? "True" : "False") << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator < \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it = vec_op.rbegin() + 50;
		NAMESPACE::vector<T1>::const_reverse_iterator it2 = vec_op.rbegin();

		for (; it != vec_op.rend(); it += 10, it2 += 10)
			std::cout << "it < it2 " << ((it < it2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Iterator - Operator > \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it = vec.begin() + 50;
		NAMESPACE::vector<T1>::iterator it2 = vec.begin();

		for (; it != vec.end(); it += 10, it2 += 10)
			std::cout << "it > it2 " << ((it > it2) ? "True" : "False") << "\n";
	}

	std::cout << "Const Iterator - Operator > \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_iterator it = vec_op.begin() + 50;
		NAMESPACE::vector<T1>::const_iterator it2 = vec_op.begin();

		for (; it != vec_op.end(); it += 10, it2 += 10)
			std::cout << "it > it2 " << ((it > it2) ? "True" : "False") << "\n";
	}

	std::cout << "Reverse Iterator - Operator > \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it = vec.rbegin() + 50;
		NAMESPACE::vector<T1>::reverse_iterator it2 = vec.rbegin();

		for (; it != vec.rend(); it += 10, it2 += 10)
			std::cout << "it > it2 " << ((it > it2) ? "True" : "False") << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator > \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it = vec_op.rbegin() + 50;
		NAMESPACE::vector<T1>::const_reverse_iterator it2 = vec_op.rbegin();

		for (; it != vec_op.rend(); it += 10, it2 += 10)
			std::cout << "it > it2 " << ((it > it2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Iterator - Operator <= \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it = vec.begin() + 50;
		NAMESPACE::vector<T1>::iterator it2 = vec.begin();

		for (; it != vec.end(); it += 10, it2 += 10)
			std::cout << "it <= it2 " << ((it <= it2) ? "True" : "False") << "\n";
	}

	std::cout << "Const Iterator - Operator <= \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_iterator it = vec_op.begin() + 50;
		NAMESPACE::vector<T1>::const_iterator it2 = vec_op.begin();

		for (; it != vec_op.end(); it += 10, it2 += 10)
			std::cout << "it <= it2 " << ((it <= it2) ? "True" : "False") << "\n";
	}

	std::cout << "Reverse Iterator - Operator <= \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it = vec.rbegin() + 50;
		NAMESPACE::vector<T1>::reverse_iterator it2 = vec.rbegin();

		for (; it != vec.rend(); it += 10, it2 += 10)
			std::cout << "it <= it2 " << ((it <= it2) ? "True" : "False") << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator <= \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it = vec_op.rbegin() + 50;
		NAMESPACE::vector<T1>::const_reverse_iterator it2 = vec_op.rbegin();

		for (; it != vec_op.rend(); it += 10, it2 += 10)
			std::cout << "it <= it2 " << ((it <= it2) ? "True" : "False") << "\n";
	}

	std::cout << "\n";

	std::cout << "Iterator - Operator >= \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::iterator it = vec.begin() + 50;
		NAMESPACE::vector<T1>::iterator it2 = vec.begin();

		for (; it != vec.end(); it += 10, it2 += 10)
			std::cout << "it >= it2 " << ((it >= it2) ? "True" : "False") << "\n";
	}

	std::cout << "Const Iterator - Operator >= \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_iterator it = vec_op.begin() + 50;
		NAMESPACE::vector<T1>::const_iterator it2 = vec_op.begin();

		for (; it != vec_op.end(); it += 10, it2 += 10)
			std::cout << "it >= it2 " << ((it >= it2) ? "True" : "False") << "\n";
	}

	std::cout << "Reverse Iterator - Operator >= \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		NAMESPACE::vector<T1>::reverse_iterator it = vec.rbegin() + 50;
		NAMESPACE::vector<T1>::reverse_iterator it2 = vec.rbegin();

		for (; it != vec.rend(); it += 10, it2 += 10)
			std::cout << "it >= it2 " << ((it >= it2) ? "True" : "False") << "\n";
	}

	std::cout << "Const Reverse Iterator - Operator >= \n";
	{
		NAMESPACE::vector<T1> vec;

		fill_vector(vec);

		const NAMESPACE::vector<T1> vec_op(vec);

		NAMESPACE::vector<T1>::const_reverse_iterator it = vec_op.rbegin() + 50;
		NAMESPACE::vector<T1>::const_reverse_iterator it2 = vec_op.rbegin();

		for (; it != vec_op.rend(); it += 10, it2 += 10)
			std::cout << "it >= it2 " << ((it >= it2) ? "True" : "False") << "\n";
	}

}
