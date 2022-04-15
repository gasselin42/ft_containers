/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 09:39:43 by gasselin          #+#    #+#             */
/*   Updated: 2022/04/15 14:45:32 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

#include <map>
#include <utility>
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

void fill_ft_map(ft::map<int, std::string>& myMap)
{
	myMap.insert(ft::make_pair<int, std::string>(44, "root"));

	myMap.insert(ft::make_pair<int, std::string>(17, "left"));
	myMap.insert(ft::make_pair<int, std::string>(28, "left"));
	myMap.insert(ft::make_pair<int, std::string>(29, "left"));

	myMap.insert(ft::make_pair<int, std::string>(88, "right"));
	myMap.insert(ft::make_pair<int, std::string>(97, "right"));
	myMap.insert(ft::make_pair<int, std::string>(65, "right"));
	myMap.insert(ft::make_pair<int, std::string>(54, "right"));
	myMap.insert(ft::make_pair<int, std::string>(82, "right"));
	myMap.insert(ft::make_pair<int, std::string>(76, "right"));
	myMap.insert(ft::make_pair<int, std::string>(80, "right"));
	myMap.insert(ft::make_pair<int, std::string>(78, "right"));
}

void fill_std_map(std::map<int, std::string>& myMap)
{
	myMap.insert(std::make_pair<int, std::string>(44, "root"));

	myMap.insert(std::make_pair<int, std::string>(17, "left"));
	myMap.insert(std::make_pair<int, std::string>(28, "left"));
	myMap.insert(std::make_pair<int, std::string>(29, "left"));

	myMap.insert(std::make_pair<int, std::string>(88, "right"));
	myMap.insert(std::make_pair<int, std::string>(97, "right"));
	myMap.insert(std::make_pair<int, std::string>(65, "right"));
	myMap.insert(std::make_pair<int, std::string>(54, "right"));
	myMap.insert(std::make_pair<int, std::string>(82, "right"));
	myMap.insert(std::make_pair<int, std::string>(76, "right"));
	myMap.insert(std::make_pair<int, std::string>(80, "right"));
	myMap.insert(std::make_pair<int, std::string>(78, "right"));
}

template <class Ta, class Tb>
bool iterate_maps(std::map<Ta, Tb>& stl_map, ft::map<Ta, Tb>& ft_map)
{
	typename std::map<Ta, Tb>::iterator stl_it;
	typename ft::map<Ta, Tb>::iterator ft_it;

	stl_it = stl_map.begin();
	ft_it = ft_map.begin();

	while (stl_it != stl_map.end())
	{
		if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
			return (false);
		stl_it++;
		ft_it++;
	}
	if (ft_it != ft_map.end())
		return (false);
	return (true);
}

template <class Ta, class Tb>
bool compare_maps(std::map<Ta, Tb>& stl_map, ft::map<Ta, Tb>& ft_map)
{
	if ((stl_map.empty() != ft_map.empty()) ||
		(stl_map.size() != ft_map.size()) ||
		(stl_map.max_size() != ft_map.max_size()))
		return (false);

	return (true);
}

template <class Ta, class Tb>
bool test_empty_map_iterators(ft::map<Ta, Tb>& ft_map)
{
	typename ft::map<Ta, Tb>::iterator ft_it1;
	typename ft::map<Ta, Tb>::iterator ft_it2;

	ft_it1 = ft_map.begin();
	ft_it2 = ft_map.end();

	if (&(*ft_it1) != &(*ft_it2))
		return (false);	

	return (true);
}

void map_tests(void)
{
	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|      CONSTRUCTORS     |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Default constructor " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map)
			|| !test_empty_map_iterators(ft_map))
			throw ko;
		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Explicit constructor " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map)
			|| !test_empty_map_iterators(ft_map))
			throw ko;

		std::map<int, std::string>::key_compare stl_key = stl_map.key_comp();
		ft::map<int, std::string>::key_compare ft_key = ft_map.key_comp();

		std::map<int, std::string> stl_map2(stl_key);
		ft::map<int, std::string> ft_map2(ft_key);

		if (!compare_maps(stl_map2, ft_map2) || !iterate_maps(stl_map2, ft_map2)
			|| !test_empty_map_iterators(ft_map2))
			throw ko;
		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Range constructor " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		std::map<int, std::string> stl_map_range(stl_map.begin(), stl_map.end());
		ft::map<int, std::string> ft_map_range(ft_map.begin(), ft_map.end());

		if (!compare_maps(stl_map_range, ft_map_range) || !iterate_maps(stl_map_range, ft_map_range))
			throw ko;
		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Copy constructor " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		std::map<int, std::string> stl_map_cpy(stl_map);
		ft::map<int, std::string> ft_map_cpy(ft_map);

		if (compare_maps(stl_map_cpy, ft_map_cpy))
			std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Assignment operator " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		std::map<int, std::string> stl_map_assign = stl_map;
		ft::map<int, std::string> ft_map_assign = ft_map;

		if (compare_maps(stl_map_assign, ft_map_assign))
			std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       ITERATORS       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";



	std::cout << BLUE << "Begin " << NC;
	try {
		bool check = true;
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		std::map<int, std::string>::iterator stl_it = stl_map.begin();
		ft::map<int, std::string>::iterator ft_it = ft_map.begin();

		while (stl_it != stl_map.end())
		{
			if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
				throw ko;
			stl_it++;
			ft_it++;
		}
		if (ft_it != ft_map.end())
			throw ko;
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Const begin " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		const std::map<int, std::string> stl_map_begin(stl_map);
		const ft::map<int, std::string> ft_map_begin(ft_map);

		std::map<int, std::string>::const_iterator stl_it = stl_map_begin.begin();
		ft::map<int, std::string>::const_iterator ft_it = ft_map_begin.begin();

		while (stl_it != stl_map.end())
		{
			if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
				throw ko;
			stl_it++;
			ft_it++;
		}
		if (ft_it != ft_map_begin.end())
			throw ko;
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "End " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		std::map<int, std::string>::iterator stl_it = stl_map.end();
		ft::map<int, std::string>::iterator ft_it = ft_map.end();

		while (stl_it != stl_map.end())
		{
			if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
				throw ko;
			stl_it++;
			ft_it++;
		}
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << BLUE << "Const end " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		fill_std_map(stl_map);
		fill_ft_map(ft_map);

		if (!compare_maps(stl_map, ft_map) || !iterate_maps(stl_map, ft_map))
			throw ko;

		const std::map<int, std::string> stl_map_begin(stl_map);
		const ft::map<int, std::string> ft_map_begin(ft_map);

		std::map<int, std::string>::const_iterator stl_it = stl_map_begin.begin();
		ft::map<int, std::string>::const_iterator ft_it = ft_map_begin.begin();

		while (stl_it != stl_map.end())
		{
			if ((*stl_it).first != (*ft_it).first || (*stl_it).second != (*ft_it).second)
				throw ko;
			stl_it++;
			ft_it++;
		}
		if (ft_it != ft_map_begin.end())
			throw ko;
		std::cout << BGRN << "PASSED!" << NC << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }



	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|        CAPACITY       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";
	
	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|     ELEMENT ACCESS    |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";

	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       MODIFIERS       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";

	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       OBSERVERS       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";

	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       OPERATIONS      |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";

	std::cout << "\n";

	std::cout << BRED << "-------------------------" << NC << "\n";
	std::cout << BRED << "|       ALLOCATOR       |" << NC << "\n";
	std::cout << BRED << "-------------------------" << NC << "\n\n";

	std::cout << BLUE << "Get allocator " << NC;
	try {
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		if (stl_map.get_allocator() != ft_map.get_allocator())
			throw ko;
		std::cout << PASSED << "\n";
	} catch(std::exception& e)
		{ std::cout << e.what() << "\n"; }
}