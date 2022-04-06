/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:53:51 by gasselin          #+#    #+#             */
/*   Updated: 2022/04/06 11:54:29 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <iostream>
// #include <string>
// #include <deque>
// // #if 1 //CREATE A REAL STL EXAMPLE
// // 	#include <map>
// // 	#include <stack>
// // 	#include <vector>
// // 	namespace ft = std;
// // #else
// #include "map.hpp"
// #include "stack.hpp"
// #include "vector.hpp"
// // #endif

// #include <stdlib.h>

// #define MAX_RAM 4294967296
// #define BUFFER_SIZE 4096
// struct Buffer
// {
// 	int idx;
// 	char buff[BUFFER_SIZE];
// };


// #define COUNT (MAX_RAM / (int)sizeof(Buffer))

// template<typename T>
// class MutantStack : public ft::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename ft::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };

// int main(int argc, char** argv) {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	ft::vector<std::string> vector_str;
// 	ft::vector<int> vector_int;
// 	ft::stack<int> stack_int;
// 	ft::vector<Buffer> vector_buffer;
// 	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
// 	ft::map<int, int> map_int;

// 	// for (int i = 0; i < COUNT; i++)
// 	// {
// 	// 	vector_buffer.push_back(Buffer());
// 	// }

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer>().swap(vector_buffer);

// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}
	
// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(ft::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		ft::map<int, int> copy = map_int;
// 	}
// 	MutantStack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
// 	{
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;
// 	return (0);
// }

#include "vector.hpp"
#include "iterators.hpp"
#include "map.hpp"
#include <vector>
#include <iterator>
#include <cstring>

template <typename T>
void fill_vector(T &cont)
{
	for (int i = 0; i < 45; i++)
		cont.push_back(i + 1);
}

template <typename T>
void fill_vector2(T &cont)
{
	for (int i = 0; i < 10; i++)
		cont.push_back(i);
}

int main()
{
	// int range_array[] = {47, 152, -325, 9, 14444};

	// const std::string extra(6, 'b');
	// ft::vector<int> ft_vec;
	// ft::vector<int> ft_vec2;
	// std::vector<int> vec;
	// std::vector<int> vec2;
	// int myarray [] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// fill_vector(ft_vec);
	// fill_vector(ft_vec2);

	// fill_vector(vec);
	// fill_vector2(ft_vec);
	// std::vector<int>::iterator it = vec.begin();
	// vec.insert(vec.begin(), 50);

	// ft_vec.insert(vec.begin(), myarray, myarray+9)
	// vec.insert(it+10, 10, 50);
	// ft_vec.insert(it, 50);

	// for (int i = 0; i < 65; i++)
		// std::cout << vec[i] << "\n";

	// ft::vector<int>::reverse_iterator rit = ft_vec.rbegin();
	// for (; rit!= ft_vec.rend(); rit++)
    // 	std::cout << *rit << " ";
	// std::cout << "\n";
	// std::vector<int>::reverse_iterator rit2 = vec.rbegin();
	// for (; rit2!= vec.rend(); rit2++)
    // 	std::cout << *rit2 << " ";

	/* ERASE */
	// for (unsigned long i = 0; i < ft_vec.size(); i++)
	// 	std::cout << ft_vec[i] << " ";
	// std::cout << '\n';
 
    // ft_vec.erase(ft_vec.begin());

	// for (unsigned long i = 0; i < ft_vec.size(); i++)
	// 	std::cout << ft_vec[i] << " ";
	// std::cout << '\n';
 
    // ft_vec.erase(ft_vec.begin()+2, ft_vec.begin()+5);

	// for (unsigned long i = 0; i < ft_vec.size(); i++)
	// 	std::cout << ft_vec[i] << " ";
	// std::cout << '\n';
 
    // for (ft::vector<int>::iterator it = ft_vec.begin(); it != ft_vec.end(); ) {
    //     if (*it % 2 == 0) {
    //         it = ft_vec.erase(it);
    //     } else {
    //         ++it;
    //     }
    // }

	// for (unsigned long i = 0; i < ft_vec.size(); i++)
	// 	std::cout << ft_vec[i] << " ";
	// std::cout << '\n';
	/* --------------- */


	ft::map<int, int> map1;

	std::cout << map1.size() << "\n";


	// std::cout << vec.size() << " " << vec.max_size() << " " << vec.capacity() << "\n";
	return (0);
}